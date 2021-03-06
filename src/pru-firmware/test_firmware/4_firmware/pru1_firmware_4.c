typedef int u32;

volatile register unsigned int __R30;
volatile register unsigned int __R31;

__far volatile char C0[0x300] __attribute__((cregister("C0", far)));
#define PINTC(_reg) \
        (*(volatile u32 *)((char *)&C0[_reg]))

#define PINTC_SISR              PINTC(0x0020)
#define PINTC_SICR              PINTC(0x0024)
#define PINTC_SRSR0             PINTC(0x0200)
#define PINTC_SRSR1             PINTC(0x0204)
#define PINTC_SECR0             PINTC(0x0280)
#define PINTC_SECR1             PINTC(0x0284)

#define INCOMING                1 << 22

extern void sc_downcall(int (*handler)(u32 nr, u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4));


static int handle_downcall(u32 id, u32 arg0, u32 arg1, u32 arg2,
                u32 arg3, u32 arg4)
{
        if(id == 0){
                __R30 = 0x00000000;
        }

        else{
                __R30 = 0x0000FFFF;
        }

        return 123;
}


void check_event(void)
{
        if( PINTC_SRSR0 & INCOMING ){
                PINTC_SICR = 22; //clear the system event
                sc_downcall(handle_downcall);
        }
}

int main()
{
        __R30 = 0x00000000; //set all pins to high

        while(1)
        {
                check_event();
        }
        return 0;
}

