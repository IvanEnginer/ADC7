#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void ADC_Init(void)
{
	ADCSRA=((1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1));
	ADMUX=((1<<REFS1)|(1<<REFS0)|(1<<ADLAR));
} 

ISR(ADC_vect)
{
	static unsigned char mode=0;
	
	if (mode==0)
	{
		PORTB=ADCH;
		mode=1;
		ADMUX|=(1<<MUX0);
	}
	
	else {
		
	_delay_ms(100);
	
	if(mode==1)
	
	{
		PORTD=ADCH;
		mode=0;
		ADMUX&=~(1<<MUX0);
	}
		ADCSRA |= (1<<ADSC);	
	}
}

int main(void)
{
	ADC_Init();
	ADCSRA |= (1<<ADSC);
	
	DDRD=0xFF;
	DDRB=0xFF;
	sei();
    while(1)
    {
     asm("nop");   
    }
}