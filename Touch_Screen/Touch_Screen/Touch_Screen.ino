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

//////////////////////////////////////////////////////////
/*
              Pre processor directives 
			  - Tells the board which headers or libraries 
			  - to compile at program runtime
*/
//////////////////////////////////////////////////////////
#include <UTFT.h>
#include <Wire.h>
#include "string.h"
#include "Menu_Class.h"
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
/*
              Declared Constants
			  - Sets the pins for this partcular program
			  - only constants are set not global 
			  - variables
*/
//////////////////////////////////////////////////////////

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
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
/*
              Declaration of Choose_Menu function
			  - Function requirement is that it passes
			  - 6 inputs and 0 outputs
*/
//////////////////////////////////////////////////////////

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
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
/*
              Declaration of Setup and Loop
*/
//////////////////////////////////////////////////////////
void setup() 
{
	pinMode(SW_Pin, INPUT_PULLUP); 
	//Sets SW_Pin to be a input pullup switch
	pinMode(VCC_pin, OUTPUT);
	//Sets the VCC_Pin to be an output
    //and powered on startup
	digitalWrite(VCC_pin, HIGH);
	Serial.begin(115200);
	//Serial monitor baud rate is set to 115200 which is not specific
}

void loop() 
{	
	Main_Menu_Glcd();
	//Only calls the Main_Menu in a loop
}
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
/*
    Defintion of Main_Mneu_Glcd
	- This function is the first function to be run
    from the loop function
			  
	Its functionality is quite consistent with other menu 
	functions, it calss a instance of the class Generic_Menu 
	and calls it Main_Menu. The constructor for the class is
	called immediately where local variables are inputted 
	that will be used to assign values to member variables in 
	this class.
	
	Also uses namespace functions to return values that are
	placed into local arrays then to be as mentioned above placed 
	as parameters in the class constructor
	
	The last part is the whil loop at the end of the tasks which
	continually loops through the call to Choose_Menu function
	this function passes in parameters which includes pointers
	to functions and the object instance created in this menu
*/
//////////////////////////////////////////////////////////
void Main_Menu_Glcd(void)
{
	//Main Menu shown when the user starts the program
	const uint8_t Preset_Choice_Colours = 2;
	const int Preset_Choice_Axis = 0;
	const int Preset_Choice_Button_Size = 1;
	//Local constants used to indent in the call to namespace7
	//functions that have preset data structures 
	//for the class member functions

	String Title = "Main Menu";
	//Title string for this object
	String Menu_Options[4] =
	{
		"Temperature",
		"Humidity",
		"Graphs",
		"Settings",  
	};
	//Options placed on the menu buttons
	uint16_t Array_Axis[5];
	//Local unsigned array that needs to be unsigned to stop
	//negative axis values that may try to be drawn on the screen

	for (int i = 0; i < 5; i++)
	{
		Array_Axis[i] = Presets::Get_Axis(Preset_Choice_Axis, i);
		//For loop which starts and ends at the max values allowed for
		//axis values in the Generic_Menu class
		//Calls the Presets namespace Get_Axis function and inputs the Preset choice 
		// for the axis to index in their preset choices
		// and the second parameter is the index parameter from the loop for which individual axis value
		if (Debug_Mode == 1)
		{
			Serial.print("Axis");
			Serial.println(Array_Axis[i]);
			//Debug mode prints out if the correct
			//axis values have been placed in each index value
		}
		delay(100);
	}

	uint8_t Buttons = Presets::Get_Amount_Of_Buttons_Preset(Preset_Choice_Axis);
    //Calls the Presets namespace Get_Amount_Of_Buttons function and inputs the Preset choice 
    // for the amount of buttons to index in their preset choices
	if (Debug_Mode == 1)
	{
		Serial.print("Buttons");
		Serial.println(Buttons);
        //Debug mode prints out if the correct
        //amount of buttons has been outputted
	}
	uint8_t Button_Size = Presets::Get_Button_Size_Preset(Preset_Choice_Button_Size);
    //Calls the Presets namespace Get_Buttons_Size function and inputs the Preset choice 
    // for the size of buttons to be returned

	// Constructor -   (Title)   
	//                 (Array of Menu Option Strings)  
	//                 (Array of Axis Values)  
	//                 (Amount of Buttons)	
	//                 (Button Size in pixels)
    //                 (Brightness_Level)
    Generic_Menu Main_Menu
    (Title,
     Menu_Options,
     Array_Axis,
     Buttons,
     Button_Size,
	 Brightness_Level);
	 //This is the constructor and instance declaration for the Generic_Menu Class

	Main_Menu.Draw_Main(Preset_Choice_Colours);
	//The drawing of the main window function that allows for the same screen to be designed 
	//but just with a different colour scheme

	Main_Menu.Draw_Menu_Options();
	//Same for draw_menu_options it bases the design of the screen off the member variables assigned in the 
	// constructor for the class instance
	uint8_t Pin = Y_pin;
	//Sets the local pin to be the constant Y_Pin
	delay(300);
	while (1)
	{
		Choose_Menu
		(&Temperature_Menu, 
		 &Humidity_Menu, 
		 &Graphs_Menu, 
		 &Settings_Menu,  
		 Pin,
		 Main_Menu);
		 //One of the most complex implementations - this function passes in 4 pointers to functions 
		 //and the pin required as well as the object declared in this function as it is local only not global
	}
}
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
/*
    Declaration of Input_Menu's
	-Function takes in a object when called but only enters that state when
	-input pullup switch is not pressed as its acting as a exit button button
*/
//////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////
/*
    Definition of Choose_Menu
	-Function takes in a object when called but only enters that state when
	-input pullup switch is not pressed as its acting as a exit button button
*/
//////////////////////////////////////////////////////////
void Choose_Menu
(
 void (*Menu_Choice_1)(Generic_Menu& Menu),
 void (*Menu_Choice_2)(Generic_Menu& Menu),
 void (*Menu_Choice_3)(Generic_Menu& Menu),
 void (*Menu_Choice_4)(Generic_Menu& Menu),
 uint8_t Pin,
 Generic_Menu& Menu
)
//Passes 4 pointers to functions as inputs
//Plus a pin variable and a class object
{
	//If a mode is set and Button_C is pressed then the user will enter on of the multiple functions lited below
	static int Mode_Select = 0;
	//Set once for program to allow setting of mode by joystick input
	uint8_t Enter = 0;
	//Local variable for returning to loop upon completion of smaller menu call
	Mode_Select = Menu.Read_Axis(Pin, Mode_Select);
	//Reads the axis set by joystick and adjusts the mode accordingly
    Menu.Draw_Frame(Mode_Select);
	//Sets the button frame from whic mode is set
	if (Debug_Mode == 1)
	{
		Serial.print("Mode \n");
		Serial.println(Mode_Select);
		//Debug mode that prints the mode that menu is in
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
//////////////////////////////////////////////////////////




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
	//                 (Array of Axis Values)  
	//                 (Amount of Buttons)	
	//                 (Button Size in pixels)
    //                 (Brightness_Level)
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
		Choose_Menu
		(&Temperature_Call,
		 &Humidity_Menu, 
		 &Graphs_Menu, 
		 &Settings_Menu, 
		 Pin,
		 Temperature_Main_Menu);
	}
}

