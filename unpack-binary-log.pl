#!/usr/bin/perl

use 5.016;
use warnings;
use autodie;
use POSIX qw(floor ceil);
use File::Basename;

if(@ARGV < 1) {
    die "$0 <binary_log_file>\n";
}

my $logname = shift @ARGV;

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

my $target = $define{$logname};
unless($target) {
    die "コンフィグが見つけられない\n";
}

if($target->{type} eq "text") {
    print_text_log($target, $logname);
} elsif($target->{type} eq "binary") {
    print_binary_log($target, $logname);
}

sub print_text_log {
    my ($target, $logname) = @_;

    # 対象のログファイルからデータを読み出す
    open my $log, '<', "log/${logname}.bin"
        or die "cat not open config file.";

    while(<$log>) {
        if($log =~ m/(.)\0/) {
            print "$1\n";
            last;
        } else {
            print $_;
        }
    }

    close($log);
}

sub print_binary_log {
    my ($target, $logname) = @_;

    my %type_list = ("int8_t" => "c", "uint8_t" => "C", "int16_t" => "s",
        "uint16_t" => "S", "int32_t" => "l", "uint32_t" => "L", "int64_t" => "q",
        "uint64_t" => "Q", "float" => "f", "double" => "d");

    my $list = $target->{data};
    my $pattern = "";
    my $filed_num = @$list / 2;
    for(my $i = 0; $i < @$list; $i += 2) {
        my $sym = $list->[$i];
        my $type = $list->[$i + 1];

        unless($type_list{$type}) {
            die "定義されていない型：$type";
        }
        print "$sym,";

        $pattern .= $type_list{$type};
    }
    $pattern = "($pattern)*";

    # 対象のログファイルからデータを読み出す
    open my $log, '<', "log/${logname}.bin"
        or die "cat not open config file.";
    binmode($log);

    # 最初の4byteにデータ長が含まれる
    my ($log_size, $log_data);
    sysread $log, $log_data, 4;
    $log_size = unpack("L", $log_data);

    sysread $log, $log_data, $log_size;
    close $log;

    my @items = unpack($pattern, $log_data);
    for(my $i = 0; $i < @items; $i++) {
        if($i % $filed_num == 0) {
            print "\n", $items[$i]; 
        } else {
            print ",", $items[$i];
        }
    }
}
