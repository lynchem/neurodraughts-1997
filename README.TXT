           ************ NeuroDraughts v1.0 **************

                       (c) Mark Lynch 1997


Please do whatever you want with these programs. I'm not responsible for
any damage etc... <usual crap>.

If you have any comments or suggestions please get in touch
For a better description of this project, please see finalreport.ps. 

What is NeuroDraughts?

NeuroDraughts is a collection of programs allowing you to construct a neural
network evaluation function which can be used to evaluate positions in
draughts. It uses Temporal Difference (TD) learning to train a fully
connected network.

Several programs are provided to facilitate the creation of the Evaluation
networks... namely:
Xtrain -    Trains using expert games.
ConvtoPDN - Convert PDN games to Training Data.
ND -        Play a Cloning Tournament.
Fight -     Pit two differering networks against one another.
Neuro -     Play against a network.


A number of files play an important role in NeuroDraughts.

Board File - starting boards. sample in test.brd
Parameter File - parameters.  sample in test.prm
Creation File - creation parameters - sample in test.crt

Known Bugs
Do anything it's not expecting and god help you ;)

Plans
Dyanamic feature allocation - specify which to use, how many bits to allocate.
Rewrite some parts, make it more efficient.


I'm to lazy to write any more, please see finalps.ps.
