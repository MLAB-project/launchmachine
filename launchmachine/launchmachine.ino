// LaunchMachine for UAV

#define SICHER 10 // mandatory number of pulses

#define IN 3      // PD3
#define MAGNET 12 // PB4
#define TIMEOUT 3000 // Magnet switch-on time

void manual_launch()
{
  if (!(PIND & 0b00010000)) 
  while (!(PIND & 0b00010000)) 
  {
    delay(2000);
    if (!(PIND & 0b00010000)) 
    {
      Serial.println("on");
          
      digitalWrite(MAGNET,HIGH);
      delay(TIMEOUT);
    }
  }
  digitalWrite(MAGNET,LOW);
}

void setup() 
{

  Serial.begin(9600);

  Serial.println("#Cvak...");
  digitalWrite(MAGNET,LOW);
  pinMode(MAGNET, OUTPUT);
  DDRD = 0;
  Serial.println("#Hmmm...");
}

int8_t flag;
boolean flag2 = HIGH;

void loop() 
{
  // waiting for 0 - 25 %
  flag=0;
  while(!(PIND & 0b00001000)) manual_launch();
  while((PIND & 0b00001000)) manual_launch();
  for (int8_t n=0; n<SICHER; n++)
  {
    while((PIND & 0b00001000)) manual_launch();
    while(!(PIND & 0b00001000)) manual_launch();
    delayMicroseconds(970);
    if ((PIND & 0b00001000))
    { 
      delayMicroseconds(300);
      if (!(PIND & 0b00001000))
      { 
        flag++;
      }
    }
  };
  Serial.print(flag);
  Serial.print("*");
  if ((flag == SICHER))
  {
    flag2=LOW;
  }        
  
  // waiting for 75 - 100 %
  flag=0;
  while(!(PIND & 0b00001000)) manual_launch();
  while((PIND & 0b00001000)) manual_launch();
  for (int8_t n=0; n<SICHER; n++)
  {
    while((PIND & 0b00001000)) manual_launch();
    while(!(PIND & 0b00001000)) manual_launch();
    delayMicroseconds(1730);
    if ((PIND & 0b00001000))
    { 
      delayMicroseconds(300);
      if (!(PIND & 0b00001000))
      { 
        flag++;
      }
    }
  };
  Serial.print(flag);
  Serial.print("#");
  if ((flag == SICHER)&&(flag2 == LOW))
  {
    Serial.print("on");
        
    digitalWrite(MAGNET,HIGH);
    delay(TIMEOUT);
    digitalWrite(MAGNET,LOW);
    flag2 = HIGH;
  }
  Serial.println(flag2);
}
