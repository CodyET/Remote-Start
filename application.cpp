/* A Spark function to parse the commands */
int remoteControl(String command);

/* Globals -------------------------------------------------------------------*/
// Constants (for pin definitions and other things which do not change)
const int pinUnlock = D0;
const int pinLock = D2;
const int pinTrunk = D4;
const int pinStart = D6;

// Desired Button Press States
bool pressUnlock = false;
bool pressLock = false;
bool pressTrunk = false;
bool pressStart = false;

// Defines
#define BUTTON_PRESS_TIME 100

/* This function is called once at start up ----------------------------------*/
void setup()
{
    //Register Spark function
    Spark.function("remoteControl", remoteControl);

    // Make all the control pins outputs
    pinMode(pinUnlock, OUTPUT);
    pinMode(pinLock, OUTPUT);
    pinMode(pinTrunk, OUTPUT);
    pinMode(pinStart, OUTPUT);

    // Set the D7 status LED to an output.
    pinMode(D7,OUTPUT);

    // Drive all the control pins high (not pressing the button)
    digitalWrite(pinUnlock, HIGH);
    digitalWrite(pinLock, HIGH);
    digitalWrite(pinTrunk, HIGH);
    digitalWrite(pinStart, HIGH);
}

/* This function loops forever --------------------------------------------*/
void loop()
{
    if(pressUnlock == true)
    {
        digitalWrite(pinUnlock,LOW);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinUnlock,HIGH);
        pressUnlock = false;
    }

    if(pressLock == true)
    {
        digitalWrite(pinLock,LOW);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinLock,HIGH);
        pressLock = false;
    }

    if(pressTrunk == true)
    {
        digitalWrite(pinTrunk,LOW);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinTrunk,HIGH);
        pressTrunk = false;
    }

    if(pressStart == true)
    {
        // Emulate a lock button press
        digitalWrite(pinLock,LOW);
        delay(BUTTON_PRESS_TIME);
        digitalWrite(pinLock,HIGH);

        // Emulate a long start button press
        digitalWrite(pinStart,LOW);
        delay(2000);
        digitalWrite(pinStart,HIGH);

        pressStart = false;
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

    // If none of the commands were executed, return false
    return -1;
}
