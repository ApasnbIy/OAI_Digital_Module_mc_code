#include "MPP_Module.h"


extern DAC_HandleTypeDef hdac;

void TIM_MPP_interrupt(type_MPP_Parametres* MPP){
	
	if(((MPP->Flag & 0x01) != 0 ) && (MPP->Pack_number>0)){ // проверяем что запусщен флаг, и что пакеты еще не все отправлены
			if(MPP->Number_period >0){ //
					MPP->Pack_period--;
					if((MPP->Period_cycler == MPP->Period_leng) && ((MPP->Flag & 0x02) != 0 )){
						if(MPP->Channel == 0){
							HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R, MPP->V_high);
						}
						else if(MPP->Channel == 1){
							HAL_DAC_SetValue(&hdac,DAC_CHANNEL_2,DAC_ALIGN_12B_R, MPP->V_high);
						}
						MPP->Period_cycler--;
					}
					else if((MPP->Period_cycler == MPP->Period_leng) && ((MPP->Flag & 0x02) == 0 )){
						if(MPP->Channel == 0){
							HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R, MPP->V_low);
						}
						else if(MPP->Channel == 1){
							HAL_DAC_SetValue(&hdac,DAC_CHANNEL_2,DAC_ALIGN_12B_R, MPP->V_low);
						}
						MPP->Period_cycler--; 
						MPP->Number_period--;
					} 
					else MPP->Period_cycler--;
					
					if((MPP->Period_cycler == 0) && ((MPP->Flag &0x02) == 0 )){ 
						MPP->Period_cycler = MPP->Period_leng;
						MPP->Flag |= 0x02;
					}
					else if((MPP->Period_cycler == 0) && ((MPP->Flag &0x02) != 0 )){ 
						MPP->Period_cycler = MPP->Period_leng;
						MPP->Flag &= ~0x02;
					}
				}
				else if(MPP->Number_period == 0){
					MPP->Pack_period--; 
					
					if(MPP->Pack_period ==0){
						MPP->Pack_period = MPP->Pack_period_original;
						MPP->Number_period = MPP->Number_period_original;
						MPP->Pack_number--;
						if(MPP->Pack_number ==0){
							MPP->Flag &= ~0x01;
						}			
					}	
				}			
	}
}
