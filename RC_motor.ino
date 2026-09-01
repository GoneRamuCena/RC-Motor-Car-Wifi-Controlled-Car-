#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define IN_1  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_2  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
#define ENB   4          // Enable/speed motors Left         GPIO4(D2)

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;    
//String to store app command state.
int speedCar = 1023;         // 400 - 1023.
int speed_Coeff = 4;
int left_tire_speedCar = speedCar;
int right_tire_speedCar = speedCar;

const char* ssid = "you can't see me ";
ESP8266WebServer server(80);


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards





void setup() 
{
   myservo.write(0);    
   myservo.attach(5);  // attaches the servo on pin 5 to the servo object
   pinMode(ENA, OUTPUT);
   pinMode(ENB, OUTPUT);  
   pinMode(IN_1, OUTPUT);
   pinMode(IN_2, OUTPUT);
   pinMode(IN_3, OUTPUT);
   pinMode(IN_4, OUTPUT); 
  
   Serial.begin(115200);
  
// Connecting WiFi

   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid);

   IPAddress myIP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(myIP);
 
 // Starting WEB-server 
   server.on ( "/", HTTP_handleRoot );
   server.onNotFound ( HTTP_handleRoot );
   server.begin();    
}

void goAhead()
  { 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, left_tire_speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, right_tire_speedCar);
  }

void goBack()
  { 
    

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, left_tire_speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, right_tire_speedCar);
  }


void goRight()
  { 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, left_tire_speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, right_tire_speedCar);
  }

void goLeft()
  {

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, left_tire_speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, right_tire_speedCar);
  }

void goAheadLeft()
  {
      
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, left_tire_speedCar/speed_Coeff);
 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, right_tire_speedCar);
   }

void goAheadRight()
  {
      
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, left_tire_speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, right_tire_speedCar/speed_Coeff);
  }

void goBackLeft()
  { 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, left_tire_speedCar/speed_Coeff);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, right_tire_speedCar);
  }

void goBackRight()
  { 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, left_tire_speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, right_tire_speedCar/speed_Coeff);
  }

void stopRobot()
{  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

void loop() 
{

      myservo.write(0);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
  
  
      myservo.write(90);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
  
      server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void)

{

  if( server.hasArg("State") )
  {
     Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
