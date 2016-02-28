#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

unsigned int SPWM[95]={ 0, 1, 4, 10, 17, 26, 37, 49, 62, 77, 93, 109,125, 141, 157, 173, 
	                     187, 201, 213, 224, 233, 240, 246, 249,
                  	    250, 249, 246, 240, 233, 224, 213, 201, 188, 173, 157, 141,
	                     125, 109, 93, 77, 63, 49, 37, 26, 17, 10, 4, 1};
	  
void PWMinit(void)
	{
	 TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<COM00); 	 //Set timer0 to fPWM
	 TCCR2|=(1<<WGM20)|(1<<WGM21)|(1<<COM21)|(1<<CS20)|(1<<COM20);   //Set timer2 to fPWM
	 TCCR1A|=(1<<WGM10)|(1<<COM1A1)|(1<<COM1A0);                     //Set timer1 to 8bit fPWM, no prescaller, 
	 TCCR1B|=(1<<WGM12)| (1<<CS10) ;                                 //OC1A set to 1 when count=OCR1A
	 DDRD|=(1<<PD7)|(1<<PD5);                                        //set OC0,OC2,OC1A pins 
    	DDRB|=(1<<PB3);
	

	}
int main(void)
{
    
	PWMinit();
	 int sineArraySize = sizeof(SPWM)/sizeof(int);                    
   int phaseShift = sineArraySize / 3;               //find sPWM value when sine is 120deg
   uint8_t phase1=0;
   uint8_t phase2=phaseShift;                         //shift phase2 120deg 
   uint8_t phase3=(phaseShift*2);					 //shift phase3 240deg
  
   while (1)
    {
		OCR0 = SPWM[phase1];                      
		phase1++;
		 OCR2 = SPWM[phase2];
		phase2++;
		 OCR1A=SPWM[phase3];
		 phase3++;
		
		 if(phase1==95)                
		 {
    		phase1=0;
		 }
	  if(phase2==95)
         {
	     phase2=0;
         }
          if(phase3==95)
        {
   	       phase3=0;
         }
		 
		 _delay_ms(10);  // speed control
     }
}

