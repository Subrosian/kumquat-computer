// calculate at compile time number of elements in an array
#define NUMELEMENTS(x) sizeof(x)/sizeof(x[0])

const int onboardLedPin = 13;

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
};


void setup() {
  Serial.begin(9600);
  pinMode(onboardLedPin, OUTPUT);

  for (byte i = 0; i < NUMELEMENTS(switches); i++)
  {
    pinMode(switches[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  checkSwitches();
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
