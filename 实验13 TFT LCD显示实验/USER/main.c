#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"

void LCD_Draw_Circle_Fill(u16 x0,u16 y0,u8 r,u32 color);
void LCD_Draw_Fireman(u16 xPos, u16 yPos, u32 color);
//void LCD_Draw_Fireman_Version2(u16 xPos, u16 yPos, u32 color);
void LCD_Fireman_Shift(u8 mode, u16 xPos, u16 yPos);
static void MX_GPIO_Init(void);

int main(void)
{
	u8 lcd_id[12];				//´æ·ÅLCD ID×Ö·û´®
  HAL_Init();                   	//³õÊ¼»¯HAL¿â    
  Stm32_Clock_Init(336,8,2,7);  	//ÉèÖÃÊ±ÖÓ,168Mhz
	delay_init(168);               	//³õÊ¼»¯ÑÓÊ±º¯Êý
	uart_init(115200);             	//³õÊ¼»¯USART
	MX_GPIO_Init();
	LED_Init();						//³õÊ¼»¯LED	
 	LCD_Init();           			//³õÊ¼»¯LCD FSMC½Ó¿Ú 625 line
	POINT_COLOR=GRAY;     			//»­±ÊÑÕÉ«£ººìÉ«
	u8 type = 0;//0 ÂÌµÆ 1 »ÆµÆ 2 ºìµÆ ¿ØÖÆÉÏÏÂµµÆ
	u8 time1 = 5;
	
	u8 time2 = 5;
	u8 type2 = 0;
	
	u8 time3 = 8;
	u8 type3 = 0;
	
	u8 time4 = 24;
	u8 type4 = 0;
	
	u8 time5 = 16;
	u8 type5 = 0;
	
	u16 distance = 440;
	u16 dis_past = 0;
	u16 xpos_shift = 40; 

	u16 distance_l = 235;
	u16 dis_past_l = 0;
	u16 ypos_shift = 250; 
	
	LCD_Fill(150,0,300,800,GRAY);
	LCD_Fill(0,325,480,475,GRAY);
	//ÌáÊ¾
	LCD_ShowString(104, 20, 300, 24, 16, "Click Key0 All Lights Turn RED");
	LCD_ShowString(140, 390, 200, 24, 24, "ChengHua Avenue");

	//LCD_Draw_Circle_Fill(400,400,200,BLUE);
	u8 r=25;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//½«LCD ID´òÓ¡µ½lcd_idÊý×é¡£
  while(1) 
	{	
		u8 time_num[10];		
		
		POINT_COLOR = BLACK;
		sprintf((char*)time_num,"%02d",time2);
		LCD_ShowString(277,187,200,24,24,time_num);// ÉÏÓÒ
		LCD_ShowString(150,588,200,24,24,time_num);// ÏÂ×ó
		sprintf((char*)time_num,"%02d",time3);
		LCD_ShowString(150,187,200,24,24,time_num);// ÉÏ×ó
		LCD_ShowString(277,588,200,24,24,time_num);// ÏÂÓÒ
		sprintf((char*)time_num,"%02d",time4);
		LCD_ShowString(48,452,200,24,24,time_num);// 
		LCD_ShowString(408,325,200,24,24,time_num);
		sprintf((char*)time_num,"%02d",time5);
		LCD_ShowString(48,325,200,24,24,time_num);// 
		LCD_ShowString(408,452,200,24,24,time_num);//
		if (type < 4) {
		//ÖÐ×ó
		LCD_Draw_Circle_Fill(60,375,r, RED);
		LCD_Draw_Circle_Fill(60,425,r, RED);
		//ÖÐÓÒ
		LCD_Draw_Circle_Fill(420,375,r, RED);
		LCD_Draw_Circle_Fill(420,425,r, RED);
		}
		if (type == 0) {
			LCD_Draw_Circle_Fill(252,200,r, GREEN); // ÉÏÓÒ
			LCD_Draw_Circle_Fill(200,200,r, RED); // ÉÏ×ó
			LCD_Draw_Circle_Fill(200,600,r, GREEN);//ÏÂ×ó
			LCD_Draw_Circle_Fill(252,600,r, RED); //ÏÂÓÒ
			if (dis_past_l <= distance_l) {
				LCD_Fireman_Shift(2,120,ypos_shift);
				ypos_shift += 85;
				dis_past_l += 85;
			}
		} else if (type == 1) {
			LCD_Draw_Circle_Fill(252,200,r, YELLOW);
			LCD_Draw_Circle_Fill(200,600,r, YELLOW);
		} else if (type == 2){
			LCD_Draw_Circle_Fill(252,200,r, RED);
			LCD_Draw_Circle_Fill(200,200,r, GREEN);
			LCD_Draw_Circle_Fill(200,600,r, RED);
			LCD_Draw_Circle_Fill(252,600,r, GREEN);
		} else if (type == 3){
			LCD_Draw_Circle_Fill(200,200,r, YELLOW);
			LCD_Draw_Circle_Fill(252,600,r, YELLOW);
			dis_past  = 0;
			xpos_shift = 40;
		} else {
			LCD_Draw_Circle_Fill(252,200,r, RED);
			LCD_Draw_Circle_Fill(200,200,r, RED);
			LCD_Draw_Circle_Fill(200,600,r, RED);
			LCD_Draw_Circle_Fill(252,600,r, RED);
			if (type == 4) {
				LCD_Draw_Circle_Fill(60,375,r, GREEN);
				LCD_Draw_Circle_Fill(60,425,r, RED);
				LCD_Draw_Circle_Fill(420,375,r, RED);
				LCD_Draw_Circle_Fill(420,425,r, GREEN);
				if (dis_past <= distance) {
					//xpos_shift = 50;
					LCD_Fireman_Shift(1,xpos_shift,250);
					xpos_shift += 80;
					dis_past += 80;
				}
			} else if (type == 5) {
				LCD_Draw_Circle_Fill(60,375,r, YELLOW);
				//LCD_Draw_Circle_Fill(420,375,r, RED);
				LCD_Draw_Circle_Fill(420,425,r, YELLOW);
				//LCD_Draw_Circle_Fill(60,425,r, RED);
			} else if (type == 6) {
				LCD_Draw_Circle_Fill(60,375,r, RED);
				LCD_Draw_Circle_Fill(60,425,r, GREEN);
				LCD_Draw_Circle_Fill(420,375,r, GREEN);
				LCD_Draw_Circle_Fill(420,425,r, RED);
			} else {
				LCD_Draw_Circle_Fill(60,375,r, RED);
				LCD_Draw_Circle_Fill(60,425,r, YELLOW);
				LCD_Draw_Circle_Fill(420,375,r, YELLOW);
				LCD_Draw_Circle_Fill(420,425,r, RED);
				dis_past_l = 0;
				ypos_shift = 250;
			}
		}
		
		time1--;	
		if (time1 == 0) {	
			type = (type + 1) % 8;
			if (type == 0) {
				time1 = 5; // green light 5s;
			} else if (type == 1) {
				time1 = 3; // yellow light 3s;
			} else if (type == 2) {
				time1 = 5; // green light 5s;
			} else if (type == 3){
				time1 = 3;
			}	else if (type == 4){
				time1 = 5;
			}	else if (type == 5) {
				time1 = 3;
			} else if (type == 6) {
				time1 = 5;
			} else {
				time1 = 3;
			}
		}
		
		time2--;
		if (time2 == 0) {
			if (type2 == 0) {
				time2 = 3;
			} else if (type2 == 1) {
				time2 = 24;
			} else {
				time2 = 5;
			}
			type2 = (type2 + 1) % 3; 
		}
		
		time3--;
		if (time3 == 0) {
			if (type3 == 0) {
				time3 = 5;
			} else if (type3 == 1) {
				time3 = 3;
			} else {
				time3 = 24;
			}
			type3 = (type3 + 1) % 3; 
		}
		
		time4--;
		if (time4 == 0) {
			if (type4 == 0) {
				time4 = 5;
			} else if (type4 == 1) {
				time4 = 3;
			} else {
				time4 = 24;
			}
			type4 = (type4 + 1) % 3; 
		}
		
		time5--;
		if (time5 == 0) {
			if (type5 == 0) {
				time5 = 5;
			} else if (type5 == 1) {
				time5 = 3;
			} else {
				time5 = 24;
			}
			type5 = (type5 + 1) % 3; 
		}
			 
		
		delay_ms(1000);	
	} 
}



void LCD_Draw_Circle_Fill(u16 x0,u16 y0,u8 r,u32 color) {
	POINT_COLOR = color; 
	for (u8 i = 10; i <= r; i++) {
		LCD_Draw_Circle(x0,y0,i);
	}
}

void LCD_Draw_Fireman(u16 xPos, u16 yPos, u32 color){
	POINT_COLOR = color;
	u8 r = 4 * 2;
	u8 h = 16 * 2;
	u8 hArm = 5 * 2;
	u8 hFeet = 4 * 2;
	u8 w = 7 * 2;
	LCD_Draw_Circle(xPos, yPos, r);//head
	LCD_DrawLine(xPos, yPos + r, xPos, yPos + h);//ÉíÌå
	LCD_DrawLine(xPos, yPos + r +(h / 2), xPos - w, yPos + r +(h / 2) - hArm);//ÊÖ±Û
	LCD_DrawLine(xPos, yPos + r + (h / 2), xPos + w, yPos + r +(h / 2) - hArm);//ÊÖ±Û
	LCD_DrawLine(xPos, yPos + h, xPos - w, yPos + h + hFeet);//½Å
	LCD_DrawLine(xPos, yPos + h, xPos + w, yPos + h + hFeet);//½Å
}

void LCD_Fireman_Shift(u8 mode, u16 x, u16 y) {
	//ºá×Å×ß ×óµ½ÓÒ
	if (mode == 1) {
		LCD_Draw_Fireman(x,y,GRAY);
		LCD_Draw_Fireman(x + 80,y,BLUE);
	} else if (mode == 2) {
		//ÉÏÏÂ×ß
			LCD_Draw_Fireman(x, y, GRAY);
			LCD_Draw_Fireman(x, y + 85, BLUE);
			//y += 85;
	}
}

//ÒÔÏÂ°´¼ü³õÊ¼»¯ ÖÐ¶Ï

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	 /*Configure GPIO pin : PE2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PF9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0., 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	/* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, -1, -1);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
		u8 r = 25;
		switch(GPIO_Pin)
		{
			case GPIO_PIN_4: 
					//HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
				{
				LCD_Draw_Circle_Fill(252,200,r, RED);
				LCD_Draw_Circle_Fill(200,200,r, RED);
				LCD_Draw_Circle_Fill(200,600,r, RED);
				LCD_Draw_Circle_Fill(252,600,r, RED);
				LCD_Draw_Circle_Fill(60,375,r, RED);
				LCD_Draw_Circle_Fill(60,425,r, RED);
				LCD_Draw_Circle_Fill(420,375,r, RED);
				LCD_Draw_Circle_Fill(420,425,r, RED);
				delay_ms(2000);break;
				}
				case GPIO_PIN_2: 
					//HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
				{
				LCD_Draw_Circle_Fill(252,200,r, GREEN);
				LCD_Draw_Circle_Fill(200,200,r, GREEN);
				LCD_Draw_Circle_Fill(200,600,r, GREEN);
				LCD_Draw_Circle_Fill(252,600,r, GREEN);
				LCD_Draw_Circle_Fill(60,375,r, GREEN);
				LCD_Draw_Circle_Fill(60,425,r, GREEN);
				LCD_Draw_Circle_Fill(420,375,r, GREEN);
				LCD_Draw_Circle_Fill(420,425,r, GREEN);
				delay_ms(2000);
				}
		}		
}

void EXTI4_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

