# send-netdata

Test APIs include send, sendto, sendmsg, write.

# reuseaddr-test
# TODO:
# 1，get host ip automatically
# 2，use cmake to compile *.cc files

  Test option SO_REUSEADDR at listening socket on both Mac( BSD kernel ) and Linux.
  On Mac, just need set the second TCP socket, and it can bind the wildcard 
address(0.0.0.0)/specific address and port(if the first socket is bind to wildcard 
address, the second socket bind to specific address on the same port will success).
  On Linux, have to set both the first and second socket, then the second can bind 
success. The reason is the Linux is more restrictive than Mac.
