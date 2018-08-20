/*
 * aula4driver.h
 *
 * Created: 8/20/2018 9:20:29 PM
 *  Author: Alexandre
 */ 


#ifndef AULA4DRIVER_H_
#define AULA4DRIVER_H_

void _pio_set(Pio *p_pio, const uint32_t ul_mask);
void _pio_clear(Pio *p_pio, const uint32_t ul_mask);
void _pio_pull_up(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_pull_up_enable);
void _pio_set_output(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_default_level, const uint32_t ul_multidrive_enable, const uint32_t ul_pull_up_enable);
void _pio_set_input(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_attribute);



#endif /* AULA4DRIVER_H_ */