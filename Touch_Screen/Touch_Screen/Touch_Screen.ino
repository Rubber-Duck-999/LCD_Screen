/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                           <2017> Simon Crowther

           The Information in this document is the property of Simon Crowther and may not be copied, or communicated
           to a third party, or used for any other purpose than than for that for which it was supplied, without written
                                   consent from Simon Crowther

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 Project:          Touch_Screen.ino
 Description:      This is a system which monitors temperature on a analog pin and saves values on iterval set by
                   a global constant. A LCD display is also used to display a menu system that allows the interface
                   to display temperature in average and graphical format


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 Change History:
      Version         Date            Author          Description
      -------         ----            ------          -----------
      1.0            24/10/17         S.Crowther      Initial version
      1.1            25/10/17         S.Crowther      Added Namespace with data structure for presets 
      1.2            27/10/17         S.Crowther      Changed constant pin declarations, uncommented functions,
                                                      Implementaed Choose Menu
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 Parameters:
    Name              Direction       Description
    ----              ---------       ----
    Button_A          Input           Button A on pin 3
    Button_B          Input           Button B on pin 5
    Button_C          Input           Button C on pin 6
    Button_D          Input           Button D on pin 7
    Temperature_Pin   Input           Analog Sensor on Pin 0
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <UTFT.h>
#include <URTouch.h>
#include <Wire.h>
#include "string.h"
#include "Menu_Class.h"

//==== Creating Objects
//Parameters should be adjusted to your Display/Schield model

URTouch  myTouch(6, 5, 4, 3, 2);

const uint8_t SW_pin = 8; // digital pin connected to switch output
const uint8_t X_pin = 1; // analog pin connected to X output
const uint8_t Y_pin = 0; // analog pin connected to Y output

const uint16_t Data_Value = 0;

const uint8_t Buttons = 4;

const uint8_t Button_Size = 40;

const int Debug_Mode = 0;

//void Temperature_Menu(void);
//
//void Humidity_Menu(void);
//
//void Temperature_Graphs_Menu(void);
//
//void Settings_Menu(void);

void Choose_Menu
(
 void (*Menu_Choice_1)(), 
 void (*Menu_Choice_2)(),
 void (*Menu_Choice_3)(),
 void (*Menu_Choice_4)(), 
 uint8_t Pin,
 Generic_Menu& Menu
);
//Pass Pointer to function in as parameter

void setup() 
{
	//pinMode(SW_pin, INPUT);
	DDRD = DDRD | B1111100;  
	//This is safer as it sets pins 2 to 7 as outputs	               
	//Port manipulation - As DigitalRead/Write take up precious space
	//Sets Pin 7,1,0 as inputs and 6-2 as outputs
	pinMode(SW_pin, INPUT_PULLUP);
	Serial.begin(115200);
}

void loop() 
{	
	Main_Menu_Glcd();
}

void Main_Menu_Glcd(void)
{
	//Main Menu shown when the user starts the program
	//Wipe();
	const int Preset_Choice_Colours = 1;
	const int Preset_Choice_Axis = 1;
	const int Preset_Choice_Button_Size = 1;

	String Title = "Main Menu";
	String Menu_Options[4] =
	{
		"Temperature Menu",
		"Humidity Menu"
		"Temperature Graphs",
		"Settings Menu",  
	};
	uint16_t Array_Colours[5];
	uint16_t Array_Axis[5];

	//Namespace - Presets returning an array of presets defined 
	//            by the constant preset choice
	
	for (int i = 0; i < 5; i++)
	{
		Array_Colours[i] = Presets::Get_Colours(Preset_Choice_Colours, i);
		if (Debug_Mode == 1)
		{
			Serial.print("Colours");
			Serial.println(Array_Colours[i]);
		}
		delay(100);
	}

	//Serial.print("Axis");	
	for (int i = 0; i < 5; i++)
	{
		Array_Axis[i] = Presets::Get_Axis(Preset_Choice_Axis, i);
		if (Debug_Mode == 1)
		{
			Serial.print("Axis");
			Serial.println(Array_Axis[i]);
		}
		delay(100);
	}

	uint8_t Buttons = Presets::Get_Amount_Of_Buttons_Preset(Preset_Choice_Axis);
	Serial.print("Buttons");
	Serial.println(Buttons);
	uint8_t Button_Size = Presets::Get_Button_Size_Preset(Preset_Choice_Button_Size);

	// Constructor -   (Title)   
	//                 (Array of Menu Option Strings)
	//                 (Array of Background_Colour)   
	//                 (Array of Axis Values)  
	//                 (Data_Value)
	//                 (Amount of Buttons)
	//                 (Button Size in pixels)
    Generic_Menu Main_Menu
    (Title,
     Menu_Options,
     Array_Colours,
     Array_Axis,
     Data_Value,
     Buttons,
     Button_Size);

	Main_Menu.Draw_Main();

	Main_Menu.Draw_Menu_Options();
	uint8_t Pin = Y_pin;
	delay(300);
	while (1)
	{
		Choose_Menu
		(&Temperature_Menu, 
		 &Humidity_Menu, 
		 &Temperature_Graphs_Menu, 
		 &Settings_Menu,  
		 Pin,
		 Main_Menu);
	}
}

void Humidity_Menu(void)
{

}

void Temperature_Graphs_Menu(void)
{

}

void Settings_Menu(void)
{

}

void Choose_Menu
(
 void (*Menu_Choice_1)(), 
 void (*Menu_Choice_2)(),
 void (*Menu_Choice_3)(),
 void (*Menu_Choice_4)(),
 uint8_t Pin,
 Generic_Menu& Menu
)
//Passes Functions in as parameters and objects
{
	//If a mode is set and Button_C is pressed then the user will enter on of the multiple functions lited below
	static int Mode_Select = 0;
	Mode_Select = Menu.Read_Axis(Pin, Mode_Select);
    Menu.Draw_Frame(Mode_Select);
	if (digitalRead(SW_pin) == 0)
	{
		Serial.println(digitalRead(SW_pin));
		delay(500);
		if (Mode_Select == 0)
		{
			Menu_Choice_1();
		}
		else if (Mode_Select == 1)
		{
			Menu_Choice_2();
		}
		else if (Mode_Select == 2)
		{
			Menu_Choice_3();
		}
		else if (Mode_Select == 3)
		{
			Menu_Choice_4();
		}
		delay(200);
	}	
}

void Temperature_Menu(void)
{
	//Main Menu shown when the user starts the program
	static int Temperature_Menu = 1;
	if (Debug_Mode == 1)
	{
		Serial.println("Temperature Menu");
	}
	String Title = "Temperature Menu";
	String Menu_Options[4] =
	{
		"Option 1",
		"Option 2",
		"Option 3",
		"Option 4"
	};
	uint16_t Array_Colours[5];
	uint16_t Array_Axis[5];

	//Namespace - Presets returning an array of presets defined 
	//            by the constant preset choice

	for (int i = 0; i < 5; i++)
	{
		Array_Colours[i] = Presets::Get_Colours(Preset_Choice, i);
		if (Debug_Mode == 1)
		{
			Serial.print("Colours");
			Serial.println(Array_Colours[i]);
		}
		delay(100);
	}

	//Serial.print("Axis");	
	for (int i = 0; i < 5; i++)
	{
		Array_Axis[i] = Presets::Get_Axis(Preset_Choice, i);
		if (Debug_Mode == 1)
		{
			Serial.print("Axis");
			Serial.println(Array_Axis[i]);
		}
		delay(100);
	}

	uint8_t Buttons = Presets::Get_Amount_Of_Buttons_Preset(Preset_Choice);
	Serial.print("Buttons");
	Serial.println(Buttons);
	uint8_t Button_Size = Presets::Get_Button_Size_Preset(Preset_Choice);

	// Constructor -   (Title)   
	//                 (Array of Menu Option Strings)
	//                 (Array of Background_Colour)   
	//                 (Array of Axis Values)  
	//                 (Data_Value)
	//                 (Amount of Buttons)
	//                 (Button Size in pixels)
	Generic_Menu Main_Menu
	(Title, 
	 Menu_Options, 
	 Array_Colours, 
	 Array_Axis, 
	 Data_Value, 
	 Buttons, 
	 Button_Size);
	 //Uses direct references to avoid overhead
	 
	Main_Menu.Draw_Main();
	
	Main_Menu.Draw_Menu_Options();
	
	int Pin = Y_pin;
	delay(300);
	while (1)
	{
		//Choose_Menu
		//(&Temperature_Menu, 
		// &Humidity_Menu, 
		// &Temperature_Graphs_Menu, 
		// &Settings_Menu, 
		// Pin);
	}
}

