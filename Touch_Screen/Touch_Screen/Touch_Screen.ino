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
#include "Menu_Class.h"

#define TOUCH_ORIENTATION  LANDSCAPE
//==== Creating Objects
UTFT    myGLCD(ITDB32S, 38, 39, 40, 41); //Parameters should be adjusted to your Display/Schield model
URTouch  myTouch(6, 5, 4, 3, 2);

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

uint8_t Preset_Choice = 1;

const uint16_t Data_Value = 0;

const uint8_t Buttons = 4;

const uint8_t Button_Size = 40;

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
	delay(1000);
	Temperature_Menu();
}

void Wipe()
{
	myGLCD.clrScr();
}

void Main_Menu_GLCD(void)
{
	//Main Mneu shown when the user starts the program
	Wipe();
	String Title = "Main Menu";
	String Menu_Options[4] =
	{
		"Option 1",
		"Option 2",
		"Option 3",
		"Option 4"
	};
	uint16_t Array_1[5] = { 0 };
	uint16_t Array_2[5] = { 0 };
    Array_1[5] = Presets::Get_Array_Of_Colours(Preset_Choice);

	Presets::Return;
	Array_2[5] = Presets::Get_Array_Of_Axis(Preset_Choice);

	// Constructor -   (Title)   
	//                 (Array of Menu Option Strings)
	//                 (Array of Background_Colour)   
	//                 (Array of Axis Values)  
	//                 (Data_Value)
	//                 (Amount of Buttons)
	//                 (Button Size in pixels)
	Generic_Menu Main_Menu(String Title, String Menu_Options[], uint16_t Array_1[] , uint16_t Array_2[], uint16_t Data_Value, uint8_t Buttons, uint8_t Button_Size);
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
	String Title = "Secondary Menu";
	String Menu_Options[4] =
	{
		"Option 1",
		"Option 2",
		"Option 3",
		"Option 4"
	};

	// Constructor -   (Title)   
	//                 (Array of Menu Option Strings)
	//                 (Array of Background_Colour)   
	//                 (Array of Axis Values)  
	//                 (Data_Value)
	//                 (Amount of Buttons)
	//                 (Button Size in pixels)
	Generic_Menu Main_Menu(String Title, String Menu_Options[], uint16_t Array_1[], uint16_t Array_2[], uint16_t Data_Value, uint8_t Buttons, uint8_t Button_Size);
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

