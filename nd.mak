#
# Borland C++ IDE generated makefile
# Generated 12/06/97 at 21:10:51 
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
IDE_LinkFLAGS32 =  -LC:\BC5\LIB -wdef
LinkerLocalOptsAtC32_nddexe =  -w-def -Tpe -ap -c
ResLocalOptsAtC32_nddexe = 
BLocalOptsAtC32_nddexe = 
CompInheritOptsAt_nddexe = -IC:\BC5\INCLUDE;C:\BC5\INCLUDE\CLASSLIB -D_RTLDLL;_BIDSDLL;
LinkerInheritOptsAt_nddexe = -x
LinkerOptsAt_nddexe = $(LinkerLocalOptsAtC32_nddexe)
ResOptsAt_nddexe = $(ResLocalOptsAtC32_nddexe)
BOptsAt_nddexe = $(BLocalOptsAtC32_nddexe)

#
# Dependency List
#
Dep_nd = \
   nd.exe

nd : BccW32.cfg $(Dep_nd)
  echo MakeNode

Dep_nddexe = \
   dgame.obj\
   player.obj\
   features.obj\
   train.obj\
   dirnet.obj\
   board.obj\
   evalnet.obj\
   nd.obj

nd.exe : $(Dep_nddexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_nddexe) $(LinkerInheritOptsAt_nddexe) +
C:\BC5\LIB\c0x32.obj+
dgame.obj+
player.obj+
features.obj+
train.obj+
dirnet.obj+
board.obj+
evalnet.obj+
nd.obj
$<,$*
C:\BC5\LIB\cg32.lib+
C:\BC5\LIB\bidsfi.lib+
C:\BC5\LIB\import32.lib+
C:\BC5\LIB\cw32i.lib

|

dgame.obj :  dgame.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_nddexe) $(CompInheritOptsAt_nddexe) -o$@ dgame.cpp
|

player.obj :  player.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_nddexe) $(CompInheritOptsAt_nddexe) -o$@ player.cpp
|

features.obj :  features.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_nddexe) $(CompInheritOptsAt_nddexe) -o$@ features.cpp
|

train.obj :  train.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_nddexe) $(CompInheritOptsAt_nddexe) -o$@ train.cpp
|

dirnet.obj :  dirnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_nddexe) $(CompInheritOptsAt_nddexe) -o$@ dirnet.cpp
|

board.obj :  board.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_nddexe) $(CompInheritOptsAt_nddexe) -o$@ board.cpp
|

evalnet.obj :  evalnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_nddexe) $(CompInheritOptsAt_nddexe) -o$@ evalnet.cpp
|

nd.obj :  nd.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_nddexe) $(CompInheritOptsAt_nddexe) -o$@ nd.cpp
|

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=nd.csm
-vGd
-vGt
-vGc
-OS
-Oc
-Od
-5
-Oi
-Ov
-WC
-vGt
-vGd
-vGc
| $@


