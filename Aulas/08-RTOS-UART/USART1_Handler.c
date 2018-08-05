void USART1_Handler(void){
	uint32_t ret = usart_get_status(USART_COM);

	BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	char c;

	// Verifica por qual motivo entrou na interrupçcao
	//  - Dadodisponível para leitura
	if(ret & US_IER_RXRDY){

  // -  Transmissoa finalizada
	} else if(ret & US_IER_TXRDY){

	}
}

