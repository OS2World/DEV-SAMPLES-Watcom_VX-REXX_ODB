;
; Class 'VRBoundPushButton'
;

class VRBoundPushButton VRPushButton
filepath BoundPB
prefix BPB
<passthru>
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
BOOL IgnoreVRSet_Caption;

<endinstancedata>
<rexxmethods>
DataAvailable
DataRequest
<endrexxmethods>
<messages>
<endmessages>
<properties>
Query saveable [type=cstring] [editGroup=Database] [editEnumValues=] [editType=string]
QueryColumns saveable [type=cstring] [editGroup=Database] [editEnumValues=] [editType=string]
Caption saveable [type=cstring] [editGroup=Text] [editEnumValues=] [editType=string]
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

