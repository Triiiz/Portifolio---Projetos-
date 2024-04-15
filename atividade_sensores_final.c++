
#include <LiquidCrystal.h>

LiquidCrystal LCD(12,11,5,4,3,2);

   int SensorTempPino = 0;
   int AlertaTempBaixa = 9;
   int AlertaTempAlta = 8;
   int TempBaixa = 10;
   int TempAlta = 20;
   int LEDS5 = 13;
   int LDR = 1;
   int ValorLDR = 0;
   int Pm = 200;
   int trig = 7; // envia onda sonora
   int eco = 6; // recebe a onda sonora
   int dist;
   int Buzzer = 10;
   int freq = 1000;
   int i;
  
void setup() 
{  
  	pinMode(AlertaTempBaixa, OUTPUT);
	pinMode(AlertaTempAlta, OUTPUT);
    pinMode(LEDS5, OUTPUT);
    pinMode(trig,OUTPUT);
    pinMode(eco,INPUT);
    pinMode(Buzzer, OUTPUT);
	LCD.begin(16,2);
    Serial.begin(9600);
}

void loop() 
{  
     // Parte Sensor de Temperatura
    LCD.begin(16,2);
	LCD.print("Temperatura:");
	LCD.setCursor(0,1);
	LCD.print("      C");
	int SensorTempTensao=analogRead(SensorTempPino);
	float Tensao=SensorTempTensao*5;
	Tensao/=1024;
	float TemperaturaC=(Tensao-0.5)*100;
  	LCD.setCursor(0,1);
	LCD.print(TemperaturaC);
    
  	if (TemperaturaC >= TempAlta) 
    {
  		digitalWrite(AlertaTempBaixa, LOW);
  		digitalWrite(AlertaTempAlta, HIGH);
    }
  	else if (TemperaturaC <= TempBaixa)
    {
  		digitalWrite(AlertaTempBaixa, HIGH);
  		digitalWrite(AlertaTempAlta, LOW);
  	}
  	else 
    {
  		digitalWrite(AlertaTempBaixa, LOW);
  		digitalWrite(AlertaTempAlta, LOW);
    }
    
    // Parte Sensor de Temperatura
    // Parte LDR
    ValorLDR = analogRead(LDR);
    if (ValorLDR < 100)
    {
      digitalWrite(LEDS5, HIGH);
    }
    else
    {
      digitalWrite(LEDS5, LOW);
    }
    // Parte LDR
  
    //Parte Sensor de Distancia e Buzzer
    
    digitalWrite(trig, LOW);  
    delayMicroseconds(2);  
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10);       
    digitalWrite(trig, LOW);  
    dist = pulseIn(eco, HIGH)/58;
    Serial.println(dist); 
    //Parte Buzzer
    if (dist < 20 && ValorLDR < 100)
    {  
      tone(Buzzer, freq);
      digitalWrite(LEDS5, HIGH);
      delay(500);
      digitalWrite(LEDS5, LOW);   
    }
    else
    {
      noTone(Buzzer);
    }
    //Parte Buzzer
} 
