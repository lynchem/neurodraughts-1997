#
# Borland C++ IDE generated makefile
# Generated 30/05/97 at 12:04:01 
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
LinkerLocalOptsAtC32_convpdndexe =  -Tpe -ap -c
ResLocalOptsAtC32_convpdndexe = 
BLocalOptsAtC32_convpdndexe = 
CompInheritOptsAt_convpdndexe = -IC:\BC5\INCLUDE 
LinkerInheritOptsAt_convpdndexe = -x
LinkerOptsAt_convpdndexe = $(LinkerLocalOptsAtC32_convpdndexe)
ResOptsAt_convpdndexe = $(ResLocalOptsAtC32_convpdndexe)
BOptsAt_convpdndexe = $(BLocalOptsAtC32_convpdndexe)

#
# Dependency List
#
Dep_convpdn = \
   convpdn.exe

convpdn : BccW32.cfg $(Dep_convpdn)
  echo MakeNode

Dep_convpdndexe = \
   train.obj\
   features.obj\
   evalnet.obj\
   dirnet.obj\
   board.obj\
   convpdn.obj

convpdn.exe : $(Dep_convpdndexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_convpdndexe) $(LinkerInheritOptsAt_convpdndexe) +
C:\BC5\LIB\c0x32.obj+
train.obj+
features.obj+
evalnet.obj+
dirnet.obj+
board.obj+
convpdn.obj
$<,$*
C:\BC5\LIB\import32.lib+
C:\BC5\LIB\cw32.lib

|

train.obj :  train.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_convpdndexe) $(CompInheritOptsAt_convpdndexe) -o$@ train.cpp
|

features.obj :  features.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_convpdndexe) $(CompInheritOptsAt_convpdndexe) -o$@ features.cpp
|

evalnet.obj :  evalnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_convpdndexe) $(CompInheritOptsAt_convpdndexe) -o$@ evalnet.cpp
|

dirnet.obj :  dirnet.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_convpdndexe) $(CompInheritOptsAt_convpdndexe) -o$@ dirnet.cpp
|

board.obj :  board.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_convpdndexe) $(CompInheritOptsAt_convpdndexe) -o$@ board.cpp
|

convpdn.obj :  convpdn.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_convpdndexe) $(CompInheritOptsAt_convpdndexe) -o$@ convpdn.cpp
|

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=convPDN.csm
-WC
-Od
| $@


