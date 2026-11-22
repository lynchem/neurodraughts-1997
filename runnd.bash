#!/usr/bin/env bash
# Run the cloning tournament from the 1997 report: 100 matches, each of
# ten training games and two test games. The networks it saves go in run/,
# and the learner is also saved as run/learner.ndnet, a file the website
# at www.neurodraughts.com can import and play.
set -e
cd "$(dirname "$0")"
make -s nd
mkdir -p run
cd run
../nd ../test.crt ../test.prm ../TEST.BRD ../OPP1.FTR null 10 100 | tee log.txt
clones=$(grep -c '\*\*\*Clone' log.txt || true)
if grep -q '^NumInputs:[[:space:]]*-1' ../test.crt; then enc=binary; else enc=samuel; fi
python3 ../tools/tondnet.py Final1.net ../OPP1.FTR $enc learner.ndnet "1997 learner" "$clones"
echo
echo "To play the learner, import run/learner.ndnet in the Arena at"
echo "https://www.neurodraughts.com."
