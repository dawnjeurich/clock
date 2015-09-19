#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned long time;
long offset = 0;

char stime[9];
byte seconds, minutes, hours;
char str[9];

void setup() {                
  lcd.begin(16,2);
  lcd.setCursor(0,0);
}

enum BUTTONS {
  NONE = 0, UP = 1, DOWN = 2,
  LEFT = 3, RIGHT = 4, SELECT = 5, RESET = 6
};

BUTTONS button;
byte selected = 0;

int ibutton = 0;
unsigned long lastRead = 0;
BUTTONS readButton () {
  unsigned long now = millis();
  if (now - lastRead < 500) return NONE; // debounce
  lastRead = now;
  ibutton = analogRead(0);
  if (ibutton > 1000) return NONE;
  if (ibutton < 50) return RIGHT;
  if (ibutton < 250) return UP;
  if (ibutton < 450) return DOWN;
  if (ibutton < 650) return LEFT;
  if (ibutton < 850) return SELECT;
  return NONE;
}

void loop() {
  time = (millis() / 1000 + offset) % (60 * 60 * 24);
  seconds = time % 60;
  minutes = time / 60 % 60;
  hours = time / 60 / 60 % 24;
  sprintf(str, "%02d:%02d:%02d", hours, minutes, seconds);
  lcd.setCursor(0,0);
  lcd.print(str);
  lcd.setCursor(0,1);
  char ostr[8];
  itoa(offset, ostr, 10);
  lcd.print(ostr);
  lcd.print("      ");

  button = readButton();
  if (button == LEFT) {
    selected = (selected + 1) % 3;
  } else if (button == RIGHT) {
    selected = (selected + 3 - 1) % 3;
  } else if (button == UP && selected == 0) {
    offset += 60 * 60;
  } else if (button == UP && selected == 1) {
    offset += 60;
  } else if (button == UP && selected == 2) {
    offset += 1;
  } else if (button == DOWN && selected == 0) {
    offset -= 60 * 60;
  } else if (button == DOWN && selected == 1) {
    offset -= 60;
  } else if (button == DOWN && selected == 2) {
    offset -= 1;
  }
}
