#
# makewatc.inc -- Default definitions for compiling with WATCOM C/C++.
#

!   define std_cc   wcc386
!   define std_link *wlink option quiet
!   define std_lib  *wlib /q

main_dir=$+ $(%cwd) $-

.before
    set OS2_INCLUDE=$(%INCLUDE)
    set OS2_TK=$(%TOOLKIT)
    set OS2_LIB=$(%LIB)
    set INCLUDE=$(main_dir)\h;$(ODKDIR)h;$(main_dir)\som\sc;$(SOMDIR)sc;$(ODKDIR)lib;$(%OS2_INCLUDE)
    set LIB=$(ODKDIR)\lib;$(%OS2_LIB)

.error
    @cd $(main_dir)

.EXTENSIONS: .rc .dll .res .lnk

obj_dir  = $(main_dir)\obj

!ifdef DEBUG
obj_dir  = $(main_dir)\objd
!endif

sc_dir   = $(main_dir)\som\sc
som_dir  = $(main_dir)\som
rc_dir   = $(main_dir)\rc

.obj: $(obj_dir)
.c: $(main_dir)\c
.res: $(obj_dir)
.rc: $(rc_dir)
.lnk: $(obj_dir)

dopts =

!ifdef DEBUG
dopts = -d2 -dDEBUG
!endif

cflags = -oailsr -s -w4 -zq -zp4 -zc -bd -4r -bt=OS2_PM -zl -zld $(dopts)

.c.obj :
    @cd $(obj_dir)
    $(std_cc) $(cflags) $[*
    @cd $(main_dir)
   
locallibs= &
    $(ODKDIR)lib\vxrexxw.lib
    
