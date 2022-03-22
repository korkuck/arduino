#include <LiquidCrystal.h>

const int RS = 11, EN = 12, D4 = 2, D5 = 3, D6 = 4, D7 = 5, V0 = 10;
const int c1 = 9, c2 = 8, c3 = 7, c4 =6, potPin = 1;
int val;

void setup() {
  initPins();
  manageLCD();
  
}

void loop() {
  controlableDiodeCircle();
}

void manageLCD(){
  digitalWrite(V0, LOW);
  digitalWrite(RS, HIGH);
  digitalWrite(EN, HIGH);
  LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
  lcd.begin(16, 2); // set up number of columns and rows
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("LCD");        // print message at (0, 0)
  lcd.setCursor(11, 1);
  lcd.print("TEST");        // print message at (0, 0)

}

void controlableDiodeCircle(){
  digitalWrite(c1, HIGH);
  readAndWait();
  digitalWrite(c4, LOW);
  readAndWait();
  digitalWrite(c2, HIGH);
  readAndWait();
  digitalWrite(c1, LOW);
  readAndWait();
  digitalWrite(c3, HIGH);
  readAndWait();
  digitalWrite(c2, LOW);
  readAndWait();
  digitalWrite(c4, HIGH);
  readAndWait();
  digitalWrite(c3, LOW);
  readAndWait();
}

void initPins(){
  pinMode(c1, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(c3, OUTPUT);
  pinMode(c4, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(V0, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void readAndWait(){
  val = analogRead(potPin) + 50;
  delay(val);
}
