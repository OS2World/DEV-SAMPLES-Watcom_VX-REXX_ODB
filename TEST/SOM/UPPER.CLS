;
; Class 'VRUpperButton'
;

class VRUpperButton VRPushButton
filepath upper
prefix UPB
<passthru>
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
<endinstancedata>
<rexxmethods>
<endrexxmethods>
<messages>
WM_BUTTON1DBLCLK
<endmessages>
<properties>
Caption saveable [type=cstring] [editGroup=Text] [editEnumValues=] [editType=string]
DoubleClick event saveable [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
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

