"""Convert a network saved by nd into the format of the 2026 engine, so that
the 2026 engine can play it.

usage: python3 tondnet.py NET FTR ENCODER OUT [NAME [GENERATION]]

ENCODER says how the network sees the board:
  legacy   the 1997 features, computed as the 1997 code computed them
  samuel   the 1997 features, computed as the report defines them
  binary   the raw board, three inputs per square
"""
import sys

net, ftr, enc, out = sys.argv[1:5]
name = sys.argv[5] if len(sys.argv) > 5 else net
generation = int(sys.argv[6]) if len(sys.argv) > 6 else 0
order = ["PieceAdvantage", "PieceDisadvatange", "PieceThreat", "PieceTake",
         "Advancement", "DoubleDiagonal", "BackrowBridge", "CentreControl",
         "XCentreControl", "TotalMobility", "Exposure", "KingCentreControl",
         "DiagonalMoment"]
bits = dict.fromkeys(order, 0)
t = open(ftr).read().split()
for k, v in zip(t[0::2], t[1::2]):
    if k in bits:
        bits[k] = int(v)

tok = open(net).read().split('\n', 1)[1].split()
ni, nh, direct = int(tok[0]), int(tok[1]), int(tok[2])
w = [float(x) for x in tok[3:]]
if enc == 'binary':
    assert ni == 96, ni
    encoder = 'binary'
else:
    assert ni == sum(b for b in bits.values() if b > 0), (ni, bits)
    encoder = enc + ' ' + ' '.join(str(bits[k]) for k in order)
assert direct == 1

# nd: input-to-hidden by input (the last row is the bias), hidden-to-output
# (the last is the bias), input-to-output (the last is the bias).
w1 = w[:(ni + 1) * nh]
w2 = w[(ni + 1) * nh:(ni + 1) * nh + nh + 1]
w3 = w[(ni + 1) * nh + nh + 1:]
assert len(w3) == ni + 1, len(w3)
# 2026: input-to-hidden, hidden biases, hidden-to-output, output bias,
# input-to-output. The two output biases add up to one.
p = w1[:ni * nh] + w1[ni * nh:] + w2[:nh] + [w2[nh] + w3[ni]] + w3[:ni]
with open(out, 'w') as f:
    f.write(f"NDNET 1\nname {name}\nencoder {encoder}\nhidden {nh}\n"
            f"activation tanh\ndirect 1\ngeneration {generation}\ngames 0\nweights {len(p)}\n")
    f.write(' '.join(repr(x) for x in p) + '\n')
