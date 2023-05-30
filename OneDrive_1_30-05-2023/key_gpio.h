// key_gpio
// uses the HPS KEY (button) directly from software

#ifndef KEY_GPIO_H_
#define KEY_GPIO_H_

void KEY_gpio_setup();
	
unsigned int KEY_gpio_pressed();
	
unsigned int KEY_gpio_released();

#endif /*KEY_GPIO_H_*/
