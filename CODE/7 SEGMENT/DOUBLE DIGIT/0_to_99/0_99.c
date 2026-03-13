#include<LPC214x.h>
void delay();
int main()
{
	int a[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  
    int first,second,k,i;
    IODIR0=0X00000FFF;
    IOCLR0=0X00000FFF;

    while(1)
    {
        for(k=0; k<100; k++)
        {
            first=k/10;
            second=k%10;

            IOSET0=0X00000200;
            IOSET0=a[first];
            delay();
            IOCLR0=0X00000FFF;

            IOSET0=0X00000100;
            IOSET0=a[second];
            delay();
            IOCLR0=0X00000FFF;
        }
    }
}
void delay()
{
    int i,j;
    for(i=0;i<200;i++)
    {
        for(j=0;j<200;j++);
    }
}
