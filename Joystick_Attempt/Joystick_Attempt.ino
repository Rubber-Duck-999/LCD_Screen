// Arduino pin numbers
const int SW_pin = 8; // digital pin connected to switch output
const int X_pin = 1; // analog pin connected to X output
const uint8_t Y_pin = 0; // analog pin connected to Y output

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
}

void loop()
{
  static int Mode = 0;
  static int Mode_Return = 0;
  if (Mode == Mode_Return)
  {
    Mode_Return = Axis(Mode);
  }
}

int Axis(int Mode)
{
  uint8_t X_Axis_Value = analogRead(Y_pin);
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
  return Mode;
}
