#include "znfat/ZNFAT.H"
#include "sd.h"
#include "uart.h"
#include "string.h"
unsigned int myTimer=0,first,last;
struct znFAT_Init_Args idata Init_Args; // ��ʼ����������
struct FileInfo idata fileinfo;         // �ļ���Ϣ����
unsigned char buf[21]={0};
void port_mode()            // �˿�ģʽ
{
	P0M1=0x00; P0M0=0x00;P1M1=0x00; P1M0=0x00;P2M1=0x00; P2M0=0x00;P3M1=0x00; P3M0=0x00;
	P4M1=0x00; P4M0=0x00;P5M1=0x00; P5M0=0x00;P6M1=0x00; P6M0=0x00;P7M1=0x00; P7M0=0x00; 
}
void Timer0Init(void)		//@22.1184MHz
{
	AUXR &= 0x7F;		
	TMOD &= 0xF0;		
	TL0 = 0xCD;		
	TH0 = 0xF8;		
	TF0 = 0;		
	TR0 = 1;		
	 ET0 = 1;
}
UINT32 fileNum=0;
int main()
{ 
	//unsigned int res=0;
	int test=0,i=0;
	unsigned int res=0,len=0; 
	Timer0Init();
	port_mode();	                   // ����IO����Ϊ׼˫����������ʽ��
	UART_Init(); 					   // �����ʣ�9600 /22.1184MHZ
	UART_Send_Str("�����������\r\n");
	znFAT_Device_Init();                     // �洢�豸��ʼ��
	UART_Send_Str("SD����ʼ�����\r\n");
	znFAT_Select_Device(0,&Init_Args);       // ѡ���豸
	res=znFAT_Init();      // �ļ�ϵͳ��ʼ��	 
	if(!res)               // �ļ�ϵͳ��ʼ���ɹ�
	{
		UART_Send_Str("�ļ�ϵͳ��ʼ���ɹ�\r\n");
		UART_Send_StrNum("DBR������ַ:",Init_Args.BPB_Sector_No);   
		UART_Send_StrNum("�ܴ洢����(K�ֽ�):",Init_Args.Total_SizeKB); 
		UART_Send_StrNum("ÿ�����ֽ�(��):",Init_Args.BytesPerSector); 
		UART_Send_StrNum("FAT������:",Init_Args.FATsectors);  
		UART_Send_StrNum("ÿ������(��):",Init_Args.SectorsPerClust); 
		UART_Send_StrNum("��һFAT����:",Init_Args.FirstFATSector); 
		UART_Send_StrNum("��Ŀ¼��ʼ����:",Init_Args.FirstDirSector); 
		UART_Send_StrNum("FSINFO������ַ:",Init_Args.FSINFO_Sec);
		UART_Send_StrNum("��һ���д�:",Init_Args.Next_Free_Cluster);
		UART_Send_StrNum("ʣ����д�:",Init_Args.Free_nCluster); 
	}
	else                  // �ļ�ϵͳ��ʼ��ʧ��
	{
		UART_Send_StrNum("�ļ�ϵͳ��ʼ��ʧ�� , ������:",res);
	}	
	res=znFAT_Modify_Name(&fileinfo,"/unsend*.txt","12345.txt",0,1);
	if(!res)
	{
		UART_Send_Str("�޸ĳɹ���");
	}else
	{
		UART_Send_StrNum("������룺",res); 
	}
	first=myTimer;
	addFAT_Find_File_Num(&fileNum,"/test");
	znFAT_Flush_FS();     // ˢ���ļ�ϵͳ
	
	UART_Send_StrNum("file num is :",fileNum);
	UART_Send_StrNum("\ntime is ",last-first);
	UART_Send_StrNum("\n times",i);
	while(1);
	return 0;
} 

void timer0() interrupt 1 
{
	myTimer++;
}



