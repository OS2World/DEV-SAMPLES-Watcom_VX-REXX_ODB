/*
 * splitba.c
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\splitba.c in preparation for compiling.  New
 * methods will be appended at the end only.
 */

#define INCL_PM

#include "vxrexx.h"
#include "vxfuncs.h"

#define VRSplitBar_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "splitba.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "splitba.ph"
#include "vxcdata.h"

#define PARENT_IS_VIRTUAL

extern PSZ VRSplitBarPicturePath;

static HPOINTER VertPointer = 0;
static HPOINTER HorzPointer = 0;

static somId id_Move = 0;

enum {
    MODE_AUTOMOVE,
    MODE_MANUAL,
    MODE_STATIC,
    MODE_LAST
};

static PSZ Modes[] =
  {
    "AutoMove",
    "Manual",
    "Static",
    NULL
  };

/*
 *  VRSplitBarInstance_somInit
 */

SOM_Scope void   SOMLINK VRSplitBarInstance_somInit(VRSplitBar *somSelf)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 

    parent_somInit(somSelf);

    _is_vertical         = TRUE;
    _height              = 0;
    _orientation_was_set = FALSE;
    _draw_ends           = TRUE;
    _standard_size       = TRUE;
    _mode                = MODE_AUTOMOVE;
}

/*
 *  VRSplitBarInstance_somUninit
 */

SOM_Scope void   SOMLINK VRSplitBarInstance_somUninit(VRSplitBar *somSelf)
{
    parent_somUninit(somSelf);
}

/*
 *  VRSplitBarInstance_vrLocalCreateWindow
 */

SOM_Scope HWND   SOMLINK VRSplitBarInstance_vrLocalCreateWindow(VRSplitBar *somSelf,
        PBOOL visible)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    HWND     hWnd = hNULL;
    SWP      swp;
    LONG     flags;
    SOMAny  *pobj;
    HWND     parent;

    pobj = get_parent_object( somSelf );
    if( !pobj ) goto leave;

    parent = _vrGetInnerWindow( pobj );
    if( !parent ) goto leave;

    if( _vrGetEditMode( pobj ) && !_orientation_was_set ){
        _vrGetWindowPos( somSelf, &swp, VR_PIXELS, TRUE );

        if( swp.cx > swp.cy ){
            _vrSet_Orientation( somSelf, "h" );
        }
    }

    /* A bit of a kludge... since StandardSize is edge-triggered, first
       we reset the instance variable and then invoke the method...
       a cleaner solution would be to have a separate method that
       this method and vrSet_StandardSize both call. */

    if( _standard_size ){
        _standard_size = FALSE;
        _vrSet_StandardSize( somSelf, TRUE );
    }

    _vrGetWindowPos( somSelf, &swp, VR_PIXELS, TRUE );

    flags = _vrGetWindowFlags( somSelf );
    *visible = ( ( flags & WS_VISIBLE ) != 0 );
    flags &= ~WS_VISIBLE;

    hWnd = WinCreateWindow( parent,
                            _vrGetWindowClass( SOM_GetClass( somSelf ) ),
                            "",
                            flags,
                            swp.x, swp.y,
                            swp.cx, swp.cy,
                            parent,
                            HWND_TOP,
                            _vrGetNewWindowID( somSelf ),
                            NULL, NULL );

  leave:
    return( hWnd );
}

/*
 *  VRSplitBarInstance_vrWM_PAINT
 */

SOM_Scope MRESULT   SOMLINK VRSplitBarInstance_vrWM_PAINT(VRSplitBar *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    HPS   hps;
    RECTL rc;
    LONG  color;
    LONG  len;
    ULONG attrFound;
    POINTL ptl1, ptl2;
    LONG   diff;
    LONG   dx, dy;

    place_holder( msg );
    place_holder( mp1 );
    place_holder( mp2 );

    hps = WinBeginPaint( hWnd, NULLHANDLE, &rc );

    len = WinQueryPresParam( hWnd, PP_BACKGROUNDCOLOR,
             PP_BACKGROUNDCOLORINDEX,
             &attrFound, sizeof( color ), &color,
             QPF_ID2COLORINDEX );

    if( len != 0 ){
        GpiCreateLogColorTable( hps, 0, LCOLF_RGB, 0, 0, NULL );
    } else {
        color = GpiQueryRGBColor( hps, 0, SYSCLR_WINDOW );
    }

    WinFillRect( hps, &rc, color );

    /*
     * Do the 3D effect....
     */

    dx = 0;
    dy = 0;

    if( _is_vertical ){
        ptl1.x = rc.xLeft;
        ptl1.y = rc.yBottom;
        ptl2.x = rc.xLeft;
        ptl2.y = rc.yTop;
        dx     = 1;
        diff   = rc.xRight - rc.xLeft;
    } else {
        ptl1.x = rc.xLeft;
        ptl1.y = rc.yTop - 1;
        ptl2.x = rc.xRight;
        ptl2.y = rc.yTop - 1;
        dy     = -1;
        diff   = rc.yTop - rc.yBottom;
    }

    GpiSetColor( hps, CLR_BLACK );
    GpiMove( hps, &ptl1 );
    GpiLine( hps, &ptl2 );

    if( diff > 4 ){
        --diff;

        ptl1.x += dx;
        ptl2.x += dx;
        ptl1.y += dy;
        ptl2.y += dy;

        GpiSetColor( hps, SYSCLR_BUTTONLIGHT );
        GpiMove( hps, &ptl1 );
        GpiLine( hps, &ptl2 );
    }

    GpiSetColor( hps, SYSCLR_BUTTONMIDDLE );

    while( diff > 3 ){
        --diff;

        ptl1.x += dx;
        ptl2.x += dx;
        ptl1.y += dy;
        ptl2.y += dy;

        GpiMove( hps, &ptl1 );
        GpiLine( hps, &ptl2 );
    }

    if( diff > 2 ){
        --diff;

        ptl1.x += dx;
        ptl2.x += dx;
        ptl1.y += dy;
        ptl2.y += dy;

        GpiSetColor( hps, SYSCLR_BUTTONDARK );
        GpiMove( hps, &ptl1 );
        GpiLine( hps, &ptl2 );
    }

    if( diff > 1 ){
        --diff;

        ptl1.x += dx;
        ptl2.x += dx;
        ptl1.y += dy;
        ptl2.y += dy;

        GpiSetColor( hps, CLR_BLACK );
        GpiMove( hps, &ptl1 );
        GpiLine( hps, &ptl2 );
    }

    if( _draw_ends ){
        GpiSetColor( hps, CLR_BLACK );

        if( _is_vertical ){
            ptl1.x = rc.xLeft;
            ptl1.y = rc.yTop - 1;
            ptl2.x = rc.xRight - 1;
            ptl2.y = rc.yTop - 1;

            GpiMove( hps, &ptl1 );
            GpiLine( hps, &ptl2 );

            ptl1.y = rc.yBottom;
            ptl2.y = rc.yBottom;

            GpiMove( hps, &ptl1 );
            GpiLine( hps, &ptl2 );
        } else {
            ptl1.x = rc.xLeft;
            ptl1.y = rc.yBottom;
            ptl2.x = rc.xLeft;
            ptl2.y = rc.yTop - 1;

            GpiMove( hps, &ptl1 );
            GpiLine( hps, &ptl2 );

            ptl1.x = rc.xRight - 1;
            ptl2.x = rc.xRight - 1;

            GpiMove( hps, &ptl1 );
            GpiLine( hps, &ptl2 );
        }
    }

    WinEndPaint( hps );

    return( 0 );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
/*
 *  VRSplitBarClass_vrLocalClassInit

 * Note: The vrLocalClassInit function is defined 
 * in the .ph file for this class....           
 */


/*
 *  VRSplitBarClass_vrLocalWindowClassInit
 */

SOM_Scope bool   SOMLINK VRSplitBarClass_vrLocalWindowClassInit(M_VRSplitBar *somSelf)
{
    return( VRRegisterWindowClass( somSelf, NULL, "VRSplitBar" ) );
}

/*
 *  VRSplitBarClass_somInit
 */

SOM_Scope void   SOMLINK VRSplitBarClass_somInit(M_VRSplitBar *somSelf)
{
    parent_somInit(somSelf);

    get_picturepath( somSelf ) = VRSplitBarPicturePath;

    if( VRQueryRunMode() == VR_DESIGN_MODE ){
        VRInstallHelp( somSelf );
    }

    HorzPointer = WinQuerySysPointer( HWND_DESKTOP, SPTR_SIZENS, FALSE );
    VertPointer = WinQuerySysPointer( HWND_DESKTOP, SPTR_SIZEWE, FALSE );

    /* Initialize our somIds... */

    id_Move = SOM_IdFromString( "Move" );
}

/*
 *  VRSplitBarClass_somUninit
 */

SOM_Scope void   SOMLINK VRSplitBarClass_somUninit(M_VRSplitBar *somSelf)
{
    /* Free the somIds... */

    if( id_Move ){
        SOMFree( id_Move );
    }

    parent_somUninit(somSelf);
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRSplitBarInstance_vrSet_Orientation
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrSet_Orientation(VRSplitBar *somSelf,
        PSZ str)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    _is_vertical = TRUE;
    _orientation_was_set = TRUE;

    if( tolower( *str ) == 'h' ){
        _is_vertical = FALSE;
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRSplitBarInstance_vrGet_Orientation
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrGet_Orientation(VRSplitBar *somSelf,
        PSZ *str)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    PSZ type;

    if( _is_vertical ){
        type = "Vertical";
    } else {
        type = "Horizontal";
    }

    if( str ){
        *str = VRMemAlloc( strlen( type ) + 1 );
        if( *str ){
            strcpy( *str, type );
        }
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRSplitBarInstance_vrHandleNotify
 */

SOM_Scope MRESULT   SOMLINK VRSplitBarInstance_vrHandleNotify(VRSplitBar *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    MRESULT         result = 0;


    switch( SHORT1FROMMP( mp1 ) ){

        case NOTIFY_GET_POINTER:
            result = parent_vrHandleNotify( somSelf, hWnd, msg, mp1, mp2 );

            if( !result && _mode != MODE_STATIC ){
                if( _is_vertical ){
                    result = (MRESULT) VertPointer;
                } else {
                    result = (MRESULT) HorzPointer;
                }
            }

            break;

        default:
            goto passthru;
    }

    return( result );

  passthru:
    return( parent_vrHandleNotify( somSelf, hWnd, msg, mp1, mp2 ) );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRSplitBarInstance_vrSet_Height
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrSet_Height(VRSplitBar *somSelf,
        LONG h,
        LONG units)
{
    SWP             swp;
    HWND            hWnd;
    TWIPS           twips;
    LONG            pixels;

    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 

    if( !somSelf ) goto error;
    hWnd = _vrGetOuterWindow( somSelf );

    pixels = h;
    twips  = h;

    if( units == VR_PIXELS ){
        twips = VRPixelsToTwips( pixels, VR_HEIGHT );
    } else if( units == VR_TWIPS ){
        pixels = VRTwipsToPixels( twips, VR_HEIGHT );
    }

    if( hWnd ){
        if( !WinQueryWindowPos( hWnd, &swp ) ) goto error;

        /* We want to keep the upper left corner fixed */

        swp.y  = swp.y - ( pixels - swp.cy );
        swp.cy = pixels;

        if( swp.cx == 0 )
            ++swp.cx;

        if( swp.cy == 0 )
            ++swp.cy;

        WinSetWindowPos( hWnd, hNULL, swp.x, swp.y, swp.cx, swp.cy,
                         SWP_MOVE | SWP_SIZE | _vrGetSWPFlags( somSelf ) );
    }

    if( !hWnd ||
        ( WinQueryWindowULong( hWnd, QWL_STYLE ) & WS_MINIMIZED ) == 0 ){
        /* only change the size properties if this window is NOT
           minimized. Done mainly for the VREDIT windows */
        _height = twips;
    }

    return( TRUE );

  error:
    return( FALSE );
}

/*
 *  VRSplitBarInstance_vrGet_Height
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrGet_Height(VRSplitBar *somSelf,
        PLONG h,
        LONG units)
{
    HWND             hWnd;
    SWP              swp;

    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 

    if( !somSelf || !h ) goto error;

    *h = 0;

    if( units == VR_TWIPS ){
        *h = _height;
    } else if( units == VR_PIXELS ){
        hWnd = _vrGetOuterWindow( somSelf );
        if( hWnd ){
            if( !WinQueryWindowPos( hWnd, &swp ) ) goto error;
            *h = swp.cy;
        } else {
            *h = VRTwipsToPixels( _height, VR_HEIGHT );
        }
    }

    return( TRUE );

  error:
    return( FALSE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRSplitBarInstance_vrWM_MOUSEMOVE
 */

SOM_Scope MRESULT   SOMLINK VRSplitBarInstance_vrWM_MOUSEMOVE(VRSplitBar *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    MRESULT result;

    _vrShowHint( somSelf );

    result = VRNotifyWindow( hWnd, NOTIFY_GET_POINTER, 0 );

    if( result ){
        WinSetPointer( HWND_DESKTOP, (HPOINTER) result );
        result = (MPARAM) TRUE;
    } else {
        result = _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );
    }

    return( result );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRSplitBarInstance_vrSet_StandardSize
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrSet_StandardSize(VRSplitBar *somSelf,
        BOOL on)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    LONG value;

    if( _standard_size != on ){
        _standard_size = on;

        if( on ){
            if( _is_vertical ){
                value = VRPixelsToTwips( 5, VR_WIDTH );
                _vrSet_Width( somSelf, value, VR_TWIPS );
            } else {
                value = VRPixelsToTwips( 5, VR_HEIGHT );
                _vrSet_Height( somSelf, value, VR_TWIPS );
            }
        }
    }

    return( TRUE );
}


/*
 *  VRSplitBarInstance_vrGet_StandardSize
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrGet_StandardSize(VRSplitBar *somSelf,
        BOOL *on)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    place_holder( somSelf );
    *on = _standard_size;

    return( TRUE );
}

/*
 *  VRSplitBarInstance_vrSet_DrawEnds
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrSet_DrawEnds(VRSplitBar *somSelf,
        BOOL on)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    HWND hWnd;

    if( on != _draw_ends ){
        _draw_ends = on;

        hWnd = _vrGetWindowHandle( somSelf );
        if( hWnd ){
            WinInvalidateRect( hWnd, NULL, FALSE );
        }
    }

    return( TRUE );
}

/*
 *  VRSplitBarInstance_vrGet_DrawEnds
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrGet_DrawEnds(VRSplitBar *somSelf,
        BOOL *on)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    place_holder( somSelf );

    *on = _draw_ends;

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRSplitBarInstance_vrWM_SIZE
 */

SOM_Scope MRESULT   SOMLINK VRSplitBarInstance_vrWM_SIZE(VRSplitBar *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    MRESULT result;
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 

    result = _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );

    /* Oops... here's that kludge again... this forces the object
       back to a standard size if the flag is set... */

    if( _standard_size ){
        _standard_size = FALSE;
        _vrSet_StandardSize( somSelf, TRUE );
    }

    return( result );
}

/*
 *  VRSplitBarInstance_vrSet_Mode
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrSet_Mode(VRSplitBar *somSelf,
        PSZ str)
{
    int i;
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 

    place_holder( somSelf );

    for( i = 0; Modes[i] != NULL; ++i ){
        if( stricmp( str, Modes[i] ) == 0 ){
            _mode = i;
            break;
        }
    }

    return( TRUE );
}

/*
 *  VRSplitBarInstance_vrGet_Mode
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrGet_Mode(VRSplitBar *somSelf,
        PSZ *str)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf); 
    place_holder( somSelf );

    if( _mode >= MODE_LAST ){
        _mode = MODE_STATIC;
    }

    *str = VRMemAlloc( strlen( Modes[ _mode ] ) + 1 );
    if( *str ){
        strcpy( *str, Modes[ _mode ] );
    }

    return( TRUE );
}

/*
 *  VRSplitBarInstance_vrSet_Move
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrSet_Move(VRSplitBar *somSelf,
        PRXSTRING rxstr)
{
    return( _vrAddEvent( somSelf, id_Move, rxstr ) );
}

/*
 *  VRSplitBarInstance_vrGet_Move
 */

SOM_Scope bool   SOMLINK VRSplitBarInstance_vrGet_Move(VRSplitBar *somSelf,
        PRXSTRING rxstr)
{
    if( !_vrFindEvent( somSelf, id_Move, rxstr ) ){
        VRSetNullRXString( rxstr );
    }

    return( TRUE );
}

void EXPENTRY test1( SOMAny *object, PRXSTRING eventstr,
                     ULONG type, vrlist_header_p vrinfolist,
                     TID tid, PVOID reserved )
{
  place_holder( object );
  place_holder( type );
  place_holder( vrinfolist);
  place_holder( reserved );
  place_holder( tid );

  WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, eventstr->strptr, "test1", 0, MB_OK );
}

void EXPENTRY test2( SOMAny *object, PRXSTRING eventstr,
                     ULONG type, vrlist_header_p vrinfolist,
                     TID tid, PVOID reserved )
{
  place_holder( object );
  place_holder( type );
  place_holder( vrinfolist);
  place_holder( reserved );
  place_holder( tid );

  WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, eventstr->strptr, "test2", 0, MB_OK );
}

/*
 * PostMoveEvent
 */

static void PostMoveEvent( SOMAny *somSelf, somId id, LONG left, LONG top )
  {
    RXSTRING       event;
    vrlist_header  eventParms;
    char           buf[ 256 ];
    char           num[ 40 ];
    LONG           val;

    /* Return if we're in the design environment... */

    if( _vrGetEditMode( somSelf ) ) return;

    /* Otherwise find the event string and post it along with
       some VRInfo data */

    event.strptr    = buf;
    event.strlength = 256;

    if( _vrFindEvent( somSelf, id, &event ) ){
        VRListNew( &eventParms );

        /* Get the left value */

        val = VRPixelsToTwips( left, VR_HORIZ );

        num[0] = NULLCHAR;
        sprintf( num, "%d", val );
        VRSetVRInfo( &eventParms, "Left", num );

        /* Get the top value */

        val = VRPixelsToTwips( top, VR_VERT );

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
 *  VRSplitBarInstance_vrWM_BUTTON1DOWN
 */

SOM_Scope MRESULT   SOMLINK VRSplitBarInstance_vrWM_BUTTON1DOWN(VRSplitBar *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRSplitBarData *somThis = VRSplitBarGetData(somSelf);
    TRACKINFO ti;
    bool      ok;
    HWND      parent;
    SWP       swp;
    MRESULT   result;
    LONG      left, top;
    LONG      width, height;
    LONG      oleft, otop;
    LONG      diff;
    SOMAny   *sibling;
    SOMAny   *manager;
    LONG      sl, st, sw, sh;
    BOOL      painting;

    extern HMODULE DLLModule;

    result = _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );

    if( _mode == MODE_STATIC ) goto leave;

    parent = WinQueryWindow( hWnd, QW_PARENT );

    memset( &ti, 0, sizeof( ti ) );

    ti.cxBorder   = 2;
    ti.cyBorder   = 2;
    ti.cxGrid     = 1;
    ti.cyGrid     = 1;
    ti.cxKeyboard = 1;
    ti.cyKeyboard = 1;

    WinQueryWindowPos( hWnd, &swp );

    ti.ptlMinTrackSize.x = ti.ptlMaxTrackSize.x = swp.cx;
    ti.ptlMinTrackSize.y = ti.ptlMaxTrackSize.y = swp.cy;

    ti.rclTrack.xLeft   = swp.x;
    ti.rclTrack.xRight  = swp.x + swp.cx;
    ti.rclTrack.yBottom = swp.y;
    ti.rclTrack.yTop    = swp.y + swp.cy;

    WinQueryWindowRect( parent, &ti.rclBoundary );

    if( _is_vertical ){
        ti.rclBoundary.yTop = swp.y + swp.cy;
        ti.rclBoundary.yBottom = swp.y;
    } else {
        ti.rclBoundary.xLeft = swp.x;
        ti.rclBoundary.xRight = swp.x + swp.cx;
    }

    /*
     * Set a hook if we want to track, then do the tracking...
     */

    ti.fs = TF_ALLINBOUNDARY | TF_MOVE;

    ok = WinTrackRect( parent, hNULL, &ti );
    if( !ok ) goto leave;

    /* Things are OK at this point, move things around if necessary */

    _vrGet_Left( somSelf, &oleft, VR_PIXELS );
    _vrGet_Top( somSelf, &otop, VR_PIXELS );

    _vrGet_Width( somSelf, &width, VR_PIXELS );
    _vrGet_Height( somSelf, &height, VR_PIXELS );

    manager = get_parent_object( somSelf );

    WinQueryWindowRect( parent, &ti.rclBoundary );

    if( _is_vertical ){
        left = ti.rclTrack.xLeft;
        _vrGet_Top( somSelf, &top, VR_PIXELS );

        diff = left - oleft;

        if( _mode != MODE_MANUAL ){
            _vrGet_Painting( manager, &painting );
            _vrSet_Painting( manager, 0 );

            for( sibling = get_firstchild_object( manager );
                 sibling != NULL;
                 sibling = get_next_object( sibling ) ){
                if( sibling == somSelf ) continue;

                _vrGet_Left( sibling, &sl, VR_PIXELS );
                _vrGet_Top( sibling, &st, VR_PIXELS );
                _vrGet_Height( sibling, &sh, VR_PIXELS );
                _vrGet_Width( sibling, &sw, VR_PIXELS );

                if( _mode == MODE_AUTOMOVE ){
                    if( st + sh >= otop && st <= otop + height ){
                        _vrSet_Left( sibling, sl + diff, VR_PIXELS );
                    }
                }
            }

            _vrSet_Left( somSelf, left, VR_PIXELS );
            _vrSet_Painting( manager, painting );
        }
    } else {
        top = ti.rclBoundary.yTop - ti.rclTrack.yTop;
        _vrGet_Left( somSelf, &left, VR_PIXELS );

        diff = top - otop;

        if( _mode != MODE_MANUAL ){
            _vrGet_Painting( manager, &painting );
            _vrSet_Painting( manager, 0 );

            for( sibling = get_firstchild_object( manager );
                 sibling != NULL;
                 sibling = get_next_object( sibling ) ){
                if( sibling == somSelf ) continue;

                _vrGet_Left( sibling, &sl, VR_PIXELS );
                _vrGet_Top( sibling, &st, VR_PIXELS );
                _vrGet_Height( sibling, &sh, VR_PIXELS );
                _vrGet_Width( sibling, &sw, VR_PIXELS );

                if( _mode == MODE_AUTOMOVE ){
                    if( sl + sw >= oleft && sl <= oleft + width ){
                        _vrSet_Top( sibling, st + diff, VR_PIXELS );
                    }
                }
            }

            _vrSet_Top( somSelf, top, VR_PIXELS );
            _vrSet_Painting( manager, painting );
        }
    }

    PostMoveEvent( somSelf, id_Move, left, top );
    WinInvalidateRect( hWnd, NULL, FALSE );

  leave:
    return( result );
}
