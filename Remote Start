/* A Spark function to parse the commands */
int RemoteStart(String command);

/* Globals -------------------------------------------------------------------*/
int Unlock   = D0;
int Lock  = D2;
int Trunk    = D4;
int Start   = D6;


/* This function is called once at start up ----------------------------------*/
void setup()
{
  //Register Spark function
  Spark.function("Remote Start", RemoteStart);

  pinMode(Unlock, INPUT);
  pinMode(Lock, INPUT);
  pinMode(Trunk, INPUT);
  pinMode(Start, INPUT);

  pinMode(D7,OUTPUT);
}

/* This function loops forever --------------------------------------------*/
void loop()
{
  // Nothing to do here
}

/*******************************************************************************
 * Function Name  : rcCarControl
 * Description    : Parses the incoming API commands and sets the motor control
                    pins accordingly
 * Input          : RC Car commands
                    e.g.: rc,FORWARD
                          rc,BACK
 * Output         : Motor signals
 * Return         : 1 on success and -1 on fail
 *******************************************************************************/
int RemoteStart(String command)
{
  if(command.substring(3,7) == "Unlock")
  {
    pinMode(Unlock, OUTPUT)
    digitalWrite(Unlock,LOW);
    delay(100);
    pinMode(Unlock, INPUT);

    return 1;
  }

  if(command.substring(3,7) == "Lock")
  {
    pinMode(Lock, OUTPUT)
    digitalWrite(Lock,LOW);
    delay(100);
    pinMode(Lock, INPUT);

    return 1;
  }

  if(command.substring(3,10) == "Trunk")
  {
    pinMode(Trunk, OUTPUT)
    digitalWrite(Trunk,LOW);
    delay(100);
    pinMode(Trunk, INPUT);

    return 1;
  }

  if(command.substring(3,8) == "Start")
  {
    pinMode(Lock, OUTPUT)
    digitalWrite(Lock,LOW);
    delay(100);
    pinMode(Lock, INPUT)
    pinMode(Start, OUTPUT)
    digitalWrite(Start,LOW);
    delay(2000);
    pinMode(Start, INPUT)



    return 1;
  }



    return 1;
  }

  // If none of the commands were executed, return false
  return -1;
}
