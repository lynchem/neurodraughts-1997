#!/usr/bin/env bash
# Run the cloning tournament from the 1997 report: 100 matches, each of
# ten training games and two test games. The networks it saves go in run/.
set -e
cd "$(dirname "$0")"
make -s nd
mkdir -p run
cd run
../nd ../test.crt ../test.prm ../TEST.BRD ../OPP1.FTR null 10 100
