#include "application.h"

/* A Spark function to parse the commands */
int remoteControl(String command);

/* Globals -------------------------------------------------------------------*/
// Constants (for pin definitions and other things which do not change)
const int pinUnlock = D0;
const int pinLock = D2;
const int pinTrunk = D4;
const int pinStart = D6;
const int pinLed = D7;
const int pinEng = D6;

// Desired Button Press States
bool pressUnlock = false;
bool pressLock = false;
bool pressTrunk = false;
bool pressStart = false;
bool pressLed = false;
bool pressEng = false;

// Defines
#define BUTTON_PRESS_TIME 300

/* This function is called once at start up ----------------------------------*/
void setup()
{
    // Serial Port Debugging GO!
    Serial.begin(115200);

    //Register Spark function
    Spark.function("rc", remoteControl);

    // Make all the control pins outputs
    pinMode(pinUnlock, OUTPUT);
    pinMode(pinLock, OUTPUT);
    pinMode(pinTrunk, OUTPUT);
    pinMode(pinStart, OUTPUT);
    pinMode(pinEng, OUTPUT);

    // Set the D7 status LED to an output.
    pinMode(D7,OUTPUT);

    // Drive all the control pins high (not pressing the button)
    digitalWrite(pinUnlock, HIGH);
    digitalWrite(pinLock, HIGH);
    digitalWrite(pinTrunk, HIGH);
    digitalWrite(pinStart, HIGH);
    digitalWrite(pinLed, LOW);
    
    // Start the time sync & wait until it actually syncs. 
    Spark.syncTime();
    while(Time.year() == 1970) {  SPARK_WLAN_Loop(); }
}

/* This function loops forever --------------------------------------------*/
void loop()
{
    //Go to sleep at 11:00PM CST till 6:30AM
    if(Time.hour() == 5)
    {
        Spark.sleep(SLEEP_MODE_DEEP,27000);
    }
    if(pressUnlock == true)
    {
        Serial.print("Emulating unlock button... ");
        digitalWrite(pinUnlock,LOW);
        digitalWrite(pinLed,HIGH);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinUnlock,HIGH);
        digitalWrite(pinLed,LOW);
        pressUnlock = false;
        Serial.println("DONE");
    }

    if(pressLock == true)
    {
        Serial.print("Emulating lock button... ");
        digitalWrite(pinLock,LOW);
        digitalWrite(pinLed,HIGH);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinLock,HIGH);
        digitalWrite(pinLed,LOW);
        pressLock = false;
        Serial.println("DONE");
    }

    if(pressTrunk == true)
    {
        Serial.print("Emulating lock button... ");
        digitalWrite(pinTrunk,LOW);
        digitalWrite(pinLed,HIGH);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinTrunk,HIGH);
        digitalWrite(pinLed,LOW);
        pressTrunk = false;
        Serial.println("DONE");
    }

    if(pressStart == true)
    {
        // Emulate a lock button press
        Serial.print("Emulating lock button... ");
        digitalWrite(pinLock,LOW);
        digitalWrite(pinLed,HIGH);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinLock,HIGH);
        digitalWrite(pinLed,LOW);
        delay(200);
        Serial.println("DONE");
        
        // Emulate a long start button press
        Serial.print("Emulating start button... ");
        digitalWrite(pinStart,LOW);
        digitalWrite(pinLed,HIGH);
        delay(2000);
        digitalWrite(pinStart,HIGH);
        digitalWrite(pinLed,LOW);
        pressStart = false;
        Serial.println("DONE");
    }
    
    if(pressEng == true)
    {
        Serial.print("Emulating Start button... ");
        digitalWrite(pinStart,LOW);
        digitalWrite(pinLed,HIGH);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinStart,HIGH);
        digitalWrite(pinLed,LOW);
        pressEng = false;
        Serial.println("DONE");
    }
}

/*******************************************************************************
 * Function Name  : remoteControl
 * Description    : Parses the incoming API commands and emulated button presses
 * Input          : Remote Control commands
                    e.g.:   UNLOCK
                            LOCK
                            TRUNK
                            START
 * Output         : Sets flags for emulated button presses
 * Return         : 1 on success and -1 on fail
 *******************************************************************************/
int remoteControl(String command)
{
    if(command.equals("UNLOCK") == true)
    {
        pressUnlock = true;
        return 1;
    }

    if(command.equals("LOCK") == true)
    {
        pressLock = true;
        return 1;
    }

    if(command.equals("TRUNK") == true)
    {
        pressTrunk = true;
        return 1;
    }

    if(command.equals("START") == true)
    {
        pressStart = true;
        return 1;
    }
    
    if(command.equals("ENG") == true)
    {
        pressEng = true;
        return 1;
    }
    
    // If none of the commands were executed, return false
    return -1;
}
