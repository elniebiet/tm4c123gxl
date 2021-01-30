#ifndef __BSP_H__
#define __BSP_H__

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

void delay(int time);

#endif // __BSP_H__