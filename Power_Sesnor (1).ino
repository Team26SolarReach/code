#include <LiquidCrystal.h>

const int voltageSensor = A1;

float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30140.0;
float R2 = 7530.0;
int value = 0;

//LiquidCrystal lcd(12, 11, , 9, 10, 13); // RS, E, D4, D5, D6, D7
const int rs = 12, en = 11, d4 = 8, d5 = 9, d6 = 10, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup()
{
Serial.begin(9600);
lcd.begin(16,2);
lcd.print(" Measure > 25V  ");
delay(2000);
}

void loop()
{

  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  unsigned int x=0;
float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;

  for (int x = 0; x < 150; x++){ //Get 150 samples
  AcsValue = analogRead(A0);     //Read current sensor values   
  Samples = Samples + AcsValue;  //Add samples together
  delay (3); // let ADC settle before next sample 3ms
}
AvgAcs=Samples/150.0;//Taking Average of Samples


//((AvgAcs * (5.0 / 1024.0)) is converitng the read voltage in 0-5 volts
//2.5 is offset(I assumed that arduino is working on 5v so the viout at no current comes
//out to be 2.5 which is out offset. If your arduino is working on different voltage than 
//you must change the offset according to the input voltage)
//0.066v(66mV) is rise in output voltage when 1A current flows at input
AcsValueF = (2.489 - (AvgAcs * (5.0 / 1024.0)) )/0.066;



Serial.println(AcsValueF);//Print the read current on Serial monitor
delay(50);

 
  lcd.setCursor(0,0);
  lcd.print("Vout =         ");
  lcd.setCursor(9,0);
  lcd.print(vIN);
  lcd.print("V");
  lcd.setCursor(0,1);
   lcd.print("Iout =         ");
   lcd.setCursor(9,1);
  lcd.print(AcsValueF);
  lcd.print("A");
  delay(500);
}
