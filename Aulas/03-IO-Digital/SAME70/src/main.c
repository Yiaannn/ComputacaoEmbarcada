/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

#include "asf.h"


/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define LED_PIO PIOC
#define LED_PIO_ID 12
#define LED_PIO_PIN 8
#define LED_PIO_PIN_MASK (1 << LED_PIO_PIN)

#define BUT_PIO PIOA
#define BUT_PIO_ID 10
#define BUT_PIO_PIN 11
#define BUT_PIO_PIN_MASK (1 << BUT_PIO_PIN)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void){
	int loopstate;
	
	//initialize the board clock
	sysclk_init();
	
	//Ativa o periferico responsavel pelo controle do LED
	//retorna 0 em sucesso, 1 em erro
	pmc_enable_periph_clk(LED_PIO_ID);
	
	//Ativa o periferico responsavel pelo controle do Botão
	//retorna 0 em sucesso, 1 em erro
	pmc_enable_periph_clk(BUT_PIO_ID);
	
	//Inicializa PC8 como saída
	pio_configure(PIOC, PIO_OUTPUT_0, LED_PIO_PIN_MASK, PIO_DEFAULT);		//Configura o botão	pio_configure(PIOA, PIO_INPUT, BUT_PIO_PIN_MASK, PIO_PULLUP);
	
	//Disativa WatchDog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	loopstate= 0;

	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1) {
		loopstate+= 2*!pio_get(PIOA, PIO_INPUT, BUT_PIO_PIN_MASK);
		
		if(loopstate == 0){

			//Set LED
			pio_clear(PIOC, LED_PIO_PIN_MASK);					delay_ms(200);					//Clear LED			pio_set(PIOC, LED_PIO_PIN_MASK);
			
			delay_ms(200);
		}
		
		if(loopstate == 2){
			loopstate= 5;
			while(loopstate){
				//Set LED
				pio_clear(PIOC, LED_PIO_PIN_MASK);							delay_ms(50);							//Clear LED				pio_set(PIOC, LED_PIO_PIN_MASK);
				
				delay_ms(50);
				
				--loopstate;
			}
			
			loopstate= 1;
		}
	}
	return 0;
}
