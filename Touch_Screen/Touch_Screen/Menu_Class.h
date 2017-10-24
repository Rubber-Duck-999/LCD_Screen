#ifndef _MENU_CLASS_h
#define _MENU_CLASS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


namespace Presets
{
	uint16_t Get_Array_Of_Colours(uint8_t Preset_Choice);
	uint16_t Get_Array_Of_Axis(uint8_t Preset_Choice);
	void Return(void);
}


class Generic_Menu
{//Class
	protected:
	  //Allows access to sub-classes

	  String   Title;
	  String   Menu_Options[4];
	  //String title is the title for each page
	  //Array of menu options strings are the button choices
	  
	  uint16_t Array_Of_Colours[5];
	  //0 - Background_Screen_Colour;
	  //1 - Title_Colour;
	  //2 - Text_Box_Colour;
	  //3 - Box_Colour_Fill;
	  //4 - Box_Colour_Outline;
	  
	  uint16_t Array_of_Axis_Values[5];
	  //X_Axis_1, 
	  //X_Axis_2;
	  //Y_Axis_1, 
	  //Y_Axis_2;
	  //Difference_Y_Axis;
	  
	  uint16_t Data_Value;
	  //Data value used for outputting on screen
	  
	  uint8_t Buttons;
	  //Amount of buttons required
	  
	  uint8_t Y_Axis_Button_Size;
	  //Size of Buttons on the screen
	  
public:
   
      // Constructor -   (Title)   
	  //                 (Array of Menu Option Strings)
	  //                 (Array of Background_Colour)   
	  //                 (Array of Axis Values)  
	  //                 (Data_Value)
	  //                 (Amount of Buttons)
	  //                 (Button Size in pixels)
      Generic_Menu (String,  String[], uint16_t[], uint16_t[], uint16_t, uint8_t, uint8_t); 
	  
	  //Declaration of member functions
	  //Definition in Cpp file of Menu_Class
	  void Draw_Main();
	  void Draw_Menu_Options();
	  int  Draw_Inputs_Option();
	  
	  //bool Draw_Switch_Option);  
	  //Future Switch menu to be added
};

#endif

