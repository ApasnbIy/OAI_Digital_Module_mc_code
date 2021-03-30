#include "my_MKO.h"
#include "modbus_data_formater.h"

extern type_mb_data_union mb_data_union; // 
 

void MKO_config_port_out(){
		GPIOE->MODER = 0x55555555; // all outputs
}

void MKO_config_port_in(){
		GPIOE->MODER = 0; // all INPUTS
}

void MKO_Init(void){
		MKO_Reset();
		__HAL_RCC_GPIOE_CLK_ENABLE(); // порты данных
		__HAL_RCC_GPIOG_CLK_ENABLE(); // адрес + управление
		__HAL_RCC_GPIOC_CLK_ENABLE(); // ресет
		GPIOE->PUPDR = 0xAAAAAAAA; 
		GPIOE->OSPEEDR = 0x55555555; // all medium speed
	
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO29|GPIO31|GPIO26|GPIO27|GPIO28; // Enable, PWRite, Addr
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
    GPIO_InitStruct.Pin = GPIO30; // ~ack
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
    GPIO_InitStruct.Pin = GPIO1; // reset pin
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOG, GPIO29|GPIO31, GPIO_PIN_SET);	//установили enable и pwrite на 1
	/* EXTI interrupt init*/
	/* Sets the priority grouping field */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  			{
   				 Error_Handler();
  			}
	MKO_Reset();
}

void MKO_ADDR_SET(uint8_t addr){
	switch(addr){
		case 0:
			HAL_GPIO_WritePin(GPIOG,GPIO26|GPIO27|GPIO28,GPIO_PIN_RESET); //addr0 //addr1 //addr2
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOG,GPIO26,GPIO_PIN_SET);	//addr0
			HAL_GPIO_WritePin(GPIOG,GPIO27|GPIO28,GPIO_PIN_RESET); //addr1
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOG,GPIO27,GPIO_PIN_SET); //addr0 //addr1
			HAL_GPIO_WritePin(GPIOG,GPIO28|GPIO26,GPIO_PIN_RESET); //addr2
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOG,GPIO26|GPIO27,GPIO_PIN_SET);	//addr0 //addr1
			HAL_GPIO_WritePin(GPIOG,GPIO28,GPIO_PIN_RESET); //addr2
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOG,GPIO26|GPIO27,GPIO_PIN_RESET);	//addr0 //addr1
			HAL_GPIO_WritePin(GPIOG,GPIO28,GPIO_PIN_SET); //addr2
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOG,GPIO26|GPIO28,GPIO_PIN_SET);	//addr0 //addr2
			HAL_GPIO_WritePin(GPIOG,GPIO27,GPIO_PIN_RESET); //addr2
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOG,GPIO27|GPIO28,GPIO_PIN_SET); //addr1 //addr2
			HAL_GPIO_WritePin(GPIOG,GPIO26,GPIO_PIN_RESET);	//addr0
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOG,GPIO26|GPIO27|GPIO28,GPIO_PIN_SET);	//addr0//addr1//addr2
			break;
		
	}
}

void MKO_Reset(void){
    HAL_GPIO_WritePin(GPIOC, GPIO1, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOC, GPIO1, GPIO_PIN_SET);
}

void MKO_Exchange(type_MKO_Struct* MKO_Struct_ptr){
	uint8_t i;
	uint16_t temp;
	uint16_t chan;
	
	MKO_Struct_ptr->MKO_Cntrl.Word_clk = 0;
	chan = MKO_Struct_ptr->scaler & 0x02;
	
	MKO_Struct_ptr->MKO_Cntrl.Len = MKO_Struct_ptr->MKO_Data.ComandWord & 0x1F;
	MKO_Struct_ptr->MKO_Data.AnswerWord = 0xFEFE;
	
	if(MKO_Struct_ptr->MKO_Cntrl.Len == 0){MKO_Struct_ptr->MKO_Cntrl.Len = 32;}
	if((MKO_Struct_ptr->MKO_Data.ComandWord & 0x400) == 0) {}
	
	else {memset(MKO_Struct_ptr->MKO_Data.Data, 0, sizeof(MKO_Struct_ptr->MKO_Data.Data));}
	
	// пишем признак что в данных лежит командное слово
	MKO_Struct_ptr->MKO_Cntrl.Cntrl = (0x0040 | (chan<<3));    						// записываем в контрольный регистр матрицы	
	MKO_Write_reg(2,&MKO_Struct_ptr->MKO_Cntrl.Cntrl);										// что будет командное слово 
	MKO_Struct_ptr->MKO_Cntrl.Data = MKO_Struct_ptr->MKO_Data.ComandWord;	// переписываем в регистр текущих данны командное слово
	temp = MKO_Struct_ptr->MKO_Data.ComandWord;	// переписываем в регистр текущих данны командное слово
	
	MKO_Write_reg(0, &temp);										// записываем командное слово в регистр данных матрицы
	// меняем признак что в данных будет слово данных
	MKO_Struct_ptr->MKO_Cntrl.Cntrl = (0x0000 | (chan<<3));					
	MKO_Write_reg(2,&MKO_Struct_ptr->MKO_Cntrl.Cntrl);				
		
	if((MKO_Struct_ptr->MKO_Data.ComandWord & 0x400) == 0) { // запись в устройство
		for(i = 0; i<MKO_Struct_ptr->MKO_Cntrl.Len; i++){
			do { MKO_Read_reg(2,&temp);} while((temp & 0x01) == 0);
			MKO_Write_reg(0,&mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Data.Data[i]);
			htim2.Init.Period = 100;
			MKO_Struct_ptr->MKO_Cntrl.TimeOutFlag = 1;
			HAL_TIM_Base_Start_IT(&htim2);		
		}
	} 
	else{ // чтение из устройства проводится в прерывании
			htim2.Init.Period = 100; // взводим флаг на таймаут
			MKO_Struct_ptr->MKO_Cntrl.TimeOutFlag = 1;
			HAL_TIM_Base_Start_IT(&htim2);
	} 
}


	
void MKO_Write_reg(uint16_t addr, uint16_t* data_ptr){
  volatile type_word_union temp;
	temp.two_half_word.LH_word = *data_ptr;
	MKO_ADDR_SET(addr);  // выставили адрес регистра 
  HAL_GPIO_WritePin(GPIOG, GPIO29|GPIO31, GPIO_PIN_SET);	//установили enable и pwrite на 1
  MKO_config_port_out(); //настроили порт данных на выход
  GPIOE->ODR = temp.word; // выставили данные
  HAL_GPIO_WritePin(GPIOG, GPIO29|GPIO31, GPIO_PIN_RESET);	// установили enable и указатель записи в 0 (показываем что будем писать в регистр)
  while (HAL_GPIO_ReadPin(GPIOG, GPIO30)!=0);
  HAL_GPIO_WritePin(GPIOG, GPIO29|GPIO31, GPIO_PIN_SET);	//установили enable и pwrite на 1
	while (HAL_GPIO_ReadPin(GPIOG, GPIO30)!=1);
	MKO_config_port_in();
}

void MKO_Read_reg(uint16_t addr, uint16_t* data_ptr){
	volatile type_word_union temp;
	MKO_ADDR_SET(addr); 
	HAL_GPIO_WritePin(GPIOG, GPIO29|GPIO31, GPIO_PIN_SET);	//установили enable и pwrite на 1
  MKO_config_port_in(); //настроили порт данных на выход
	 // выставили адрес регистра 0 (контрольный регистр)
  HAL_GPIO_WritePin(GPIOG, GPIO29, GPIO_PIN_RESET);	// установили enable  в 0 (показываем что будем read в регистр)
	while(GPIOG->IDR & 0x020);
  //while(HAL_GPIO_ReadPin(GPIOG, GPIO30));
	__dsb(0); __isb(0);
	temp.word = (uint16_t)GPIOE->IDR; // забрали данные
	*data_ptr = temp.two_half_word.LH_word;
  HAL_GPIO_WritePin(GPIOG, GPIO29|GPIO31, GPIO_PIN_SET);	//установили enable и pwrite на 1
}
	


/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint16_t temp;
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
	if(HAL_GPIO_ReadPin(GPIOG, GPIO25)){
		MKO_Read_reg(0, &temp);
		if(mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Data.ComandWord & 0x400){ //read
			if(mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Cntrl.Word_clk == 0)	
			{	
				mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Data.AnswerWord = temp;
				mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Cntrl.Word_clk++;
				htim2.Init.Period = 100; // взводим флаг на таймаут

			}
			else
			{	
				mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Data.Data[mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Cntrl.Word_clk-1] = temp;
				mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Cntrl.Word_clk++;
				htim2.Init.Period = 100; // взводим флаг на таймаут
			}
			if(mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Cntrl.Word_clk == (mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Cntrl.Len + 1))
			{	
				mb_data_union.mb_data_named.mb_MKO_Struct.scaler &=~0x04;
				HAL_TIM_Base_Stop_IT(&htim2);
			}			

		}
		else{// write
			mb_data_union.mb_data_named.mb_MKO_Struct.MKO_Data.AnswerWord = temp;
			mb_data_union.mb_data_named.mb_MKO_Struct.scaler &=~0x04;
			HAL_TIM_Base_Stop_IT(&htim2);	
		}		
	}
	//led_alt_setup(&mcu_state_led, LED_BLINK, 200, 127, 200);
	
	
  /* 
  NOTE: This function Should not be modified, when the callback is needed,
    the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}
