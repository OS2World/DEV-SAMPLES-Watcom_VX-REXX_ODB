/*
 * mousebx.c -- Implements the VRMouseBox class
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\mousebx.c in preparation for compiling.  It
 * will not be modified further.  You must port any changes you
 * make by manually cutting and pasting from the SOM-generated
 * C file to this one.
 */

#define INCL_PM

#include "vxrexx.h"
#include "vxfuncs.h"

#define VRMouseBox_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "mousebx.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "mousebx.ph"
#include "vxcdata.h"

extern PSZ  VRMouseBoxPicturePath;

/*
 * Define storage for the somIds we need... they are initialized
 * below when the class is initialized...
 */

static somId id_MB1Down = 0;
static somId id_MB2Down = 0;
static somId id_MB1Up   = 0;
static somId id_MB2Up   = 0;
static somId id_MMove   = 0;

/********** INSTANCE METHODS ***********/

/*
 *  VRMouseBoxInstance_somInit
 */

SOM_Scope void   SOMLINK VRMouseBoxInstance_somInit(VRMouseBox *somSelf)
{
    VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf);
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_somInit");

    parent_somInit(somSelf);

    _enabled = TRUE; /* Controls are enabled by default... */
}

/*
 *  VRMouseBoxInstance_somUninit
 */

SOM_Scope void   SOMLINK VRMouseBoxInstance_somUninit(VRMouseBox *somSelf)
{
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_somUninit");

    parent_somUninit(somSelf);
}

/*
 *  VRMouseBoxInstance_vrLocalCreateWindow
 */

SOM_Scope HWND   SOMLINK VRMouseBoxInstance_vrLocalCreateWindow(VRMouseBox *somSelf,
        PBOOL visible)
{
    HWND            hWnd;

    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrLocalCreateWindow");

    /* We'll just call the PictureBox routine to create a window... */

    hWnd = parent_vrLocalCreateWindow(somSelf,visible);

    return( hWnd );
}

/*
 *  VRMouseBoxInstance_vrSet_MouseButton1Down
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrSet_MouseButton1Down(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrSet_MouseButton1Down");

    return( _vrAddEvent( somSelf, id_MB1Down, rxstr ) );
}

/*
 *  VRMouseBoxInstance_vrGet_MouseButton1Down
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrGet_MouseButton1Down(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrGet_MouseButton1Down");

    if( !_vrFindEvent( somSelf, id_MB1Down, rxstr ) ){
        VRSetNullRXString( rxstr );
    }

    return( TRUE );
}

/*
 *  VRMouseBoxInstance_vrSet_MouseButton2Down
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrSet_MouseButton2Down(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrSet_MouseButton2Down");

    return( _vrAddEvent( somSelf, id_MB2Down, rxstr ) );
}

/*
 *  VRMouseBoxInstance_vrGet_MouseButton2Down
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrGet_MouseButton2Down(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrGet_MouseButton2Down");

    if( !_vrFindEvent( somSelf, id_MB2Down, rxstr ) ){
        VRSetNullRXString( rxstr );
    }

    return( TRUE );
}

/*
 *  VRMouseBoxInstance_vrSet_MouseButton1Up
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrSet_MouseButton1Up(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrSet_MouseButton1Up");

    return( _vrAddEvent( somSelf, id_MB1Up, rxstr ) );
}

/*
 *  VRMouseBoxInstance_vrGet_MouseButton1Up
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrGet_MouseButton1Up(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrGet_MouseButton1Up");

    if( !_vrFindEvent( somSelf, id_MB1Up, rxstr ) ){
        VRSetNullRXString( rxstr ); 
    }

    return( TRUE );
}

/*
 *  VRMouseBoxInstance_vrSet_MouseButton2Up
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrSet_MouseButton2Up(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrSet_MouseButton2Up");

    return( _vrAddEvent( somSelf, id_MB2Up, rxstr ) );
}

/*
 *  VRMouseBoxInstance_vrGet_MouseButton2Up
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrGet_MouseButton2Up(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrGet_MouseButton2Up");

    if( !_vrFindEvent( somSelf, id_MB2Up, rxstr ) ){
        VRSetNullRXString( rxstr );
    }

    return( TRUE );
}

/*
 *  VRMouseBoxInstance_vrSet_MouseMove
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrSet_MouseMove(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrSet_MouseMove");

    return( _vrAddEvent( somSelf, id_MMove, rxstr ) );
}

/*
 *  VRMouseBoxInstance_vrGet_MouseMove
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrGet_MouseMove(VRMouseBox *somSelf,
        PRXSTRING rxstr)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrGet_MouseMove");

    if( !_vrFindEvent( somSelf, id_MMove, rxstr ) ){
        VRSetNullRXString( rxstr );
    }

    return( TRUE );
}

/*
 *  VRMouseBoxInstance_vrSet_Enabled
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrSet_Enabled(VRMouseBox *somSelf,
        BOOL on)
{
    VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf);
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrSet_Enabled");

    /* All we want to do is catch the current enabled state... we could
       just do a _vrGet_Enabled everytime we wanted to check the state,
       but that's more expensive than just keeping track of it with
       some instance data... */

    _enabled = on;

    return( parent_vrSet_Enabled( somSelf, on ) );
}

/*
 *  VRMouseBoxInstance_vrGet_Enabled
 */

SOM_Scope bool   SOMLINK VRMouseBoxInstance_vrGet_Enabled(VRMouseBox *somSelf,
        BOOL *on)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrGet_Enabled");

    return( parent_vrGet_Enabled( somSelf, on ) );
}

/*
 * PostMouseEvent -- Post a mouse event...  This is not a method,
 *                   just a C function that other methods use.
 */

static void PostMouseEvent( SOMAny *somSelf, somId id, MPARAM mp1,
                            MPARAM mp2 )
  {
    RXSTRING       event;
    vrlist_header  eventParms;
    char           buf[ 256 ];
    char           num[ 40 ];
    LONG           val;
    SWP            swp;
    HWND           hWnd;

    place_holder( mp2 );

    /* Return if we're in the design environment... */

    if( _vrGetEditMode( somSelf ) ) return;

    /* Otherwise find the event string and post it along with
       some VRInfo data */

    event.strptr    = buf;
    event.strlength = 256;

    if( _vrFindEvent( somSelf, id, &event ) ){
        VRListNew( &eventParms );

        /* Get the left value */

        val = SHORT1FROMMP( mp1 );
        val = VRPixelsToTwips( val, VR_HORIZ );

        num[0] = NULLCHAR;
        sprintf( num, "%d", val );
        VRSetVRInfo( &eventParms, "Left", num );

        /* Get the top value */

        hWnd = _vrGetOuterWindow( somSelf );

        WinQueryWindowPos( hWnd, &swp );

        val = SHORT2FROMMP( mp1 );
        val = VRPixelsToTwips( swp.cy - val, VR_VERT );

        sprintf( num, "%d", val );
        VRSetVRInfo( &eventParms, "Top", num );

        /* Post the event */

        VRPostEvent( somSelf, 0, SOM_StringFromId( id ),
                     &event, &eventParms );

        if( event.strptr != NULL && event.strptr != buf ){
            DosFreeMem( event.strptr ); /* Free what FindEvent returned */
        }
    }
  }

/*
 *  VRMouseBoxInstance_vrWM_BUTTON1DOWN
 */

SOM_Scope MRESULT   SOMLINK VRMouseBoxInstance_vrWM_BUTTON1DOWN(VRMouseBox *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrWM_BUTTON1DOWN");

    PostMouseEvent( somSelf, id_MB1Down, mp1, mp2 );

    return( _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 ) );
}

/*
 *  VRMouseBoxInstance_vrWM_BUTTON2DOWN
 */

SOM_Scope MRESULT   SOMLINK VRMouseBoxInstance_vrWM_BUTTON2DOWN(VRMouseBox *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrWM_BUTTON2DOWN");

    PostMouseEvent( somSelf, id_MB2Down, mp1, mp2 );

    return( _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 ) );
}

/*
 *  VRMouseBoxInstance_vrWM_MOUSEMOVE
 */

SOM_Scope MRESULT   SOMLINK VRMouseBoxInstance_vrWM_MOUSEMOVE(VRMouseBox *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf);
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrWM_MOUSEMOVE");

    /* We don't care about mouse movement events if we're not enabled... */

    if( _enabled ){
        PostMouseEvent( somSelf, id_MMove, mp1, mp2 );
    }

    return( parent_vrWM_MOUSEMOVE( somSelf, hWnd, msg, mp1, mp2 ) );
}

/*
 *  VRMouseBoxInstance_vrWM_BUTTON1UP
 */

SOM_Scope MRESULT   SOMLINK VRMouseBoxInstance_vrWM_BUTTON1UP(VRMouseBox *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrWM_BUTTON1UP");

    PostMouseEvent( somSelf, id_MB1Up, mp1, mp2 );

    return( _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 ) );
}

/*
 *  VRMouseBoxInstance_vrWM_BUTTON2UP
 */

SOM_Scope MRESULT   SOMLINK VRMouseBoxInstance_vrWM_BUTTON2UP(VRMouseBox *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    /* VRMouseBoxData *somThis = VRMouseBoxGetData(somSelf); */
    VRMouseBoxMethodDebug("VRMouseBox","VRMouseBoxInstance_vrWM_BUTTON2UP");

    PostMouseEvent( somSelf, id_MB2Up, mp1, mp2 );

    return( _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 ) );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta

/********** CLASS METHODS ***********/

   /* The LocalClassInit function is defined */
   /* in the .ih file for this class.... */


/*
 *  VRMouseBoxClass_vrLocalWindowClassInit
 */

SOM_Scope bool   SOMLINK VRMouseBoxClass_vrLocalWindowClassInit(M_VRMouseBox *somSelf)
{
    /* M_VRMouseBoxData *somThis = M_VRMouseBoxGetData(somSelf); */
    M_VRMouseBoxMethodDebug("M_VRMouseBox","VRMouseBoxClass_vrLocalWindowClassInit");

    return( VRRegisterWindowClassX( somSelf, NULL, "VRMouseBox", CS_PARENTCLIP ) );
}

/*
 *  VRMouseBoxClass_somInit
 */

SOM_Scope void   SOMLINK VRMouseBoxClass_somInit(M_VRMouseBox *somSelf)
{
    /* M_VRMouseBoxData *somThis = M_VRMouseBoxGetData(somSelf); */
    M_VRMouseBoxMethodDebug("M_VRMouseBox","VRMouseBoxClass_somInit");

    parent_somInit(somSelf);

    get_picturepath( somSelf ) =  VRMouseBoxPicturePath;

    /* Make sure that the somIds are initialized... */

    id_MB1Down = SOM_IdFromString( "MouseButton1Down" );
    id_MB2Down = SOM_IdFromString( "MouseButton2Down" );
    id_MB1Up   = SOM_IdFromString( "MouseButton1Up" );
    id_MB2Up   = SOM_IdFromString( "MouseButton2Up" );
    id_MMove   = SOM_IdFromString( "MouseMove" );
}

/*
 *  VRMouseBoxClass_somUninit
 */

SOM_Scope void   SOMLINK VRMouseBoxClass_somUninit(M_VRMouseBox *somSelf)
{
    /* M_VRMouseBoxData *somThis = M_VRMouseBoxGetData(somSelf); */
    M_VRMouseBoxMethodDebug("M_VRMouseBox","VRMouseBoxClass_somUninit");

    SOMFree( id_MB1Down );
    SOMFree( id_MB2Down );
    SOMFree( id_MB1Up );
    SOMFree( id_MB2Up );
    SOMFree( id_MMove );

    parent_somUninit(somSelf);
}
