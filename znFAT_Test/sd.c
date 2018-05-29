#include "sd.h"
#include "myfun.h" 
#include "uart.h"

//��������
//--------------------------------------------------------------
bit is_init;  //�ڳ�ʼ����ʱ�����ô˱���Ϊ1,ͬ�����ݴ��䣨SPI������� 

unsigned char Addr_Mode=0;        // Ѱַ��ʽ��1Ϊ��Ѱַ��0Ϊ�ֽ�Ѱַ��ʹ��ʱ�轫��ַ����9λ��
unsigned char SD_Ver=SD_VER_ERR;  // SD���İ汾
//---------------------------------------------------------------

unsigned char bdata _dat; //�����Ż�ģ��SPI���м�bdata���ͱ���������ȡ����λ
sbit _dat7=_dat^7;
sbit _dat6=_dat^6;
sbit _dat5=_dat^5;
sbit _dat4=_dat^4;
sbit _dat3=_dat^3;
sbit _dat2=_dat^2;
sbit _dat1=_dat^1;
sbit _dat0=_dat^0;

unsigned char IO_SPI_Init(void)  // ��SPI�йس�ʼ��
{
	//P1M1=0xf0;	  // 1111 0000	 // ����P1.5.6.7.8 ��©���
	//P1M0=0xf0;	  // 1111 0000	
	SPI_SO=1;	  // IO���� 	
	return 0;
}

/******************************************************************
���ܣ�IOģ��SPI������һ���ֽ�
������x��Ҫ���͵��ֽ�
      ����is_initΪ1ʱ��д���ٶȷ�������ʼ��SD��SPI�ٶȲ���̫��
 ******************************************************************/

void SD_SPI_WByte(unsigned char x) 
{
	_dat=x;
	
	SPI_SI=_dat7;
	SPI_CLK=0; 
	if(is_init) delay(DELAY_TIME); 
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	
	SPI_SI=_dat6;
	SPI_CLK=0; 
	if(is_init) delay(DELAY_TIME); 
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	
	SPI_SI=_dat5;
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	
	SPI_SI=_dat4;
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME); 
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	
	SPI_SI=_dat3;
	SPI_CLK=0; 
	if(is_init) delay(DELAY_TIME); 
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	
	SPI_SI=_dat2;
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME); 
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	
	SPI_SI=_dat1;
	SPI_CLK=0; 
	if(is_init) delay(DELAY_TIME); 
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	
	SPI_SI=_dat0;
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME);  
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
}

/******************************************************************
���ܣ�IOģ��SPI����ȡһ���ֽ�
���أ����ض������ֽ�
 ******************************************************************/
unsigned char SD_SPI_RByte() //SPI��һ���ֽ�
{  
	SPI_SO=1;
	
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME); 
	_dat7=SPI_SO; 
	
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME);
	_dat6=SPI_SO; 
	
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME);
	_dat5=SPI_SO; 
	
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME);
	_dat4=SPI_SO; 
	
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME); 
	_dat3=SPI_SO; 
	
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME);
	_dat2=SPI_SO; 
	
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME);
	_dat1=SPI_SO;
	
	SPI_CLK=1;
	if(is_init) delay(DELAY_TIME);
	SPI_CLK=0;
	if(is_init) delay(DELAY_TIME);
	_dat0=SPI_SO; 
	
	return (_dat);
}

/******************************************************************
���ܣ���SD��д����
������SD����������6���ֽڣ�pcmd��ָ�������ֽ����е�ָ��
���أ�����д��󣬵��ò��ɹ���������0xff
 ******************************************************************/

unsigned char SD_Write_Cmd(unsigned char *pcmd) 
{
	unsigned char temp,time=0;
	
	SPI_CS=1;
	SD_SPI_WByte(0xff); //��߼����ԣ����û�������ЩSD�����ܲ�֧��   
	SPI_CS=0;
	while(0XFF!=SD_SPI_RByte()); //�ȴ�SD��׼���ã������䷢������

	SD_SPI_WByte(pcmd[0]);
	SD_SPI_WByte(pcmd[1]);
	SD_SPI_WByte(pcmd[2]);
	SD_SPI_WByte(pcmd[3]);
	SD_SPI_WByte(pcmd[4]);
	SD_SPI_WByte(pcmd[5]);
	if(pcmd[0]==0X1C) SD_SPI_RByte(); // �����ֹͣ�������������ֽ�
	do 
	{  
		temp = SD_SPI_RByte();        // һֱ����ֱ�������Ĳ���0xff��ʱ
		time++;
	}while((temp==0xff)&&(time<TRY_TIME)); 
	
	return(temp);
}

 /******************************************************************
���ܣ�SD����ʼ��������ڲ�ͬ��SD������MMC��SD��SDHC����ʼ�������ǲ�ͬ��
���أ����óɹ�������0x00�����򷵻ش�����
 ******************************************************************/
unsigned char SD_Init()	
{  
	unsigned char time=0,temp=0,i=0; 
	unsigned char rbuf[4]={0};
	
	unsigned char pCMD0[6] ={0x40,0x00,0x00,0x00,0x00,0x95}; //CMD0����SD����Ĭ���ϵ���SDģʽ�л���SPIģʽ��ʹSD������IDLE״̬
	unsigned char pCMD1[6] ={0x41,0x00,0x00,0x00,0x00,0x01}; //CMD1��MMC��ʹ��CMD1������г�ʼ��
	unsigned char pCMD8[6] ={0x48,0x00,0x00,0x01,0xAA,0x87}; //CMD8�����ڼ���SD���İ汾�����ɴ�Ӧ���֪SD���Ĺ�����ѹ
	unsigned char pCMD16[6]={0x50,0x00,0x00,0x02,0x00,0x01}; //CMD16������������СΪ512�ֽڣ������������ڳ�ʼ�����֮�������̽�ԵĲ�����
	                                                         //��������ɹ���˵����ʼ��ȷʵ�ɹ�
	unsigned char pCMD55[6]={0x77,0x00,0x00,0x00,0x00,0x01}; //CMD55�����ڸ�֪SD��������ACMD����Ӧ�ò����� CMD55+ACMD41���ʹ��
	                                                         //MMC��ʹ��CMD1�����г�ʼ������SD����ʹ��CMD55+ACMD41�����г�ʼ��
	unsigned char pACMD41H[6]={0x69,0x40,0x00,0x00,0x00,0x01}; //ACMD41,���������ڼ��SD���Ƿ��ʼ����ɣ�MMC���������ô�������2.0��SD��
	unsigned char pACMD41S[6]={0x69,0x00,0x00,0x00,0x00,0x01}; //ACMD41,���������ڼ��SD���Ƿ��ʼ����ɣ�MMC���������ô�������1.0��SD��
	
	unsigned char pCMD58[6]={0x7A,0x00,0x00,0x00,0x00,0x01}; //CMD58�����ڼ���SD2.0������SDHC��������ͨ��SD�������߶�������ַ��Ѱַ��ʽ��ͬ
 
	//******************** ��λSD����ʼ���õ�CMD0��ʹ��SD���л���SPIģʽ********************// 
	IO_SPI_Init();             // ��SPI�й�IO�ڳ�ʼ��
	is_init=1;                 // is_init��Ϊ1����SPI�ٶ�������
	SPI_CS=1;
	for(i=0;i<0x0f;i++)        // ����Ҫ��������74��ʱ���źţ����Ǳ���ģ�����SD��
	{
		SD_SPI_WByte(0xff);    // 120��ʱ��
	}  
	time=0;				
	do
	{ 
		temp=SD_Write_Cmd(pCMD0);     //д��CMD0
		time++;
		if(time==TRY_TIME) 
		{ 
			return(INIT_CMD0_ERROR); //CMD0д��ʧ��
		}
	}while(temp!=0x01);
	//*************************** ��λSD������ ********************************************// 

	if(1==SD_Write_Cmd(pCMD8))      //д��CMD8���������ֵΪ1����SD���汾Ϊ2.0
	{
		rbuf[0]=SD_SPI_RByte(); rbuf[1]=SD_SPI_RByte(); //��ȡ4���ֽڵ�R7��Ӧ��ͨ������֪��SD���Ƿ�֧��2.7~3.6V�Ĺ�����ѹ
		rbuf[2]=SD_SPI_RByte(); rbuf[3]=SD_SPI_RByte(); 
		 
		if(rbuf[2]==0X01 && rbuf[3]==0XAA)  //SD���Ƿ�֧��2.7~3.6V,����������֧��
		{		
			time=0;
			do
			{								   
				SD_Write_Cmd(pCMD55);       // д��CMD55
				temp=SD_Write_Cmd(pACMD41H);   // д��ACMD41�����SD2.0
				time++;
				if(time>=TRY_TIME) 
				{ 
					return(INIT_SDV2_ACMD41_ERROR);//��SD2.0ʹ��ACMD41���г�ʼ��ʱ��������
				}
			}while(temp!=0);	
			
			if(0==SD_Write_Cmd(pCMD58)) //д��CMD58����ʼ����SD2.0
			{
				rbuf[0]=SD_SPI_RByte(); rbuf[1]=SD_SPI_RByte();  //��ȡ4���ֽڵ�OCR������CCSָ������SDHC������ͨ��SD
				rbuf[2]=SD_SPI_RByte(); rbuf[3]=SD_SPI_RByte(); 	
				
				if(rbuf[0]&0x40) 
				{
					SD_Ver=SD_VER_V2HC; //SDHC��	
					Addr_Mode=1; //SDHC��������Ѱַ��ʽ������ط
				}	
				else SD_Ver=SD_VER_V2; //��ͨ��SD����2.0�Ŀ�����SDHC��һЩ��ͨ�Ŀ�				
			}
		}
	}
	else                          // SD V1.0��MMC 
	{
		// SD��ʹ��ACMD41���г�ʼ������MMCʹ��CMD1�����г�ʼ������������һ���ж���SD����MMC
		SD_Write_Cmd(pCMD55);            // д��CMD55
		temp=SD_Write_Cmd(pACMD41S);     // д��ACMD41�����SD1.0
		
		if(temp<=1) //��鷵��ֵ�Ƿ���ȷ�������ȷ��˵��ACMD41������ܣ���ΪSD��
		{
			SD_Ver=SD_VER_V1; //��ͨ��SD1.0����һ����˵�������ᳬ��2G				
			time=0;
			do
			{
				SD_Write_Cmd(pCMD55);//д��CMD55
				temp=SD_Write_Cmd(pACMD41S);//д��ACMD41�����SD1.0
				time++;
				if(time>=TRY_TIME) 
				{ 
					return(INIT_SDV1_ACMD41_ERROR);//��SD1.0ʹ��ACMD41���г�ʼ��ʱ��������
				}
			}while(temp!=0);			 
		}
		else //����ΪMMC	
		{
			SD_Ver=SD_VER_MMC; //MMC��������֧��ACMD41�������ʹ��CMD1���г�ʼ��				
			time=0;
			do
			{ 
				temp=SD_Write_Cmd(pCMD1);//д��CMD1
				time++;
				if(time>=TRY_TIME) 
				{ 
					return(INIT_CMD1_ERROR);//MMC��ʹ��CMD1������г�ʼ���в�������
				}
			}while(temp!=0);			
		}
	}
	
	if(0!=SD_Write_Cmd(pCMD16)) //SD���Ŀ��С����Ϊ512�ֽ�
	{
		SD_Ver=SD_VER_ERR; //������ɹ�����˿�Ϊ�޷�ʶ��Ŀ�
		return INIT_ERROR;
	}	
	
	SPI_CS=1;             // �ر�SD����Ƭѡ 
	SD_SPI_WByte(0xFF);   // ����SD���Ĳ���ʱ�������ﲹ8��ʱ�� 
	
	is_init=0;            // ��ʼ����ϣ���is_init����Ϊ0,Ϊ������Ժ�����ݴ����ٶ�
	
	return 0;              //����0,˵����ʼ�������ɹ�
}  

/****************************************************************************
���ܣ���bufferָ���512���ֽڵ�����д�뵽SD����addr������
������addr:������ַ
      buffer:ָ�����ݻ�������ָ��
���أ����óɹ�������0x00�����򷵻ش�����
      SD����ʼ���ɹ��󣬶�д����ʱ��������SPI�ٶ������������Ч��
 ****************************************************************************/
unsigned char SD_Write_Sector(unsigned long addr,unsigned char *buffer)	//��SD���е�ָ����ַ������д��512���ֽڣ�ʹ��CMD24��24�����
{  
	unsigned char temp,time;
	unsigned char i=0;
	unsigned char pCMD24[]={0x58,0x00,0x00,0x00,0x00,0xff}; //��SD���е����飨512�ֽڣ�һ��������д�����ݣ���CMD24
	
	if(!Addr_Mode) addr<<=9; //addr = addr * 512	�����ַ��������ַ��תΪ�ֽڵ�ַ
	
	pCMD24[1]=addr>>24; //���ֽڵ�ַд�뵽CMD24�ֽ�������
	pCMD24[2]=addr>>16;
	pCMD24[3]=addr>>8;
	pCMD24[4]=addr;		
	time=0;
	do
	{  
		temp=SD_Write_Cmd(pCMD24);
		time++;
		if(time==TRY_TIME) 
		{ 
			return(temp); //����д��ʧ��
		}  
	}while(temp!=0); 	
	while(0XFF!=SD_SPI_RByte()); //�ȴ�SD��׼���ã������䷢��������������� 	
	SD_SPI_WByte(0xFE);          //д�뿪ʼ�ֽ� 0xfe���������Ҫд���512���ֽڵ�����
		
	for(i=0;i<4;i++) //����������Ҫд���512���ֽ�д��SD��������ѭ���������������д���ٶ�
	{
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
	}
	
	SD_SPI_WByte(0xFF); 
	SD_SPI_WByte(0xFF); //�����ֽڵ�CRCУ���룬���ù���	   
	temp=SD_SPI_RByte();   //��ȡ����ֵ
	if((temp & 0x1F)!=0x05) //�������ֵ�� XXX00101 ˵�������Ѿ���SD��������
	{
		return(WRITE_BLOCK_ERROR); //д������ʧ��
	} 	
	while(0xFF!=SD_SPI_RByte());  //�ȵ�SD����æ�����ݱ������Ժ�SD��Ҫ����Щ����д�뵽�����FLASH�У���Ҫһ��ʱ�䣩
						                 //æʱ����������ֵΪ0x00,��æʱ��Ϊ0xff 	
	SPI_CS=1;
	SD_SPI_WByte(0xFF); //����SD���Ĳ���ʱ�������ﲹ8��ʱ��  	
	return(0);		 //����0,˵��д���������ɹ�
} 

/****************************************************************************
���ܣ���ȡaddr������512���ֽڵ�bufferָ������ݻ�����
������addr:������ַ
      buffer:ָ�����ݻ�������ָ��
���أ����óɹ�������0x00�����򷵻ش�����
      SD����ʼ���ɹ��󣬶�д����ʱ��������SPI�ٶ������������Ч��
 ****************************************************************************/

unsigned char SD_Read_Sector(unsigned long addr,unsigned char *buffer)//��SD����ָ�������ж���512���ֽڣ�ʹ��CMD17��17�����
{
	 unsigned char i;
	 unsigned char time,temp;		
	 unsigned char pCMD17[]={0x51,0x00,0x00,0x00,0x00,0x01}; //CMD17���ֽ�����	   
	 if(!Addr_Mode) addr<<=9; //sector = sector * 512	   �����ַ��������ַ��תΪ�ֽڵ�ַ
	
	 pCMD17[1]=addr>>24; //���ֽڵ�ַд�뵽CMD17�ֽ�������
	 pCMD17[2]=addr>>16;
	 pCMD17[3]=addr>>8;
	 pCMD17[4]=addr;	
	
	 time=0;
	 do
	 {  
		temp=SD_Write_Cmd(pCMD17); //д��CMD17
		time++;
		if(time==TRY_TIME) 
		{
			return(READ_BLOCK_ERROR); //����ʧ��
		}
	 }while(temp!=0); 	   			
	 while(SD_SPI_RByte()!= 0xFE); //һֱ����������0xfeʱ��˵���������512�ֽڵ�������
	
	 for(i=0;i<4;i++)	 //������д�뵽���ݻ�������
	 {	
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	  *(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
	 }
	
	 SD_SPI_RByte();
	 SD_SPI_RByte();//��ȡ�����ֽڵ�CRCУ���룬���ù�������	 	
	 SPI_CS=1;
	 SD_SPI_WByte(0xFF); //����SD���Ĳ���ʱ�������ﲹ8��ʱ�� 	
	 return 0;
}

///****************************************************************************
// ���ܣ���addr������ʼ��nsec������д�����ݣ���Ӳ��������д�룩
// ������nsec:������
//       addr:��ʼ������ַ
//       buffer:ָ�����ݻ�������ָ��
// ���أ����óɹ�������0x00�����򷵻ش�����
//       SD����ʼ���ɹ��󣬶�д����ʱ��������SPI�ٶ������������Ч��
// ****************************************************************************/	 
//unsigned char SD_Write_nSector(unsigned long nsec,unsigned long addr,unsigned char *buffer)	
//{  
//	unsigned char temp,time;
//	unsigned long i=0,j=0;		
//	unsigned char pCMD25[6]={0x59,0x00,0x00,0x00,0x00,0x01}; //CMD25������ɶ������д
//	unsigned char pCMD55[6]={0x77,0x00,0x00,0x00,0x00,0x01}; //CMD55�����ڸ�֪SD��������ACMD,CMD55+ACMD23
//	unsigned char pACMD23[6]={0x57,0x00,0x00,0x00,0x00,0x01};//CMD23���������Ԥ����	
//	
//	if(!Addr_Mode) addr<<=9; 	
//	pCMD25[1]=addr>>24;
//	pCMD25[2]=addr>>16;
//	pCMD25[3]=addr>>8;
//	pCMD25[4]=addr;
//	
//	pACMD23[1]=nsec>>24;
//	pACMD23[2]=nsec>>16;
//	pACMD23[3]=nsec>>8;
//	pACMD23[4]=nsec; 
//	
//	if(SD_Ver!=SD_VER_MMC) //�������MMC����������д��Ԥ�������CMD55+ACMD23�����������������д���ٶȻ����
//	{
//		SD_Write_Cmd(pCMD55);
//		SD_Write_Cmd(pACMD23);
//	}
//	
//	time=0;
//	do
//	{  
//		temp=SD_Write_Cmd(pCMD25);
//		time++;
//		if(time==TRY_TIME) 
//		{ 
//			return(WRITE_CMD25_ERROR); //����д��ʧ��
//		}
//	}while(temp!=0); 	
//	while(0XFF!=SD_SPI_RByte()); //�ȴ�SD��׼���ã������䷢��������������� 	
//	for(j=0;j<nsec;j++)
//	{
//		SD_SPI_WByte(0xFC);//д�뿪ʼ�ֽ� 0xfc���������Ҫд���512���ֽڵ�����	
//		
//		for(i=0;i<4;i++) //����������Ҫд���512���ֽ�д��SD��
//		{
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));SD_SPI_WByte(*(buffer++));
//		}
//		
//		SD_SPI_WByte(0xFF); 
//		SD_SPI_WByte(0xFF); //�����ֽڵ�CRCУ���룬���ù���
//		   
//		temp=SD_SPI_RByte();   //��ȡ����ֵ
//		if((temp & 0x1F)!=0x05) //�������ֵ�� XXX00DELAY_TIME1 ˵�������Ѿ���SD��������
//		{
//			return(WRITE_NBLOCK_ERROR); //д������ʧ��
//		}  	
//		while(0xFF!=SD_SPI_RByte());//�ȵ�SD����æ�����ݱ������Ժ�SD��Ҫ����Щ����д�뵽�����FLASH�У���Ҫһ��ʱ�䣩
//							                  //æʱ����������ֵΪ0x00,��æʱ��Ϊ0xff
//	} 	
//	SD_SPI_WByte(0xFD);		
//	while(0xFF!=SD_SPI_RByte());
//	
//	SPI_CS=1;      //�ر�Ƭѡ
//	
//	SD_SPI_WByte(0xFF);//����SD���Ĳ���ʱ�������ﲹ8��ʱ��
//	
//	return(0);		 //����0,˵��д���������ɹ�
//} 
//
///****************************************************************************
// ���ܣ���ȡaddr������ʼ��nsec�����������ݣ���Ӳ����������ȡ��
// ������nsec:������
//       addr:��ʼ������ַ
//       buffer:ָ�����ݻ�������ָ��
// ���أ����óɹ�������0x00�����򷵻ش�����
//       SD����ʼ���ɹ��󣬶�д����ʱ��������SPI�ٶ������������Ч��
// ****************************************************************************/
//
//unsigned char SD_Read_nSector(unsigned long nsec,unsigned long addr,unsigned char *buffer)
//{
//	 unsigned char temp,time;
//	 unsigned long i=0,j=0;		
//	 unsigned char pCMD18[6]={0x52,0x00,0x00,0x00,0x00,0x01}; //CMD18���ֽ�����
//	 unsigned char pCMD12[6]={0x1C,0x00,0x00,0x00,0x00,0x01}; //CMD12��ǿ��ֹͣ����	   
//	 if(!Addr_Mode) addr<<=9; //sector = sector * 512	   �����ַ��������ַ��תΪ�ֽڵ�ַ
//	
//	 pCMD18[1]=addr>>24; //���ֽڵ�ַд�뵽CMD17�ֽ�������
//	 pCMD18[2]=addr>>16;
//	 pCMD18[3]=addr>>8;
//	 pCMD18[4]=addr;	
//	 time=0;
//	 do
//	 {  
//		temp=SD_Write_Cmd(pCMD18); //д��CMD18
//		time++;
//		if(time==TRY_TIME) 
//		{
//			return(READ_CMD18_ERROR); //д��CMD18ʧ��
//		}
//	 }while(temp!=0); 
//	 	 
//	 for(j=0;j<nsec;j++)
//	 {  
//		while(SD_SPI_RByte()!= 0xFE); //һֱ����������0xfeʱ��˵���������512�ֽڵ������� 
//				
//		for(i=0;i<4;i++)	 //������д�뵽���ݻ�������
//		{	
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();*(buffer++)=SD_SPI_RByte();
//		} 		
//		SD_SPI_RByte();
//		SD_SPI_RByte();//��ȡ�����ֽڵ�CRCУ���룬���ù�����
//	 } 
//	 	
//	 SD_Write_Cmd(pCMD12); //д��CMD12���ֹͣ���ݶ�ȡ 	
//	 SPI_CS=1;
//	 SD_SPI_WByte(0xFF); //����SD���Ĳ���ʱ�������ﲹ8��ʱ��	
//	 return 0;
//}
//
//
///******************************************************************
// ���ܣ���SD�����ɸ��������в����������������е����ݴ󲿷����
//       ��Ϊȫ0����Щ��������Ϊȫ0XFF����Ҫʹ�ô˺�������ȷ�ϣ�
// ������addr_sta����ʼ������ַ   addr_end������������ַ
// ���أ����óɹ�������0x00�����򷵻ش�����
// ******************************************************************/
//unsigned char SD_Erase_nSector(unsigned long addr_sta,unsigned long addr_end)
//{
//	unsigned char temp,time;
//	unsigned char i=0;
//	unsigned char pCMD32[]={0x60,0x00,0x00,0x00,0x00,0xff}; //���ò����Ŀ�ʼ������ַ
//	unsigned char pCMD33[]={0x61,0x00,0x00,0x00,0x00,0xff}; //���ò����Ľ���������ַ
//	unsigned char pCMD38[]={0x66,0x00,0x00,0x00,0x00,0xff}; //��������
//	
//	if(!Addr_Mode) {addr_sta<<=9;addr_end<<=9;} //addr = addr * 512	�����ַ��������ַ��תΪ�ֽڵ�ַ
//	
//	pCMD32[1]=addr_sta>>24; //����ʼ��ַд�뵽CMD32�ֽ�������
//	pCMD32[2]=addr_sta>>16;
//	pCMD32[3]=addr_sta>>8;
//	pCMD32[4]=addr_sta;	 
//	
//	pCMD33[1]=addr_end>>24; //����ʼ��ַд�뵽CMD32�ֽ�������
//	pCMD33[2]=addr_end>>16;
//	pCMD33[3]=addr_end>>8;
//	pCMD33[4]=addr_end;	
//	
//	time=0;
//	do
//	{  
//		temp=SD_Write_Cmd(pCMD32);
//		time++;
//		if(time==TRY_TIME) 
//		{ 
//			return(temp); //����д��ʧ��
//		}
//	}while(temp!=0);  
//	
//	time=0;
//	do
//	{  
//		temp=SD_Write_Cmd(pCMD33);
//		time++;
//		if(time==TRY_TIME) 
//		{ 
//			return(temp); //����д��ʧ��
//		}
//	}while(temp!=0);  
//	
//	time=0;
//	do
//	{  
//		temp=SD_Write_Cmd(pCMD38);
//		time++;
//		if(time==TRY_TIME) 
//		{ 
//			return(temp); //����д��ʧ��
//		}
//	}while(temp!=0); 	
//	return 0; 	 
//}
//
//
/****************************************************************************
 ���ܣ���ȡSD��������������ͨ����ȡSD����CSD���������õ�����������
 ���أ�����SD������������
 ****************************************************************************/
unsigned long SD_GetTotalSec(void)
{
	unsigned char pCSD[16];
	unsigned long Capacity;  
	unsigned char n,i;
	unsigned short csize; 	
	unsigned char pCMD9[6]={0x49,0x00,0x00,0x00,0x00,0x01}; //CMD9	
	
	if(SD_Write_Cmd(pCMD9)!=0) //д��CMD9����
	{
		return GET_CSD_ERROR; //��ȡCSDʱ��������
	} 	
	while(SD_SPI_RByte()!= 0xFE); //һֱ����������0xfeʱ��˵���������16�ֽڵ�CSD���� 	
	for(i=0;i<16;i++) pCSD[i]=SD_SPI_RByte(); //��ȡCSD����	
	SD_SPI_RByte();
	SD_SPI_RByte();      // ��ȡ�����ֽڵ�CRCУ���룬���ù�������
	
	SPI_CS=1;
	SD_SPI_WByte(0xFF);  // ����SD���Ĳ���ʱ�������ﲹ8��ʱ�� 
	
	//���ΪSDHC�����������������������淽ʽ����
	if((pCSD[0]&0xC0)==0x40)	 //SD2.0�Ŀ�
	{	
		csize=pCSD[9]+(((unsigned short)(pCSD[8]))<<8)+1;
		Capacity=((unsigned long)csize)<<10;                    // �õ�������	 		   
	}
	else //SD1.0�Ŀ�
	{	
		n=(pCSD[5]&0x0F)+((pCSD[10]&0x80)>>7)+((pCSD[9]&0x03)<<1)+2;
		csize=(pCSD[8]>>6)+((unsigned short)pCSD[7]<<2)+((unsigned short)(pCSD[6]&0x03)<<0x0A)+1;
		Capacity=(unsigned long)csize<<(n-9);                  // �õ�������   
	}
	return Capacity;
}