#ifndef __BSP_H__
#define __BSP_H__

/* system clock tick [Hz] */
#define BSP_TICKS_PER_SEC 100U

void bsp_init(void);

uint32_t bsp_tick_ctr(void);

/* delay (polling version) */
void bsp_delay(uint32_t ticks);

void bsp_led_red_on(void);
void bsp_led_red_off(void);

void bsp_led_blue_on(void);
void bsp_led_blue_off(void);

void bsp_led_green_on(void);
void bsp_led_green_off(void);

#endif // __BSP_H__
