


unsigned int row_val[4]={0x100,0x200,0x400,0x800}
unsigned char data[4][4]={'0','1','2','3','4','5','6','7','8','9','c','a'};

//-----------------------------MAIN-------------------------------------------------------
main()
{

  LPC_PINCON->PINSEL0=0X00000000;            //GPIO
  LPC_GPIO0->FIODIR=0X00000F00;              // rows= output   col=input
  

  LPC_GPIO0->FIOSET1=0X0F;      //ALL ROWS ARE SET (P0.8 - P0.11)


  LPC_GPIOINT->IO0IntEnR|=(F<<4);
  


  NVIC_EnableIRQ(EINT3_IRQn);

  while(1);
}


//----------------------------ISS--------------------------------------

void EINT3_IRQHandler(void)
{
   unsigned int x=LPC_GPIOINT->IO0IntStatR;
 
   switch(x)
  {
    case 0x010: col=0;  break;
    case 0x020: col=1;  break;
    case 0x040: col=2; break;
    case 0x080: col=3; break;
  }   

   
	
   LPC_GPIO0->FIOCLR1=0X0F;   //ROWS SET TO ZERO
  
   for(row=0;row<=3;row++)
   {
      LPC_GPIO0->FIOSET=row_val[i]       //MAKING ROWS HIGH ONE BY ONE
      
      temp=LPC_GPIO0->FIOPIN
      if(!(temp & x))
      {
           lcd_puts(data[row][col])
                  
      }






	return;
}  
