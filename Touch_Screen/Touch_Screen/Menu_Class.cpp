#include "Menu_Class.h"
#include <stdint.h>
#include "string.h"
#include <string>
#include "WString.h"

namespace Presets
{
	//Namespace for presets for colours in menu's
	// Contains two structures one for colours and axis

	struct Preset_Colours
	{
		uint16_t Array_Of_Colours[4];
	};

	//A data structure of four preset choices
	Preset_Colours Presets_Colours[4]
	{
		//0 - Background_Screen_Colour;
		//1 - Title_Colour;
		//2 - Text_Box_Colour;
		//3 - Box_Colour_Fill;
		//4 - Box_Colour_Outline;
		{ 
			0, 
		},//Preset 1

		{ 
			0,
		},//Preset 2
		{
			0,
		},//Preset 3         
		{
			0,
		},//Preset 4 
	};

	struct Preset_Axis
	{
		uint16_t Array_Of_Axis[5] =
		{
			//X_Axis_1, 
			//X_Axis_2;
			//Y_Axis_1, 
			//Y_Axis_2;
			//Difference_Y_Axis;
			X_Axis_1,
			X_Axis_2,
			Y_Axis_1,
			Y_Axis_2,
			Difference_Y_Axis
		};
	};

	//A data structure of four preset choices
	Preset_Axis Presets_Axis[4]
	{
		//X_Axis_1, 
		//X_Axis_2;
		//Y_Axis_1, 
		//Y_Axis_2;
		//Difference_Y_Axis;
		{ 35,
		285,
		40,
		110,
		50
		},//Preset 1

		{ 35,
		285,
		40,
		110,
		50
		},//Preset 2

		{ 35,
		285,
		40,
		110,
		50
		},//Preset 3  

		{ 35,
		285,
		40,
		110,
		50
		}//Preset 4 
	};

	//Namespace function that returns the array required for running class member functions
	//Done twice for presets and axis
	uint16_t Get_Array_Of_Colours(uint8_t Preset_Choice)
	{
		uint16_t Array_Of_Colours[5];
		for (int i = 0; i < 5; i++)
		{
			Array_Of_Colours[i] = Presets_Colours[Preset_Choice].Array_Of_Colours[i];
		}
		return Array_Of_Colours[5];
	};

	uint16_t Get_Array_Of_Axis(uint8_t Preset_Choice)
	{
		uint16_t Array_Of_Axis[5];
		for (int i = 0; i < 5; i++)
		{
			Array_Of_Axis[i] = Presets_Axis[Preset_Choice].Array_Of_Axis[i];
		}
		return Array_Of_Axis[5];
	};

	void Return(void);
}


void Generic_Menu::Generic_Menu
(String In_Title,  
 String In_Options[], 
 uint16_t In_Colours[], 
 uint16_t In_Axis[], 
 uint16_t In_Data, 
 uint8_t In_Buttons, 
 uint8_t In_Buttons_Size)
 // Constructor -   (Title)   
 //                 (Array of Menu Option Strings)
 //                 (Array of Background_Colour)   
 //                 (Array of Axis Values)  
 //                 (Data_Value)
 //                 (Amount of Buttons)
 //                 (Button Size in pixels)
{
	//Constructor Function
	// Initialises all Member Values
	Title = In_Title;
	Menu_Options[] = In_Options[];
	Array_Of_Colours[] = In_Colours[];
	Array_Of_Axis[] = In_Axis[];
	Data_Value = In_Data;
	Buttons = In_Buttons;
	Y_Axis_Button_Size = In_Buttons_Size;
}


void Generic_Menu::Draw_Main()
{
	//Definition of Draw Main Menu Mmember Function from Generic Menu Class
	//Background Colour
    myGLCD.fillScr(Array_Of_Colours[0]);
	//Text Back Colour
	myGLCD.setBackColor(Array_Of_Colours[2]);
	//Font Size for String
	myGLCD.setFont(BigFont);
	//Title Colour
	myGLCD.setColor(Array_Of_Colours[1]);
	//Prints Title string in the centre at size 1
	myGLCD.print(Title, CENTER, 1);
}


void Generic_Menu::Draw_Menu_Options()
{
	//Definition of Draw Main Menu Member Function from Generic Menu Class
	for (int i = 0; i < 4; i++)
	{
		myGLCD.setColor(Array_Of_Colours[3]); 
		//Fill of the rectangle Colour
		myGLCD.fillRoundRect(Array_Of_Axis[0], Array_Of_Axis[2], Array_Of_Axis[1], Array_Of_Axis[3]); 
		// Draws filled rounded rectangle
		myGLCD.setColor(Array_Of_Colours[4]); 
		// Outline colour is set
		myGLCD.drawRoundRect(Array_Of_Axis[0], Array_Of_Axis[2], Array_Of_Axis[1], Array_Of_Axis[3]); 
		// Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
		myGLCD.setFont(BigFont); 
		// Sets the font to big
		myGLCD.setBackColor(Array_Of_Colours[2]);
		// Sets the background color of the area where the text will be printed to green, same as the button
		int Text_Point = Array_Of_Axis[2] + 10;
		//Clculates placement of text based off box axis values
		myGLCD.print(Menu_Options[i], CENTER, Text_Point); 
		// Prints the string from button menu options array
		Array_Of_Axis[2] = Array_Of_Axis[2] + Array_Of_Axis[4];
		//Increments the y axis start value to move the box down
		Array_Of_Axis[3] = Array_Of_Axis[3] + Array_Of_Axis[4];
		//Increments the y axis end value to move the box down
	}
}

void Generic_Menu::Draw_Inputs_Option()
{
	//Definition of Draw Inputs Member Function from Generic Menu Class

}