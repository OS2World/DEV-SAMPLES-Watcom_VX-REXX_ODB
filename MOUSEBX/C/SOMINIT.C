/*
 * SOMINIT.C -- SOM class initialization.
 */

#define INCL_PM
#define INCL_DOS

#include "vxrexx.h"
#include "visible.h"
#include "vxfuncs.h"

/* Header files for classes */
#include "mousebx.h"
/* :sominit:hfiles: */


#include "..\version.h"

/* Icon definitions */
PSZ VRMouseBoxPicturePath = "#100:" DLLNAME ;
/* :sominit:icons:101: */

extern HMODULE VRParentModule;
extern PSZ     VRParentName;
extern PFN     VRParentLoadFunction;

/*
 * _VXREXX_CALLER_ -- If this routine is found by VX-REXX, it is called
 *                    before the SOMInitModule routine is called.  The
 *                    two args that are passed are the module name
 *                    and module handle of the caller.
 */

void _System _VXREXX_CALLER_( PSZ modname, HMODULE modhandle )
  {
    PTIB tib;
    PPIB pib;

    DosGetInfoBlocks( &tib, &pib );

    if( modhandle == pib->pib_hmte && modname ){
        VRParentLoadFunction = (PFN) modname;
        VRParentModule       = modhandle;
    } else {
        if( modname ){
            VRParentName = modname;
        }
    
        if( modhandle ){
            VRParentModule = modhandle;
        }
    }
  }

/*
 * SOMInitModule -- This routine is called automatically by VX-REXX
 *                  when the DLL is loaded.  It should call the
 *                  appropriate class initialization routines.
 */

void _System SOMInitModule( integer4 majorVersion, integer4 minorVersion )
  {
    /* Make sure we're running the correct version of VX-REXX... if not,
     * then don't load the classes...
     */

    if( VRVersion() < MINIMUM_VXREXX_LEVEL ){
        WinMessageBox( HWND_DESKTOP, hNULL, LEVEL_ERRORMSG,
                       LEVEL_TITLE, 0, MB_OK | MB_MOVEABLE );
        return;
    }

    /* This is where you add your class definitions, as in...
     *     MyClassNewClass( majorVersion, minorVersion )
     */

    VRMouseBoxNewClass( majorVersion, minorVersion );
    /* :sominit:init: */
  }


#define UnClass( x ) _somUnregisterClass( SOMClassMgrObject, x ## ClassData.classObject )

void _System SOMUninitModule( void )
  {
    /* This is where you undefine the class, as in...
     *        UnClass( MyClass )
     */

    UnClass( VRMouseBox );
    /* :sominit:uninit: */
  }

/* VersionEntry is a macro -- see above for its definition */

ULONG _System VersionEntry( PULONG version_number, PSZ buf, ULONG length )
  {
    ULONG ok = TRUE;

    if( version_number ){
        *version_number = VERSION;
    }

    if( buf && length > 0 ){
        if( strlen( VERSION_STRING ) <= length + 1 ){
            strcpy( buf, VERSION_STRING );
        }
    }

    return( ok );
  }
