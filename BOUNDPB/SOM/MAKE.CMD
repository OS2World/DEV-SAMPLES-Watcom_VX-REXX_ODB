/**/
"@echo off"
vxodk = value( "VXODK",,"OS2ENVIRONMENT" )
if( vxodk = "" )then do
    say "Please define the VXODK environment variable."
    exit 32000
end
toolkit = value( "TOOLKIT",,"OS2ENVIRONMENT" )
if( toolkit = "" )then do
    say "Please define the TOOLKIT environment variable."
    exit 32000
end
"setlocal"
"cd sc"
"set SMINCLUDE=.;"||vxodk||"\SOM.210\SC;%TOOLKIT%\SC;%SMINCLUDE%;%INCLUDE%"
"set PATH=%VXODK%\BIN;%TOOLKIT%\OS2BIN;%PATH%"
"wmake USE_WMAKE=1 /f vxrexx.mak" arg(1)
"cd .."
"endlocal"
