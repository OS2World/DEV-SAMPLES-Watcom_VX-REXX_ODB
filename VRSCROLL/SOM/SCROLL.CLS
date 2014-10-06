;
; Class 'VRScroll'
;

class VRScroll VRPrimitive
filepath scroll
prefix SCR
parent_is_virtual
<passthru>
#define VRSCR_GRABFOCUS (WM_USER + 10)
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
HWND scrollbar;
BOOL standardsize;
USHORT thumbsize;
USHORT line_increment;
USHORT page_increment;
BOOL is_frame_control;
BOOL orientation_was_set;

<endinstancedata>
<rexxmethods>
AttachToWindow
<endrexxmethods>
<messages>
WM_SIZE
WM_QUERYDLGCODE
WM_SETFOCUS
VRSCR_GRABFOCUS
WM_HSCROLL
WM_VSCROLL
<endmessages>
<properties>
Orientation create-time read-only saveable [type=cstring] [editGroup=Style] [editEnumValues=;Horizontal;Vertical] [editType=enumerated type]
StandardSize create-time saveable [type=boolean] [editGroup=Size] [editEnumValues=] [editType=boolean]
MinimumValue saveable [type=whole] [editGroup=Value] [editEnumValues=] [editType=string]
MaximumValue saveable [type=whole] [editGroup=Value] [editEnumValues=] [editType=string]
Value saveable [type=whole] [editGroup=Value] [editEnumValues=] [editType=string]
ThumbSize saveable [type=whole] [editGroup=Value] [editEnumValues=] [editType=string]
Change event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
LineIncrement saveable [type=whole] [editGroup=Value] [editEnumValues=] [editType=string]
PageIncrement saveable [type=whole] [editGroup=Value] [editEnumValues=] [editType=string]
Track event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
Caption saveable hidden [type=cstring] [editGroup=Text] [editEnumValues=] [editType=string]
Click event saveable hidden [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
Font saveable hidden [type=cstring] [editGroup=Text] [editEnumValues=] [editType=font]
Visible create-time saveable optimizable [type=boolean] [editGroup=Style] [editEnumValues=] [editType=boolean]
<endproperties>
<classmethods>
vrLocalClassInit [bool] 
vrLocalWindowClassInit [bool] 
somInit [void] 
somUninit [void] 
<endclassmethods>
<instancemethods>
somInit [void] 
somUninit [void] 
vrLocalCreateWindow [HWND] HWND myparent, LONG argc, PRXSTRING argv
<endinstancemethods>
endclass

