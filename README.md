Conatins a bit of C to listen on a UDP socket and write to that socket.

This does the same as 
   nc -u -l localhost 9999
and 
   echo helo | nc -u -w1 -q1 localhost 9999 

but without the gip.


The server side can run predefined commands.

/etc/ops.allow defines the commands that are available

    #
    # Commands to run as root
    #

    echo     echo hello world
    reboot   init 6
   
/var/ops/command should have a list of command permitted on this host.

    echo
    reboot

Security implications of this should be obvious.

It is not possible to run arbitrary commands (that would be silly) or to pass arguments.

If you want a more elaborate solution for this problem with security concerns addressed and a mechanism to pass arguments look at nagios.


