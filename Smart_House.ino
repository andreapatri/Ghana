
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int trigPin = 9;    // Trigger pin which sends the wave from the Transmitter end 
int echoPin = 10;    // Echo pin which receives the wave at the Receiver end
long duration, cm;
int m;
#define BLUE 7
#define GREEN 8
#define RED 6
#define delayTime 10  

int redValue;
int greenValue;
int blueValue;

int photocellPin = 0;     
int photocellReading;   

void setup() {
  lcd.begin(16, 2);
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  pinMode(A1, OUTPUT);
  pinMode(13, OUTPUT);
  
}

void loop() {

// 1) ULTRASOUND
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm =  (duration*0.0343)/2 ;    
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(250);
    
  int m;
  
  if (cm <  20)                 m = 1;
  if (cm >= 20 && cm <= 40)     m=2;
  if (cm > 40)                  m=3;
  
// 2) BUZZER
  
  if (cm <  20)   {digitalWrite(A1, HIGH); Serial.print("h");}
  else            {digitalWrite(A1, LOW); Serial.print("L");}

// 2) LCD
  lcd.setCursor(0, 0);
  if(m == 1)  lcd.print("alert!intruder!          ");
  if(m == 2)  lcd.print("Beware                   ");
  if(m == 3)  lcd.print("You are safe             ");
  lcd.setCursor(0, 1);
  lcd.print("Distance = ");
  lcd.print(cm);
  lcd.print("    ");

// 3) RGB 
  if (cm <  20)
    {
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0); 
     }
     
  if (cm >= 20 && cm <= 40)
  {
    analogWrite(RED, 255);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 0);
   }  
      
  if (cm > 40)    
  {
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 255);
   }
   
   delay(delayTime);
   
// 4) PHOTOCELL 
  photocellReading = analogRead(photocellPin);  

  if (photocellReading > 100 ) digitalWrite(13, LOW );
  if (photocellReading <= 100) digitalWrite(13, HIGH);
  delay(100);


}
