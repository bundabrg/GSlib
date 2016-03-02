# GSlib
Some misc libraries to use with Sming ESP8266

This project assumes the following: -
  * Your ESP has 2 Roms of about 512Kb each in the 1Mb of its flash
  * The rest of the flash is dedicated to SPIFFS
  * You have a web server at 172.x.x.x
  

#GS_Debug 
This provides some simple debugging. It creates an object that can be used like a Serial class (supports printf, print etc) and will
by default write out to the Serial.
  
However once wireless exists it will also write the same output out to a multicast, for now hard coded to 224.1.0.1 port 1223.
  
To listen for multicast on your dev machine the easiest way is to use socat in the following manner: -
  $ socat UDP4-RECVFROM:1223,ip-add-membership=224.1.0.1:<your_own_real_ip>,fork -


So if my machine that I want to listen for log events is IP 192.168.0.1, and my compiler machine (a vagrant sandbox with the toolchain to
compile for the ESP) is 192.168.0.2, then I would use on 192.168.0.1: -
  $ socat UDP4-RECVFROM:1223,ip-add-membership=224.1.0.1:192.168.0.1,fork -


I could test this by starting (either in a new window or on another machine) the following:
  $ socat STDIO UDP4-DATAGRAM:224.1.0.1:1223,range=192.168.0.0/24

which would then multicast anything I type into there to the other machine


#GS_Update
A very simplistic OTA updater. We download from our web site a file 'gs_version', and compare its contents to
a variable GS_BUILD_NUMBER, which is generated at build time. If it is different then we download the appropriate
rom and boot into it.

