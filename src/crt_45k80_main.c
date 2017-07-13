
#include    <pic18.h>

#include 		"crt_45k80_main.h"
#include        "cpu18f45k80.h"
#include		"you_can.h"

unsigned    int		msec=0;

bit bVirt_RxGood = 0;
unsigned int Virt_RxGoodTimer = 0;


void    PortInit(void)
{
	TRISA=0;
	TRISB=0;
	TRISC=0;
	TRISD=0;
	TRISE=0;

  	LATA=0xff;	
  	LATB=0xff;	
  	LATC=0xff;	
  	LATD=0xff;	
  	LATE=0xff;	
}


/*
// Timer 기능 구현 	 
*/
void main(void)
{
	unsigned char i;	
    
    di();
    Initial();
    PortInit();
    Timer0Init(); 
    Can1Init();
    ei();

	msec=0;
	IdPt = (LocalNumber * HOST_DATA_RECOD) + RCV_DATA;

    while (1)
	{ 		
        CLRWDT();

        if (CanTxAct)
        {
           	Can1TxData(); 
            CanTxAct = 0;
			LED_TX=!LED_TX;
        }	

		// can rx 데이타 수신 했을 때 
		if (CanRx_GOOD)
		{
			CanRx_GOOD = FALSE;		
			LED_RX = !LED_RX; 			
		}

		
    }
}

	

void interrupt isr(void)
{
   
    if( TMR0IF )		
    {    
        TMR0IF = 0;
        TMR0L=MSEC_L;
        TMR0H=MSEC_H;    

        msec++;

        if(msec>1000){
            msec=0;			
        } 
    }

    if(PIR5 > 0)
	{
        Can1Interrupt();
    }	
}




