#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Items must be shorter than 14 characters in this version
String remembers[] = {"Sekk", "Matpakke", "Gymbag", "Nokler", "Mobil", "Lommebok"};
int cursor = 0;
//Button at port 8, buzzer at port 10
int fakeSensePort = 8;
int sensVal = 0;
unsigned long timeSinceMovementSensored = 0;

void setup() {
  Serial.begin(9600);
  pinMode(fakeSensePort, INPUT);
  lcd.begin(16, 2);
  
}

void loop() {
	// Checks if the sensor (read button) is activated
	if(digitalRead(fakeSensePort) == 1){
		lcd.print("HUSK!:");
		tone(10, 1567, 550);
		delay(600);
		tone(10, 1318, 300);
		delay(350);
		tone(10, 1174, 300);
		delay(350);
		tone(10, 1046, 400);
		timeSinceMovementSensored = millis();
		Serial.print(timeSinceMovementSensored);
		// In 6000 milliseconds run the print remebers-method
		while(millis() - timeSinceMovementSensored < 12000){
			printSepLines();
		}
		lcd.clear();

	}
	
}

void printSepLines(){
 

  for(int i=0; i<(sizeof(remembers)/sizeof(String))-1; i+=2){
    lcd.clear();
    // TODO:  code to make it handle odd number list
    if((i%2) != 0 and i == (sizeof(remembers)/sizeof(String))-1 ){

    }
    Serial.print(remembers[i]);
    lcd.setCursor(0,0);
    lcd.print(i+1);
    lcd.print(". "+ remembers[i]);
    lcd.setCursor(0,1);
    lcd.print(i+2);
    lcd.print(". "+ remembers[i+1]);
    delay(1500);
  }
}
// Funker ikkje
void printSameLines(){
  	
	for(int i=0; i<(sizeof(remembers)/sizeof(String))-1; i+=2){
		lcd.setCursor(0,cursor);
		if( (remembers[i].length() + remembers[i+1].length()) < 15){
			lcd.print(remembers[i] + ", " + remembers[i+1]);
			
		}else{
			lcd.print(remembers[i] + ",");
		}
		if(cursor == 0){
			cursor = 1;
		}else{
			delay(1500);
			lcd.clear();
			cursor = 0;
		}
	}
}