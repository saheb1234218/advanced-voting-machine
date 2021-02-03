/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> http://www.adafruit.com/products/751

  These displays use TTL Serial to communicate, 2 pins are required to 
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <Servo.h>
#include <Password.h> //http://playground.arduino.cc/uploads/Code/Password.zip //tells to use password library
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip  //tells to use keypad library
#include <LiquidCrystal_I2C.h>


#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,20,4);
int fingerprintID();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Password password = Password( "1245" ); //password to unlock, can be changed
const byte ROWS = 4; // Four rows
const byte COLS = 4; // columns
// Define the Keymap
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 10, 8, 7, 6 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 1};


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


int pos = 0;    // variable to store the servo position


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  myservo.attach(9);
  Serial.begin(9600);
   pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
 
  keypad.addEventListener(keypadEvent);
Serial.println("fingertest");
lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
 
  // set the data rate for the sensor serial port
  finger.begin(57600);
    lcd.setCursor(0,0);
    lcd.print("Welcome");
    
    lcd.setCursor(10,1);
    lcd.print("To");
    lcd.setCursor(0,2);
    lcd.print("Adv Voting Machine");
    delay(4000);
    lcd.clear();
   
  if (finger.verifyPassword()) {
    
    lcd.setCursor(0,0);
    lcd.print("Found sensor!");
    delay(3000);
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Didnot Find sensor!");
    delay(3000);
       while (1);
  }
  lcd.clear();
    lcd.setCursor(0,1);
   lcd.print("Scan your finger");
    delay(1000);
   
   lcd.setCursor(0,3);
   lcd.print("Waiting for finger");
   delay(2000);
}

void loop()                     // run over and over again
{
  int fingerprintID=0;
  fingerprintID = getFingerprintIDez(); //We scan the fingerprint here
  delay(50);
  if(fingerprintID == 3) //We have found a valid fingerprint with the id 1
  {
    
     lcd.clear();
       lcd.setCursor(0,0);
    lcd.print("Fingerprint matched");
    
  lcd.setCursor(0,1);
 lcd.print("Hi MR Apurba Ganguly");
  lcd.setCursor(0,2);
 lcd.print("Enter Voter ID No:");
    lcd.setCursor(0,3);
 lcd.print("Insert your card:");
 
 delay(5000);
 lcd.clear();
 keypad.waitForKey();
  keypad.getKey();
 keypad.waitForKey();
  keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
 
  }   if(fingerprintID == 1){ 
    
    lcd.clear();
     lcd.setCursor(0,0);
    lcd.print("Fingerprint matched");
    
  lcd.setCursor(0,1);
 lcd.print("Hi Mr Abhinav Sharma");
     lcd.setCursor(0,2);
 lcd.print("Enter Voter ID No:");
    lcd.setCursor(0,3);
 lcd.print("Insert your card:");
 delay(5000);
 lcd.clear();
  keypad.waitForKey();
  keypad.getKey();
keypad.waitForKey();
  keypad.getKey();
  keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
 
  }
   if(fingerprintID == 2){ 
    
    
   
    
    lcd.clear();
     lcd.setCursor(0,0);
    lcd.print("Fingerprint matched");
    
  lcd.setCursor(0,1);
 lcd.print("Hi Mr Aritra Dutta");
     lcd.setCursor(0,2);
 lcd.print("Enter Voter ID No:");
    lcd.setCursor(0,3);
 lcd.print("Insert your card:");
 delay(5000);
 lcd.clear();
 keypad.waitForKey();
  keypad.getKey();
 keypad.waitForKey();
  keypad.getKey();
  keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
keypad.waitForKey();
 keypad.getKey();
    }
    
 //don't ned to run this at full speed.
}
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); 
  Serial.println(finger.confidence);
  return finger.fingerID; 
}
 void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
  case PRESSED:
  
  Serial.print("Enter:");
  Serial.println(eKey);
  switch (eKey){
    case '*': checkPassword(); 
    break;
    
    case '0': password.reset();
    break;
    
     default: password.append(eKey);
}
}
}
void checkPassword(){
  
if (password.evaluate()){  //if password is right open
   
    {
    lcd.setCursor(0,0);
    lcd.print("Eligible to Vote");
     lcd.setCursor(0,1);
     lcd.print("Take out your card");
     lcd.setCursor(0,2);
     lcd.print("Give your vote");
     delay(4000);
   lcd.clear();
   
    digitalWrite(12,HIGH);
    delay(3000);
    digitalWrite(12,LOW);
    }
   }
else{digitalWrite(13,HIGH);
      digitalWrite(11,HIGH);
 myservo.write(-90);
 delay(1000);
  myservo.write(90); 
       
   lcd.setCursor(0,2);
  
    lcd.print("Not eligible to vote");
    delay(4000);
    lcd.clear();
    //if passwords wrong keep locked
    digitalWrite(13,LOW);
    digitalWrite(11,LOW);
 delay(1000);
 
}
}
