void UART_Init(void);			         // ����1��ʼ����9600 /22.1184MHZ
void UART_Send_Str(char *s);	         // �����ַ���
void UART_Send_Num(unsigned long dat);	 // ������ֵ
void UART_Send_StrNum(char *inf,unsigned long dat);	  // �����ַ���+��ֵ
void UART_Send_Hex(unsigned int hex);				  // ����16����(������Χ)
void UART_Send_binary(unsigned char dat);			  // ����2����
