// LaunchMachine for UAV

#define SICHER 5

#define IN 3
#define MAGNET 12

void setup() {

  Serial.begin(9600);

  Serial.println("#Cvak...");
  digitalWrite(MAGNET,LOW);
  pinMode(MAGNET, OUTPUT);
  DDRD = 0;
  Serial.println("#Hmmm...");
}

int8_t flag;
boolean flag2 = HIGH;

void loop() {
  flag=0;
  while(!(PIND & 0b00001000));
  while((PIND & 0b00001000));
  for (int8_t n=0; n<SICHER; n++)
  {
    while((PIND & 0b00001000));
    while(!(PIND & 0b00001000));
    delayMicroseconds(1800);
    if ((PIND & 0b00001000))
    { 
      flag++;
    }
  };
  Serial.print(flag);
  Serial.print(" ");
  if ((flag == SICHER)&&(flag2 == LOW))
  {
    Serial.println("on");
        
    digitalWrite(MAGNET,HIGH);
    delay(1000);
    digitalWrite(MAGNET,LOW);
    flag2 = HIGH;
  }
  if (flag==0)
  { 
    flag2 = LOW;
    Serial.println("off");
  }

}
