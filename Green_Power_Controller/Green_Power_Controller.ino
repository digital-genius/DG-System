volatile byte REV;        //The volatile data type has to be used because the variable is used in an interupt function.
unsigned long int rpm;    //  Define RPM variable
unsigned long time;       //  Define the variable for the time taken for one revolution.
//comment
void setup(){
  Serial.begin(9600);  //Begin the serial monitor to send the values to a computer.
  attachInterrupt(digitalPinToInterrupt(2), RPMCount, RISING);     //Call the RPMCount function when pin 2 goes from low to high.
  REV = 0;      //Innitialise the variable.
  rpm = 0;      //Init.
  time = 0;     //Init.
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, HIGH);               //Works as a VCC pin for the sensor. I have done this so that I can use sequential pins.
  digitalWrite(4, LOW);                //Works as a GND pin.
  Serial.println("TACHOMETER");        //Print to the serial monitor to show that the connection is active.  
}
 
void loop() {
  if(REV >= 5 ){ //Every 5th time the wheel turns;
    calcRPM();
  }
}

void calcRPM(){
  rpm = 30*1000/(millis() - time)*REV;   //Calculate the RPM.
  time = millis();   //Take the relative time of the calculation for use in the next one.
  REV = 0;   //Reset the RPM variable to begin the incramentation again.
  Serial.print(rpm,DEC);   //
  Serial.print("RPM");     //  Print the RPM to the serial bus.
  Serial.println(" ");     //
  delay(500);
}

void RPMCount(){ REV++; }   // When the photodiode is triggered this function is called, and REV is incramented.
