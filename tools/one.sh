#!/usr/bin/env bash
# one.sh SEED ENCODER DIR: run the tournament from the report from one seed,
# then score the learner against the June 1997 network and against random
# play. Called by measure.sh.
set -e
seed=$1; enc=$2; dir=$3; w=$dir/s$seed
here=$(cd "$(dirname "$0")" && pwd); repo=$(dirname "$here")
rm -rf "$w"; mkdir -p "$w"; cd "$w"
sed "s/^NetworkSeed:.*/NetworkSeed:    $seed/" "$repo/test.crt" > crt
if [ "$enc" = binary ]; then sed -i "s/^NumInputs:.*/NumInputs:      -1/" crt; fi
"$dir/nd" crt "$repo/test.prm" "$repo/TEST.BRD" "$repo/OPP1.FTR" null 10 100 > log.txt || true
clones=$(grep -c '\*\*\*Clone' log.txt || true)
python3 "$here/tondnet.py" Final1.net "$repo/OPP1.FTR" "$enc" final.ndnet "seed $seed"
vs1997=$("$ND" fight final.ndnet 1997 --games 400 | tail -1)
random=$("$ND" fight final.ndnet random --games 200 | tail -1 | grep -o '([0-9]*%)' | tr -d '()%')
echo "$seed clones=$clones random=$random $vs1997"
