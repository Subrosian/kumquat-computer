//calculate at compile time number of elements in an array
#define NUMELEMENTS(x) sizeof(x)/sizeof(x[0])

//Neopixel stuff
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define neopixelPin 2
#define neopixelNum 32
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(neopixelNum, neopixelPin, NEO_GRB + NEO_KHZ800);

//Setting variables
const int onboardLedPin = 13;
int mode = 0;
int input1 = 0;
int input2 = 0;
int output = 0;
String outputBin = 0;

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
  {3, "Switch A0", 15, 0},
  {4, "Switch A1", 14, 0},
  {5, "Switch A2", 13, 0},
  {6, "Switch A3", 12, 0},
  {7, "Switch A4", 11, 0},
  {8, "Switch A5", 10, 0},
  {9, "Switch A6", 9, 0},
  {10, "Switch A7", 8, 0},
  {11, "Switch B0", 0, 0},
  {12, "Switch B1", 1, 0},
  {14, "Switch B2", 2, 0},
  {15, "Switch B3", 3, 0},
  {16, "Switch B4", 4, 0},
  {17, "Switch B5", 5, 0},
  {20, "Switch B6", 6, 0},
  {21, "Switch B7", 7, 0},
  {22, "Switch C0", -1, 0},
  {23, "Switch C1", -1, 0},
  {28, "Switch C2", -1, 0},
  {29, "Switch C3", -1, 0},
  {30, "Switch C4", -1, 0},
  {31, "Switch C5", -1, 0},
  {32, "Switch C6", -1, 0},
  {33, "Switch C7", -1, 0},
};

byte switchesBankA[] = {0, 1, 2, 3, 4, 5, 6, 7};
byte switchesBankB[] = {8, 9, 10 , 11, 12, 13, 14, 15};
byte switchesBankC[] = {16, 17, 18, 19, 20, 21, 22, 23};

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
byte buttonsBankA[] = {0, 1, 2, 3, 4, 5};

//Setting up LEDs
struct LED
{
  const byte number;
  char label[20];
  bool state;
};

LED leds[] =
{
  {0, "LED B0", 0},
  {1, "LED B1", 0},
  {2, "LED B2", 0},
  {3, "LED B3", 0},
  {4, "LED B4", 0},
  {5, "LED B5", 0},
  {6, "LED B6", 0},
  {7, "LED B7", 0},
  {8, "LED A7", 0},
  {9, "LED A6", 0},
  {10, "LED A5", 0},
  {11, "LED A4", 0},
  {12, "LED A3", 0},
  {13, "LED A2", 0},
  {14, "LED A1", 0},
  {15, "LED A0", 0},
  {16, "LED O0", 0},
  {17, "LED O1", 0},
  {18, "LED O2", 0},
  {19, "LED O3", 0},
  {20, "LED O4", 0},
  {21, "LED O5", 0},
  {22, "LED O6", 0},
  {23, "LED O7", 0},
  {24, "LED O8", 0},
  {25, "LED O9", 0},
  {26, "LED O10", 0},
  {27, "LED O11", 0},
  {28, "LED O12", 0},
  {29, "LED O13", 0},
  {30, "LED O14", 0},
  {31, "LED O15", 0},
};

byte ledsBankA[] = {15, 14, 13, 12, 11, 10, 9, 8};
byte ledsBankB[] = {0, 1, 2, 3, 4, 5, 6, 7};
byte ledsBankC[] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

void setup() {
  Serial.begin(9600);
  pinMode(onboardLedPin, OUTPUT);
  pixels.begin(); // This initializes the NeoPixel library.

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
  checkMode();
  updateLeds();
  if (mode == 1) {
    modeAdd();
  }
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
        Serial.print(" is On. ");
        if (switches[i].linkedLed != -1) {
          Serial.print("Linked LED is " );
          Serial.print(switches[i].linkedLed);
          leds[switches[i].linkedLed].state = 1;
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

void checkMode() {
//  if (switches[16].state == 1) {
    if (switches[16].state == 1) {
    mode = 1;
  }
}

void updateLeds() {
  for (byte i = 0; i < NUMELEMENTS(leds); i++)
  {
    if (leds[i].state == 1) {
      pixels.setPixelColor(i, pixels.Color(0, 20, 0)); // Moderately bright red color.
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // black
    }
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void modeAdd() {
  Serial.println("---");
  convertInput1ToDec();
  convertInput2ToDec();
  output = input1 + input2;
  Serial.print("Output:");
  Serial.println(output);
  convertOutputToBin();
  Serial.print("OutputBin:");
  Serial.println(outputBin);
  clearLedOutputState();
  sendOutputToLeds();
}

void convertInput1ToDec() {
  input1 = (switches[0].state * pow(2, 0)) + (switches[1].state * pow(2, 1)) + (switches[2].state * pow(2, 2)) + (switches[3].state * pow(2, 3)) + (switches[4].state * pow(2, 4)) + (switches[5].state * pow(2, 5)) + (switches[6].state * pow(2, 6)) + (switches[7].state * pow(2, 7));
}

void convertInput2ToDec() {
  input2 = (switches[8].state * pow(2, 0)) + (switches[9].state * pow(2, 1)) + (switches[10].state * pow(2, 2)) + (switches[11].state * pow(2, 3)) + (switches[12].state * pow(2, 4)) + (switches[13].state * pow(2, 5)) + (switches[14].state * pow(2, 6)) + (switches[15].state * pow(2, 7));
}

void convertOutputToBin() {
  outputBin = String(output, BIN);
}

void sendOutputToLeds() {
  Serial.print("Length:");
  Serial.println(outputBin.length());
  //for (int i = 0; i <= outputBin.length(); i++)
  for (int i = outputBin.length() - 1, j = 0, k = 16; i >= 0; i--, j++, k++)
  {

    Serial.print("Character ");
    Serial.print(j);
    Serial.print(" LED ");
    Serial.print(k);
    Serial.print("=");
    Serial.println(outputBin.charAt(i));
    if (outputBin.charAt(i) == '1') {
      leds[k].state = 1;
    } else {
      leds[k].state = 0;
    }
  }
}

void clearLedOutputState() {
  for (byte i = 16; i < NUMELEMENTS(leds); i++)
  {
    leds[i].state = 0;
  }
}
