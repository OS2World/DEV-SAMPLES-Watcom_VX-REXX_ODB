#
# makecset.inc -- Default definitions for compiling with CSet++.
#

o     = obj
copts = /O+
lopts =

!ifdef DEBUG
o     = objd
copts = /O- /Ti+ /dDEBUG
lopts = /DEBUG
!endif

cflags = $(copts) /Ss /Gd- /Q /C /Se /W2 /Gm+ /Ge- /I..\h /I$(ODKDIR)h /I..\som\sc /I$(SOMDIR)sc
lflags = $(lopts) /NOLOGO /NOE /NOI /EXEPACK /PACKCODE /PACKDATA /MAP

.SUFFIXES:

.SUFFIXES: .c .obj .dll .rc .res

#
# Rules to compile C files and RC files
#

{c}.c.obj :
    @cd $(o)
    icc $(cflags) ..\c\%|feF
    @cd ..

{rc}.rc.res :
    @cd rc
    rc -r %|feF ..\$(o)\%|fF.res
    @cd ..

