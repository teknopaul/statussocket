Conatins a bit of C to listen on a UDP socket and write to that socket.

This does the same as 
   nc -u -l localhost 9999
and 
   echo helo | nc -u -w1 -q1 localhost 9999 

but without the gip.

