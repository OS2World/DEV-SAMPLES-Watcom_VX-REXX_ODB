/*
 * BoundPB.c
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\BoundPB.c in preparation for compiling.  New
 * methods will be appended at the end only.
 */

#define INCL_PM

#include "vxrexx.h"
#include "vxfuncs.h"

#define VRBoundPushButton_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "BoundPB.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "BoundPB.ph"
#include "vxcdata.h"

#ifndef NDEBUG
#include <stdio.h>
#define Dbg(x)  printf x
#endif

extern PSZ VRBoundPushButtonPicturePath;


/*
 *  VRBoundPushButtonInstance_somInit
 */

SOM_Scope void   SOMLINK VRBoundPushButtonInstance_somInit(VRBoundPushButton *somSelf)
{
    VRBoundPushButtonData *somThis = VRBoundPushButtonGetData(somSelf);
    
    _IgnoreVRSet_Caption = FALSE;
    parent_somInit(somSelf);
}

/*
 *  VRBoundPushButtonInstance_somUninit
 */

SOM_Scope void   SOMLINK VRBoundPushButtonInstance_somUninit(VRBoundPushButton *somSelf)
{
    parent_somUninit(somSelf);
}

/*
 *  VRBoundPushButtonInstance_vrLocalCreateWindow
 */

SOM_Scope HWND   SOMLINK VRBoundPushButtonInstance_vrLocalCreateWindow(VRBoundPushButton *somSelf,
        PBOOL visible)
{
    return (parent_vrLocalCreateWindow(somSelf,visible));
}

/*
 *  VRBoundPushButtonInstance_vrSet_Query
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonInstance_vrSet_Query(VRBoundPushButton *somSelf,
        PSZ str)
{
    return (parent_vrSet_Query(somSelf,str));
}

/*
 *  VRBoundPushButtonInstance_vrGet_Query
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonInstance_vrGet_Query(VRBoundPushButton *somSelf,
        PSZ *str)
{
    return (parent_vrGet_Query(somSelf,str));
}

/*
 *  VRBoundPushButtonInstance_vrSet_QueryColumns
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonInstance_vrSet_QueryColumns(VRBoundPushButton *somSelf,
        PSZ str)
{
    return (parent_vrSet_QueryColumns(somSelf,str));
}

/*
 *  VRBoundPushButtonInstance_vrGet_QueryColumns
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonInstance_vrGet_QueryColumns(VRBoundPushButton *somSelf,
        PSZ *str)
{
    return (parent_vrGet_QueryColumns(somSelf,str));
}


/*
 *  VRBoundPushButtonInstance_vrRXMethod_DataAvailable
 *
 *  ok = VRMethod( pb, "DataAvailable", query, reason, columnHandle )
 *
 *  NOTE: The Query object passes NULL for the rxdata argument.
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonInstance_vrRXMethod_DataAvailable(VRBoundPushButton *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    VRBoundPushButtonData *somThis = VRBoundPushButtonGetData(somSelf);
    bool        ok = FALSE;
    int         colHandle;
    SOMAny      *query;
    RXSTRING    value;
    char        *reason;
    
    place_holder( rxdata );
    place_holder( argsused );

    /*  Parse arguments
    */
    if( ( argc != 3 ) ||
        !RXVALIDSTRING( argv[0] ) ||
        !VRRXStringToSOMObject( &argv[0], &query, 0 ) ||
        !RXVALIDSTRING( argv[1] ) ||
        !RXVALIDSTRING( argv[2] ) ) {
        Dbg(( "BoundPushButton DataAvailable: bad parms given\n" ));
        goto leave;
    }
    reason = RXSTRPTR( argv[1] );
    colHandle = atoi( RXSTRPTR( argv[2] ) );
    
    Dbg(( "BoundPushButton DataAvailable: query=%p, reason=%s, column=%p\n",
             query, reason, colHandle ));
 
     
    _IgnoreVRSet_Caption = TRUE;
    
    if( stricmp( reason, "close" ) == 0 || stricmp( reason, "close" == 0 ) ) {     // Clear/Close
        _vrSet_Caption( somSelf, "" );
        if( stricmp( reason, "close" ) == 0 ) {
            _vrSetQueryObject( somSelf, NULL );
        }
        ok = TRUE;
    }
    else {
        /*  Invoke the DataGet method
        */
        _vrSetQueryObject( somSelf, query );
        MAKERXSTRING( value, NULL, 0 );

        ok = VRInvokeREXXMethod( query, "DataGet", 1, &argv[2], &value, NULL );

        if( ok ) {
            _vrSet_Caption( somSelf, value.strptr );
            VRMemFree( value.strptr );
        }

#ifdef DEBUG
        else {
            char *status;
            Dbg(( "BoundPushButton dataAvailable failed.\n" ));
            _vrGet_Caption( query, &status );
            if( status ) {
               Dbg(( "BoundPushButton dataAvailable: status = %s\n", status ));
               VRMemFree( status );
            }
            goto leave;
        }
#endif
    }

    VRBooleanToRXString( retstr, ok );
    ok = TRUE;
    
leave:
    _IgnoreVRSet_Caption = FALSE;
    return( ok );    
}

/*
 *  VRBoundPushButtonInstance_vrRXMethod_DataRequest
 *
 *  ok = VRMethod( pb, "DataRequest", query, columnHandle )
 *
 *  NOTE: The Query object passes NULL for the rxdata argument.
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonInstance_vrRXMethod_DataRequest(VRBoundPushButton *somSelf,
        LONG argc,
        PRXSTRING argv,
        PLONG argsused,
        PRXSTRING retstr,
        PVRMETHEXTRA rxdata)
{
    bool        ok = FALSE;
    RXSTRING    value;
    PSZ         caption = NULL;
    SOMAny      *query;
    RXSTRING    parm[2];
//  VRBoundPushButtonData *somThis = VRBoundPushButtonGetData(somSelf);

    place_holder( argsused );
    place_holder( rxdata );
    VRBoundPushButtonMethodDebug("VRBoundPushButton","VRBoundPushButtonInstance_vrRXMethod_DataRequest");


    /*  Parse arguments
    */
    if( ( argc != 2 ) ||
        !RXVALIDSTRING( argv[0] ) ||
        !VRRXStringToSOMObject( &argv[0], &query, 0 ) ||
        !RXVALIDSTRING( argv[1] ) ) {
        Dbg(( "BoundPushButton DataRequest: no parms given!\n" ));
        goto leave;
    }

    
    /*  Get the current caption of the push button
    */ 
    ok = _vrGet_Caption( somSelf, &caption );
    if (!ok) goto leave;

    /*  Pass the current value to the Query object using the DataSet method
    */
    value.strptr = NULL;
    value.strlength = 0;

    parm[0] = argv[1];
    parm[1].strptr = caption;
    parm[1].strlength = strlen( caption );

    ok = VRInvokeREXXMethod( query, "DataSet", 2, &parm, &value, NULL );

    if( value.strptr ) {
        VRMemFree( value.strptr );
    }

    VRBooleanToRXString( retstr, TRUE );
    ok = TRUE;
    
leave:
    if( caption ) {
        VRMemFree( caption );
    }
    return( ok );
}



#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
/*
 *  VRBoundPushButtonClass_vrLocalClassInit

 * Note: The vrLocalClassInit function is defined 
 * in the .ph file for this class....           
 */


/*
 *  VRBoundPushButtonClass_vrLocalWindowClassInit
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonClass_vrLocalWindowClassInit(M_VRBoundPushButton *somSelf)
{
    return (parent_vrLocalWindowClassInit(somSelf));
}

/*
 *  VRBoundPushButtonClass_somInit
 */

SOM_Scope void   SOMLINK VRBoundPushButtonClass_somInit(M_VRBoundPushButton *somSelf)
{
    parent_somInit(somSelf);

    get_picturepath( somSelf ) = VRBoundPushButtonPicturePath;

    if( VRQueryRunMode() == VR_DESIGN_MODE ){
        VRInstallHelp( somSelf );
    }
}

/*
 *  VRBoundPushButtonClass_somUninit
 */

SOM_Scope void   SOMLINK VRBoundPushButtonClass_somUninit(M_VRBoundPushButton *somSelf)
{
    parent_somUninit(somSelf);
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRBoundPushButtonInstance_vrSet_Caption
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonInstance_vrSet_Caption(VRBoundPushButton *somSelf,
                PSZ str)
{
    bool    ok;
    SOMAny  *query;
    VRBoundPushButtonData *somThis = VRBoundPushButtonGetData(somSelf);

    if( !_IgnoreVRSet_Caption ) {
        query = _vrGetQueryObject( somSelf );
        VRInvokeREXXMethod( query, "DataChanged", 0, NULL, NULL, NULL );
    }

    ok = parent_vrSet_Caption( somSelf,str );
    return ( ok );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRBoundPushButtonInstance_vrGet_Caption
 */

SOM_Scope bool   SOMLINK VRBoundPushButtonInstance_vrGet_Caption(VRBoundPushButton *somSelf,
                PSZ *str)
{
    return (parent_vrGet_Caption(somSelf,str));
}
