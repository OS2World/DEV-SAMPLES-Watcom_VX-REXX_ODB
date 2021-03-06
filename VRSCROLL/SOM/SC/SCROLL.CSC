#
# This file was generated by the VX-REXX Class Browser
#

#include "somobj.sc"
#include "core.sc"
#include "visible.sc"
#include "primiti.sc"

class: VRScroll,
    local,
    classprefix = VRScrollClass_,
    external prefix = VRScrollInstance_,
    major version = 1,
    minor version = 1;

parent class: VRPrimitive;

passthru: C.h, after;

#define VRSCR_GRABFOCUS (WM_USER + 10)

#ifdef __WATCOMC__
    #pragma aux VRScrollCClassData "*"
    #pragma aux VRScrollClassData "*"
    #pragma aux M_VRScrollCClassData "*"
    #pragma aux M_VRScrollClassData "*"
#endif
endpassthru;


passthru: C.ih, after;

#include "vxrexx.h"

endpassthru;

data:

HWND scrollbar;
BOOL standardsize;
USHORT thumbsize;
USHORT line_increment;
USHORT page_increment;
BOOL is_frame_control;
BOOL orientation_was_set;


methods:


#
# Instance methods
#

    override somInit;
    -- VRScrollInstance_somInit
    override somUninit;
    -- VRScrollInstance_somUninit
    override vrLocalCreateWindow;
    -- VRScrollInstance_vrLocalCreateWindow

#
# REXX Properties
#

    bool vrSet_Orientation( PSZ str );
    -- VRScrollInstance_vrSet_Orientation
    bool vrGet_Orientation( PSZ *str );
    -- VRScrollInstance_vrGet_Orientation
    bool vrSet_StandardSize( BOOL on );
    -- VRScrollInstance_vrSet_StandardSize
    bool vrGet_StandardSize( BOOL *on );
    -- VRScrollInstance_vrGet_StandardSize
    bool vrSet_MinimumValue( ULONG val );
    -- VRScrollInstance_vrSet_MinimumValue
    bool vrGet_MinimumValue( PULONG val );
    -- VRScrollInstance_vrGet_MinimumValue
    bool vrSet_MaximumValue( ULONG val );
    -- VRScrollInstance_vrSet_MaximumValue
    bool vrGet_MaximumValue( PULONG val );
    -- VRScrollInstance_vrGet_MaximumValue
    bool vrSet_Value( ULONG val );
    -- VRScrollInstance_vrSet_Value
    bool vrGet_Value( PULONG val );
    -- VRScrollInstance_vrGet_Value
    bool vrSet_ThumbSize( ULONG val );
    -- VRScrollInstance_vrSet_ThumbSize
    bool vrGet_ThumbSize( PULONG val );
    -- VRScrollInstance_vrGet_ThumbSize
    bool vrSet_Change( PRXSTRING rxstr );
    -- VRScrollInstance_vrSet_Change
    bool vrGet_Change( PRXSTRING rxstr );
    -- VRScrollInstance_vrGet_Change
    bool vrSet_LineIncrement( ULONG val );
    -- VRScrollInstance_vrSet_LineIncrement
    bool vrGet_LineIncrement( PULONG val );
    -- VRScrollInstance_vrGet_LineIncrement
    bool vrSet_PageIncrement( ULONG val );
    -- VRScrollInstance_vrSet_PageIncrement
    bool vrGet_PageIncrement( PULONG val );
    -- VRScrollInstance_vrGet_PageIncrement
    bool vrSet_Track( PRXSTRING rxstr );
    -- VRScrollInstance_vrSet_Track
    bool vrGet_Track( PRXSTRING rxstr );
    -- VRScrollInstance_vrGet_Track
    override vrSet_Visible;
    -- VRScrollInstance_vrSet_Visible
    override vrGet_Visible;
    -- VRScrollInstance_vrGet_Visible

#
# REXX Methods
#

    bool vrRXMethod_AttachToWindow( LONG argc, PRXSTRING argv, PLONG argsused, PRXSTRING retstr, PVRMETHEXTRA rxdata ), generate apply = VRScroll_RXMethod_stub;
    -- VRScrollInstance_vrRXMethod_AttachToWindow

#
# Message handlers
#

    MRESULT vrWM_SIZE( HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2 ), generate apply = VRScroll_WM_stub;
    -- VRScrollInstance_vrWM_SIZE
    MRESULT vrWM_QUERYDLGCODE( HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2 ), apply = VRScroll_WM_stub;
    -- VRScrollInstance_vrWM_QUERYDLGCODE
    override vrWM_SETFOCUS;
    -- VRScrollInstance_vrWM_SETFOCUS
    MRESULT vrVRSCR_GRABFOCUS( HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2 ), apply = VRScroll_WM_stub;
    -- VRScrollInstance_vrVRSCR_GRABFOCUS
    MRESULT vrWM_HSCROLL( HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2 ), apply = VRScroll_WM_stub;
    -- VRScrollInstance_vrWM_HSCROLL
    MRESULT vrWM_VSCROLL( HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2 ), apply = VRScroll_WM_stub;
    -- VRScrollInstance_vrWM_VSCROLL

#
# Class methods
#

    override vrLocalClassInit, class;
    -- VRScrollClass_vrLocalClassInit
    override vrLocalWindowClassInit, class;
    -- VRScrollClass_vrLocalWindowClassInit
    override somInit, class;
    -- VRScrollClass_somInit
    override somUninit, class;
    -- VRScrollClass_somUninit
