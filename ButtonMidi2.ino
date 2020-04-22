
#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); // Change to (0x27,16,2) for 16x2 LCD.

struct MySettings : public midi::DefaultSettings {
  static const long BaudRate = 128000;
};

enum NoteStatus : bool {
  NOT_PLAYING = 0,
  PLAYING
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings)


// constants won't change. They're used here to set pin numbers:
const int buttonPin[17] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38}; // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // current state of the button
int lastButtonState[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // previous state of the button
unsigned long cd[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Cooldown

int hamIdx = 0;
String ham[273] = 
  {
  "I am William",
  "Heres some music",
  "Sam I am",
  "That Sam-I-am",
  "That Sam-I-am!",
  "I do not like",
  "That Sam-I-am",
  "Do you like",
  "Green eggs ",
  "and ham.",
  "I do not ",
  "like them,",
  "Sam-I-am.",
  "I do not like",
  "Green eggs",
  "and ham.",
  "Would you ",
  "like them",
  "Here or there?",
  "I would not",
  "like them",
  "Here or there.",
  "I would not",
  "like them",
  "Anywhere.",
  "I do not like",
  "Green eggs",
  "and ham.",
  "I do not like",
  "them, Sam-I-am",
  "Would you like",
  "in them a house?",
  "Would you like",
  "them with a",
  "mouse?",
  "I do not like",
  "them in a house.",
  "I do not like",
  "them with ",
  "a mouse.",
  "I do not like",
  "them here",
  "or there",
  "I do not like",
  "them Anywhere.",
  "I do not like",
  "Green eggs",
  "and ham.",
  "I do not like",
  "them, Sam-I-am",
  "Would you eat",
  "them in a box?",
  "Would you eat",
  "them with a fox?",
  "Not in a box.",
  "Not with a fox.",
  "Not in a house.",
  "Not with a mouse.",
  "I would not eat",
  "them here ",
  "or there.",
  "I would not eat",
  "them anywhere.",
  "I would not eat",
  "green eggs ",
  "and ham.",
  "I do not like ",
  "them, Sam-I-am.",
  "Would you? ",
  "Could you?",
  "In a car?",
  "Eat them! ",
  "Eat them! ",
  "Here they are.",
  "I would not,",
  "Could not,",
  "In a car",
  "You may ",
  "like them.",
  "You will see.",
  "You may ",
  "like them",
  "In a tree?",
  "I would not, ",
  "could not ",
  "in a tree.",
  "Not in a car!",
  "You let me be.",
  "I do not like ",
  "them in a box.",
  "I do not like",
  "them with a fox.",
  "I do not like",
  "them in a house.",
  "I do not like",
  "them with ",
  "a mouse.",
  "I do not like",
  "them here ",
  "or there.",
  "I do not like ",
  "them anywhere.",
  "I do not like",
  "green eggs",
  "and ham.",
  "I do not like",
  "them, Sam-I-am.",
  "A train!A train!",
  "A train!A train!",
  "Could you, ",
  "would you",
  "On a train?",
  "Not on a train!",
  "Not in a tree!",
  "Not in a car!",
  "Sam! Let me be!",
  "I would not,",
  "could not,",
  "in a box.",
  "I could not,",
  "would not,",
  "with a fox.",
  "I will not eat ",
  "them with",
  "a mouse.",
  "I will not eat",
  "them in a house",
  "I will not eat",
  "them here",
  "or there.",
  "I will not eat ",
  "them anywhere.",
  "I do not like ",
  "them, Sam-I-am.",
  "Say!",
  "In the dark?",
  "Here",
  "in the dark!",
  "Would you, ",
  "could you, ",
  "in the dark?",
  "I would not,",
  "could not,",
  "In the dark.",
  "Would you,",
  "could you,",
  "In the rain?",
  "I would not,",
  "could not,",
  "in the rain.",
  "Not in the dark",
  "Not on a train,",
  "Not in a car,",
  "Not in a tree.",
  "I do not like",
  "them, Sam,",
  "you see.",
  "Not in a house.",
  "Not in a box.",
  "Not with",
  "a mouse.",
  "Not with a fox.",
  "I will not eat ",
  "them here ",
  "or there.",
  "I do not like",
  "them anywhere!",
  "You do not like",
  "Green eggs",
  "and ham?",
  "I do not",
  "Like them,",
  "Sam-I-am.",
  "Could you,",
  "would you,",
  "With a goat?",
  "I would not,",
  "Could not.",
  "With a goat!",
  "Would you, ",
  "could you,",
  "On a boat?",
  "I could not,",
  "would not,",
  "on a boat.",
  "I will not,",
  "will not,",
  "with a goat.",
  "I will not eat ",
  "them in ",
  "the rain.",
  "I will not eat ",
  "them on",
  "a train.",
  "Not in the dark",
  "Not in a tree!",
  "Not in a car!",
  "You let me be!",
  "I do not like ",
  "them in a box.",
  "I do not like",
  "them with a fox.",
  "I will not eat ",
  "them in a house.",
  "I do not like ",
  "them with ",
  "a mouse.",
  "I do not like ",
  "them here ",
  "or there.",
  "I do not like ",
  "them anywhere!",
  "I do not like",
  "Green eggs",
  "And ham!",
  "I do not like",
  "them ,Sam-I-am.",
  "You do not ",
  "like them.",
  "So you say.",
  "Try them! ",
  "Try them! ",
  "And you may.",
  "Try them and ",
  "you may I say.",
  "Sam!",
  "If you will ",
  "let me be,",
  "I will try them.",
  "You will see.",
  "Say!",
  "I like ",
  "green eggs ",
  "and ham!",
  "I do! ",
  "I like them, ",
  "Sam-I-am!",
  "And I would",
  "eat them in",
  "a boat!",
  "And I would ",
  "eat them",
  "with a goat...",
  "And I will eat ",
  "them in the rain",
  "And in the dark.",
  "And on a train.",
  "And in a car.",
  "And in a tree.",
  "They are so good",
  "so good",
  "you see!",
  "So I will eat",
  "them in a box.",
  "And I will eat",
  "them with a fox.",
  "And I will eat ",
  "them in a house.",
  "And I will eat",
  "them with ",
  "a mouse.",
  "And I will eat ",
  "them here ",
  "and there.",
  "Say! ",
  "I will eat them ",
  "Anywhere!",
  "I do so like",
  "Green eggs",
  "and ham!",
  "Thank you!",
  "Thank you!",
  "William",
  };

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  // Initiate the LCD:
  lcd.init();
  lcd.backlight();

  // Print 'Hello World!' on the first line of the LCD:
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print(ham[hamIdx]); // 
  lcd.setCursor(0, 1);
  lcd.print(ham[hamIdx+1]);

  //LaunchMidi and listen
  MIDI.begin(5);

}

void loop() 
{
  unsigned long currTime = millis();



  
  for(int x = 0; x<17; x++)
  {
    // read the state of the pushbutton value:
    buttonState[x] = digitalRead(buttonPin[x]);

    if(buttonState[x] != lastButtonState[x]) //If there is a change in button state
    {
      if(buttonState[x] == HIGH)//If the button is pressed
      {
        if(currTime - cd[x] >= 30)//Has enough time passed so we can press the button again?
        {
          lcd.clear();
          
          // Print 'Hello World!' on the first line of the LCD:
          lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
          lcd.print(ham[hamIdx]); // Print the string "Hello World!"
          lcd.setCursor(0, 1);
          lcd.print(ham[hamIdx+1]);
          
          hamIdx=hamIdx+1;
          
          if(hamIdx > 271)
          {
            hamIdx = 0;
          }
          
          cd[x]=currTime;
          MIDI.sendNoteOn((67+x), 127, 1);
          lastButtonState[x] = buttonState[x];
        }
        else
        {
          //lastButtonState[x] = HIGH;
        }
        
      }
      //else if(buttonState[x] != lastButtonState[x])      
      else if(buttonState[x] == LOW)
      {
        MIDI.sendNoteOff((67+x), 0, 1);
        lastButtonState[x] = buttonState[x];
      }
      //Error Handling
      else
      {
        
      }
      
    }
  }
}
