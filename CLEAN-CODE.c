#include <lpc17xx.h>
#include<math.h>
#define RS_CTRL  0x08000000  //P0.27
#define EN_CTRL  0x10000000  //P0.28
#define DT_CTRL  0x07800000  //P0.23 to P0.26 data lines
void lcd_init(void);
void wr_cn(void);
void clr_disp(void);
void delay_lcd(unsigned int);
void lcd_com(void);						   
void wr_dn(void);
void lcd_data(void);
void clear_ports(void);
void lcd_puts(unsigned char );
 unsigned long int temp1=0, temp2=0 ;
 unsigned char val[4][4]={'0','1','2','3','4','5','6','7','8','9','c','k'};
 unsigned char temp[3];
 unsigned	int counter,number[10],i,j,bno_count;
 unsigned int result=0;
 
 //-----KEYBOARD--------
 
 void key_lcd(void);
  void scan(void);
 void disp(void);
 unsigned char col,row,flag;
 unsigned long int i,var1,temp,temp3,temp2;

 


 int main(void)
 {
	SystemInit();
	SystemCoreClockUpdate();
//-----------KEYBOARD INIT------------------------   
	 
	LPC_PINCON->PINSEL3 &= 0xFFC03FFF; //P1.23 to P1.26 MADE GPIO
	LPC_PINCON->PINSEL3 &= 0xF00FFFFF; //P2.10 t P2.13 made GPIO
	LPC_GPIO2->FIODIR |= 0x00003C00; //made output P2.10 to P2.13 (rows)
	LPC_GPIO1->FIODIR &= 0xF87FFFFF; //made input P1.23 to P1.26 (cols) 
	  
//---------------LCD INIT--------------------------------	 
  lcd_init();				
	delay_lcd(3200);
	temp1 = 0x80;			//1st message on LCD 1st line
	lcd_com();
	delay_lcd(800);
	 
//------------------------------------------------ADD -----------------------------------------
 
  for(bno_count=0;bno_count<10;bno_count++)    //10 BCD NUMBERS
 { //-----ENTER THE CLEAR DISPLAY CODE
	 
	 
   for(counter=0;counter<3;counter++)
   {
	  delay_lcd(500000);      //MAIN DELAY
	  key_lcd();
	
   }
	
	 for(j=0;j<3;j++)                          //storing the num in number array
	 {
		 number[bno_count]+=((int)temp[j])*pow(10,2-j);
		 if(j==2)
			 result+=number[bno_count];
	 } 
 }
  //---ENTER CLEAR DISP AND DISPLAY RESULT
}


/* -------------START DELETE---------------------------
 void key_lcd()
 {

 while(1)
	{ 
		for(row=0;row<4;row++)
			{ 
				if(row == 0)
				temp = 0x00000400;
				else if(row == 1)
				temp = 0x00000800;
				else if(row == 2)
				temp = 0x00001000;
				else if(row == 3)
				temp = 0x00002000;
			
				LPC_GPIO2->FIOPIN = temp;
				flag = 0;
				scan();
				if(flag == 1)
				{ 
					disp();
					delay_lcd(5000);
				break;
				}
			} 
			
			if(flag==1)
			break;
		
    }	 
	  
 }*/	 
 
 //---------------------------------------------SCAN & DISPLAY--------------------------------------------------------

 
 
  void scan(void)
 {
 	unsigned long temp3;

	temp3 = LPC_GPIO1->FIOPIN;	
	temp3 &= 0x07800000;
	if(temp3 != 0x00000000)
	{
			flag = 1;
			if (temp3 ==0x00800000)
				col=0;
			else if (temp3==0x01000000)
				col=1;
			else if (temp3==0x02000000)
				col=2;
			else if (temp3==0x04000000)
				col=3;
   
	}
	
 }

*/    --------  END -----------








 void disp()
 { 
/*	 if(val[row][col]=='c')
	 { counter--;
		 temp1=0x04;
		 delay_lcd(800);                        //CLEAR 
		 lcd_com();
		 delay_lcd(1000);
		 return;
	 }
*/	 
	 temp[counter]=val[row][col]
	 lcd_puts(val[row][col]);
 } 
 
  void lcd_puts(unsigned char d)
 {
    unsigned int i=0;
    temp1 = d;
    lcd_data();

    return;
 }
 
	 
//------------------"IGNORE"------------INIT & CONFIG (LCD)--------------------------------------------------------------------

 void lcd_init()
 {

  LPC_PINCON->PINSEL1 &= 0xFC003FFF;  //P0.23 to P0.28

  LPC_GPIO0->FIODIR |= DT_CTRL;	
	LPC_GPIO0->FIODIR |= RS_CTRL;	
	LPC_GPIO0->FIODIR |= EN_CTRL;	
        
  clear_ports();
	delay_lcd(3200);

	temp2 = (0x30<<19);
	wr_cn();	   
	delay_lcd(30000); 
		
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);	 
		
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);

	temp2 = (0x20<<19);
	wr_cn();
	delay_lcd(30000);

	temp1 = 0x28;
	lcd_com();
	delay_lcd(30000);
		
	temp1 = 0x0F;		
	lcd_com();
	delay_lcd(800);
	
	temp1 = 0x06;
	lcd_com();
	delay_lcd(800);
	
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(10000);
	
	temp1 = 0x80;
	lcd_com();
	delay_lcd(800);
    return;
 }

 void lcd_com(void)
 {
	temp2 = temp1 & 0xf0;//move data (26-8+1) times : 26 - HN place, 4 - Bits
	temp2 = temp2 << 19;//data lines from 23 to 26
	wr_cn();
	temp2 = temp1 & 0x0f; //26-4+1
	temp2 = temp2 << 23; 
	wr_cn();
	delay_lcd(1000);
    return;
 }

void wr_cn(void)                        //write command reg
 { 	 
	clear_ports();
	LPC_GPIO0->FIOPIN = temp2;		// Assign the value to the data lines    
    LPC_GPIO0->FIOCLR = RS_CTRL;		// clear bit RS
	LPC_GPIO0->FIOSET = EN_CTRL;   	// EN=1
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;		 		// EN =0
    return;
    
 }

 void lcd_data(void)
 {             
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 19;
    wr_dn();
    temp2= temp1 & 0x0f;	
    temp2= temp2 << 23;
    wr_dn();
    delay_lcd(1000);	
    return;
 } 

 void wr_dn(void)
 {  	  
	clear_ports();

	LPC_GPIO0->FIOPIN = temp2;		// Assign the value to the data lines    
	LPC_GPIO0->FIOSET = RS_CTRL;	// set bit  RS
	LPC_GPIO0->FIOSET = EN_CTRL;   	// EN=1
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;	// EN =0
    return;
 }

 void delay_lcd(unsigned int r1)
 {
  	unsigned int r;
  	for(r=0;r<r1;r++);
    return;
 }

 void clr_disp(void)
 {
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(10000);
    return;
 }
 void clear_ports(void)
 {
    /* Clearing the lines at power on */
	LPC_GPIO0->FIOCLR = DT_CTRL; //Clearing data lines
	LPC_GPIO0->FIOCLR = RS_CTRL;  //Clearing RS line
	LPC_GPIO0->FIOCLR = EN_CTRL; //Clearing Enable line
        
    return;
 }

