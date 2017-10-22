

/*
   This is Seulah Hyun's Project Code
*/

#include <UTFT.h>
#include <URTouch.h>
#include <Wire.h>
#define TOUCH_ORIENTATION  LANDSCAPE
//==== Creating Objects
UTFT    myGLCD(ITDB32S, 38, 39, 40, 41); //Parameters should be adjusted to your Display/Schield model
URTouch  myTouch( 6, 5, 4, 3, 2);

/*
 * Set Variables
 */
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t SmallFont[];
uint32_t cx, cy;
uint32_t rx[8], ry[8];
uint32_t clx, crx, cty, cby;
float px, py;
int dispx, dispy, text_y_center;
uint32_t calx, caly, cals;
char buf[13];
int x, y;
char Page, selectedUnit;
long duration;
int distanceInch, distanceCm;

int xR = 38;
int xG = 38;
int xB = 38;
int Volume = 0;
int Gain = 0;

int Volume_Wire = 10;
int Gain_Wire = 10;
int Bass_Wire = 10;
int Middle_Wire = 0;
int Treble_Wire = 0;


void setup() {
  // Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();
  Serial.begin(9600);
  myTouch.setPrecision(PREC_HI);
  dispx = myGLCD.getDisplayXSize();
  dispy = myGLCD.getDisplayYSize();
  text_y_center = (dispy / 2) - 6;
  myTouch.InitTouch();
  myGLCD.clrScr();
  MainHomeScreen();
  Page = '0';
  selectedUnit = '0';
  Wire.begin();
}

void loop()  { 
  // Home Screen
 // myGLCD.clrScr();
  Wire.beginTransmission(3); // transmit to device #3
  // Sends wire data for this slider data
  Wire.write(Volume_Wire); 
  Serial.println(Volume_Wire);
  Wire.write(Gain_Wire);
  Wire.write(Bass_Wire);
  Wire.write(Middle_Wire);
  Wire.write(Treble_Wire);
  Wire.endTransmission();    // stop transmitting 
  if (Page == '0') {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x=myTouch.getX(); // X coordinate where the screen has been pressed
      y=myTouch.getY(); // Y coordinates where the screen has been pressed
      // If we press the Distance Sensor Button 
      if ((x>=35) && (x<=285) && (y>=40) && (y<=110)) {
        Frame(35, 40, 285, 110); // Custom Function -Highlighs the buttons when it's pressed
        Page = '1'; // Indicates that we are the first example
        myGLCD.clrScr(); // Clears the screen
        Amplifier();     
      }
      if ((x>=35) && (x<=285) && (y>=130) && (y<=200)) {
        Frame(35, 130, 285, 200);
        Page = '2';
        myGLCD.clrScr();
        Equaliser();
      }  
    }
  }
  if (Page == '1') {   
     Amplifier();
     Buttons_Amplifier();
    if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
        if ((x>=10) && (x<=90) &&(y>=10) && (y<=36)) {
          Frame(10, 25, 90, 46);
          Page = '0';
          myGLCD.clrScr();
          MainHomeScreen();
        }
    }
  }
  if (Page == '2') {
    Equaliser();
    Buttons_Equaliser();
    if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
        if ((x>=10) && (x<=90) &&(y>=10) && (y<=36)) {
          Frame(10, 10, 90, 36);
          Page = '0';
          myGLCD.clrScr();
          MainHomeScreen();
        }
    }
  }
}

void Welcome()
{
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("Sound System", CENTER, 50);
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.setFont(BigFont); // Sets the font to small
  myGLCD.print("by Seulah Hyun", CENTER, 91); // Prints the string
  delay(1000);
}


void MainHomeScreen() {
  myGLCD.fillScr(VGA_RED);
  myGLCD.setBackColor(VGA_RED);
  myGLCD.setFont(BigFont);
  myGLCD.setColor(VGA_BLACK);
  myGLCD.print("Main Menu", CENTER, 1);
  myGLCD.setColor(VGA_BLACK); // Sets green color
  myGLCD.fillRoundRect (35, 40, 285, 110); // Draws filled rounded rectangle
  myGLCD.setColor(VGA_WHITE); // Sets color to white
  myGLCD.drawRoundRect (35, 40, 285, 110); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(VGA_BLACK); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("Amplifier", CENTER, 65); // Prints the string
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (35, 130, 285, 200);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (35, 130, 285, 200);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.print("Equalizer", CENTER, 155);
}

void Frame(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(VGA_TEAL);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

void Amplifier() {
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (10, 25, 90, 46);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 25, 90, 46);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("Back", 18, 28);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("Amplifier", CENTER, 1);
  myGLCD.print("Slider:", 10, 95);
  myGLCD.print("V", 10, 135);
  myGLCD.print("G", 10, 175);
  myGLCD.setColor(VGA_BLUE);
  myGLCD.drawLine(0, 75, 319, 75);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(30, 131, 310, 148); // R - Slider
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setFont(BigFont);
  myGLCD.print("Volume:", 30, 153);
  myGLCD.drawRect(30, 174, 310, 191);
  myGLCD.print("Gain:", 30, 195);
}

void Buttons_Amplifier() {
  if (myTouch.dataAvailable()) {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    if ( (y >= 130) && (y <= 156)) {
      xR = x; // Stores the X value where the screen has been pressed in to variable xR
      if (xR <= 38) { // Confines the area of the slider to be above 38 pixels
        xR = 38;
      }
      if (xR >= 303) { /// Confines the area of the slider to be under 310 pixels
        xR = 303;
      }
    }
    // Area of the Green color slider
    if ( (y >= 170) && (y <= 196)) {
      xG = x;
      if (xG <= 38) {
        xG = 38;
      }
      if (xG >= 303) {
        xG = 303;
      }
    }
  }
  // Maps the values of the X - Axis from 38 to 0 and 310 to 255, because we need values from 0 to 255 for turning on the led
  int xRC = map(xR, 38, 310, 0, 255);
  Volume = xRC/2.5;
  Volume_Wire = xRC;
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setFont(BigFont);
  myGLCD.printNumI(Volume,150, 153, 3,'0');
  myGLCD.print("%", 205,153);
  int xGC = map(xG, 38, 310, 0, 255);
  Gain_Wire = xGC;
  Gain = xGC/2.5;
  myGLCD.printNumI(Gain,120, 195, 3,'0');
  myGLCD.print("%", 185,195);

  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xR, 132, (xR + 4), 147); 
  myGLCD.setColor(VGA_RED);
  myGLCD.fillRect(31, 132, (xR - 1), 147);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xR + 5), 132, 309, 147);

  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xG, 175, (xG + 4), 190);
  myGLCD.setColor(VGA_BLUE);
  myGLCD.fillRect(31, 175, (xG - 1), 190);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xG + 5), 175, 309, 190);
}

void Equaliser()
{
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (10, 10, 90, 36);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 10, 90, 36);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("Back", 18, 15);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("Equaliser", CENTER, 50);
  myGLCD.print("Slider", 10, 95);
  myGLCD.print("B", 10, 135);
  myGLCD.print("M", 10, 175);
  myGLCD.print("T", 10, 215);
  myGLCD.setColor(VGA_BLUE);
  myGLCD.drawLine(0, 75, 319, 75);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(30, 138, 310, 148); // R - Slider
  myGLCD.drawRect(30, 178, 310, 188);
  myGLCD.drawRect(30, 218, 310, 228);
}



void Buttons_Equaliser() {
  if (myTouch.dataAvailable()) {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    // Area of the Bass slider
    if ( (y >= 130) && (y <= 156)) {
      xR = x; // Stores the X value where the screen has been pressed in to variable xR
      if (xR <= 38) { // Confines the area of the slider to be above 38 pixels
        xR = 38;
      }
      if (xR >= 303) { /// Confines the area of the slider to be under 310 pixels
        xR = 303;
      }
    }
    // Area of the Middle slider
    if ( (y >= 170) && (y <= 196)) {
      xG = x;
      if (xG <= 38) {
        xG = 38;
      }
      if (xG >= 303) {
        xG = 303;
      }
    }
    // Area of the Treble slider
    if ( (y >= 210) && (y <= 236)) {
      xB = x;
      if (xB <= 38) {
        xB = 38;
      }
      if (xB >= 303) {
        xB = 303;
      }
    }
  }
  // Maps the values of the X - Axis from 38 to 0 and 310 to 255, because we need values from 0 to 255 for turning on the led
  int xRC = map(xR, 38, 310, 0, 255);
  Bass_Wire = xRC;
  int xGC = map(xG, 38, 310, 0, 255);
  Middle_Wire = xGC;
  int xBC = map(xB, 38, 310, 0, 255);
  Treble_Wire = xBC;

  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xR, 139, (xR + 4), 147); // Positioner
  myGLCD.setColor(VGA_LIME);
  myGLCD.fillRect(31, 139, (xR - 1), 147);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xR + 5), 139, 309, 147);

  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xG, 179, (xG + 4), 187);
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.fillRect(31, 179, (xG - 1), 187);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xG + 5), 179, 309, 187);

  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xB, 219, (xB + 4), 227);
  myGLCD.setColor(VGA_SILVER);
  myGLCD.fillRect(31, 219, (xB - 1), 227);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xB + 5), 219, 309, 227);
}


