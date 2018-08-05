/**
 * Mutirão C - Aula 1
 * 5 semestre - Eng. da Computação - Insper
 * Igor/ Hashimoto/ Rafael
 *
 * Processamento de imagem embarcado e exibição no LCD
 *
 * Objetivo :
 *  - Introducao aos cursos :
 *    - Sistemas Hardware Software
 *    - Desafios de Programacao
 *    - Computacao Embarcada
 *  - Introducao a linguagem C
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 *  - Dispositivos : maXTouchXPLAINED PRO conectado ao EXT1
 */

#include "asf.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ioport.h"
#include "image.h"
#include "mutirao.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define IMG_HEIGHT 320u // pxs
#define IMG_WIDTH  320u // pxs

/************************************************************************/
/* VAR globais                                                          */
/************************************************************************/

// Espaco de memoria reservado para armazenar a imagem pos processamento
ili9488_color_t imgOutProcess[IMG_WIDTH][IMG_HEIGHT];

// Variavel global alterada para o valor 1 (pela interrupcao) toda vez
// que o botao SW0  é pressionado, uma vez servido o request deve-se
// atribuir 0 a variavel.
volatile uint8_t buttonFlag = 0;

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

/**
 * Funcao chamada para o processamento de imagem
 * parametros :
 *  in  : imgIn , imagem original no formato IMG_HEIGHT X IMG_WIDTH [px]
 *  out : imgOut, imagem processada no formato IMG_HEIGHT X IMG_WIDTH [px]
 *  in  : imgW  , largura da imagem em pxs
 *  in  : imgH  , altura da imagem em pxs
 */
uint32_t imageProcess(ili9488_color_t imgIn[IMG_WIDTH][IMG_HEIGHT], ili9488_color_t imgOut[IMG_WIDTH][IMG_HEIGHT], int imgW, int imgH){
	uint32_t timeUs;
	int x,y;

	// inicializa contagem do tempo de processamento
	tic();

	// usar memcpy ?
	//for (x=0;x<imgH;x++){
	//	for (y=0;y<imgW;y++){
	//		imgOut[imgH-x][y] = imgIn[x][y];
	//	}
	//}

	for (y=0;y<imgW;y++){
		for (x=0;x<imgH;x++){
			imgOut[imgH-x][y] = imgIn[x][y];
		}
	}

	// retorna tempo de processamento em microsegundos us.
	timeUs = toc();
	return(timeUs);
}

// Funcao principal chamada na inicalizacao do uC.
int main(void){

	uint32_t time;            // variavel para armazenar tempo de processamento
	uint8_t  imageSelect = 1; // variavle para selecao da imagem a ser exibida
                            // quando o botao for pressionado
                            // 1 = imagem processada
                            // 0 = imagem orignal

	// inicializa placa e seus perifericos
	initBoardMutirao();

	// exibe imagem orignal, tempo de processamento suprimido.
	imgShow(imgRaw, 0);

	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1) {

		// se buttonFlag = 1 existe alteracao no estado do botao
		if(buttonFlag){

			// Verificamos qual imagem deve ser exibida (toggle)
			// se imageSelect = 1, processar e exibir img processada.
			if(imageSelect){
				// chama a funcao para processamento de imagem, resultando
				// na matriz imgOutProcess
				time = imageProcess(imgRaw, imgOutProcess, IMG_HEIGHT, IMG_WIDTH);

				// exibe imagem processada e seu tempo de processamento
				imgShow(imgOutProcess, time);

				// toggle na variavel, proximo request do botao
				// exibir imagem orignal.
				imageSelect = 0;
			}
			// se imageSelect = 0, exibir img original (imgRaw)
			else{
				// exibe imagem original, tempo de processamento é suprimido.
				imgShow(imgRaw, 0);

				// toggle na variavel, proximo requisicao do botao
				// exibir imagem processada.
				imageSelect = 1;
			}

			// A requisicao foi tratada, devemos agora zerar a flag.
			buttonFlag = 0;
		}
	}
	return 0;
}
