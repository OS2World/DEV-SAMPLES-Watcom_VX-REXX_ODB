/**/

call "..\settings.cmd"

vxodk = value( "VXODK",,"OS2ENVIRONMENT" )
compiler = Value( "vxcompiler", ,"OS2ENVIRONMENT" )
version = Value( "vxversion", , "OS2ENVIRONMENT" )
dllname = Value( "vxdllname", , "OS2ENVIRONMENT" ) 
som = Value( "vxsom", , "OS2ENVIRONMENT" )

if( vxodk = "" )then do
    say "Please define the VXODK environment variable."
    exit 32000
end
toolkit = value( "TOOLKIT",,"OS2ENVIRONMENT" )
if( toolkit = "" )then do
    say "Please define the TOOLKIT environment variable."
    exit 32000
end

"@echo off"
"setlocal"
"cd sc"

if( som = 'SOM2' )then do
    "set SMINCLUDE=.;"||vxodk||"\SOM."version"\SC;%SOMBASE%\INCLUDE;%SMINCLUDE%;%INCLUDE%"
    "set PATH=%VXODK%\BIN;%SOMBASE%\BIN;%TOOLKIT%\OS2BIN;%PATH%"
    if( compiler = 'CSET' )then do
         "nmake /nologo SOM2=1 /f vxrexx.mak" arg(1)
    end;else do
    "wmake USE_WMAKE=1 SOM2=1 /f vxrexx.mak" arg(1)
    end
end; else do
    "set SMINCLUDE=.;"||vxodk||"\SOM."version"\SC;%TOOLKIT%\SC;%SMINCLUDE%;%INCLUDE%"
    "set PATH=%VXODK%\BIN;%TOOLKIT%\OS2BIN;%PATH%"
    if( compiler = 'CSET' )then do
    "nmake /nologo /f vxrexx.mak" arg(1)
    end; else do
    "wmake USE_WMAKE=1 /f vxrexx.mak" arg(1)
    end
end

"cd .."
"endlocal"
