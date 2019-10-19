#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit  ad=P1^5;
sbit  start=P1^3;
sbit  beep=P1^2;
sbit  button=P1^4;
uint sw;
uint i=0;
uchar k;
void delay_1(void)//延时函数
{
	uint a=180000;
	while(a--);
}
void delay_2(void)
{
	uint b=80000;
	while(b--);
}
void delay_3(void)
{
	
	uint c=8000;
	while(c--);
}
void delay(uchar t)
{
	uint j;
	for(;t>0;t--)
	for(j=6245;j>0;j--);
}
	
void main(void)
{
	uint p=1;
	TMOD=0xe;//设置计数器工作模式，即受外部中断；计数器；并且为8位自动复位寄存器,二进制即为1110
	TH0=0xff;//设置寄存器的初始值为最大值11111111，则当输入低电平时，触发中断
	TL0=0xff;
	TR0=1;//将T0打开，计数器开始工作
	ET0=1;//启动终断服务
	EA=1; 
	EX0=1;
	EX1=1;
	IT0=1;
	IT1=1;
	k=0xfe;
	beep=0;
	sw=0;
	while(1)//进入循环，此时LED全灭
	{
		P2=0Xff;//11111111
	while(sw==1)//判断 SW电位，若为1则进入循环
	{
		if(start==1)//此时判断START电位，为高则进入IF
		{
			beep=0;
			switch(i%3)
		    {
			    case 0:
			  {
					P2=k;//将LED点亮
	        delay_1();
	        k=_crol_(k,1);
	        break;
				}
			  case 1:
			  {
			    P2=k;//将LED点亮
	        delay_2();
	        k=_crol_(k,1);
			    break;
			  }
			  case 2:
			  {
			    P2=k;//将LED点亮
	        delay_3();
	        k=_crol_(k,1);
				  break;
			  }
	      }
		}
		else beep=1;
	}
}
}
void pause_start() interrupt 2
{
	start=!start;
}
void on_off() interrupt 0
{
	sw=!sw;
	k=0xfe;
	start=1;
	i=0;
}

void adjust_speed() interrupt 1
{
	i++;
}