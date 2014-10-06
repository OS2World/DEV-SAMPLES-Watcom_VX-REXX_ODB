/*
 * Custom.c
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\Custom.c in preparation for compiling.  New
 * methods will be appended at the end only.
 */

#define INCL_PM

#include "vxrexx.h"
#include "vxfuncs.h"

#define VRCustom_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "Custom.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "Custom.ph"
#include "vxcdata.h"

extern PSZ VRCustomPicturePath;


/*
 *  VRCustomInstance_somInit
 */

SOM_Scope void   SOMLINK VRCustomInstance_somInit(VRCustom *somSelf)
{
    VRCustomData *somThis = VRCustomGetData(somSelf);
    
    _distance = 0;

    parent_somInit(somSelf);
}

/*
 *  VRCustomInstance_somUninit
 */

SOM_Scope void   SOMLINK VRCustomInstance_somUninit(VRCustom *somSelf)
{
    parent_somUninit(somSelf);
}

/*
 *  VRCustomInstance_vrLocalCreateWindow
 */

SOM_Scope HWND   SOMLINK VRCustomInstance_vrLocalCreateWindow(VRCustom *somSelf,
                PBOOL visible)
{
    return (parent_vrLocalCreateWindow(somSelf,visible));
}


bool RXStringToDistUnit ( PRXSTRING str, distunit *unit ){

    if( !unit ) goto error;

    switch( str->strptr[0] ){
        case 'C':
            *unit=DIST_CENTIMETRES;
        break;
        
        case 'M':
            *unit=DIST_METRES;
        break;
        
        case 'K':
            *unit=DIST_KILOMETRES;
        break;
        
        default:
            goto error;
    }
    
    return TRUE;
  error:
    return FALSE;
}


/*
 *  VRCustomInstance_vrRXSet_Distance
 */

SOM_Scope bool   SOMLINK VRCustomInstance_vrRXSet_Distance(VRCustom *somSelf,
                LONG argc,
                PRXSTRING argv,
                PULONG argsused)
{
    ULONG dist ;
    distunit unit;
    place_holder( argsused );
    
    /*
     * Check Preconditions
     */
    if ( !somSelf || !argv || argc<1 || argc>2 ) goto error;
    
   
    /*
     * Convert Parameters
     */
    if (!VRRXStringToULong ( &argv[0], &dist ) ) goto error;
    
    if (argc==2){
        if (!RXStringToDistUnit ( &argv[1], &unit )) goto error;
    }else{
        unit = DIST_CENTIMETRES;
    }
    
    /*
     * Store Data
     */
    return ( _vrSet_Distance( somSelf, dist, unit ) );
    
  error:
    return ( FALSE );
}

/*
 *  VRCustomInstance_vrRXGet_Distance
 */

SOM_Scope bool   SOMLINK VRCustomInstance_vrRXGet_Distance(VRCustom *somSelf,
                LONG argc,
                PRXSTRING argv,
                PULONG argsused,
                PRXSTRING retstr)
{
    ULONG distance;
    distunit unit;
    place_holder( argsused );
    
    /* 
     * Check Parms
     */   
     
    if( !somSelf || argc<0 || argc>1 ) goto error;
    
    if(argc==1){
        if(! RXStringToDistUnit( &argv[0], &unit ) )goto error;
    }else{
        unit = DIST_CENTIMETRES;
    }
    
    /* 
     * Get Data
     */
    
    if( !_vrGet_Distance( somSelf, &distance, unit ) )  goto error;
    
    /* 
     * Return it
     */
    
    if( !VRULongToRXString( distance, retstr, 0 ) ) goto error;
    
    return( TRUE );
  error:
    return( FALSE );
}

ULONG multiplier( distunit unit ){
    ULONG mult;

    switch ( unit ){
        case DIST_CENTIMETRES:
            mult = 1;
            break;
        case DIST_METRES:
            mult = 100;
            break;
        
        case DIST_KILOMETRES:
            mult=100000;
            break;
        default:
            mult = 0;
    }
    
    return mult;
}


/*
 *  VRCustomInstance_vrSet_Distance
 */

SOM_Scope bool   SOMLINK VRCustomInstance_vrSet_Distance(VRCustom *somSelf,
                ULONG dist,
                distunit unit)
{
    VRCustomData *somThis = VRCustomGetData(somSelf);

    ULONG mult = multiplier ( unit );
    if (mult==0) goto error;
   
    _distance = dist * mult;
    return ( TRUE ) ;
    
  error:
    return ( FALSE ) ;
}


/*
 *  VRCustomInstance_vrGet_Distance
 */

SOM_Scope bool   SOMLINK VRCustomInstance_vrGet_Distance(VRCustom *somSelf,
                ULONG *dist,
                distunit unit)
{
    ULONG mult = multiplier( unit );
    VRCustomData *somThis = VRCustomGetData(somSelf);
    
    if(mult==0) goto error;
    
    *dist = _distance / mult;
    return ( TRUE );
    
  error:
    return ( FALSE );
}


/*
 *  VRCustomInstance_vrSave_Distance
 */

SOM_Scope bool   SOMLINK VRCustomInstance_vrSave_Distance(VRCustom *somSelf,
                VRSAVEHANDLE sh)
{
    ULONG dist;
    BOOL ok;

    if(!_vrGet_Distance( somSelf, &dist, DIST_CENTIMETRES )) goto error;
    ok = VRWriteProp( "Distance", &dist, sizeof( dist ), sh );

    return( ok );
  error:
    return( FALSE ); 
}

/*
 *  VRCustomInstance_vrLoad_Distance
 */

SOM_Scope bool   SOMLINK VRCustomInstance_vrLoad_Distance(VRCustom *somSelf,
                VRLOADHANDLE lh)
{
    USHORT len;
    ULONG dist;
    
    if( !VRReadDataLen( &len, lh ) ) goto error;
    if ( len!=sizeof( dist ) ) goto error;
    
    if ( !VRReadData( &dist, len, lh ) )goto error; 
    
    _vrSet_Distance( somSelf, dist, DIST_CENTIMETRES );
    
    return( TRUE );
  error:
    return( FALSE );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
/*
 *  VRCustomClass_vrLocalClassInit

 * Note: The vrLocalClassInit function is defined 
 * in the .ph file for this class....           
 */


/*
 *  VRCustomClass_vrLocalWindowClassInit
 */

SOM_Scope bool   SOMLINK VRCustomClass_vrLocalWindowClassInit(M_VRCustom *somSelf)
{
    return (parent_vrLocalWindowClassInit(somSelf));
}

/*
 *  VRCustomClass_somInit
 */

SOM_Scope void   SOMLINK VRCustomClass_somInit(M_VRCustom *somSelf)
{
    parent_somInit(somSelf);

    get_picturepath( somSelf ) = VRCustomPicturePath;

    if( VRQueryRunMode() == VR_DESIGN_MODE ){
        VRInstallHelp( somSelf );
    }
}

/*
 *  VRCustomClass_somUninit
 */

SOM_Scope void   SOMLINK VRCustomClass_somUninit(M_VRCustom *somSelf)
{
    parent_somUninit(somSelf);
}

