
#include "main.h"

void MX_MPP_Module_DMA_Init(void)
{

  /* DMA controller clock enable */
  //__HAL_RCC_DMA2_CLK_ENABLE();
	__HAL_RCC_DMA1_CLK_DISABLE();	
  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  //HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
	//HAL_NVIC_DisableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  //HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  //HAL_NVIC_DisableIRQ(DMA1_Stream6_IRQn);
	
 
  

}
