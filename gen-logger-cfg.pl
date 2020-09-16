#!/usr/bin/perl

use 5.016;
use warnings;
use autodie;
use POSIX qw(floor ceil);
use File::Basename;

############## コンフィグ項目##############
# マップ先メモリの先頭アドレスを設定する
my $mmap_address = 0x30000000;
my $mmap_maxsize = 0x10000000;
my $logdir = "log";
my $page_size = 8 * 1024;
#########################################
my $mmap_maxaddr = $mmap_address + $mmap_maxsize;

if(@ARGV < 1) {
    die "コンフィグファイルが指定されていない";
}

my %define;
foreach my $item (@ARGV) {
    # コンフィグファイルから読み出し
    open my $file, '<', $item
        or die "cat not open config file.";
    my $src = do { local $/;  <$file>; };
    close $file;

    my $def = eval($src);
    if($@) {
        die "logコンフィグファイルが解析できない:$@\n";
    }
    @define{ keys %$def } = values %$def;
}

#以降の処理は、スクリプトファイルがあるフォルダを基準に行う
chdir(dirname($0));

# 使用可能な型の情報
my %type_list = ("int8_t" => 1, "uint8_t" => 1, "int16_t" => 2,
    "uint16_t" => 2, "int32_t" => 4, "uint32_t" => 4, "int64_t" => 8,
    "uint64_t" => 8,"float" => 4, "double" => 8);

my $template_binary_class_declear = <<'EOS';
class _$key : public BinaryLogger {
public:
    _$key(uint32_t addr) : BinaryLogger(\"$key\", addr, $size) {}
    bool write($arguments);
};

EOS

my $template_binary_class_implement = <<'EOS';
bool _${key}::write($arguments) {
    bool ret;
$implement
    return ret;
}

EOS

open my $c_file, "> UTIL/cfg/logger_cfg.cpp"
    or die "cat not open file for writing.";

open my $h_file, "> UTIL/cfg/logger_cfg.inc"
    or die "cat not open file for writing.";

open my $mmap_file, "> memory_mmap.txt"
    or die "cat not open file for writing.";

open my $init_file, "> init_mmap.sh"
    or die "cat not open file for writing.";

print $mmap_file "ROM, 0x00000000, 512
RAM, 0x00200000, 512
RAM, 0x05FF7000, 10240
RAM, 0x07FF7000, 10240
";

print $init_file "mkdir -p log/\n";

print  $c_file "#ifdef MEMMAP_LOG\n";
print $c_file qq(#include "Logger.h"\n\n);

# 各定義を読み出して出力する。
while(my ($key, $def) = each(%define)) {
    if($def->{type} eq "text") {
        gen_text_log_define($key, $def);
    } elsif($def->{type} eq "binary") {
        gen_binary_log_define($key, $def);
    } else {
        die "$key の定義で、unknown 'type'";
    }
}

print  $c_file "#endif //MEMMAP_LOG\n";

close($c_file);
close($h_file);
close($mmap_file);
close($init_file);

sub alloc_memory {
    my $size = shift;
    my $ret = $mmap_address;
    $mmap_address += $size;
    if($mmap_address >= $mmap_maxaddr) {
        die "マップ先メモリがコンフィグで指定した最大値を超えた";
    }
    return $ret;
}

sub gen_text_log_define {
    my ($key, $def) = @_;

    my $count = POSIX::ceil($def->{size} / ($page_size));
    my $size  = $count * ($page_size);
    my $addr  = alloc_memory($size);

    print  $h_file "extern TextLogger $key;\n";
    printf $c_file "TextLogger $key(\"$key\", 0x%x, 0x%x);\n\n", $addr, $size;
    printf $mmap_file "MMAP, 0x%x, $logdir/$key.bin\n", $addr;
    printf $init_file "dd if=/dev/zero of=log/$key.bin bs=$page_size count=$count\n";
}

sub gen_binary_log_define {
    my ($key, $def) = @_;

    my $size = check_binary_log_define($def->{data}) * $def->{size} + 4;
    my $count = POSIX::ceil($size / ($page_size));
    $size  = $count * ($page_size);
    my $addr  = alloc_memory($size);

    my $list = $def->{data};
    my $arguments = "";
    my $implement = "";
    for(my $i = 0; $i < @$list; $i += 2) {
        my $sym = $list->[$i];
        my $type = $list->[$i + 1];
        if($i != 0) {
            $arguments .= ", ";
            $implement .= "\n";
        }
        $arguments .= "$type $sym";
        $implement .= "\tret = this->_write((const void*)&$sym, sizeof($type));";
    }

    print  $h_file eval(qq("$template_binary_class_declear"));
    if($@) {
        die $@;
    }
    print  $h_file "extern _$key $key;\n";

    printf $mmap_file "MMAP, 0x%x, $logdir/$key.bin\n", $addr;
    printf $init_file "dd if=/dev/zero of=log/$key.bin bs=$page_size count=$count\n";

    print  $c_file eval(qq("$template_binary_class_implement"));
    if($@) {
        die $@;
    }
    printf $c_file "_$key $key(0x%x);\n\n", $addr;

}

sub check_binary_log_define {
    my ($define) = @_;
    my $sum = 0;
    for(my $i = 0; $i < @$define; $i += 2) {
        my $type = $define->[$i + 1];
        if(my $size = $type_list{$type}) {
            $sum += $size;
        } else {
            die "$type は使用できないです";
        }
    }
    return $sum;
}