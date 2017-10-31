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
      1.3            28/10/17         S.Crowther      Added a preset to Data_Input structure, Created the Draw_Input_Data function
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
	Preset_Colours Presets_Colours[4]
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
		   VGA_WHITE
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
		{
		 {
		   VGA_GREEN,
		   VGA_BLACK,
		   VGA_GREEN,
		   VGA_BLACK,
		   VGA_WHITE
		  }
		},//Preset 3
		{
		  {
		   VGA_BLUE,
		   VGA_WHITE,
		   VGA_BLUE,
		   VGA_WHITE,
		   VGA_BLACK
		  }
		}
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
	};
	
	uint8_t Get_Button_Size_Preset(int Preset_Choice)
	{
		return Presets_Buttons[Preset_Choice].Button_Size;
	};

	struct Preset_Data_Input
	{
		const uint16_t Input_Array_Of_Colours[6];
		//0 - Exit_Button_Colour_Fill;
		//1 - Exit_Button_Colour_Outline;
		//2 - Text_Colour;
		//3 - Arrow_Line_Colour;
		//4 - Segment_Colour;
		//5 - Background_Colour_Fill;
		const uint16_t Exit_Axis[15];
		//0  - Exit_X_Axis_1;
		//1  - Exit_X_Axis_2;
		//2  - Exit_Y_Axis_1;
		//3  - Exit_Y_Axis_2;
		//4  - Exit_Text_X_Axis;
		//5  - Exit_Text_Y_Axis;
		//6  - Arrow_line_X_Axis_1;
		//7  - Arrow_line_X_Axis_2;
		//8  - Arrow_line_Y_Axis_1;
		//9  - Arrow_line_Y_Axis_2;
		//10 - Measurement_X_Axis  
		//11 - Measurement_Y_Axis
		//12 - Title_Axis
		//13 - Unit_X_Axis
		//14 - Unit_Y_Axis
	};

	Preset_Data_Input Data_Input[1]
	{
		{
			//Input_Array_Of_Colours
			{
             VGA_RED,  //0 - Exit_Button_Colour_Fill;
			 VGA_BLACK,//1 - Exit_Button_Colour_Outline;
			 VGA_WHITE,//2 - Text_Colour;
			 VGA_BLUE, //3 - Arrow_Line_Colour;
			 VGA_GREEN,//4 - Segment_Colour;
			 VGA_WHITE //5 - Background_Colour_Fill;
			},
		    //Exit_Axis
			{
             10, //0  - Exit_X_Axis_1;
			 90, //1  - Exit_X_Axis_2;
			 10, //2  - Exit_Y_Axis_1;
			 36, //3  - Exit_Y_Axis_2;
			 20, //4  - Exit_Text_X_Axis;
			 15, //5  - Exit_Text_Y_Axis;
			 0,	 //6  - Arrow_line_X_Axis_1;
			 319,//7  - Arrow_line_X_Axis_2;
			 100,//8  - Arrow_line_Y_Axis_1;
			 105,//9  - Arrow_line_Y_Axis_2;
			 130,//10 - Measurement_X_Axis  
			 120,//11 - Measurement_Y_Axis
			 50, //12 - Title_Axis
			 235,//13 - Unit_X_Axis
			 178 //14 - Unit_Y_Axis
			},
		}
	};
	uint16_t Get_Data_Colours(int Preset_Choice, uint8_t Colour_Choice)
	{
		return Data_Input[Preset_Choice].Input_Array_Of_Colours[Colour_Choice];
	};

	uint16_t Get_Data_Axis(int Preset_Choice, uint8_t Axis_Choice)
	{
		return Data_Input[Preset_Choice].Exit_Axis[Axis_Choice];
	};
}


Generic_Menu::Generic_Menu
(String In_Title,  
 String In_Options[], 
 uint16_t In_Axis[], 
 uint8_t In_Buttons, 
 uint8_t In_Buttons_Size,
 uint8_t Brightness_Level)
	// Constructor -   (Title)   
	//                 (Array of Menu Option Strings)  
	//                 (Array of Axis Values)  
	//                 (Amount of Buttons)	
	//                 (Button Size in pixels)
    //                 (Brightness_Level)
{
	//Constructor Function
	// Initialises all Member Values
	myGLCD.setBrightness(Brightness_Level);
	static int Initialise_Lcd = 1;
	Title = In_Title;
	for(int i = 0; i < 4; i++)
	{
	   Menu_Options[i] = In_Options[i];		
	}
	for (int i = 0; i < 5; i++)
	{
		Array_Of_Axis[i] = In_Axis[i];
	}
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


void Generic_Menu::Draw_Main(uint8_t Preset_Choice)
{
	//Definition of Draw Main Menu Mmember Function from Generic Menu Class
	//Background Colour
	for (int i = 0; i < 5; i++)
	{
		Array_Of_Colours[i] = Presets::Get_Colours(Preset_Choice, i);
		if (Debug_Mode_Class == 1)
		{
			Serial.print("Colours");
			Serial.println(Array_Of_Colours[i]);
		}
		delay(100);
	}
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
	uint16_t Array[5];
	for(int i = 0; i < 5; i++)
	{
		Array[i] = Array_Of_Axis[i];
	}
	for (int i = 0; i < Buttons; i++)
	{
		myGLCD.setColor(Array_Of_Colours[3]); 
		//Fill of the rectangle Colour
		myGLCD.fillRoundRect(Array[0], Array[2], Array[1], Array[3]);
		// Draws filled rounded rectangle
		myGLCD.setColor(Array_Of_Colours[4]); 
		// Outline colour is set
		myGLCD.drawRoundRect(Array[0], Array[2], Array[1], Array[3]);
		// Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
		myGLCD.setFont(BigFont); 
		// Sets the font to big
		myGLCD.setBackColor(Array_Of_Colours[3]);
		// Sets the background color of the area where the text will be printed to green, same as the button
		int Text_Point = Array[2] + 10;
		//Clculates placement of text based off box axis values
		myGLCD.print(Menu_Options[i], CENTER, Text_Point); 
		// Prints the string from button menu options array
		Array[2] = Array[2] + Array[4];
		//Increments the y axis start value to move the box down
		Array[3] = Array[3] + Array[4];
		//Increments the y axis end value to move the box down
		{
			if (Debug_Mode_Class == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					Serial.print("String: \n");
					Serial.println(Menu_Options[i]);
					delay(100);
				}
				Serial.print("Array of Axis: \n");
				for (int i = 0; i < 5; i++)
				{
					Serial.println(Array_Of_Axis[i]);
					delay(100);
				}
				Serial.print("String Place: \n");
				Serial.println(Text_Point);
				delay(100);
			}
		}
	}
}

void Generic_Menu::Draw_Inputs_Option(String Title, String Unit, uint8_t Preset_Choice, String Measurement, uint16_t Data_Value, uint8_t Pin)
{
	myGLCD.clrScr();
	uint16_t Array_Colours[6], Array_Axis[15];
	Serial.print("Input Colours");
	for (int i = 0; i < 6; i++)
	{
		Array_Colours[i] = Presets::Get_Data_Colours(Preset_Choice, i);
		if (Debug_Mode_Class == 1)
		{
			Serial.println(Array_Colours[i]);
		}
		delay(100);
	}
	Serial.print("Input Axis");
	for (int i = 0; i < 15; i++)
	{
		Array_Axis[i] = Presets::Get_Data_Axis(Preset_Choice, i);
		if (Debug_Mode_Class == 1)
		{
			Serial.println(Array_Axis[i]);
		}
		delay(100);
	}
	//Input_Array_Of_Colours[6];
	//0 - Exit_Button_Colour_Fill;
	//1 - Exit_Button_Colour_Outline;
	//2 - Text_Colour;
	//3 - Arrow_Line_Colour;
	//4 - Segment_Colour;
	//5 - Background_Colour_Fill;

	//Exit_Axis[6];
	//0  - Exit_X_Axis_1;
	//1  - Exit_X_Axis_2;
	//2  - Exit_Y_Axis_1;
	//3  - Exit_Y_Axis_2;
	//4  - Exit_Text_X_Axis;
	//5  - Exit_Text_Y_Axis;
	//6  - Arrow_line_X_Axis_1
	//7  - Arrow_line_X_Axis_2
	//8  - Arrow_line_Y_Axis_1
	//9  - Arrow_line_Y_Axis_2
	//10 - Measurement_X_Axis
	//11 - Measurement_Y_Axis
	//12 - Title_Axis
	//13 - Unit_X_Axis
	//14 - Unit_Y_Axis

	//0 - Exit Button Colour Fill;
	myGLCD.fillScr(Array_Colours[5]);
	myGLCD.setColor(Array_Colours[0]);
	myGLCD.fillRoundRect(Array_Axis[0], Array_Axis[2], Array_Axis[1], Array_Axis[3]);
	//Exit Button Draw frame
	myGLCD.setColor(Array_Colours[1]);
	myGLCD.drawRoundRect(Array_Axis[0], Array_Axis[2], Array_Axis[1], Array_Axis[3]);
	//Write and set colours of exit button
	myGLCD.setFont(BigFont);
	myGLCD.setBackColor(Array_Colours[0]); // Same Exit button fill
	myGLCD.setColor(Array_Colours[2]);
	myGLCD.print("Exit", Array_Axis[4], Array_Axis[5]);
	//Arrow line and Title
	myGLCD.setBackColor(Array_Colours[5]);
	myGLCD.setColor(Array_Colours[3]);
	myGLCD.drawLine(Array_Axis[6], Array_Axis[8], Array_Axis[7], Array_Axis[8]);
	myGLCD.setFont(BigFont);
	myGLCD.print(Title, CENTER, Array_Axis[12]);
	//Measurement print on screen
	myGLCD.setFont(BigFont);
	myGLCD.print(Measurement, Array_Axis[10], Array_Axis[11]);
	//Prints Units
	myGLCD.setFont(SmallFont);
	myGLCD.print(Unit, Array_Axis[13], Array_Axis[14]);
	//Loop to continully update part of screen only saving memory
	bool Exit_Loop = false;
	uint16_t Data_Value_Loop = Data_Value;
	uint16_t Interval = 10000;
	uint16_t Previous_Millis = 0;
	unsigned long Current_Millis = millis();
	bool Continue_Loop = true;
	while (Continue_Loop)
	{
		if(Debug_Mode_Class == 1)
		{
			Serial.print("Data Value Publish \n");
		}
		Previous_Millis = Current_Millis;
		myGLCD.setFont(SevenSegNumFont);
		myGLCD.setColor(Array_Colours[4]);
		myGLCD.setBackColor(Array_Colours[5]);
		myGLCD.printNumI(Data_Value_Loop, Array_Axis[10], (Array_Axis[11] + 15), 3, '0');
		Data_Value_Loop++;
		delay(50);
		if (Data_Value_Loop > 1000)
		{
			Continue_Loop = false;
		}
		//Exits the loop if time is larger than interval
	}
}

void Generic_Menu::Draw_Frame(uint8_t Mode) 
{
	//Do something with Generic Menu object

  uint16_t Difference = (Array_Of_Axis[4] * Mode);
  uint16_t Y_Axis[4];
  for(int i = 2; i < 4; i++)
  {
	 Y_Axis[i] = Array_Of_Axis[i] + Difference;
  }
  if (Debug_Mode_Class == 1)
  {
	  Serial.print("Frame Axis: \n");
	  Serial.println(Y_Axis[2]);
	  Serial.println(Y_Axis[3]);
	  Serial.println(Difference);
	  delay(1000);
  }
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.drawRoundRect
	(Array_Of_Axis[0],
  	 Y_Axis[2],
	 Array_Of_Axis[1],
	 Y_Axis[3]
	);
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
	delay(500);
	return Mode;
}
