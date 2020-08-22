#!/usr/bin/perl

use 5.016;
use warnings;
use autodie;
use POSIX qw(floor ceil);
use File::Basename;

if(@ARGV < 1) {
    die "$0 <binary_log_file>\n";
}

my $logcfg = dirname($0) . "/UTIL/cfg/logger_cfg.pl";

# コンフィグファイルから読み出し
open my $file, '<', $logcfg
    or die "cat not open config file.";
my $src = do { local $/;  <$file>; };
close $file;

my $define = eval($src);
if($@) {
    die "logコンフィグファイルが解析できない:\n$@\n";
}

my $filename = basename($ARGV[0], ('.bin'));
my $target = $define->{$filename};
unless($target) {
    die "コンフィグが見つけられない\n";
}

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
open my $log, '<', $ARGV[0]
    or die "cat not open config file.";
binmode($log);

# 最初の4byteにデータ長が含まれる
my ($log_size, $log_data);
sysread $log, $log_size, 4;
$log_size = unpack("L", $log_size);

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
