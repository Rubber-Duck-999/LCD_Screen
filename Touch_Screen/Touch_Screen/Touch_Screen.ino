/* ------------------------------------------------------------------------------------------------------------------------
// --                                           <2017> Simon Crowther
// --
// --           The Information in this document is the property of Simon Crowther and may not be copied, or communicated
// --           to a third party, or used for any other purpose than than for that for which it was supplied, without written
// --                                   consent from Simon Crowther
// --
// ------------------------------------------------------------------------------------------------------------------------
// --
// -- Project:          LCD_Display.ino
// -- Description:      This is a system which monitors temperature on a analog pin and saves values on iterval set by
//                      a global constant. A LCD display is also used to display a menu system that allows the interface
//                      to display temperature in average and graphical format
// --
// --
// ------------------------------------------------------------------------------------------------------------------------
// -- Change History:
// --      Version         Date            Author          Description
// --      -------         ----            ------          -----------
// --      1.0            15/10/17         S.Crowther      Initial version
// ------------------------------------------------------------------------------------------------------------------------
// -- Parameters:
// --    Name              Direction       Description
// --    ----              ---------       ----
// --    Button_A          Input           Button A on pin 3
// --    Button_B          Input           Button B on pin 5
// --    Button_C          Input           Button C on pin 6
// --    Button_D          Input           Button D on pin 7
// --    Temperature_Pin   Input           Analog Sensor on Pin 0
// --
// ------------------------------------------------------------------------------------------------------------------------
*/

#include <URTouchCD.h>
#include <UTFT.h>
#include <URTouch.h>
#include <Wire.h>
#include "string.h"
#define TOUCH_ORIENTATION  LANDSCAPE
//==== Creating Objects
UTFT    myGLCD(ITDB32S, 38, 39, 40, 41); //Parameters should be adjusted to your Display/Schield model
URTouch  myTouch(6, 5, 4, 3, 2);

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t SmallFont[];

const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

void setup() 
{
	pinMode(SW_pin, INPUT);
	digitalWrite(SW_pin, HIGH);
	Serial.begin(115200);
	myGLCD.InitLCD();
	myGLCD.clrScr();
}

void loop() 
{	
	int Mode = 0;
	//Read_Axis(Y_pin, Mode);
	delay(1000);
	Main_Menu_GLCD();
}

void Wipe()
{
	myGLCD.clrScr();
}

void Main_Menu_GLCD(void)
{
	//Main Mneu shown when the user starts the program
	Wipe();
	//Calls both generic functions and inputs the specific strings to this menu design
	String Menu_Options[4] = { "Option 1", "Option 2", "Option 3", "Option 4" };
	Generic_Menu("Main Menu", Menu_Options);
	int Mode = 0;
	int Pin = Y_pin;
	delay(300);
	while (1)
	{
		//If a mode is set and Button_C is pressed then the user will enter on of the multiple functions lited below
		Mode = Read_Axis(Pin, Mode);
		if (digitalRead(SW_pin) == 0)
		{
			Serial.println(digitalRead(SW_pin));
			delay(500);
			if (Mode == 0)
			{
				//Enters a another menu
				Temperature_Menu();
			}
			else if (Mode == 1)
			{
				//Enters a another menu
				//Menu_Average();
			}
			else if (Mode == 2)
			{
				//Enters the current temperature checks and display
				//Temperature_Read();
			}
			else if (Mode == 3)
			{
				//Delete_Memory();
			}
			delay(200);
			break;
		}
		//If button D function is entered, it will do two things
		//Check if button d is pressed and also what mode is entered determines what menu option line is drawn or erased
		//Check_Buttons_D(Mode, Button_D);
	}
}

int Read_Axis(int Pin, int Mode)
{
	unsigned int X_Axis_Value = analogRead(Pin);
	if (X_Axis_Value > 750)
	{
		if (Mode < 2)
		{
			Mode++;
		}
	}
	else if (X_Axis_Value < 250)
	{
		if (Mode > 0)
		{
			Mode--;
		}
	}
	Serial.println(Mode);
	delay(500);
}

void Temperature_Menu(void)
{
	//Main Mneu shown when the user starts the program
	Wipe();
	//Calls both generic functions and inputs the specific strings to this menu design
	String Menu_Options[4] = { "Option 1", "Option 2", "Option 3", "Option 4" };
	Generic_Menu("Temperature Menu", Menu_Options);
	int Mode = 0;
	int Pin = Y_pin;
	delay(300);
	while (1)
	{
		//If a mode is set and Button_C is pressed then the user will enter on of the multiple functions lited below
		Mode = Read_Axis(Pin, Mode);
		if (digitalRead(SW_pin) == 0)
		{
			delay(500);
			if (Mode == 0)
			{
				//Enters a another menu
				//Graph_Menu();
			}
			else if (Mode == 1)
			{
				//Enters a another menu
				//Menu_Average();
			}
			else if (Mode == 2)
			{
				//Enters the current temperature checks and display
				//Temperature_Read();
			}
			else if (Mode == 3)
			{
				//Delete_Memory();
			}
			delay(200);
			break;
		}
		//If button D function is entered, it will do two things
		//Check if button d is pressed and also what mode is entered determines what menu option line is drawn or erased
		//Check_Buttons_D(Mode, Button_D);
	}
}

void Generic_Menu(String Title, String Menu_Options[])
{
	myGLCD.fillScr(VGA_RED);
	myGLCD.setBackColor(VGA_RED);
	myGLCD.setFont(BigFont);
	myGLCD.setColor(VGA_BLACK);
	myGLCD.print(Title, CENTER, 1);

	int X_Axis_1 = 35, X_Axis_2 = 285;
	int Y_Axis_1 = 40, Y_Axis_2 = 80;
	int Difference_Y_Axis = 50;
	for (int i = 0; i < 4; i++)
	{
		myGLCD.setColor(VGA_BLACK); //Fill of the rectangle Colour
		myGLCD.fillRoundRect(X_Axis_1, Y_Axis_1, X_Axis_2, Y_Axis_2); // Draws filled rounded rectangle
		myGLCD.setColor(VGA_WHITE); // Outline colour is set
		myGLCD.drawRoundRect(X_Axis_1, Y_Axis_1, X_Axis_2, Y_Axis_2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
		myGLCD.setFont(BigFont); // Sets the font to big
		myGLCD.setBackColor(VGA_BLACK); // Sets the background color of the area where the text will be printed to green, same as the button
		int Text_Point = Y_Axis_1 + 10;
		myGLCD.print(Menu_Options[i], CENTER, Text_Point); // Prints the string
		Y_Axis_1 = Y_Axis_1 + Difference_Y_Axis;
		Y_Axis_2 = Y_Axis_2 + Difference_Y_Axis;
	}
}
