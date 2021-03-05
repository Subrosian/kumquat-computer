// calculate at compile time number of elements in an array
#define NUMELEMENTS(x) sizeof(x)/sizeof(x[0])

const int onboardLedPin = 13;

struct SWITCH
{
  const byte pin;
  char label[20];
  bool lastState;
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
  for (byte i = 0; i < NUMELEMENTS(switches); i++)
  {
    if (!switches[i].lastState)
    {
      if (digitalRead(switches[i].pin) == LOW)
      {
        switches[i].lastState = true;
        Serial.print("INFO: ");
        Serial.print(switches[i].label);
        Serial.print(" is Low");
      }
    }
    else
    {
      if (digitalRead(switches[i].pin) == HIGH)
      {
        switches[i].lastState = false;
        Serial.print("INFO: ");
        Serial.print(switches[i].label);
        Serial.print(" is High");
      }
    }
  }
  delay(15);
}
