#
# Makefile for vxrexx.cls classes
#

prepopts = 
scopts = -r -s 64000 -s "h;sc;ih;c"

!ifdef SOM2
prepopts = SOM2
scopts = -maddstar -mnotc -mcsc -r -s 64000 -s "h;sc;ih;c"

!endif

!ifdef USE_WMAKE
.EXTENSIONS: .cls .csc
!else
.SUFFIXES: .cls .csc
!endif

.csc.h:
    -@echo foo > $*.c
    -@del $*.c 2>&1 >nul
    sc $(scopts) $<
    vxgetrel $*.sc ..\$*.rel
    vxprepc $*.c $(prepopts)

!ifdef USE_WMAKE
hfiles = Custom.h 
!else
hfiles = Custom.h 
!endif

!ifdef USE_WMAKE
all: $(hfiles) .SYMBOLIC
    @echo SOM class files are up-to-date.
!else
all: $(hfiles)
    @echo SOM class files are up-to-date.
!endif

Custom.h: Custom.csc 

clean:
    -del *.ih
    -del *.sc
    -del *.c
    -del *.ph
    -del *.def
    -del *.h
    -del *.cs2

#
# End of makefile
#
