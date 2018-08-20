#include "asf.h"

void _pio_set(Pio *p_pio, const uint32_t ul_mask){
	// __O  uint32_t PIO_SODR;      /**< \brief (Pio Offset: 0x0030) Set Output Data Register */
	
	//*(p_pio + 0x0030)= ul_mask;
	p_pio->PIO_SODR = ul_mask;
}

void _pio_clear(Pio *p_pio, const uint32_t ul_mask){
	
	p_pio->PIO_CODR = ul_mask;
}

void _pio_pull_up(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_pull_up_enable){
	//jeito 1
	//
	if(ul_pull_up_enable){
		p_pio->PIO_PUER = ul_mask;
	}else{
		p_pio->PIO_PUDR = ul_mask;
	}
	//
	
	//jeito 2
	//  __O  uint32_t PIO_PUDR;      /**< \brief (Pio Offset: 0x0060) Pull-up Disable Register */
	//  __O  uint32_t PIO_PUER;      /**< \brief (Pio Offset: 0x0064) Pull-up Enable Register */
	
	/*
	*(p_pio + 0x0060 + 4 * (!!ul_pull_up_enable))= ul_mask;
	*/
}

void _pio_set_output(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_default_level, const uint32_t ul_multidrive_enable, const uint32_t ul_pull_up_enable){
	
	p_pio->PIO_PER = ul_mask;
	p_pio->PIO_OER = ul_mask;
	switch(ul_default_level){
		case 0:
			_pio_clear(p_pio, ul_mask);
			break;
		default:
			_pio_set(p_pio, ul_mask);
			break;
	}
	
	switch(ul_multidrive_enable){
		case 0:
			p_pio->PIO_MDDR = ul_mask;
			break;
			
		default:
			p_pio->PIO_MDER = ul_mask;
			break;
	}
	
	_pio_pull_up(p_pio, ul_mask, ul_pull_up_enable);
}

void _pio_set_input(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_attribute){
	p_pio->PIO_PER = ul_mask;
	p_pio->PIO_ODR = ul_mask;
	
	_pio_pull_up(p_pio, ul_mask, ul_attribute & PIO_PULLUP);
	
	p_pio->PIO_IFDR = ul_mask;
	if(ul_attribute & PIO_DEGLITCH){
		p_pio->PIO_IFER = ul_mask;
		p_pio->PIO_IFSCDR = ul_mask;
	}
	if(ul_attribute & PIO_DEBOUNCE){
		p_pio->PIO_IFER = ul_mask;
		p_pio->PIO_IFSCER = ul_mask;
	}
	
	switch(ul_attribute & PIO_OPENDRAIN){
		case 0:
			p_pio->PIO_MDDR = ul_mask;
			break;
		
		default:
			p_pio->PIO_MDER = ul_mask;
			break;
	}
}