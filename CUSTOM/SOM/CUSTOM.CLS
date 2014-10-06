;
; Class 'VRCustom'
;

class VRCustom VREntryField
filepath Custom
prefix CUST
<passthru>
typedef enum { DIST_CENTIMETRES, DIST_METRES, DIST_KILOMETRES } distunit;
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
ULONG distance; /* centimetres */

<endinstancedata>
<rexxmethods>
<endrexxmethods>
<messages>
<endmessages>
<properties>
Distance saveable [getargs=ULONG *dist, distunit unit] [setargs=ULONG dist, distunit unit] [type=custom] [editGroup=Distance] [editEnumValues=] [editType=string]
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

