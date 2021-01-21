long Start;   // this is the time in microseconds that the shutter opens 
long Stop;    // this is the time in microseconds that the shutter closes
int Risingflag = 0;  //  Rising flag is set to = 1 when the voltage INCREASES in the interrupt
int Fallingflag = 0;  // Fallingflag is set to =1 when the voltage DECREASES in the interrupt
int Fired = 0;  // flag indicating when the shutter has been fired



void setup() {                                                 

  Serial.begin(9600);                                          //opens a serial connection
  attachInterrupt(digitalPinToInterrupt(2), CLOCK, CHANGE);    //run the function CLOCK every time the voltage on pin 2 changes

}

void loop() {                                                  
  if(Risingflag == 1)
  {                       
    Start = micros();       //set Start to current microseconds
    Risingflag = 0;           
  }
  if(Fallingflag == 1)
  {
    Stop = micros();      // set Stop to current microseconds
    Fallingflag = 0;      
    Fired = 1;            // set the fired flag to 1
  }
  if(Fired == 1)
  {                            //if the flag Fired = 1, print this information to the serial monitor
    Serial.print("Start: ");
    Serial.println(Start);
    Serial.print("Stop: ");
    Serial.println(Stop);
    long Speed = (Stop - Start);      // Speed is the total number of microseconds that the shutter is open for
    Serial.print("Microseconds: ");
    Serial.println(Speed);               //display total microseconds in shutter interval
  

    float SS = (float)Speed/1000000;    //how many seconds that the shutter open for
    float SS2 = 1/SS;                   //inverse of the SS, or 1/ the shutter speed
    Serial.print("shutter speed: 1/");
    Serial.println(SS2);                //display the shutter speed
    Serial.println();
    Start = 0;                         
    Stop = 0;                           
    Fired = 0;                          
  } 
}

void CLOCK(){                     //this is the interrupt function, which is called everytime the voltage on pin 2 changes
  if(digitalRead(2) == HIGH)
  {
    Risingflag = 1;                // if the voltage on pin 2 is high, set the Risingflag to 1 
  }
  if(digitalRead(2) == LOW)
  {                               // . if the voltage on pin 2 is low, set the Fallingflag to 1 
    Fallingflag =1;
  }
}
