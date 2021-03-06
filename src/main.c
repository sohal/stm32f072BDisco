#include "timer.h"
#include "led.h"
#include "usart.h"
#include "button.h"
#include "spi.h"
// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
static uint32_t BLINK_ON_TICKS 	= (TIMER_FREQUENCY_HZ * 3 / 4);
static uint32_t BLINK_OFF_TICKS = (TIMER_FREQUENCY_HZ * 1 / 4);

// ----- main() ---------------------------------------------------------------

int
main(int argc, char* argv[])
{
	led_Init(BLUE);
	led_Init(GREEN);
	led_Init(RED);
	led_Init(ORANGE);
	usart_Init();
	timer_start();
	button_Init();
	spi_Init();
	uint8_t hi[] = "hello";
	usart_Send(hi, sizeof(hi));

	while (1)
	{
		led_ON(ORANGE);
		led_OFF(BLUE);
		timer_sleep(BLINK_ON_TICKS);
		led_OFF(ORANGE);
		led_ON(BLUE);
		timer_sleep(BLINK_OFF_TICKS);
		if(0U == spi_Recv(hi, 5))
		{
			spi_Reset();
			led_ON(RED);
		}
	}
	// Infinite loop, never return.
}
