#define F_CPU 9600000

#include <avr/io.h>

void adc_init(void)
{
	ADMUX |= (1 << MUX0);
	ADMUX |= (1 << ADLAR);
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

int adc_read(void)
{
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC)); // Wait
	return ADCH;
}

void pwm_init(void)
{
	TCCR0B |= (1 << CS01) | (1 << CS00); // clkdiv 64
	TCCR0A |= (1 << WGM01) | (1 << WGM00); // fast pwm
	TCCR0A |= (1 << COM0B1);
}

void pwm_write(int val)
{
	OCR0B = val;
}

int main(void)
{
	int adc_sample;

	DDRB |= (1 << PB1);

	adc_init();
	pwm_init();

	while (1) {
		adc_sample = adc_read();
		pwm_write(adc_sample);
	}

	return 0;
}

