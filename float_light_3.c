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
void delay_1(void)//��ʱ����
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
	TMOD=0xe;//���ü���������ģʽ�������ⲿ�жϣ�������������Ϊ8λ�Զ���λ�Ĵ���,�����Ƽ�Ϊ1110
	TH0=0xff;//���üĴ����ĳ�ʼֵΪ���ֵ11111111��������͵�ƽʱ�������ж�
	TL0=0xff;
	TR0=1;//��T0�򿪣���������ʼ����
	ET0=1;//�����նϷ���
	EA=1; 
	EX0=1;
	EX1=1;
	IT0=1;
	IT1=1;
	k=0xfe;
	beep=0;
	sw=0;
	while(1)//����ѭ������ʱLEDȫ��
	{
		P2=0Xff;//11111111
	while(sw==1)//�ж� SW��λ����Ϊ1�����ѭ��
	{
		if(start==1)//��ʱ�ж�START��λ��Ϊ�������IF
		{
			beep=0;
			switch(i%3)
		    {
			    case 0:
			  {
					P2=k;//��LED����
	        delay_1();
	        k=_crol_(k,1);
	        break;
				}
			  case 1:
			  {
			    P2=k;//��LED����
	        delay_2();
	        k=_crol_(k,1);
			    break;
			  }
			  case 2:
			  {
			    P2=k;//��LED����
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