#
# Borland C++ IDE generated makefile
# Generated 30/05/97 at 12:08:06 
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
LinkerLocalOptsAtC32_fightdexe =  -Tpe -ap -c
ResLocalOptsAtC32_fightdexe = 
BLocalOptsAtC32_fightdexe = 
CompInheritOptsAt_fightdexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_fightdexe = -x
LinkerOptsAt_fightdexe = $(LinkerLocalOptsAtC32_fightdexe)
ResOptsAt_fightdexe = $(ResLocalOptsAtC32_fightdexe)
BOptsAt_fightdexe = $(BLocalOptsAtC32_fightdexe)

#
# Dependency List
#
Dep_fight = \
   fight.exe

fight : BccW32.cfg $(Dep_fight)
  echo MakeNode

Dep_fightdexe = \
   evalnet.obj\
   features.obj\
   player.obj\
   dirnet.obj\
   dgame.obj\
   board.obj\
   fight.obj

fight.exe : $(Dep_fightdexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_fightdexe) $(LinkerInheritOptsAt_fightdexe) +
C:\BC5\LIB\c0x32.obj+
evalnet.obj+
features.obj+
player.obj+
dirnet.obj+
dgame.obj+
board.obj+
fight.obj
$<,$*
C:\BC5\LIB\bidsf.lib+
C:\BC5\LIB\import32.lib+
C:\BC5\LIB\cw32.lib

|

evalnet.obj :  evalnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fightdexe) $(CompInheritOptsAt_fightdexe) -o$@ evalnet.cpp
|

features.obj :  features.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fightdexe) $(CompInheritOptsAt_fightdexe) -o$@ features.cpp
|

player.obj :  player.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fightdexe) $(CompInheritOptsAt_fightdexe) -o$@ player.cpp
|

dirnet.obj :  dirnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fightdexe) $(CompInheritOptsAt_fightdexe) -o$@ dirnet.cpp
|

dgame.obj :  dgame.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fightdexe) $(CompInheritOptsAt_fightdexe) -o$@ dgame.cpp
|

board.obj :  board.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fightdexe) $(CompInheritOptsAt_fightdexe) -o$@ board.cpp
|

fight.obj :  fight.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fightdexe) $(CompInheritOptsAt_fightdexe) -o$@ fight.cpp
|

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=fight.csm
-Od
-WC
| $@


