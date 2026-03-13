#include<LPC214x.h>
void delay()
{
    int i,j;
    for(i=0;i<2000;i++)
    {
        for(j=0;j<2000;j++);
    }
}
int main()
{
    int n;
    IODIR0=0X000000FF;
    IOCLR0=0X000000FF;

    while(1)
    {
        int a[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
        for(n=9; n>=0; n--)
        {
            IOSET0=a[n];
            delay();
            IOCLR0=a[n];
        }
    }
}
