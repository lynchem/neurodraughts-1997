#
# Borland C++ IDE generated makefile
# Generated 09/03/97 at 17:10:11 
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
LinkerLocalOptsAtC32_sigdexe =  -Tpe -ap -c
ResLocalOptsAtC32_sigdexe = 
BLocalOptsAtC32_sigdexe = 
CompInheritOptsAt_sigdexe = -IC:\BC5\INCLUDE -D_RTLDLL;
LinkerInheritOptsAt_sigdexe = -x
LinkerOptsAt_sigdexe = $(LinkerLocalOptsAtC32_sigdexe)
ResOptsAt_sigdexe = $(ResLocalOptsAtC32_sigdexe)
BOptsAt_sigdexe = $(BLocalOptsAtC32_sigdexe)

#
# Dependency List
#
Dep_sig = \
   sig.exe

sig : BccW32.cfg $(Dep_sig)
  echo MakeNode

Dep_sigdexe = \
   sig.obj

sig.exe : $(Dep_sigdexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_sigdexe) $(LinkerInheritOptsAt_sigdexe) +
C:\BC5\LIB\c0x32.obj+
sig.obj
$<,$*
C:\BC5\LIB\cg32.lib+
C:\BC5\LIB\import32.lib+
C:\BC5\LIB\cw32i.lib

|

sig.obj :  sig.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_sigdexe) $(CompInheritOptsAt_sigdexe) -o$@ sig.cpp
|

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=sig.csm
-vGd
-vGt
-vGc
-WC
-vGt
-vGd
-vGc
| $@


