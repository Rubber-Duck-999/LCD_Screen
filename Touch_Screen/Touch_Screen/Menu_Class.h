/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                           <2017> Simon Crowther

           The Information in this document is the property of Simon Crowther and may not be copied, or communicated
           to a third party, or used for any other purpose than than for that for which it was supplied, without written
                                   consent from Simon Crowther

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 Project:          Menu_Class.h
 Description:      C plus plus file that contains the class for menus and namespace data sturucture for creating presets menu's of the
                   user's choice


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 Change History:
      Version         Date            Author          Description
      -------         ----            ------          -----------
      1.0            24/10/17         S.Crowther      Initial version
      1.1            25/10/17         S.Crowther      Added Namespace with data structure for presets 
      1.2            27/10/17         S.Crowther      Added changes to main functions created in the namespace presets, swapped
                                                      the longer functions with shorter and more useful ones
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#ifndef _MENU_CLASS_h
#define _MENU_CLASS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

const int Debug_Mode_Class = 0;

namespace Presets
{
	uint16_t Get_Colours(int Preset_Choice, uint8_t Colour_Choice);
	uint16_t Get_Axis(int Preset_Choice, uint8_t Axis_Choice);
	uint8_t Get_Amount_Of_Buttons_Preset(int Preset_Choice);
	uint8_t Get_Button_Size_Preset(int Preset_Choice);
}


class Generic_Menu
{//Class
	private:
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
	  
	  uint16_t Array_Of_Axis[5];
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
      Generic_Menu 
	     (String In_Title,
		  String In_Options[],
		  uint16_t In_Colours[],
		  uint16_t In_Axis[],
		  uint16_t In_Data,
		  uint8_t In_Buttons,
		  uint8_t In_Buttons_Size);
	  
	  //Declaration of member functions
	  //Definition in Cpp file of Menu_Class
	  void Draw_Main();
	  void Draw_Menu_Options();
	  void Draw_Inputs_Option();
	  void Draw_Frame(uint8_t Mode);
	  uint8_t Read_Axis(int Pin, uint8_t Mode);
	  
	  //bool Draw_Switch_Option);  
	  //Future Switch menu to be added
};

#endif

