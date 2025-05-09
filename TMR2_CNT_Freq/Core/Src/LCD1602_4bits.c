#include <LCD1602_4bits.h>

#include "stm32f1xx_hal.h"

/********* Definição dos PINOS do LCD ***********/

/***** Pino RS do LCD *****/
#define RS_Pin GPIO_PIN_11
#define RS_GPIO_Port GPIOA

/***** Pino EN do LCD *****/
#define EN_Pin GPIO_PIN_8
#define EN_GPIO_Port GPIOA

/** Pinos de dados do LCD **/
#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_13
#define D5_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_14
#define D6_GPIO_Port GPIOB
#define D7_Pin GPIO_PIN_15
#define D7_GPIO_Port GPIOB

/*************** Funções para operação do LCD ************/

void send_to_lcd (char data, int rs)
{
	/* RS = 1 para dados e RS = 0 para comandos */
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs);

	/* Escreve o dado em seu respectivo pino */
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, ((data>>3)&0x01));
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, ((data>>2)&0x01));
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, ((data>>1)&0x01));
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, ((data>>0)&0x01));

	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);

	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);

	HAL_Delay(1);
}

void lcd_send_cmd (char cmd)
{
    char datatosend;

    /* Envia os 4 bits mais significativos do dado */
    datatosend = ((cmd>>4)&0x0f);
    send_to_lcd(datatosend,0);  // RS deve ser 0 para envio de comandos

    /* Envia os 4 bits menos significativos do dado */
    datatosend = ((cmd)&0x0f);
	send_to_lcd(datatosend, 0);
}

void lcd_send_data (char data)
{
	char datatosend;

	/* Envia os 4 bits mais significativos do dado */
	datatosend = ((data>>4)&0x0f);
	send_to_lcd(datatosend, 1);  // RS deve ser 0 para envio de caracteres

	/* Envia os 4 bits menos significativos do dado */
	datatosend = ((data)&0x0f);
	send_to_lcd(datatosend, 1);
}

void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}


void lcd_init (void)
{
	// Inicialização no modo 4 bits
	HAL_Delay(50);  // Aguarda por tempo >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // Aguarda por tempo >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // Aguarda por tempo >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);

	lcd_send_cmd (0x02);  // Modo 4bits
	HAL_Delay(1);

    // Inicialização do LCD
	lcd_send_cmd (0x28); /* Comunicação em 4 bits, display de 2 linhas e
                            matriz 7X5 */
	HAL_Delay(1);
	lcd_send_cmd (0x08); /* Controle para ligar/desligar o display
                            --> D=0,C=0, B=0  ---> display off */
	HAL_Delay(1);
	lcd_send_cmd (0x01); // Limpa o LCD
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); /* Deslocamento do cursor à direita após um novo
                            caractere */
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Liga o display sem cursor
}


void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
