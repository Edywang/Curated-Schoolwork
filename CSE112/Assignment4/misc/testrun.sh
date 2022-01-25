#!/bin/sh
# $Id: testrun.sh,v 1.3 2020-11-26 18:30:24-08 - - $

function testrun {
   echo ================================
   run.perl $*
}

cid -si $0 run.perl
testrun
testrun error 0
testrun error 1
testrun error -1
testrun abort
testrun segfault
testrun zerodivide
testrun foo bar baz
