#!/usr/bin/perl

use 5.016;
use warnings;
use autodie;
use POSIX qw(floor ceil);

############## コンフィグ項目##############
# マップ先メモリの先頭アドレスを設定する
my $mmap_address = 0x30000000;
my $mmap_maxsize = 0x10000000;
#########################################
my $mmap_maxaddr = $mmap_address + $mmap_maxsize;

# コンフィグファイルから読み出し
open my $file, '<', 'UTIL/cfg/logger_cfg.pl'
    or die "cat not open config file.";
my $src = do { local $/;  <$file>; };
close $file;

my $define = eval($src);
if($@) {
    print "$@\n";
    exit 1;
}

open my $c_file, "> UTIL/cfg/logger_cfg.cpp"
    or die "cat not open file for writing.";

open my $h_file, "> UTIL/cfg/logger_cfg.h"
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

print $c_file qq(#include "Logger.h"\n);

# 各定義を読み出して出力する。
while(my ($key, $def) = each(%$define)) {
    if($def->{type} eq "text") {
        gen_text_log_define($key, $def);
    } elsif($def->{type} eq "binary") {
        gen_binary_log_define($key, $def);
    } else {
        die "$key の定義で、unknown 'type'";
    }
}

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

    my $count = POSIX::ceil($def->{size} / (4 * 1024));
    my $size  = $count * (4 * 1024);
    my $addr  = alloc_memory($size);

    print  $h_file "extern TextLogger $key;\n";
    printf $c_file "TextLogger $key(0x%x, 0x%x);\n", $addr, $size;
    printf $mmap_file "MMAP, 0x%x, $key.bin\n", $addr;
    printf $init_file "dd if=/dev/zero of=log/$key.bin bs=4K count=$count\n";
}

sub gen_binary_log_define {
    my ($key, $def) = @_;
}
