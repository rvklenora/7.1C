#include <SoftwareSerial.h>
SoftwareSerial HM10(0, 1); // RX = 2, TX = 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
/*SoftwareSerial HM10(0, 1);*/
HM10.begin(9600);
#define Mleft_dir 2  //defines the direction of left motors
#define Mleft 5   //defines the speed of left motors
#define Mright_dir 4   //defines the direction of right motors
#define Mright 9   //defines the speed of right motors
}

void loop() {
  // put your main code here, to run repeatedly:
  keyboardControl();
}

 //moves forward
  void front(int ms)
  {
    digitalWrite(Mleft_dir,HIGH);
    analogWrite(Mleft,200);
    digitalWrite(Mright_dir,LOW);
    analogWrite(Mright,200);
    delay(ms);
  }
  
  //moves backward
  void back(int ms)
  {
    digitalWrite(Mleft_dir,LOW);
    analogWrite(Mleft,200);
    digitalWrite(Mright_dir,HIGH);
    analogWrite(Mright,200);
    delay(ms);
  }
  
  //moves left
  void left(int ms)
  {
    digitalWrite(Mleft_dir,HIGH);
    analogWrite(Mleft,200);
    digitalWrite(Mright_dir,HIGH);
    analogWrite(Mright,200);
    delay(ms);
  }
  
  //moves right
  void right(int ms)
  {
    digitalWrite(Mleft_dir,LOW);
    analogWrite(Mleft,200);
    digitalWrite(Mright_dir,LOW);
    analogWrite(Mright,200);
    delay(ms);
  }
  
  //brake
  void brake(int ms)
  {
    analogWrite(Mleft,0);
    analogWrite(Mright,0);
    delay(ms);
  }

/*control robot via computer keyboard & bluetooth module
  * Uses serial monitor
  * Must be paired to bluetooth module HC-06 on host computer!
   */
void keyboardControl(){
 /* if (Serial.available() > 0){ //Listen for signal in the serial port
    *int data = Serial.read();*/
    HM10.listen();  // listen the HM10 port
  while (HM10.available() > 0) {   // if HM10 sends something then read
    char data = HM10.read();
    char indata = char(data); 
    Serial.println(data);
    switch (data) { // Switch-case of the signals in the serial port 
    case 'a' : // Case Number 1 is received, 
    Serial.println("left");
    left(700); //replace with your leftTurn method
    break;
    case 's' : //// Case Number 2 is received,
    Serial.println("backward");
    back(2000); //replace with your backwards method
    break;
    case 'd' : // Case Number 3 is received,
    Serial.println("right"); 
    right(700); //replace with your rightTurn method
    break;
    case 'w': // Case Number 5 is received,
    Serial.println("forward"); 
    front(2000); //replace with your forward method
    break;
    case '0': // Case Number 0 is received, 
    Serial.println("stop");
    default : 
    break;
    }
  }
}
