//calculate at compile time number of elements in an array
#define NUMELEMENTS(x) sizeof(x)/sizeof(x[0])

//Setting
const int onboardLedPin = 13;

//Setting up the switches
struct SWITCH
{
  const byte pin;
  char label[20];
  bool state;
};

SWITCH switches[] =
{
  {3, "Switch A0", 0},
  {4, "Switch A1", 0},
  {5, "Switch A2", 0},
  {6, "Switch A3", 0},
  {7, "Switch A4", 0},
  {8, "Switch A5", 0},
  {9, "Switch A6", 0},
  {10, "Switch A7", 0},
  {11, "Switch B0", 0},
  {12, "Switch B1", 0},
  {14, "Switch B2", 0},
  {15, "Switch B3", 0},
  {16, "Switch B4", 0},
  {17, "Switch B5", 0},
  {20, "Switch B6", 0},
  {21, "Switch B7", 0},
  {22, "Switch C0", 0},
  {23, "Switch C1", 0},
  {28, "Switch C2", 0},
  {29, "Switch C3", 0},
  {30, "Switch C4", 0},
  {31, "Switch C5", 0},
  {32, "Switch C6", 0},
  {33, "Switch C7", 0},
};

//Setting up the buttons
struct BUTTON
{
  const byte pin;
  char label[20];
  bool state;
};

BUTTON buttons[] =
{
  {34, "Button 0", 0},
  {35, "Button 1", 0},
  {36, "Button 2", 0},
  {37, "Button 3", 0},
  {38, "Button 4", 0},
  {39, "Button 5", 0},
};


void setup() {
  Serial.begin(9600);
  pinMode(onboardLedPin, OUTPUT);

  for (byte i = 0; i < NUMELEMENTS(switches); i++)
  {
    pinMode(switches[i].pin, INPUT_PULLUP);
  }
  for (byte i = 0; i < NUMELEMENTS(buttons); i++)
  {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  checkSwitches();
  checkButtons();
  delay(15);
}

void checkSwitches() {
  for (byte i = 0; i < NUMELEMENTS(switches); i++)
  {
    if (!switches[i].state)
    {
      if (digitalRead(switches[i].pin) == LOW)
      {
        switches[i].state = true;
        Serial.print("INFO: ");
        Serial.print(switches[i].label);
        Serial.println(" is On");
      }
    }
    else
    {
      if (digitalRead(switches[i].pin) == HIGH)
      {
        switches[i].state = false;
        Serial.print("INFO: ");
        Serial.print(switches[i].label);
        Serial.println(" is Off");
      }
    }
  }
}

void checkButtons() {
  for (byte i = 0; i < NUMELEMENTS(buttons); i++)
  {
    if (!buttons[i].state)
    {
      if (digitalRead(buttons[i].pin) == LOW)
      {
        buttons[i].state = true;
        Serial.print("INFO: ");
        Serial.print(buttons[i].label);
        Serial.println(" is On");
      }
    }
    else
    {
      if (digitalRead(buttons[i].pin) == HIGH)
      {
        buttons[i].state = false;
        Serial.print("INFO: ");
        Serial.print(buttons[i].label);
        Serial.println(" is Off");
      }
    }
  }
}
