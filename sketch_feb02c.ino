#include <IRremote.h>
#include <Ultrasonic.h>
#define RECV_PIN 11
#define IN1 5
#define IN2 4
#define IN3 6
#define IN4 7

void forward()
{
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void backward()
{
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void right()
{
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

void left()
{
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void pause()
{
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

IRrecv irrecv(RECV_PIN);
decode_results results;
Ultrasonic ultrasonic(2, 3);
int distance = 0;

void setup()
{
//  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
// Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
 // Serial.println("Enabled IRin");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, 0);
  digitalWrite(13, 1);
  pause();
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
//    Serial.println(results.value);
    if(results.value == 16738455) //AUTO *
    {
 //     Serial.println("AUTO MODE ON");
      while(results.value != 16756815)//#
      {
        distance = ultrasonic.read();
 //       Serial.print("Distance in CM: ");
 //       Serial.println(distance);
        if(distance >= 20)
          forward();
        else 
        {
          backward();
          delay(500);
          right();
          delay(500);
        }
        irrecv.resume();
        delay(100);
        irrecv.decode(&results);   
      }
//      Serial.println("AUTO MODE OFF");
    }
    if(results.value == 16726215) //pause OK
    {
//      Serial.println("STOP");
      pause();
    }
    if(results.value == 16718055) 
    {
//      Serial.println("^");
      forward();
    }
    if(results.value == 16716015)
    {
 //     Serial.println("<");
      left();
    }
    if(results.value == 16734885)
    {
//      Serial.println(">");
      right();
    }
    if(results.value == 16730805)
    {
//      Serial.println("V");
      backward();
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
  
}
