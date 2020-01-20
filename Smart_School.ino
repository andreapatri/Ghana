
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

#define BLUE 8
#define GREEN 7
#define RED 9
static const int DHT_SENSOR_PIN = 13;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
int photocellPin = 0;     
int photocellReading;    

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int trigPin = 6  ;    // Trigger pin which sends the wave from the Transmitter end 
int echoPin = 10;    // Echo pin which receives the wave at the Receiver end
long duration, cm;

void setup( )
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  pinMode(A3,OUTPUT);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


// define variables
int redValue;
int greenValue;
int blueValue;


static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );
  if( millis( ) - measurement_timestamp > 1000 )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }
  return( false );
}

void loop( )
{
  
  //photoresistor
  photocellReading = analogRead(photocellPin); 
  
  
  //TEMP
  float temperature;
  float humidity;
  if( measure_environment( &temperature, &humidity ) == true )
  { 
    lcd.setCursor(0, 1);
    Serial.print( "T = " );
    Serial.print( temperature, 1);
    Serial.println("  ");
    lcd.print( "T = " );
    lcd.print(temperature);
    lcd.print(" C");
    ultrasound();
  }

  //RGB
  photocellReading = analogRead(photocellPin); 

if (temperature <= 31)  
  {  
  analogWrite(RED, 0);  
  analogWrite(GREEN, 0);  
  analogWrite(BLUE, 255);
  } 

if (temperature > 31 && temperature < 33)  
  {
  analogWrite(RED, 255);
  analogWrite(GREEN,255);
  analogWrite(BLUE,255);
  } 

if (temperature >= 33)
  {
  analogWrite(RED, 255);  
  analogWrite(GREEN, 0);  
  analogWrite(BLUE, 0);
  digitalWrite(A1,HIGH);
  if (photocellReading <= 400)  digitalWrite(A3,HIGH);
  else digitalWrite(A3,LOW);
  } 
  
}


void ultrasound()
{
  //ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
  cm = (duration*0.0343)/2;     // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  lcd.setCursor(0, 0);
  if (cm <  15)              lcd.print("YOU GOT THIS        ");
  if (cm >= 15  &&  cm<= 50) lcd.print("SIT WELL           ");
  if (cm >= 50)              lcd.print("ARE YOU SLEEPING?       ");
}
