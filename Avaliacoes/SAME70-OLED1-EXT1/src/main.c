/**
 *	Avaliacao intermediaria 
 *	Computacao - Embarcada
 *        Abril - 2018
 * Objetivo : criar um Relogio + Timer 
 * Materiais :
 *    - SAME70-XPLD
 *    - OLED1
 *
 * Exemplo OLED1 por Eduardo Marossi
 * Modificacoes: 
 *    - Adicionado nova fonte com escala maior
 */
#include <asf.h>

#include "oled/gfx_mono_ug_2832hsweg04.h"
#include "oled/gfx_mono_text.h"
#include "oled/sysfont.h"

int main (void)
{
	board_init();
	sysclk_init();
	delay_init();
	gfx_mono_ssd1306_init();
	
	gfx_mono_draw_filled_circle(115, 5, 5, GFX_PIXEL_SET, GFX_WHOLE);
    gfx_mono_draw_string("14:03PM", 0, 0, &sysfont);
	
	while(1) {
	
	}
}
