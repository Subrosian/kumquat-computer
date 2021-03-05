//calculate at compile time number of elements in an array
#define NUMELEMENTS(x) sizeof(x)/sizeof(x[0])

//Setting
const int onboardLedPin = 13;

//Setting up the switches
struct SWITCH
{
  const byte pin;
  char label[20];
  const int linkedLed;
  bool state;

};

SWITCH switches[] =
{
  {3, "Switch A0", 16, 0},
  {4, "Switch A1", 17, 0},
  {5, "Switch A2", 18, 0},
  {6, "Switch A3", 19, 0},
  {7, "Switch A4", 20, 0},
  {8, "Switch A5", 21, 0},
  {9, "Switch A6", 22, 0},
  {10, "Switch A7", 23, 0},
  {11, "Switch B0", 24, 0},
  {12, "Switch B1", 25, 0},
  {14, "Switch B2", 26, 0},
  {15, "Switch B3", 27, 0},
  {16, "Switch B4", 28, 0},
  {17, "Switch B5", 29, 0},
  {20, "Switch B6", 30, 0},
  {21, "Switch B7", 31, 0},
  {22, "Switch C0", -1, 0},
  {23, "Switch C1", -1, 0},
  {28, "Switch C2", -1, 0},
  {29, "Switch C3", -1, 0},
  {30, "Switch C4", -1, 0},
  {31, "Switch C5", -1, 0},
  {32, "Switch C6", -1, 0},
  {33, "Switch C7", -1, 0},
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

//Setting up LEDs
struct LED
{
  const byte number;
  char label[20];
  bool state;
};

LED leds[] =
{
  {0, "LED 0", 0},
  {1, "LED 1", 0},
  {2, "LED 2", 0},
  {3, "LED 3", 0},
  {4, "LED 4", 0},
  {5, "LED 5", 0},
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
  if (switches[3].state == true) {
    digitalWrite(onboardLedPin, HIGH);
  } else {
    digitalWrite(onboardLedPin, LOW);
  }
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
        Serial.print(" is On. ");
        if (switches[i].linkedLed != -1) {
          Serial.print("Linked LED is " );
          Serial.print(switches[i].linkedLed);
          leds[switches[i].linkedLed].state = 1;
        }
        Serial.println("");
        for (byte j = 0; j < NUMELEMENTS(leds); j++)
        {
          Serial.print(leds[j].state);
          Serial.print(",");
        }
        Serial.println("");
      }
    }
    else
    {
      if (digitalRead(switches[i].pin) == HIGH)
      {
        switches[i].state = false;
        Serial.print("INFO: ");
        Serial.print(switches[i].label);
        Serial.print(" is Off. ");
        if (switches[i].linkedLed != -1) {
          Serial.print("Linked LED is " );
          Serial.print(switches[i].linkedLed);
          leds[switches[i].linkedLed].state = 0;
        }
        Serial.println("");
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
