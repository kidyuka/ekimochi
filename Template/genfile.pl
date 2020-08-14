#!/usr/bin/perl

use 5.016;
use warnings;
use autodie;

if(@ARGV < 2) {
    die "genfile <template file> <out file> -Define1 Value1 ...\n";
}

open my $template, "< $ARGV[0]"
    or die "cannot open $ARGV[0]";

my $content = do { local $/; <$template> };
close $template;

open my $outfile, "> $ARGV[1]"
    or die "cannot open $ARGV[1]";

my %var;
for(my $idx = 2; $idx < @ARGV; $idx += 2) {
    $ARGV[$idx] =~ s/^-//;
    $var{$ARGV[$idx]} = $ARGV[$idx + 1];
}

my $prev = 0;
while($content =~ m/%\{([^%]*(?:%[^}][^%]*)*)%\}/g) {
    my $sta = $-[0];
    my $end = $+[0];
    my $script = $1;

    print $outfile substr($content, $prev, $sta - $prev);
    my $result = eval($script);
    if($@) {
        print "error: $@\n";
    } else {
        print $outfile $result;
    }
    $prev = $end;
}
print $outfile substr($content, $prev);

close $outfile;