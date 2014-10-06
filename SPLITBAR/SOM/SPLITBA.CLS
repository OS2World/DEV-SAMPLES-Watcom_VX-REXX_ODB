;
; Class 'VRSplitBar'
;

class VRSplitBar VRPrimitive
filepath splitba
prefix SPLIT
parent_is_virtual
<passthru>
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
BOOL  is_vertical;
TWIPS height;
BOOL  orientation_was_set;
BOOL  standard_size;
BOOL  draw_ends;
ULONG mode;

<endinstancedata>
<rexxmethods>
<endrexxmethods>
<messages>
WM_PAINT
WM_MOUSEMOVE
WM_SIZE
WM_BUTTON1DOWN
<endmessages>
<properties>
Orientation create-time read-only saveable [type=cstring] [editGroup=Style] [editEnumValues=;Horizontal;Vertical] [editType=enumerated type]
Height create-time saveable optimizable [type=dimension] [editGroup=Size] [editEnumValues=] [editType=string]
StandardSize create-time saveable [type=boolean] [editGroup=Size] [editEnumValues=] [editType=boolean]
DrawEnds create-time saveable [type=boolean] [editGroup=Style] [editEnumValues=] [editType=boolean]
Mode create-time saveable [type=cstring] [editGroup=Style] [editEnumValues=;AutoMove;Manual;Static] [editType=enumerated type]
Move event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
BackColor saveable hidden [type=cstring] [editGroup=Color] [editEnumValues=] [editType=color]
ForeColor saveable hidden [type=cstring] [editGroup=Color] [editEnumValues=] [editType=color]
Caption saveable hidden [type=cstring] [editGroup=Text] [editEnumValues=] [editType=string]
Font saveable hidden [type=cstring] [editGroup=Text] [editEnumValues=] [editType=font]
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
vrLocalCreateWindow [HWND] PBOOL visible
vrHandleNotify [MRESULT] HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2
<endinstancemethods>
endclass

