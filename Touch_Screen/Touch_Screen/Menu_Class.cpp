/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                           <2017> Simon Crowther

           The Information in this document is the property of Simon Crowther and may not be copied, or communicated
           to a third party, or used for any other purpose than than for that for which it was supplied, without written
                                   consent from Simon Crowther

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 Project:          Menu_Class.cpp
 Description:      C plus plus file that contains the class for menus and namespace data sturucture for creating presets menu's of the
                   user's choice


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 Change History:
      Version         Date            Author          Description
      -------         ----            ------          -----------
      1.0            24/10/17         S.Crowther      Initial version
      1.1            25/10/17         S.Crowther      Added Namespace with data structure for presets 
      1.2            27/10/17         S.Crowther      Added Read_Axis and Draw_Frame member functions in the class
                                                      created more presets and edited axis values inside preset 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include "Menu_Class.h"
#include <stdint.h>
#include "string.h"
#include "WString.h"
#include "UTFT.h"

UTFT    myGLCD(ITDB32S, 38, 39, 40, 41);
 //Parameters should be adjusted to your Display/Schield model

namespace Presets
{
	//Namespace for presets for colours in menu's
	// Contains two structures one for colours and axis

	struct Preset_Colours
	{
		uint16_t Array_Of_Colours[5];
	};

	//A data structure of four preset choices
	Preset_Colours Presets_Colours[2]
	{
		//0 - Background_Screen_Colour;
		//1 - Title_Colour;
		//2 - Text_Box_Colour;
		//3 - Box_Colour_Fill;
		//4 - Box_Colour_Outline;
		{  
		  {
		   VGA_RED,
		   VGA_BLACK,
		   VGA_RED,
		   VGA_BLACK,
		   VGA_RED
		  }
		},//Preset 1
		{
		  {
		   VGA_BLUE,
		   VGA_BLACK,
		   VGA_BLUE,
		   VGA_BLACK,
		   VGA_WHITE
		  }
		},//Preset 2
		//{
		//   {VGA_RED,
		//	VGA_BLACK,
		//	VGA_RED,
		//	VGA_BLUE,
		//    VGA_BLACK
		//   }
		//},//Preset 3         
		//{
		//   {VGA_RED,
		//	VGA_BLACK,
		//	VGA_RED,
		//	VGA_BLUE,
		//    VGA_BLACK
		//   }
		//},//Preset 4 
	};

	struct Preset_Axis
	{
		uint16_t Array_Of_Axis[5];
	};

	//A data structure of four preset choices
	Preset_Axis Presets_Axis[4]
	{
		//X_Axis_1, 
		//X_Axis_2;
		//Y_Axis_1, 
		//Y_Axis_2;
		//Difference_Y_Axis;
		{ 
		   {35,
            285,
            30,
			70,
            50
		   }
		},//Preset 1

		{ 
		   {55,
            265,
            30,
			70,
            45
		   }
		},//Preset 2

		{ 
		   {35,
            285,
            40,
			70,
            50
		   }
		},//Preset 3  

		{ 
		   {35,
            285,
            40,
			70,
            50
		   }
		}//Preset 4 
	};

	struct Preset_Buttons
	{
		const uint8_t Buttons;

		const uint8_t Button_Size;
	};

	Preset_Buttons Presets_Buttons[2]
	{
		{ 4, 40},
		
		{ 4, 40}	
	};
	//Namespace function that returns the array required for running class member functions
	//Done twice for presets and axis

	uint16_t Get_Colours(int Preset_Choice, uint8_t Colour_Choice)
	{
		return Presets_Colours[Preset_Choice].Array_Of_Colours[Colour_Choice];
	};

	uint16_t Get_Axis(int Preset_Choice, uint8_t Axis_Choice)
	{
		return Presets_Axis[Preset_Choice].Array_Of_Axis[Axis_Choice];
	};
	
	uint8_t Get_Amount_Of_Buttons_Preset(int Preset_Choice)
	{
		return Presets_Buttons[Preset_Choice].Buttons;
	}
	
	uint8_t Get_Button_Size_Preset(int Preset_Choice)
	{
		return Presets_Buttons[Preset_Choice].Button_Size;
	}
}


Generic_Menu::Generic_Menu
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
	static int Initialise_Lcd = 1;
	Title = In_Title;
	for(int i = 0; i < 5; i++)
	{
	   Array_Of_Colours[i] = In_Colours[i];
	   Array_Of_Axis[i] = In_Axis[i];
	}
	for(int i = 0; i < 4; i++)
	{
	   Menu_Options[i] = In_Options[i];		
	}
	Data_Value = In_Data;
	Buttons = In_Buttons;
	Y_Axis_Button_Size = In_Buttons_Size;
	if (Debug_Mode_Class == 1)
	{
		Serial.print("LCD Clear");
		Serial.println(Initialise_Lcd);
	}
	if (Initialise_Lcd == 1)
	{
		myGLCD.InitLCD();
		myGLCD.clrScr();
		Initialise_Lcd = 2;
	}
	if (Debug_Mode_Class == 1)
	{
		Serial.print("LCD Clear");
		Serial.println(Initialise_Lcd);
	}
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
	if (Debug_Mode_Class == 1)
	{
		Serial.println("Main has been Drawn");
	}
}


void Generic_Menu::Draw_Menu_Options()
{
	//Definition of Draw Main Menu Member Function from Generic Menu Class
	for (int i = 0; i < Buttons; i++)
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
		myGLCD.setBackColor(Array_Of_Colours[3]);
		// Sets the background color of the area where the text will be printed to green, same as the button
		int Text_Point = Array_Of_Axis[2] + 10;
		//Clculates placement of text based off box axis values
		myGLCD.print(Menu_Options[i], CENTER, Text_Point); 
		// Prints the string from button menu options array
		Array_Of_Axis[2] = Array_Of_Axis[2] + Array_Of_Axis[4];
		//Increments the y axis start value to move the box down
		Array_Of_Axis[3] = Array_Of_Axis[3] + Array_Of_Axis[4];
		//Increments the y axis end value to move the box down
		{
			if (Debug_Mode_Class == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					//Serial.print("String");
					//Serial.println(Menu_Options[i]);
					//delay(1000);
				}
				Serial.print("Array of Axis: ");
				for (int i = 0; i < 5; i++)
				{
					Serial.println(Array_Of_Axis[i]);
					delay(500);
				}
				Serial.print("String Place");
				Serial.println(Text_Point);
				delay(500);
			}
		}
	}
}

void Generic_Menu::Draw_Inputs_Option()
{
	//Definition of Draw Inputs Member Function from Generic Menu Class

}

void Generic_Menu::Draw_Frame(uint8_t Mode) 
{
	//Do something with Generic Menu object
  myGLCD.setColor(VGA_YELLOW);
  uint16_t Difference = (Array_Of_Axis[4] * Mode);
  int Y_Axis[2];
  for(int i = 2; i < 4; i++)
  {
	 Y_Axis[i - 2] = Array_Of_Axis[i] + Difference;
  }
  myGLCD.drawRoundRect
	(Array_Of_Axis[0],
  	 Y_Axis[0],
	 Array_Of_Axis[1],
	 Y_Axis[1]
	);
  myGLCD.setColor(VGA_BLUE);
  myGLCD.drawRoundRect(Array_Of_Axis[0], Y_Axis[0], Array_Of_Axis[1], Y_Axis[1]);
}

uint8_t Generic_Menu::Read_Axis(int Pin, uint8_t Mode)
{
	unsigned int X_Axis_Value = analogRead(Pin);
	if (X_Axis_Value > 750)
	{
		if (Mode < (Buttons - 1))
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
	return Mode;
}
