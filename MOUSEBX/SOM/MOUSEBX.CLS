;
; Class 'VRMouseBox'
;

class VRMouseBox VRPictureBox
filepath mousebx
prefix MouseBox
<passthru>
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
BOOL enabled;

<endinstancedata>
<rexxmethods>
<endrexxmethods>
<messages>
WM_BUTTON1DOWN
WM_BUTTON2DOWN
WM_MOUSEMOVE
WM_BUTTON1UP
WM_BUTTON2UP
<endmessages>
<properties>
MouseButton1Down event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
MouseButton2Down event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
MouseButton1Up event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
MouseButton2Up event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
MouseMove event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
Enabled create-time saveable optimizable [type=boolean] [editGroup=Style] [editEnumValues=] [editType=boolean]
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
<endinstancemethods>
endclass

