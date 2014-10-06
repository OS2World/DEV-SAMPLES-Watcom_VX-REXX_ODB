/*
 * INITTERM.C -- DLL initialization and termination.  Works with both
 *               WATCOM C and IBM C.
 */

#define INCL_DOSMODULEMGR
#define INCL_DOSPROCESS

#include "vxrexx.h"

/*
 * The global variable DLLModule will be set to the module handle of
 * the DLL.
 */

ULONG DLLModule = 0;

#ifdef __WATCOMC__
extern ULONG __hmodule;
#endif

/*
 * __dll_initialize -- WATCOM C calls this routine automatically, and the
 *                     CSET entry point code below has also been modified
 *                     to call this routine.
 */

int __dll_initialize( void )
  {
    #ifdef __WATCOMC__
        DLLModule = __hmodule;
    #endif

    /* Do all your DLL initialization here */

    return( TRUE );
  }

/*
 * __dll_terminate -- WATCOM C calls this routine automatically, and the
 *                    CSET entry point code below has also been modified
 *                    to call this routine.
 */

int __dll_terminate( void )
  {
    return( TRUE );
  }

/*
 * CSET entry points... don't modify this code.  Put your DLL
 * initialization/termination code in the two routines above instead.
 * Or wait until the SOMInitModule routine is called.
 */

#ifdef __IBMC__

extern int  _CRT_init( void );
extern void _CRT_term( void );

#pragma handler( _DLL_InitTerm )
unsigned long _System _DLL_InitTerm( unsigned long hModule,
                                     unsigned long ulFlag )
/**********************************************************
    Called by the system (hence uses _System linkage) the first time
    the DLL is loaded or the last time it is freed for a particular
    process.

    In: ulFlag  If 0, the DLL is being loaded and initialization should be
                performed.  If ulFlag is 1 then the DLL is being freed so
                termination should be performed.
        hModule Module handle of this DLL
*/
{
    if( ulFlag == 0 ){
        /*  The C run-time environment initialization function must be
            called before any calls to C run-time functions that are
            not inlined.
        */
        if( _CRT_init() == -1 )
            return( FALSE );

        DLLModule = hModule;

        if( !__dll_initialize() )
            return( FALSE );
    }
    else if( ulFlag == 1 ){
        __dll_terminate();

        _CRT_term();
    }

    /* A non-zero value must be returned to indicate success.
    */
    return( TRUE );
}

#endif
