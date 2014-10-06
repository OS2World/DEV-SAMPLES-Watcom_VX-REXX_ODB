/*
 * scroll.c
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\scroll.c in preparation for compiling.  New
 * methods will be appended at the end only.
 */

#define INCL_PM

#include "vxrexx.h"
#include "vxfuncs.h"

#define VRScroll_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "scroll.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "scroll.ph"
#include "vxcdata.h"

#define PARENT_IS_VIRTUAL

extern PSZ VRScrollPicturePath;

static somId id_Change = 0;
static somId id_Track  = 0;

/*
 *  VRScrollInstance_somInit
 *
 *    This method initializes per-object instance data.
 */

SOM_Scope void   SOMLINK VRScrollInstance_somInit(VRScroll *somSelf)
{
    VRScrollData *somThis = VRScrollGetData(somSelf); 
    LONG flags;

    parent_somInit(somSelf);

    /* Initialize our instance data */

    _scrollbar        = NULLHANDLE;
    _standardsize     = TRUE;
    _line_increment   = 0;
    _page_increment   = 0;
    _is_frame_control = 0;

    /* By default, make the scrollbar a vertical scrollbar.  The only
       reason we're doing this is because the icon in the toolbar
       is a vertical scrollbar.... */

    flags = _vrGetWindowFlags( somSelf );
    flags |= SBS_VERT;
    _vrSetWindowFlags( somSelf, flags );

    _orientation_was_set = FALSE;
}

/*
 *  VRScrollInstance_somUninit
 *
 *    This method uninitializes per-object instance data.
 */

SOM_Scope void   SOMLINK VRScrollInstance_somUninit(VRScroll *somSelf)
{
    VRScrollData *somThis = VRScrollGetData(somSelf); 
    /* Destroy the child window */

    if( _scrollbar ){
        WinDestroyWindow( _scrollbar );
        _scrollbar = NULLHANDLE;
    }

    parent_somUninit(somSelf);
}

/*
 *  VRScrollInstance_vrLocalCreateWindow
 *
 *    This method creates the window associated with the object
 *    and the WC_SCROLLBAR window that is its child.
 */

SOM_Scope HWND   SOMLINK VRScrollInstance_vrLocalCreateWindow(VRScroll *somSelf,
        PBOOL visible)
{
    VRScrollData *somThis = VRScrollGetData(somSelf); 
    HWND     hWnd = hNULL;
    SWP      swp;
    LONG     flags;
    SOMAny  *pobj;
    HWND     parent;

    pobj = get_parent_object( somSelf );
    if( !pobj ) goto leave;

    parent = _vrGetInnerWindow( pobj );
    if( !parent ) goto leave;

    /* If orientation was not set, set it to something intelligent... */

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

    if( _standardsize ){
        _standardsize = FALSE;
        _vrSet_StandardSize( somSelf, TRUE );
    }

    /* Get the initial window position. */

    _vrGetWindowPos( somSelf, &swp, VR_PIXELS, TRUE );

    /* Get the flags... this code is generated automatically. */

    flags = _vrGetWindowFlags( somSelf );
    *visible = ( ( flags & WS_VISIBLE ) != 0 );
    flags &= ~WS_VISIBLE;

    /* Create the outer window */

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


    /* Create the scrollbar window as a child of the outer window */

    if( hWnd ){

        /* Set the font to something small, because VX-REXX uses
           the font size to determine the minimum size of an object. */

        #define FONTSTR "8.Helv"

        WinSetPresParam( hWnd, PP_FONTNAMESIZE,
                         strlen( FONTSTR ) + 1, FONTSTR );

        /* Now create the scrollbar control as a child of our
           own window */

        _scrollbar = WinCreateWindow( hWnd, WC_SCROLLBAR,
                                      "",
                                      flags | WS_VISIBLE,
                                      0, 0,
                                      swp.cx, swp.cy,
                                      hWnd,
                                      HWND_TOP,
                                      0,
                                      NULL, NULL );

        /* Cleanup if something went wrong, otherwise set some initial
           defaults... */

        if( !_scrollbar ){
            WinDestroyWindow( hWnd );
            hWnd = NULLHANDLE;
        } else {
            WinSendMsg( _scrollbar, SBM_SETSCROLLBAR, MPFROMSHORT( 0 ),
                        MPFROM2SHORT( 1, 100 ) );
            WinSendMsg( _scrollbar, SBM_SETTHUMBSIZE, MPFROM2SHORT( 25, 100 ),
                        0 );
            _thumbsize = 25;
        }
    }

  leave:
    /* If NULLHANDLE is returned, the object creation fails.... otherwise
       return the window handle for the object... */

    return( hWnd );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta

/*
 *  VRScrollClass_vrLocalClassInit

 * Note: The vrLocalClassInit function is defined 
 * in the .ph file for this class....           
 */


/*
 *  VRScrollClass_vrLocalWindowClassInit
 *
 *     This method is called automatically when the class is being
 *     initialized.  You should register a window class here.
 */

SOM_Scope bool   SOMLINK VRScrollClass_vrLocalWindowClassInit(M_VRScroll *somSelf)
{

    /* First try -- replace line with this:
     *
     *   return( VRRegisterWindowClass( somSelf, WC_SCROLLBAR, "VRScroll" ) );
     *
     * but that doesn't help us because we need to intercept the
     * WM_HSCROLL and WM_VSCROLL messages that are sent to the
     * scrollbar's owner.  So instead we create a simple window class
     * that will be used as a parent for the scrollbar itself.
     * When a window of this class is created, it will also create
     * a scrollbar control as its (only) child.
     */

    return( VRRegisterWindowClass( somSelf, NULL, "VRScroll" ) );
}

/*
 *  VRScrollClass_somInit
 *
 *     SOM calls this method when the class is being initialized.
 */

SOM_Scope void   SOMLINK VRScrollClass_somInit(M_VRScroll *somSelf)
{

    parent_somInit(somSelf);

    /* Assign an icon for the class and install help if necessary... */

    get_picturepath( somSelf ) = VRScrollPicturePath;

    if( VRQueryRunMode() == VR_DESIGN_MODE ){
        VRInstallHelp( somSelf );
    }

    /* Initialize our somIds... */

    id_Change = SOM_IdFromString( "Change" );
    id_Track  = SOM_IdFromString( "Track" );
}

/*
 *  VRScrollClass_somUninit
 *
 *     SOM calls this method when the class is being uninitialized.
 */

SOM_Scope void   SOMLINK VRScrollClass_somUninit(M_VRScroll *somSelf)
{

    /* Free the somIds... */

    if( id_Change ){
        SOMFree( id_Change );
    }

    if( id_Track ){
        SOMFree( id_Track );
    }

    parent_somUninit(somSelf);
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrWM_SIZE
 *
 *    This method is called whenever the object receives a WM_SIZE
 *    message.  All it does is resize the scroll bar control.
 */

SOM_Scope MRESULT   SOMLINK VRScrollInstance_vrWM_SIZE(VRScroll *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    SHORT cx, cy;
    MRESULT result = 0;

    if( _scrollbar ){
        cx = SHORT1FROMMP( mp2 );
        cy = SHORT2FROMMP( mp2 );

        WinSetWindowPos( _scrollbar, NULLHANDLE, 0, 0, cx, cy,
                         SWP_SIZE );
    }

    result = _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );

    /* Oops... here's that kludge again... this forces the object
       back to a standard size if the flag is set... */

    if( _standardsize ){
        _standardsize = FALSE;
        _vrSet_StandardSize( somSelf, TRUE );
    }

    return( result );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrWM_QUERYDLGCODE
 */

SOM_Scope MRESULT   SOMLINK VRScrollInstance_vrWM_QUERYDLGCODE(VRScroll *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    place_holder( hWnd );

    if( _scrollbar ){
        return( WinSendMsg( _scrollbar, msg, mp1, mp2 ) );
    }

    return( MRFROMLONG( DLGC_SCROLLBAR ) );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrWM_SETFOCUS
 *
 *    If the object window gets the focus, post a message to itself
 *    to move the focus to its child window....
 */

SOM_Scope MRESULT   SOMLINK VRScrollInstance_vrWM_SETFOCUS(VRScroll *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    if( _scrollbar && SHORT1FROMMP( mp2 ) ){
        WinPostMsg( hWnd, VRSCR_GRABFOCUS, 0, 0 );
    }

    return( parent_vrWM_SETFOCUS( somSelf, hWnd, msg, mp1, mp2 ) );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrVRSCR_GRABFOCUS
 *
 *     Handle the focus changing....
 */

SOM_Scope MRESULT   SOMLINK VRScrollInstance_vrVRSCR_GRABFOCUS(VRScroll *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    place_holder( msg );
    place_holder( mp1 );
    place_holder( mp2 );

    if( _scrollbar && WinQueryFocus( HWND_DESKTOP ) == hWnd ){
        WinSetFocus( HWND_DESKTOP, _scrollbar );
    }

    return( 0 );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_Orientation
 *
 *     Set which type of scrollbar we are, either vertical or horizontal.
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_Orientation(VRScroll *somSelf,
        PSZ str)
{
    VRScrollData *somThis = VRScrollGetData(somSelf); 
    LONG flags;


    if( !_vrGetWindowHandle( somSelf ) ){
        flags = _vrGetWindowFlags( somSelf );

        if( str && tolower( *str ) == 'v' ){
            flags |= SBS_VERT;
        } else {
            flags &= ~SBS_VERT;
        }

        _vrSetWindowFlags( somSelf, flags );

        _orientation_was_set = TRUE;
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_Orientation
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_Orientation(VRScroll *somSelf,
        PSZ *str)
{
    /* VRScrollData *somThis = VRScrollGetData(somSelf); */
    ULONG flags;
    PSZ   type;
    bool  ok = FALSE;


    flags = _vrGetWindowFlags( somSelf );

    if( flags & SBS_VERT ){
        type = "Vertical";
    } else {
        type = "Horizontal";
    }

    *str = VRMemAlloc( strlen( type ) + 1 );

    if( *str ){
        strcpy( *str, type );
        ok = TRUE;
    }

    return( ok );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_StandardSize
 *
 *    When this property is set to on, adjust the height or width of
 *    the scrollbar (depending on the type) so that it looks like a
 *    standard scrollbar... 
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_StandardSize(VRScroll *somSelf,
        BOOL on)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    LONG          flags;
    LONG          value;


    if( _standardsize != on ){
        _standardsize = on;

        if( on ){
            flags = _vrGetWindowFlags( somSelf );

            if( flags & SBS_VERT ){
                value = WinQuerySysValue( HWND_DESKTOP, SV_CXVSCROLL );
                value = VRPixelsToTwips( value, VR_WIDTH );
                _vrSet_Width( somSelf, value, VR_TWIPS );
            } else {
                value = WinQuerySysValue( HWND_DESKTOP, SV_CYHSCROLL );
                value = VRPixelsToTwips( value, VR_HEIGHT );
                _vrSet_Height( somSelf, value, VR_TWIPS );
            }
        }
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_StandardSize
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_StandardSize(VRScroll *somSelf,
        BOOL *on)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    *on = _standardsize;

    return( TRUE );
}


#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_MinimumValue
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_MinimumValue(VRScroll *somSelf,
        ULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    MRESULT result;
    SHORT   min, max;
    SHORT   pos;


    if( val > 32767 )
        val = 32767;

    if( _scrollbar ){
        result = WinSendMsg( _scrollbar, SBM_QUERYRANGE, 0, 0 );
        max    = SHORT2FROMMR( result );

        min = (SHORT) val;
        if( min > max ){
            max = min;
        }

        result = WinSendMsg( _scrollbar, SBM_QUERYPOS, 0, 0 );
        pos    = SHORT1FROMMR( result );

        WinSendMsg( _scrollbar, SBM_SETSCROLLBAR, MPFROMSHORT( pos ),
                    MPFROM2SHORT( min, max ) );
        WinSendMsg( _scrollbar, SBM_SETTHUMBSIZE,
                    MPFROM2SHORT( _thumbsize, 100 ), 0 );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_MinimumValue
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_MinimumValue(VRScroll *somSelf,
        PULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    MRESULT       result;


    *val = 0;

    if( _scrollbar ){
        result = WinSendMsg( _scrollbar, SBM_QUERYRANGE, 0, 0 );
        
        *val = SHORT1FROMMR( result );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_MaximumValue
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_MaximumValue(VRScroll *somSelf,
        ULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    MRESULT result;
    SHORT   min, max;
    SHORT   pos;


    if( val > 32767 )
        val = 32767;

    if( _scrollbar ){
        result = WinSendMsg( _scrollbar, SBM_QUERYRANGE, 0, 0 );
        min    = SHORT1FROMMR( result );

        max = (SHORT) val;
        if( max < min ){
            min = max;
        }

        result = WinSendMsg( _scrollbar, SBM_QUERYPOS, 0, 0 );
        pos    = SHORT1FROMMR( result );

        WinSendMsg( _scrollbar, SBM_SETSCROLLBAR, MPFROMSHORT( pos ),
                    MPFROM2SHORT( min, max ) );
        WinSendMsg( _scrollbar, SBM_SETTHUMBSIZE,
                    MPFROM2SHORT( _thumbsize, 100 ), 0 );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_MaximumValue
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_MaximumValue(VRScroll *somSelf,
        PULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    MRESULT       result;


    *val = 0;

    if( _scrollbar ){
        result = WinSendMsg( _scrollbar, SBM_QUERYRANGE, 0, 0 );
        
        *val = SHORT2FROMMR( result );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_Value
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_Value(VRScroll *somSelf,
        ULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    if( _scrollbar ){
        WinSendMsg( _scrollbar, SBM_SETPOS, MPFROMSHORT( val ), 0 );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_Value
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_Value(VRScroll *somSelf,
        PULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    MRESULT       result;


    *val = 0;

    if( _scrollbar ){
        result = WinSendMsg( _scrollbar, SBM_QUERYPOS, 0, 0 );
        *val   = SHORT1FROMMR( result );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_ThumbSize
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_ThumbSize(VRScroll *somSelf,
        ULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    if( val > 100 )
        val = 100;

    _thumbsize = val;

    if( _scrollbar ){
        WinSendMsg( _scrollbar, SBM_SETTHUMBSIZE,
                    MPFROM2SHORT( _thumbsize, 100 ), 0 );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_ThumbSize
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_ThumbSize(VRScroll *somSelf,
        PULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    *val = _thumbsize;

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_Change
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_Change(VRScroll *somSelf,
        PRXSTRING rxstr)
{
    return( _vrAddEvent( somSelf, id_Change, rxstr ) );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_Change
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_Change(VRScroll *somSelf,
        PRXSTRING rxstr)
{
    if( !_vrFindEvent( somSelf, id_Change, rxstr ) ){
        VRSetNullRXString( rxstr );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrWM_HSCROLL
 */

SOM_Scope MRESULT   SOMLINK VRScrollInstance_vrWM_HSCROLL(VRScroll *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    LONG val;
    SHORT nmsg;

    place_holder( msg );
    place_holder( hWnd );
    place_holder( mp1 );

    if( _vrGetEditMode( somSelf ) ) return( 0 );

    nmsg = SHORT2FROMMP( mp2 );

    switch( nmsg ){
        case SB_SLIDERPOSITION:
            if( !_vrGetEditMode( somSelf ) &&
                !VRIsEventQueued( somSelf, "Change" ) ){
                _vrPostEvent( somSelf, id_Change );
            }
            break;

        case SB_LINELEFT:
        case SB_LINERIGHT:
        case SB_PAGELEFT:
        case SB_PAGERIGHT:
            _vrGet_Value( somSelf, (PULONG) &val );

            if( nmsg == SB_LINELEFT ){
                val -= _line_increment;
            } else if( nmsg == SB_LINERIGHT ){
                val += _line_increment;
            } else if( nmsg == SB_PAGELEFT ){
                val -= _page_increment;
            } else {
                val += _page_increment;
            }

            if( val < 0 ){
                val = 0;
            } else if( val > 65535 ){
                val = 65535;
            }

            _vrSet_Value( somSelf, (ULONG) val );

            if( !_vrGetEditMode( somSelf ) &&
                !VRIsEventQueued( somSelf, "Change" ) ){
                _vrPostEvent( somSelf, id_Change );
            }

            break;

        case SB_SLIDERTRACK:
            if( !_vrGetEditMode( somSelf ) &&
                !VRIsEventQueued( somSelf, "Track" ) ){
                _vrPostEvent( somSelf, id_Track );

                _vrSet_Value( somSelf, SHORT1FROMMP( mp2 ) );
            }
            break;
    }

    return( 0 );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrWM_VSCROLL
 */

SOM_Scope MRESULT   SOMLINK VRScrollInstance_vrWM_VSCROLL(VRScroll *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    LONG val;
    SHORT nmsg;

    place_holder( msg );
    place_holder( hWnd );
    place_holder( mp1 );

    nmsg = SHORT2FROMMP( mp2 );

    if( _vrGetEditMode( somSelf ) ) return( 0 );

    switch( nmsg ){
        case SB_SLIDERPOSITION:
            if( !VRIsEventQueued( somSelf, "Change" ) ){
                _vrPostEvent( somSelf, id_Change );
            }
            break;

        case SB_LINEUP:
        case SB_LINEDOWN:
        case SB_PAGEUP:
        case SB_PAGEDOWN:
            _vrGet_Value( somSelf, (PULONG) &val );

            if( nmsg == SB_LINEUP ){
                val -= _line_increment;
            } else if( nmsg == SB_LINEDOWN ){
                val += _line_increment;
            } else if( nmsg == SB_PAGEUP ){
                val -= _page_increment;
            } else {
                val += _page_increment;
            }

            if( val < 0 ){
                val = 0;
            } else if( val > 65535 ){
                val = 65535;
            }

            _vrSet_Value( somSelf, (ULONG) val );

            if( !_vrGetEditMode( somSelf ) &&
                !VRIsEventQueued( somSelf, "Change" ) ){
                _vrPostEvent( somSelf, id_Change );
            }

            break;

        case SB_SLIDERTRACK:
            if( !_vrGetEditMode( somSelf ) &&
                !VRIsEventQueued( somSelf, "Track" ) ){
                _vrPostEvent( somSelf, id_Track );

                _vrSet_Value( somSelf, SHORT1FROMMP( mp2 ) );
            }
            break;
    }

    return( 0 );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_LineIncrement
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_LineIncrement(VRScroll *somSelf,
        ULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    if( val > 65535 ){
        val = 65535;
    }

    _line_increment = val;

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_LineIncrement
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_LineIncrement(VRScroll *somSelf,
        PULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    *val = _line_increment;

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_PageIncrement
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_PageIncrement(VRScroll *somSelf,
        ULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    if( val > 65535 ){
        val = 65535;
    }

    _page_increment = val;

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_PageIncrement
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_PageIncrement(VRScroll *somSelf,
        PULONG val)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);

    *val = _page_increment;

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_Track
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_Track(VRScroll *somSelf,
        PRXSTRING rxstr)
{
    return( _vrAddEvent( somSelf, id_Track, rxstr ) );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_Track
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_Track(VRScroll *somSelf,
        PRXSTRING rxstr)
{
    if( !_vrFindEvent( somSelf, id_Track, rxstr ) ){
        VRSetNullRXString( rxstr );
    }

    return( TRUE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrRXMethod_AttachToWindow
 *
 *      Syntax:  ok = VRMethod( obj, 'AttachToWindow' )
 *
 *      When this method is called, the scrollbar object reparents
 *      itself to the frame window.
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrRXMethod_AttachToWindow(VRScroll *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    bool    ok = FALSE;
    SOMAny *window;
    HWND    hWnd, frame;
    bool    is_vert = FALSE;
    USHORT  id;
    BOOL    visible;

    place_holder( argv );
    place_holder( argsused );
    place_holder( rxdata );

    if( argc != 0 ) goto syntax_error;

    /* OK, find the frame window we're a child of... */

    window = _vrFindAncestor( somSelf, NULL );
    if( !window ) goto leave;

    frame = _vrGetOuterWindow( window );
    hWnd  = _vrGetWindowHandle( somSelf );

    is_vert = ( ( _vrGetWindowFlags( somSelf ) & SBS_VERT ) != 0 );

    /* Figure out if the frame window already has the scrollbar */

    id = is_vert ? FID_VERTSCROLL : FID_HORZSCROLL;

    if( WinWindowFromID( frame, id ) ) goto leave;

    /* Coast is clear, so assign a new window ID and then reparent
       the window... */

    _is_frame_control = TRUE;

    WinSetWindowUShort( hWnd, QWS_ID, id );
    WinSetOwner( hWnd, frame );

    _vrGet_Visible( somSelf, &visible );

    if( visible ){
        WinSetParent( hWnd, frame, TRUE );
    } else {
        WinSetParent( hWnd, HWND_OBJECT, TRUE );
    }

    WinSendMsg( frame, WM_UPDATEFRAME,
                MPFROMLONG( FCF_VERTSCROLL | FCF_HORZSCROLL ), 0 );

    ok = TRUE;

  leave:
    VRBooleanToRXString( retstr, ok );
    return( TRUE );

  syntax_error:
    return( FALSE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrSet_Visible
 *
 *    If the scrollbar is attached to the frame window as a frame control,
 *    we have to handle visibility a bit differently:  when the scrollbar
 *    is made invisible, we actually reparent it to HWND_OBJECT.
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrSet_Visible(VRScroll *somSelf,
        BOOL on)
{
    VRScrollData *somThis = VRScrollGetData(somSelf);
    bool ok = FALSE;
    HWND hWnd, frame;
    
    ok = parent_vrSet_Visible( somSelf, on );

    if( ok && _is_frame_control ){
        hWnd  = _vrGetWindowHandle( somSelf );
        frame = WinQueryWindow( hWnd, QW_OWNER );

        if( on ){
            WinSetParent( hWnd, frame, TRUE );
        } else {
            WinSetParent( hWnd, HWND_OBJECT, TRUE );
        }

        WinSendMsg( frame, WM_UPDATEFRAME,
                    MPFROMLONG( FCF_VERTSCROLL | FCF_HORZSCROLL ), 0 );
    }

    return( ok );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRScrollInstance_vrGet_Visible
 */

SOM_Scope bool   SOMLINK VRScrollInstance_vrGet_Visible(VRScroll *somSelf,
        BOOL *on)
{
    return( parent_vrGet_Visible( somSelf, on ) );
}

