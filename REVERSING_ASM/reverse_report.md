intel syntax

DWORD PTR is used to indicate that the memory location is of 2-word size 
also exists: BYTE WORD and QWORD PTR's

main: 
1) stack allocates 32 bytes of space
2) edi gets rbp-20 value 
3) rsi gets rbp-32 value
4) cmp value of rbp-20 [edi] to 1 and raise flag
5) jumps to L2 if cmp value of edi is greater than 1.

if jumps to L2:
1) content of rbp-32 is moved to rax
2) then incremented by 8
3) rax's stored val moved to reg itself
4) content of rax moved to rdi reg
5) and atoi function is invoked on it
	converting string to int
6) eax gets rbp-12 value
7) rbp-4 and rbp-8 is set to "0"
8) jump to L4:

L4:
1) eax gets rbp-8 value 
2) cmp rbp-12 with eax
		if rbp is lower than 0
1) jl to L5:

if jump to L5:
1) rbp-8 val placed in eax
2) adds rbp-4 to eax value
3) adds to rbp-8 value of 1
4) function returns to L4.

back to L4 after L5:
1) eax gets the value of rbp-4 
2) esi gets the value of eax
3) edi gets the value of LC1 "%d\n"
4) eax gets value of zero
5) printf is invoked
6) eax gets value of zero

if not jumps: (or returns from L2)
1) edi gets LC0 address
2) puts "please enter..."
3) then eax gets the value "1"
4) and program jumps to L3.

The function 1 uses printf then puts a number

rsi+8 which is of qword size, gets the value of rdi

xor eax, eax sets eax value to zero