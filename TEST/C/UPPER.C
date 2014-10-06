/*
 * upper.c
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\upper.c in preparation for compiling.  New methods
 * will be appended to this file.  No other changes will be made.
 */

#define INCL_PM

#include "vxrexx.h"
#include "vxfuncs.h"

#define VRUpperButton_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "upper.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "upper.ph"
#include "vxcdata.h"

extern PSZ VRUpperButtonPicturePath;

static somId id_DoubleClick = 0;

/*
 *  VRUpperButtonInstance_somInit
 */

SOM_Scope void   SOMLINK VRUpperButtonInstance_somInit(VRUpperButton *somSelf)
{
    parent_somInit(somSelf);
}

/*
 *  VRUpperButtonInstance_somUninit
 */

SOM_Scope void   SOMLINK VRUpperButtonInstance_somUninit(VRUpperButton *somSelf)
{
    parent_somUninit(somSelf);
}

/*
 *  VRUpperButtonInstance_vrLocalCreateWindow
 */

SOM_Scope HWND   SOMLINK VRUpperButtonInstance_vrLocalCreateWindow(VRUpperButton *somSelf,
        PBOOL visible)
{
    return (parent_vrLocalCreateWindow(somSelf,visible));
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta

/* The LocalClassInit function is defined */
/* in the .ih file for this class.... */

/*
 *  VRUpperButtonClass_vrLocalWindowClassInit
 */

SOM_Scope bool   SOMLINK VRUpperButtonClass_vrLocalWindowClassInit(M_VRUpperButton *somSelf)
{
    return (parent_vrLocalWindowClassInit(somSelf));
}

/*
 *  VRUpperButtonClass_somInit
 */

SOM_Scope void   SOMLINK VRUpperButtonClass_somInit(M_VRUpperButton *somSelf)
{
    parent_somInit(somSelf);

    get_picturepath( somSelf ) = VRUpperButtonPicturePath;

    id_DoubleClick = SOM_IdFromString( "DoubleClick" );
}

/*
 *  VRUpperButtonClass_somUninit
 */

SOM_Scope void   SOMLINK VRUpperButtonClass_somUninit(M_VRUpperButton *somSelf)
{
    if( id_DoubleClick ){
        SOMFree( id_DoubleClick );
    }

    parent_somUninit(somSelf);
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRUpperButtonInstance_vrSet_Caption
 */

SOM_Scope bool   SOMLINK VRUpperButtonInstance_vrSet_Caption(VRUpperButton *somSelf,
        PSZ str)
{
    PSZ  new_caption = NULL;
    bool ok = FALSE;

    new_caption = VRMemAlloc( strlen( str ) + 1 );
    if( !new_caption ) return( FALSE );

    strcpy( new_caption, str );
    strupr( new_caption );

    ok = parent_vrSet_Caption( somSelf, new_caption );

    VRMemFree( new_caption );

    return( ok );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRUpperButtonInstance_vrGet_Caption
 */

SOM_Scope bool   SOMLINK VRUpperButtonInstance_vrGet_Caption(VRUpperButton *somSelf,
        PSZ *str)
{
    return (parent_vrGet_Caption(somSelf,str));
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRUpperButtonInstance_vrSet_DoubleClick
 */

SOM_Scope bool   SOMLINK VRUpperButtonInstance_vrSet_DoubleClick(VRUpperButton *somSelf,
        PRXSTRING rxstr)
{
    return( _vrAddEvent( somSelf, id_DoubleClick, rxstr ) );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRUpperButtonInstance_vrGet_DoubleClick
 */

SOM_Scope bool   SOMLINK VRUpperButtonInstance_vrGet_DoubleClick(VRUpperButton *somSelf,
        PRXSTRING rxstr)
{
    if( !_vrFindEvent( somSelf, id_DoubleClick, rxstr ) ){
        VRSetNullRXString( rxstr );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRUpperButtonInstance_vrWM_BUTTON1DBLCLK
 */

SOM_Scope MRESULT   SOMLINK VRUpperButtonInstance_vrWM_BUTTON1DBLCLK(VRUpperButton *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    place_holder( hWnd );
    place_holder( msg );
    place_holder( mp1 );
    place_holder( mp2 );

    _vrPostEvent( somSelf, id_DoubleClick );

    return( 0 );
}
