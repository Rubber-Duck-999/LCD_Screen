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
                                                      Implemented Choose Menu
      1.3            28/10/17         S.Crowther      Created calls to the new function Draw_Input_Options and passing of a object to choose menu
	                                                  parameters
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 Parameters:
    Name              Direction       Description
    ----              ---------       ----
    SW_Pin            Input           Button on Pin 9
    X_Pin             Input           Analog Sensor on Pin 1
	Y_Pin             Input           Analog Sensor on Pin 0
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <UTFT.h>
#include <Wire.h>
#include "string.h"
#include "Menu_Class.h"

//==== Creating Objects
//Parameters should be adjusted to your Display/Schield model

const uint8_t VCC_pin = 8; //Short term issue fix for power issue
const uint8_t SW_Pin = 9; // digital pin connected to switch output
const uint8_t X_pin = 1; // analog pin connected to X output
const uint8_t Y_pin = 0; // analog pin connected to Y output

const uint16_t Data_Value = 0;

const uint8_t Buttons = 4;

const uint8_t Button_Size = 40;
const uint8_t Humidity_Pin = 4;

const uint8_t Brightness_Level = 1;

const int Debug_Mode = 0;

void Choose_Menu
(
 void (*Menu_Choice_1)(Generic_Menu& Menu),
 void (*Menu_Choice_2)(Generic_Menu& Menu),
 void (*Menu_Choice_3)(Generic_Menu& Menu),
 void (*Menu_Choice_4)(Generic_Menu& Menu),
 uint8_t Pin,
 Generic_Menu& Menu
);
//Pass Pointer to function in as parameter

void Humidity_Menu(Generic_Menu& Menu);


void setup() 
{
	pinMode(SW_Pin, INPUT_PULLUP); 
	//This is safer as it sets pins 2 to 7 as outputs	               
	//Port manipulation - As DigitalRead/Write take up precious space
	//Sets Pin 7,1,0 as inputs and 6-2 as outputs
	pinMode(VCC_pin, OUTPUT);
	digitalWrite(VCC_pin, HIGH);
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
	const uint8_t Preset_Choice_Colours = 2;
	const int Preset_Choice_Axis = 0;
	const int Preset_Choice_Button_Size = 1;

	String Title = "Main Menu";
	String Menu_Options[4] =
	{
		"Temperature",
		"Humidity",
		"Graphs",
		"Settings",  
	};
	uint16_t Array_Axis[5];

	//Namespace - Presets returning an array of presets defined 
	//            by the constant preset choice

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
	if (Debug_Mode == 1)
	{
		Serial.print("Buttons");
		Serial.println(Buttons);
	}
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
     Array_Axis,
     Buttons,
     Button_Size,
	 Brightness_Level);

	Main_Menu.Draw_Main(Preset_Choice_Colours);

	Main_Menu.Draw_Menu_Options();
	Main_Menu.Draw_Inputs_Option("Humidity", "Percentage", 0, "%", Data_Value, SW_Pin);
	uint8_t Pin = Y_pin;
	delay(300);
	while (1)
	{
		//Choose_Menu
		//(&Temperature_Menu, 
		// &Humidity_Menu, 
		// &Graphs_Menu, 
		// &Settings_Menu,  
		// Pin,
		// Main_Menu);
	}
}

void Humidity_Menu(Generic_Menu& Menu)
{
	if (Debug_Mode == 1)
	{
		Serial.println("Humidity Menu");
	}
	uint8_t Preset = 0;
	while (digitalRead(SW_Pin) == 1)
	{
		uint16_t Data_Value = analogRead(Humidity_Pin);
		Menu.Draw_Inputs_Option("Humidity", "Percentage", Preset, "%", Data_Value, SW_Pin);
	}
}

void Graphs_Menu(Generic_Menu& Menu)
{
	if (Debug_Mode == 1)
	{
		Serial.println("Graphs Menu");
	}
}

void Settings_Menu(Generic_Menu& Menu)
{
	if (Debug_Mode == 1)
	{
		Serial.println("Settings");
	}
}

void Choose_Menu
(
 void (*Menu_Choice_1)(Generic_Menu& Menu),
 void (*Menu_Choice_2)(Generic_Menu& Menu),
 void (*Menu_Choice_3)(Generic_Menu& Menu),
 void (*Menu_Choice_4)(Generic_Menu& Menu),
 uint8_t Pin,
 Generic_Menu& Menu
)
//Passes Functions in as parameters and objects
{
	//If a mode is set and Button_C is pressed then the user will enter on of the multiple functions lited below
	static int Mode_Select = 0;
	uint8_t Enter = 0;
	Mode_Select = Menu.Read_Axis(Pin, Mode_Select);
    Menu.Draw_Frame(Mode_Select);
	if (Debug_Mode == 1)
	{
		Serial.print("Mode \n");
		Serial.println(Mode_Select);
	}
	if (digitalRead(SW_Pin) == 0)
	{
		if (Mode_Select == 0)
		{
			Menu_Choice_1(Menu);
			Enter = 1;
		}
		else if (Mode_Select == 1)
		{
			Menu_Choice_2(Menu);
			Enter = 1;
		}
		else if (Mode_Select == 2)
		{
			Menu_Choice_3(Menu);
			Enter = 1;
		}
		else if (Mode_Select == 3)
		{
			Menu_Choice_4(Menu);
			Enter = 1;
		}
		delay(200);
	}	
	if (Enter == 1)
	{
		loop();
	}
}

void Temperature_Menu(Generic_Menu& Menu)
{
	//Main Menu shown when the user starts the program
	static int Temperature_Menu = 1;
	const int Preset_Choice_Colours = 3;
	const int Preset_Choice_Axis = 0;
	const int Preset_Choice_Button_Size = 1;
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
	uint16_t Array_Axis[5];

	//Namespace - Presets returning an array of presets defined 
	//            by the constant preset choice

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
	Generic_Menu Temperature_Main_Menu
	(Title, 
	 Menu_Options,  
	 Array_Axis, 
	 Buttons, 
	 Button_Size,
     Brightness_Level);
	 //Uses direct references to avoid overhead
	 
	Temperature_Main_Menu.Draw_Main(Preset_Choice_Colours);
	
	Temperature_Main_Menu.Draw_Menu_Options();
	
	uint8_t Pin = Y_pin;
	delay(300);
	while (1)
	{
		//Choose_Menu
		//(&Temperature_Call,
		// &Humidity_Menu, 
		// &Graphs_Menu, 
		// &Settings_Menu, 
		// Pin,
		// Temperature_Main_Menu);
	}
}

void Temperature_Call(void)
{

}
