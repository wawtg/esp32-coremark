# esp32-coremark
Porting the coremark bench mark to the espressif esp32 platform

Original sources: https://github.com/eembc/coremark

I tried to port the coremark bench mark to the esp32

I started copying linux/core_portme.h and linux/core_portme.c into the main directory

Apart from adding debugging output, I "hardwired" the command line arguments (argc, argv).

Forced it to execute all three benchmark algorithms (since leaving one out leads to uninitialised pointers):

in core_main.c:

results[0].execs=ALL_ALGORITHMS_MASK;

in core_portme.h:

typedef float ee_f32; // instead of double, since 4 byte data type is expected

#define COMPILER_FLAGS ""

Currently it crashes with a Stack smashing protect failure.

See log:

ets Jun  8 2016 00:22:57

rst:0x1 (POWERON_RESET),boot:0x17 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0018,len:4
load:0x3fff001c,len:5140
load:0x40078000,len:9684
ho 0 tail 12 room 4
load:0x40080400,len:6240
entry 0x4008070c
Hello world!
This is ESP32 chip with 2 CPU cores, WiFi/BT/BLE, silicon revision 1, 4MB external flash
sizeof = 2, ee_s16
sizeof = 2, ee_u16
sizeof = 4, ee_s32
sizeof = 4, ee_f32
sizeof = 1, ee_u8
sizeof = 4, ee_u32
sizeof = 4, ee_u32
sizeof = 4, size_t
argv[0] = '0x0'
argv[1] = '0x0'
argv[2] = '0x66'
argv[3] = '0'
argv[4] = '7'
argv[5] = '7'
Arg[0]=0x0
Arg[1]=0x0
Arg[2]=0x66
Arg[3]=0
Arg[4]=7
Arg[5]=7
malloc(2000) = 3ffb8a9c
Initialized list:
[0000,8080][0001,5b5b][0002,5252][0003,4949][0004,4040][0005,3f3f][0007,2d2d][000f,6d6d][0017,2d2d][0108,2424][0110,6464][0118,2424][0209,1b1b][0211,5b5b][0219,1b1b][030a,1212][0312,5252][031a,1212][040b,0909][0413,4949][041b,0909][050c,0000][0514,4040][051c,0000][060d,7f7f][0615,3f3f][0706,3636][070e,7676][0716,3636][7fff,ffff]
A=3ffb8d38, B=3ffb8dda, C=3ffb8e7c
Matrix A [9x9]:
2,4,6,8,10,12,14,16,18
20,22,24,26,28,30,32,34,36
38,40,42,44,46,48,50,52,54
56,58,60,62,64,66,68,70,72
74,76,78,80,82,84,86,88,90
92,94,96,98,100,102,104,106,108
110,112,114,116,118,120,122,124,126
128,130,132,134,136,138,140,142,144
146,148,150,152,154,156,158,160,162
Matrix B [9x9]:
1,2,3,4,5,6,7,8,9
10,11,12,13,14,15,16,17,18
19,20,21,22,23,24,25,26,27
28,29,30,31,32,33,34,35,36
37,38,39,40,41,42,43,44,45
46,47,48,49,50,51,52,53,54
55,56,57,58,59,60,61,62,63
64,65,66,67,68,69,70,71,72
73,74,75,76,77,78,79,80,81
State: 666,0
State Input: 5012,5012,35.54400,35.54400,5.500e+3,5.500e+3,T0.3e-1F,1234,1234,1234,.1234500,.1234500,-.123e-2,-.123e-2,-T.T++Tq,-874,-874,-874,-110.700,-110.700,-87e+832,-87e+832,1T3.4e4z,+122,+122,+122,+0.64400,+0.64400,+0.6e-12,+0.6e-12,34.0e-T^,5012,501
Stack smashing protect failure!

abort() was called at PC 0x400d1938 on core 0
0x400d1938: __stack_chk_fail at /home/volker/Dokoki/sparkfun/esp-idf-v3.3/components/esp32/stack_check.c:36


Backtrace: 0x4008974b:0x3ffb8780 0x40089a40:0x3ffb87b0 0x400d1938:0x3ffb87e0 0x400d4051:0x3ffb8800 0x400d53a1:0x3ffb8950 0x400d441b:0x352e352c
0x4008974b: invoke_abort at /home/volker/Dokoki/sparkfun/esp-idf-v3.3/components/esp32/panic.c:681

0x40089a40: abort at /home/volker/Dokoki/sparkfun/esp-idf-v3.3/components/esp32/panic.c:681

0x400d1938: __stack_chk_fail at /home/volker/Dokoki/sparkfun/esp-idf-v3.3/components/esp32/stack_check.c:36

0x400d4051: printf at /home/volker/Dokoki/sparkfun/coremark/main/ee_printf.c:598

0x400d53a1: core_init_state at /home/volker/Dokoki/sparkfun/coremark/main/core_state.c:165

0x400d441b: coremark_main at /home/volker/Dokoki/sparkfun/coremark/main/core_main.c:197


Entering gdb stub now.
