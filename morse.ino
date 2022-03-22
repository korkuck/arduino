// Txt to Morse 
// Display on diode + buzzer

#define MAXSPLIT 6
bool stop = 1;
String inputString = "sos SOS"; //Type your input sentence here
String splitInput[MAXSPLIT];
int splitCount = 0;
const int diode = 13;
const int buzzer = 2;
const int buzzerTone = 1000;
const int unit = 350;
const int dot = unit;
const int dash = 3 * unit;
const int nextSign = unit;
const int nextLetter = 3 * unit;
const int nextWord = 7 * unit;
const char code[27][5] = {
"01","1000","1010","100","0","0010","110","0000","00","0111",
"101","0100","11","10","111","0110","1101","010","000","1",
"001","0001","011","1001","1011","1100"
};

void setup() {
    initPins();
    Serial.begin(9600);
    inputString.toLowerCase();
    for(int i = 0; i < split(inputString, ' '); i++){
      if(splitInput[i].length() > 0){
        Serial.println(splitInput[i]);
        signalMorse(splitInput[i]);
        Serial.print(" - ");
        delay(nextWord);  
      }
    }
}

void loop() {
  
}

void initPins(){
  pinMode(diode, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

int split(String str, char c){
  String tmp = str;
  int i;
  int n = 0;
  while(i = findChar(tmp, c)){
    i--;
    splitInput[n++] = tmp.substring(0,i);
    tmp = tmp.substring(i+1); 
    if(n >= MAXSPLIT)
      return n;
  }
  if(i < str.length())
    splitInput[n++] = tmp;
  return n;
}

int findChar(String str, char c){
  int i = 0;
  while(str.charAt(i) == c)
    i++;
  for(; i < str.length(); i++)
    if(str.charAt(i) == c)
      return i+1;
  return 0;
}

void signalMorse(String str){
  int a;
  for(int i = 0; i < str.length(); i++){
      a = str.charAt(i) - 'a';
      if(a >= 0 && a <= 25)
        blink(a);
      Serial.print(" ");
      delay(nextLetter);
  }
}

void blink(int a){
  for(byte i = 0; i < 4; i++){
    if(code[a][i] == '0'){
      digitalWrite(diode, HIGH);
      tone(buzzer, buzzerTone);
      delay(dot);
      digitalWrite(diode, LOW);
      noTone(buzzer);
      Serial.print("dot");
      delay(nextSign);
    }
    if(code[a][i] == '1'){
      digitalWrite(diode, HIGH);
      tone(buzzer, buzzerTone);
      delay(dash);
      digitalWrite(diode, LOW);
      noTone(buzzer);
      Serial.print("dash");
      delay(nextSign);
    }
  }
}
