#!/usr/bin/perl -w

# /******************************************************************************/
# /*                                                                            */
# /*   This file is part of SuperShortReversals.                                */
# /*                                                                            */
# /*   SuperShortReversals is free software: you can redistribute it and/or     */
# /*   modify it under the terms of the GNU General Public License as published */
# /*   by the Free Software Foundation, either version 2 of the License, or     */
# /*   any later version.                                                       */
# /*                                                                            */
# /*   SuperShortReversals is distributed in the hope that it will be useful,   */
# /*   but WITHOUT ANY WARRANTY; without even the implied warranty of           */
# /*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
# /*   GNU General Public License for more details.                             */
# /*                                                                            */
# /*   You should have received a copy of the GNU General Public License        */
# /*   along with SuperShortReversals.                                          */
# /*   If not, see <http://www.gnu.org/licenses/>.                              */
# /*                                                                            */
# /******************************************************************************/

use strict;

my ($file) = @ARGV;
if (! defined $file) {
  print "perl createShufflingMatrix.pl <permutations>\n\n";
  print "ERROR: Missing permutations file.\n\n";
  exit 1;
}

###############################################################################
my @permutations;
my %idToCode;

###############################################################################
my $id = 0;
open(IN, $file);
while (my $line = <IN>) {
  chomp($line);
  my ($code, @permutation) = split(",", $line);
  push(@permutations, join(",", @permutation));
  if (length($code) >= 10) {
    $code = substr($code, 0, 10);
  } else {
    while (length($code) < 10) {
      $code = "${code} ";
    }
  }
  $idToCode{$id} = $code;
  ++$id;
}
close(IN);

###############################################################################
my $nPermutations = @permutations;
print "     ${nPermutations}\n";
for (my $i = 0; $i < $nPermutations; ++$i) {
  my $code = $idToCode{$i};
  my @distances = getDistances($i, $nPermutations);
  print join("  ", ($code, @distances))."\n";
}

###############################################################################
sub getDistances {
  my ($baseId, $nPermutations) = @_;
  my @toReturn;
  for (my $i = 0; $i < $nPermutations; ++$i) {
    my $correctedPermutation = correctPermutation($permutations[$baseId], $permutations[$i]);
    my $cmd = "shuffling_distance ${correctedPermutation} | grep Distance | cut -f2 -d : | tr -d ' '";
    my $distance = `${cmd}`;
    chomp($distance);
    push(@toReturn, sprintf("%05d", $distance));
  }
  return @toReturn;
}

###############################################################################
sub correctPermutation {
  my ($iotaString, $piString) = @_;
  my @iota = split(",", $iotaString);
  my @pi   = split(",", $piString);

  my %map;
  my $permutationSize = @iota;
  for (my $i = 1; $i <= $permutationSize; ++$i) {
    my $e = $iota[$i - 1];
    $map{abs($e)} = $i;
  }

  my @corrected;
  foreach my $e (@pi) {
    push(@corrected, $map{abs($e)});
  }

  return join(",", @corrected);
}
