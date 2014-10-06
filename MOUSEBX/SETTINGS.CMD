/**/
"set vxversion=200" 
"set vxdllname=MOUSEBX" 
"set vxsom=SOM1"
if value( "VXCOMPILER", ,"OS2ENVIRONMENT") = "" then "set vxcompiler=CSET"
if value( "VXODK", ,"OS2ENVIRONMENT") = "" then "set vxodk="
if value( "TOOLKIT", ,"OS2ENVIRONMENT") = "" then "set toolkit="
if value( "WATCOM", ,"OS2ENVIRONMENT") = "" then "set watcom="
if value( "IBMC", ,"OS2ENVIRONMENT") = "" then "set ibmc="

/*
 * Settings -- Set up environment variables for compiler etc.
 */
 
vxodk = value( 'VXODK',, 'OS2ENVIRONMENT' )
if( vxodk = '' )then do
    say "Please enter a value for the VXODK environment variable.  It should"
    say "point to the directory where the VX-REXX ODK is installed, as in:"
    say "      C:\VXODK"
    say "Or enter 'quit' to abort:"
    pull vxodk
    if( vxodk = 'QUIT' )then exit 32000
    call value 'VXODK', vxodk, 'OS2ENVIRONMENT'
    call value "PATH", Value( "PATH",,"OS2ENVIRONMENT")";"vxodk"\bin", "OS2ENVIRONMENT"
end

toolkit = value( 'TOOLKIT',, 'OS2ENVIRONMENT' )
if( toolkit = '' )then do
    say "Please enter a value for the TOOLKIT environment variable.  It should"
    say "point to the directory where the OS/2 Toolkit is installed, as in:"
    say "      C:\TOOLKT20"
    say "Or enter 'quit' to abort:"
    pull toolkit
    if( toolkit = 'QUIT' )then exit 32000
    call value 'TOOLKIT', toolkit, 'OS2ENVIRONMENT' 
    call value "PATH", Value( "PATH",,"OS2ENVIRONMENT")";"toolkit"\os2bin" , "OS2ENVIRONMENT"
end

compiler = translate( value( "VXCOMPILER", ,"OS2ENVIRONMENT" ) )
if( compiler = 'WATCOM' )then do
    watcom = value( 'WATCOM',, 'OS2ENVIRONMENT' )
    if( watcom = '' )then do
        say "Please enter a value for the WATCOM environment variable.  It should"
        say "point to the directory where WATCOM C/C++ is installed, as in:"
        say "      C:\WATCOM"
        say "Or enter 'quit' to abort:"
        pull watcom
        if( watcom = 'QUIT' )then exit 32000
        call value 'WATCOM', watcom, 'OS2ENVIRONMENT'
	call value "PATH", Value( "PATH",,"OS2ENVIRONMENT")";"watcom"\bin", "OS2ENVIRONMENT"
    end
end; else do
    ibmc = value( 'IBMC',, 'OS2ENVIRONMENT' )
    if( ibmc = '' )then do
        say "Please enter a value for the IBMC environment variable.  It should"
        say "point to the directory where CSet is installed, as in:"
        say "      C:\IBMCPP"
        say "Or enter 'quit' to abort:"
        pull ibmc
        if( ibmc = 'QUIT' )then exit 32000
        call value 'IBMC', ibmc, 'OS2ENVIRONMENT'
	call value "PATH", Value( "PATH",,"OS2ENVIRONMENT")";"ibmc"\bin", "OS2ENVIRONMENT"
    end
end

exit 0

