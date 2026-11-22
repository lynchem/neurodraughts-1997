#!/usr/bin/env bash
# measure.sh ENCODER [DIR]
#
# Builds nd, runs the tournament from the report (1,000 training games)
# from seeds 1 to 20, and scores each learner
# with the 2026 engine: 400 games against the network shipped in June 1997
# and 200 against random play, both sides looking three plies ahead under
# the real rules, games starting with four random plies.
#
# ENCODER is how the 2026 engine should read the networks: legacy before
# the features were corrected, samuel after, binary for the raw board.
# Needs the nd program from the 2026 rebuild in $ND (default: nd on the PATH).
set -e
enc=$1; dir=${2:-$(mktemp -d)}
here=$(cd "$(dirname "$0")" && pwd); repo=$(dirname "$here")
export ND=${ND:-nd}
mkdir -p "$dir"; make -s -C "$repo" nd; cp "$repo/nd" "$dir/nd"
seq 1 20 | xargs -P "$(nproc)" -I{} bash "$here/one.sh" {} "$enc" "$dir" > "$dir/results.txt"
sort -n "$dir/results.txt" | sed 's/ average.*//'
python3 - "$dir/results.txt" <<'PY'
import re, sys, statistics as st
vs, rnd = [], []
for line in open(sys.argv[1]):
    seed, clones, r, w, d, l = re.search(r'^(\S+) clones=(\d+) random=(\d+) .*\+(\d+) =(\d+) -(\d+)', line).groups()
    score = (int(w) + int(d) / 2) / 4
    vs.append(score); rnd.append(int(r))
print(f"seeds 1 to 20: {st.mean(vs):.1f} ± {st.stdev(vs) / len(vs) ** .5:.1f}% against 1997 (from {min(vs):.1f} to {max(vs):.1f}),"
      f" {st.mean(rnd):.1f}% against random, {sum(x < 50 for x in rnd)} of 20 losing to random")
PY
