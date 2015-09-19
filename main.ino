#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned long time;
char stime[9];

void setup() {                
  lcd.begin(16,2);
  lcd.setCursor(0,0);
}

void loop() {
  time = millis();
  byte seconds = time / 1000 % 60;
  byte minutes = time / 1000 / 60 % 60;
  byte hours = time / 1000 / 60 / 60 % 24;
  char str[9];
  sprintf(str, "%02d:%02d:%02d", hours, minutes, seconds);
  lcd.setCursor(0,0);
  lcd.print(str);
  delay(250);
}
