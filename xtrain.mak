#
# Borland C++ IDE generated makefile
# Generated 30/05/97 at 12:02:48 
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
LinkerLocalOptsAtC32_xtraindexe =  -Tpe -ap -c
ResLocalOptsAtC32_xtraindexe = 
BLocalOptsAtC32_xtraindexe = 
CompInheritOptsAt_xtraindexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_xtraindexe = -x
LinkerOptsAt_xtraindexe = $(LinkerLocalOptsAtC32_xtraindexe)
ResOptsAt_xtraindexe = $(ResLocalOptsAtC32_xtraindexe)
BOptsAt_xtraindexe = $(BLocalOptsAtC32_xtraindexe)

#
# Dependency List
#
Dep_xtrain = \
   xtrain.exe

xtrain : BccW32.cfg $(Dep_xtrain)
  echo MakeNode

Dep_xtraindexe = \
   train.obj\
   features.obj\
   evalnet.obj\
   dirnet.obj\
   board.obj\
   xtrain.obj

xtrain.exe : $(Dep_xtraindexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_xtraindexe) $(LinkerInheritOptsAt_xtraindexe) +
C:\BC5\LIB\c0x32.obj+
train.obj+
features.obj+
evalnet.obj+
dirnet.obj+
board.obj+
xtrain.obj
$<,$*
C:\BC5\LIB\import32.lib+
C:\BC5\LIB\cw32.lib

|

train.obj :  train.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_xtraindexe) $(CompInheritOptsAt_xtraindexe) -o$@ train.cpp
|

features.obj :  features.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_xtraindexe) $(CompInheritOptsAt_xtraindexe) -o$@ features.cpp
|

evalnet.obj :  evalnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_xtraindexe) $(CompInheritOptsAt_xtraindexe) -o$@ evalnet.cpp
|

dirnet.obj :  dirnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_xtraindexe) $(CompInheritOptsAt_xtraindexe) -o$@ dirnet.cpp
|

board.obj :  board.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_xtraindexe) $(CompInheritOptsAt_xtraindexe) -o$@ board.cpp
|

xtrain.obj :  xtrain.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_xtraindexe) $(CompInheritOptsAt_xtraindexe) -o$@ xtrain.cpp
|

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=xtrain.csm
-WC
-Od
| $@


