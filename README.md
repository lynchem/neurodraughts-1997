# NeuroDraughts, 1997

NeuroDraughts was my final-year project at the University of Limerick in
1997: a program that learns to play draughts by temporal difference learning.
A learner network plays against a clone of itself, the champion. When the
learner beats the champion convincingly, it is cloned to become the new
champion, and training carries on.

This repository is the program as I handed it in, then one commit for each
mistake fixed in 2026. Each commit message says what was wrong, how it was
found and what fixing it changed. Most of the fixes made no measurable
difference. The two that did were not bug fixes: one changes the training
method, and the other sets the momentum term in the settings file to zero.

A version you can play and train in a browser, and the story of the project,
are at [www.neurodraughts.com](https://www.neurodraughts.com).

## The commits

| Commit | Against the June 1997 network | Runs losing to random play |
|---|---|---|
| NeuroDraughts v1.01, built with today's g++ | 22.9 ± 4.9% | 10 of 20 |
| Captures are forced at every move | 14.7 ± 3.7% | 14 of 20 |
| A multiple capture may take any route | 18.8 ± 4.5% | 12 of 20 |
| Compute the features as the report defines them | 29.3 ± 4.1% | 4 of 20 |
| Give the hidden layer the right gradient | 32.8 ± 5.7% | 7 of 20 |
| Decay the eligibility traces by gamma times lambda | 30.1 ± 4.7% | 6 of 20 |
| Learn from both players' positions | 48.9 ± 4.5% | 2 of 20 |
| Switch off the momentum term | 70.4 ± 1.8% | 0 of 20 |
| Put back the alpha-beta pruning | the same, twice as fast | |
| Let the raw-board encodings see the whole board, then train on the raw board | 49.5 ± 1.9% | 0 of 20 |

The score is for a learner after the tournament from the report: 100 matches
of ten training games, 1,000 games in all. It plays 400 games against the
network shipped in June 1997, both sides looking three plies ahead under the
real rules, and 200 against a player that picks its moves at random. Each step
is the average of 20 runs from different seeds, with the standard error after
the ±. A single run of 1,000 games says very little: until the learner learned
from both sides with momentum off, runs that differed only in their seed
scored anywhere from under 5% to over 60%. Each commit message has the
details.

Learning from both sides and switching off momentum depend on each other.
Switching off momentum while the learner learned only from its own positions
made no measurable difference (30.1% to 34.1%). Learning from both sides with
momentum still on reached 48.9%, and with both changes 70.4%. Why they
interact this way is not yet understood.

## Building and running

You need g++, make and Python 3.

```bash
./runnd.bash
```

`runnd.bash` builds the program, runs the tournament from the report and
saves the networks in `run/`. It takes about nine seconds.

The last file it writes is `run/learner.ndnet`, the learner in the format of
the engine behind [www.neurodraughts.com](https://www.neurodraughts.com).
Import it in the Arena there and you can play it yourself, or set it against
the June 1997 network. Over 400 games, learners from seeds 1 to 20 scored
between 54% and 81% against it.

For a different run, change `NetworkSeed` in `test.crt`. The one there,
051201, is Arthur Samuel's birthday. To train on the raw board instead of the
features, set `NumInputs` to -1.

The numbers in the table come from `tools/measure.sh`, which plays the
learners with a command-line build of the site's engine. That build isn't
published, so the script is here to show how the measuring was done rather
than for running. The Arena gives a rougher version of the same comparison,
40 games at a time.

## What is here

| File | What it is |
|---|---|
| `nd.cpp` | The tournament runner, the only program built. |
| `dgame.cpp` | A game between two networks, with TD training. |
| `player.cpp` | The search that picks a move. |
| `board.cpp` | The board, moves and captures. |
| `features.cpp` | The thirteen board features, after Samuel. |
| `dirnet.cpp` | From a board to the network's inputs. |
| `evalnet.cpp` | The network and its training. |
| `runnd.bash` | Builds `nd`, runs the tournament and saves the learner for the website. |
| `tools/` | The scripts that measured each step, and `tondnet.py`, which converts a network for the website. |
| `test.crt`, `test.prm`, `TEST.BRD` | The network to create, the training settings and the starting board for the tournament in the report. |
| `OPP1.NET`, `OPP1.FTR` | The network shipped in June 1997, and its features. |
| `neuro.cpp`, `fight.cpp`, `train.cpp`, `xtrain.cpp`, `convpdn.cpp`, ... | The Windows programs: play against a network, pit two against each other, train from expert games. Kept as they were, and not built. |

## Licence

MIT: see [LICENSE](LICENSE). The 1997 source headers carry a note letting
one person modify the code as long as it was not distributed. The licence
replaces it.
