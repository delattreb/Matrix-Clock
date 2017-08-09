//
// Created by Bruno on 11/07/2017.
//

#include <Arduino.h>
#include <SPI.h>
#include "rtcAccess.h"
#include "var.h"
#include "calculation.h"
#include "LedControl.h" 

#pragma region Global
LedControl lcd = LedControl(PIN_DATA, PIN_CLK, PIN_CS, (CHAINED_MATRIX_WIDTH*CHAINED_MATRIX_HEIGHT) - 1);
char binary[4] = { '0','0','0','0' };
char hourbinary[4][7];
char matrix[MATRIX_WIDTH*DIGIT_WIDTH + 1][MATRIX_HEIGHT*DIGIT_HEIGHT + 1];

rtcAccess rtc;
String hour;
DateTime h, lh;

int nbdigit = 6;
int nbbit = 4;
int widthText = (nbdigit * (DIGIT_WIDTH + SPACE_WIDTH)) - 1;
int heightText = (nbbit * (DIGIT_HEIGHT + SPACE_HEIGHT)) - 2;
int centerx = ((CHAINED_MATRIX_WIDTH * MATRIX_WIDTH) - widthText) / 2;
int centery = ((CHAINED_MATRIX_HEIGHT * MATRIX_HEIGHT) - heightText) / 2;
#pragma endregion 

//
// CalculateBinary
//
void CalculateBinary()
{
	for (int i = 0; i < hour.length(); i++)
	{
		IntToBinary(binary, int(hour[i]) - 0x30);
		ReoderMatrix(hourbinary, binary, i);
	}
}

//
// CalculateMatrix
//
void CalculateMatrix()
{
	//Scroll into hourbinary 
	for (int j = 0; j < nbdigit; j++)
		for (int i = 0; i < nbbit; i++)
		{
			int startx = j*(DIGIT_WIDTH + SPACE_WIDTH) + centerx;
			int starty = i*(DIGIT_HEIGHT + SPACE_HEIGHT) + centery;

			//Scroll into matrix
			for (int x = startx; x < startx + DIGIT_WIDTH; x++)
				for (int y = starty; y < starty + DIGIT_HEIGHT; y++)
					matrix[y][x] = hourbinary[i][j];
		}
}

//
// Setup
//
void setup()
{
#ifdef DEBUG
	Serial.begin(SERIAL_BAUD);
	while (!Serial) {
		; //Needed for native USB port only
	}
#endif
	//rtc.init();

	//Init table
	for (int i = 0; i <= 3; i++)
		hourbinary[i][6] = '\0';

	// Init matrix
	for (int i = 0; i < MATRIX_WIDTH*DIGIT_WIDTH; i++) {
		for (int j = 0; j < MATRIX_HEIGHT*DIGIT_HEIGHT; j++) {
			matrix[i][j] = '0';
		}
		matrix[i][MATRIX_WIDTH*DIGIT_WIDTH] = '\0';
	}

	for (int i = 0; i < CHAINED_MATRIX_WIDTH*CHAINED_MATRIX_HEIGHT; i++)
	{
		lcd.shutdown(i, false); //turn off power saving, enables display
		lcd.setIntensity(i, LED_INTENSITY);
		lcd.clearDisplay(i);
	}

#ifdef DEBUG
	for (int i = 0; i < nbbit; i++)
		Serial.println(hourbinary[i]);
	Serial.println(" ");

	for (int i = 0; i < MATRIX_WIDTH*DIGIT_WIDTH; i++)
		Serial.println(matrix[i]);
#endif
}

//
// DisplayMatrix
//
void DisplayMatrix(int block, int i, int j)
{
	for (int x = 0; x < MATRIX_WIDTH; x++) {
		int max = j * MATRIX_WIDTH;
		int may = i * MATRIX_HEIGHT;
		for (int y = 0; y < MATRIX_HEIGHT; y++) {
			lcd.setLed(block, x, y, (matrix[x + max][y + may] == '1'));
		}
	}
}


//
// Loop
//
void loop()
{
	//h = rtc.getDateTime();
	//hour = rtc.getTimeStr();
	hour = "124854";
	CalculateBinary();
	CalculateMatrix();
//	if (h.second() != lh.second()) {
		DisplayMatrix(0, 2, 2);
		DisplayMatrix(3, 2, 1);
		DisplayMatrix(6, 2, 0);
//	}
//	if (h.minute() != lh.minute()) {
		DisplayMatrix(1, 1, 2);
		DisplayMatrix(4, 1, 1);
		DisplayMatrix(7, 1, 0);
//	}
//	if (h.hour() != lh.hour()) {
		DisplayMatrix(2, 0, 2);
		DisplayMatrix(5, 0, 1);
		DisplayMatrix(8, 0, 0);
//	}
	//lh = h;
}
