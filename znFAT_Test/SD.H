#ifndef __SDX_H__
#define __SDX_H__
#include "STC15W4K.H"
sbit SPI_CS =P1^4; // SD��Ƭѡ 	    ����
sbit SPI_SI =P1^5; // SD��ͬ������  ����
sbit SPI_SO =P1^7; // SD��ͬ������  ���	
sbit SPI_CLK=P1^6; // SD��ͬ��ʱ��  ����
				   
#define DELAY_TIME 2000 //SD���ĸ�λ���ʼ��ʱSPI����ʱ����������ʵ�������޸���ֵ����������SD����λ���ʼ��ʧ��
#define TRY_TIME 100   //��SD��д������֮�󣬶�ȡSD���Ļ�Ӧ����������TRY_TIME�Σ������TRY_TIME���ж�������Ӧ��������ʱ��������д��ʧ��

//��غ궨��
//-------------------------------------------------------------
#define SD_VER_ERR     0X00				 // �޷�ʶ��İ汾
#define SD_VER_MMC     0X01				 // �汾�ţ�MMC
#define SD_VER_V1      0X02				 // �汾�ţ�SD1.0
#define SD_VER_V2      0X03			     // �汾�ţ�SD2.0(��ͨSD)
#define SD_VER_V2HC    0X04				 // �汾�ţ�SD2.0(������SDHC)

#define INIT_ERROR                  0x01 //��ʼ������
#define INIT_CMD0_ERROR             0x02 //CMD0����
#define INIT_CMD1_ERROR             0x03 //CMD1����
#define INIT_SDV2_ACMD41_ERROR	    0x04 //ACMD41����
#define INIT_SDV1_ACMD41_ERROR	    0x05 //ACMD41����

#define WRITE_CMD24_ERROR           0x06 //д��ʱ����CMD24����
#define WRITE_BLOCK_ERROR           0x07 //д�����

#define READ_BLOCK_ERROR            0x08 //�������

#define WRITE_CMD25_ERROR           0x09 //���������дʱ����CMD25����
#define WRITE_NBLOCK_ERROR          0x0A //�������дʧ��

#define READ_CMD18_ERROR            0x0B //����������ʱ����CMD18����
 
#define GET_CSD_ERROR               0x0C //��CSDʧ�� 

//-------------------------------------------------------------
unsigned char SD_Init();                                                 //SD����ʼ��
unsigned char SD_Write_Sector(unsigned long addr,unsigned char *buffer); //��buffer���ݻ������е�����д���ַΪaddr��������
unsigned char SD_Read_Sector(unsigned long addr,unsigned char *buffer);	 //�ӵ�ַΪaddr�������ж�ȡ���ݵ�buffer���ݻ�������
unsigned char SD_Write_nSector(unsigned long nsec,unsigned long addr,unsigned char *buffer); //��buffer���ݻ������е�����д����ʼ��ַΪaddr��nsec������������
unsigned char SD_Read_nSector(unsigned long nsec,unsigned long addr,unsigned char *buffer); //��buffer���ݻ������е�����д����ʼ��ַΪaddr��nsec������������
unsigned char SD_Erase_nSector(unsigned long addr_sta,unsigned long addr_end);
unsigned long SD_GetTotalSec(void);                                     //��ȡSD������������

#endif