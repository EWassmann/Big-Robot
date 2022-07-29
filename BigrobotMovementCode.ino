//DIGITAL OUTPUTS FROM ARDUINO (right motors,left osmc)
int fivevR = 2;
int ahiPinR = 12; // pin 8 on arduino to AHI on OSMC which is OSMC pin 5
int bhiPinR = 13; //pin 7 on arduino to BHI on OSMC which is OSMC pin 7
int aliPinR = 9;   //NOTE I am using an Arduino Mega 1280 (the cheapo Mega available on ebay). Pins 9 and 10 are pwm capable and controlled by Timer 2
int bliPinR = 10;    //This is important as we are going to mess with Timer 2 so the pwm frequency changes to a much faster rate than the standard pwm on Arduinos.
//left motors right osmc
//fivev on this one will be going to the 5v port on the arduino
int ahiPinL = 8; //osmc pin 5
int bhiPinL = 7; //osmc pin 7
int aliPinL = 3; 
int bliPinL = 11;

//We want this because it is so fast the motor "whine" becomes higher than human ear can hear and also it is much smoother in terms of speed control.

//So, Use pins 9 and 10 for this and not any other pwm pins.

int osmcdisablePinR = 4; //this pin 4 on arduino disables osmc if it is set to HIGH (i.e. 5V sent to osmc pin 4)
int osmcdisablePinL = 1;
int commandfromjetson;
 void setup() {
    //digital outputs
 TCCR1B = TCCR1B & B11111000 | B00000001;
 pinMode(fivevR, OUTPUT);
pinMode(ahiPinR, OUTPUT);
pinMode(bhiPinR, OUTPUT);
pinMode(osmcdisablePinR, OUTPUT);
pinMode(aliPinR, OUTPUT);
pinMode(bliPinR, OUTPUT);

TCCR2B = TCCR2B & B11111000 | B00000001;
pinMode(ahiPinL, OUTPUT);
pinMode(bhiPinL, OUTPUT);
pinMode(osmcdisablePinL, OUTPUT);
pinMode(aliPinL, OUTPUT);
pinMode(bliPinL, OUTPUT);


Serial.begin(2000000);
  while(!Serial){
    ;//WAITING FOR THE Serial TO CONNECT
  }
  Serial.setTimeout(200);
esc.write(80);
commandfromjetson =4;
// i do not want the get ready command to run a ton of times so trying to put it in the setup
digitalWrite(fivevR, HIGH);
digitalWrite(osmcdisablePinR, LOW); //0V to osmc pin 4 will ENABLE the OSMC
digitalWrite(ahiPinR, HIGH);  //AHI and BHI have to be high on osmc for it to work
digitalWrite(bhiPinR, HIGH);

digitalWrite(osmcdisablePinL, LOW); //0V to osmc pin 4 will ENABLE the OSMC
digitalWrite(ahiPinL, HIGH);  //AHI and BHI have to be high on osmc for it to work
digitalWrite(bhiPinL, HIGH);
 }


void getReady() {
digitalWrite(fivevR, HIGH);
digitalWrite(osmcdisablePinR, LOW); //0V to osmc pin 4 will ENABLE the OSMC
digitalWrite(ahiPinR, HIGH);  //AHI and BHI have to be high on osmc for it to work
digitalWrite(bhiPinR, HIGH);

digitalWrite(osmcdisablePinL, LOW); //0V to osmc pin 4 will ENABLE the OSMC
digitalWrite(ahiPinL, HIGH);  //AHI and BHI have to be high on osmc for it to work
digitalWrite(bhiPinL, HIGH);
}
void Forward() {
analogWrite(aliPinR, LOW); //0V to OSMC pin 6
analogWrite(bliPinR, 200 ); //pwm to OSMC pin 8
analogWrite(aliPinL, LOW); //0V to OSMC pin 6
analogWrite(bliPinL, 200 ); //pwm to OSMC pin 8
}
void Backwards(){
analogWrite(aliPinR, 200); //0V to OSMC pin 6
analogWrite(bliPinR, LOW); //pwm to OSMC pin 8
analogWrite(aliPinL, 200); //0V to OSMC pin 6
analogWrite(bliPinL, LOW ); //pwm to OSMC pin 8
}
void Stop() {
analogWrite(aliPinR, LOW); //0V to OSMC pin 6
analogWrite(bliPinR, LOW); //pwm to OSMC pin 8
analogWrite(aliPinL, LOW); //0V to OSMC pin 6
analogWrite(bliPinL, LOW ); //pwm to OSMC pin 8
}
void Left(){
  analogWrite(aliPinR, LOW); //0V to OSMC pin 6
analogWrite(bliPinR, 200 ); //pwm to OSMC pin 8
analogWrite(aliPinL, 200); //0V to OSMC pin 6
analogWrite(bliPinL, LOW ); //pwm to OSMC pin 8
}
void Right(){
   analogWrite(aliPinR, 200); //0V to OSMC pin 6
analogWrite(bliPinR, LOW ); //pwm to OSMC pin 8
analogWrite(aliPinL, LOW); //0V to OSMC pin 6
analogWrite(bliPinL, 200 ); //pwm to OSMC pin 8
}

//-----------------------------------------




//attaching servo pins and waiting to connect to the jetson, also trying to initalize the esc, you may need to open up other code of get the main
//function to write 80 to it somehow if the robot is not moving, need to hear the beep!


void loop() {
   
  //waiting for jetson command, then goes through the if loops and sees which one it triggers. 
  //any sort of decision on when to go into search needs to be included in the larger python code.
  if (Serial.available()>0){
  commandfromjetson = Serial.readString().toInt();
 //0 is straight 1 is left 2 is right 3 is bacwards 4 is stop
 if (commandfromjetson != 5){
timer = 0;
  }
 }
 
  if (commandfromjetson == 0){
    Forward();
  }
  if (commandfromjetson == 1){
    Left();
  }                       
  if (commandfromjetson ==2){
  Right();
  }
  if (commandfromjetson == 3){
    Backwards();
  }
  if (commandfromjetson == 4){
    Stop();
  }
  if (commandfromjetson == 5){
  Right();
  }
  

  }  
