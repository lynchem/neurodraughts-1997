#
# Borland C++ IDE generated makefile
# Generated 30/05/97 at 12:11:20 
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCC32   = Bcc32 +BccW32.cfg 
TLINK32 = TLink32
TLIB    = TLib
BRC32   = Brc32
TASM32  = Tasm32
#
# IDE macros
#


#
# Options
#
IDE_LinkFLAGS32 =  -LC:\BC5\LIB
IDE_ResFLAGS32 = 
LinkerLocalOptsAtW32_neurodexe =  -Tpe -aa -V4.0 -c
ResLocalOptsAtW32_neurodexe = 
BLocalOptsAtW32_neurodexe = 
CompInheritOptsAt_neurodexe = -IC:\BC5\INCLUDE;C:\BC5\INCLUDE\CLASSLIB -DSTRICT;_OWLPCH;
LinkerInheritOptsAt_neurodexe = -x
LinkerOptsAt_neurodexe = $(LinkerLocalOptsAtW32_neurodexe)
ResOptsAt_neurodexe = $(ResLocalOptsAtW32_neurodexe)
BOptsAt_neurodexe = $(BLocalOptsAtW32_neurodexe)

#
# Dependency List
#
Dep_neuro = \
   neuro.exe

neuro : BccW32.cfg $(Dep_neuro)
  echo MakeNode

Dep_neurodexe = \
   board.obj\
   dirnet.obj\
   features.obj\
   evalnet.obj\
   player.obj\
   dgame.obj\
   neuro.obj\
   neuro.res

neuro.exe : $(Dep_neurodexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_neurodexe) $(LinkerInheritOptsAt_neurodexe) +
C:\BC5\LIB\c0w32.obj+
board.obj+
dirnet.obj+
features.obj+
evalnet.obj+
player.obj+
dgame.obj+
neuro.obj
$<,$*
C:\BC5\LIB\owlwf.lib+
C:\BC5\LIB\bidsf.lib+
C:\BC5\LIB\import32.lib+
C:\BC5\LIB\cw32.lib

|
   $(BRC32) neuro.res $<

board.obj :  board.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_neurodexe) $(CompInheritOptsAt_neurodexe) -o$@ board.cpp
|

dirnet.obj :  dirnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_neurodexe) $(CompInheritOptsAt_neurodexe) -o$@ dirnet.cpp
|

features.obj :  features.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_neurodexe) $(CompInheritOptsAt_neurodexe) -o$@ features.cpp
|

evalnet.obj :  evalnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_neurodexe) $(CompInheritOptsAt_neurodexe) -o$@ evalnet.cpp
|

player.obj :  player.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_neurodexe) $(CompInheritOptsAt_neurodexe) -o$@ player.cpp
|

dgame.obj :  dgame.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_neurodexe) $(CompInheritOptsAt_neurodexe) -o$@ dgame.cpp
|

neuro.obj :  neuro.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_neurodexe) $(CompInheritOptsAt_neurodexe) -o$@ neuro.cpp
|

neuro.res :  neuro.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_neurodexe) $(CompInheritOptsAt_neurodexe)  -FO$@ neuro.rc
|
# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=neuro.csm
-O-S
-4
-Od
-W
-H"owl\pch.h"
| $@


