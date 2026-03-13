#include<lpc214x.h>

int main()
{
    IODIR0=(1<<0);
	IODIR0=~(1<<1);

    while(1)
    {
	
        if(!(IOPIN0 & (1<<1)))
        {
            IOSET0=1<<0;
		
        }

        else
        {
              IOCLR0=1<<0;
        }
    }
}