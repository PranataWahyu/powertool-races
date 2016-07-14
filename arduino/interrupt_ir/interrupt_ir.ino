//Hooked up to signal pin of IR reader
#define END_PIN 2
//Hooked up to normally-closed nonlatching pushbutton switch. Other end goes to ground.
#define START_PIN 8

//ASR routine vars need to be volatile.
volatile unsigned long endTime;
//When the current race started (i.e. when the button was pushed)
unsigned long startTime;
bool started;
bool stopped;
volatile bool recordEnd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.write("starting up...\n");
  pinMode(END_PIN, INPUT_PULLUP);
  pinMode(START_PIN, INPUT_PULLUP);
  //set an interrupt to trigger whenever the IR pin changes
  attachInterrupt(digitalPinToInterrupt(END_PIN), endfn, CHANGE);
  started = false;
  stopped = false;
  recordEnd = false;
  startTime=0;
  endTime = 0;
}

void loop() {
  // Race start (!started condition because the switch bounces).
  if(!started && digitalRead(START_PIN) == HIGH)
  {
    Serial.write("Starting...\n");
    startTime = millis();
    started = true;
    endTime = 0;
    stopped = false;
    recordEnd = true;
  }
  if(started)
  {
    //We set endTime to 0 when the race starts,
    //so if it's nonzero we know the race has ended.
    if(endTime != 0)
    {
      Serial.print("Stopped. EndTime: ");
      Serial.print(endTime);
      Serial.print("\n");
      Serial.print("Total time ");
      Serial.print(endTime - startTime);
      Serial.print(" milliseconds\n");
      stopped = true;
      started = false;
    }
  }
  else if(stopped)
  {
    //do nothing, no need to clutter up serial output.
  }
  else
  {
    //No need to clutter up with this.
    //Serial.write("Not started, nothing to do\n");
  }

}

//ISR triggered when the beam is broken (or unbroken).
//Just sets the end time.
void endfn()
{
  if(recordEnd)
  {
    endTime = millis();
    recordEnd = false;
  }
}


