#include <Servo.h>
#include <SoftwareSerial.h>

Servo s1,s2;  

SoftwareSerial bt_connection(7, 6);
void setup() {
  s1.attach(10); //defining the pins for the servo's
  s2.attach(11);
  pinMode(12,OUTPUT); //Laser Output
  pinMode(2,INPUT);   //SW pin status
  digitalWrite(2,HIGH);
  Serial.begin(9600);  //Start Seria Monitor
  
  bt_connection.begin(9600);
  pinMode(6,INPUT); //  Input pin for distance sensor.
  pinMode(7,OUTPUT); // Output pin for distance sensor.
}


int p1=90,p2=90;   // initial position of both servos in degree
long duration, cm, inches;

void loop() 
{
  if (bt_iletisim.available())
  {
    char data = bt_connection.read();
    Serial.println(data);
  }
  
  int t1=0,t2=0;  //rate of increment/decrement of angle
  int a=analogRead(A0); // reads analog x-y readings of joystick
  int b=analogRead(A1);
  int dist = digitalRead(7);
  
  //when joystick is moved away from the center
  if(a<=450 or a>=550)
  {
    t1=map(a,0,1023,10,-10);
    p1=change(p1,t1);  //change the servo's current position
   
  }
  if(b<=450 or b>=550)
  {
    t2=map(b,0,1023,-10,10);
    p2=change(p2,t2);  //change the servo's current position

  }
   s1.write(p1); // rotate the servo's if the joystick is moved
   s2.write(p2);
  if(digitalRead(2)==LOW)  //reads the status of joystick's SW pin
  digitalWrite(12,HIGH);
  else
  digitalWrite(12,LOW);
  
  delay(70);          // for Stability
}

int change(int pos,int t)
{
    pos=pos+t;                   // Increment/decrement the Servo angle
    if (pos>180)                //  maximum anlgle of servo is 180 degree
    pos=180;
    if(pos<0)                  // minimum angle of servo is 0 degree
    pos=0;
    return(pos);               //return the change of position
}


int distance(){
  
  digitalWrite(7, LOW);
  delayMicroseconds(5);
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  pinMode(6, INPUT);
  duration = pulseIn(6, HIGH);
  cm = (duration/2)*0.0343;    
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);

  
  return cm;
}

}
