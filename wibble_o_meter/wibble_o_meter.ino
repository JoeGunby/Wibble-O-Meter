#include <LiquidCrystal.h>
#include <IRremote.h>

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int long WibbLevel = 0;
int LastStatusSensor = 1;

//IR Reciever setup
const int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Initialising...");
  delay(2000);
  lcd.clear();

  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  Title();
  WibbCount();
}

void Title() {
  lcd.setCursor(0, 0);
  lcd.print("Wibble-O-Meter:");
}

void WibbCount() {
  lcd.setCursor(0, 1);
  lcd.print(WibbLevel);
  lcd.print(" MW/H");


  int StatusSensor = digitalRead(RECV_PIN);
  if (StatusSensor != LastStatusSensor) {
    if (irrecv.decode(&results)){
  
          if (results.value == 0XFFFFFFFF)
            results.value = WibbLevel;
          
          switch(results.value){
            case 0xFFA857:
            WibbLevel--;
            Serial.println(WibbLevel);
            break;
            case 0xFF629D:
            WibbLevel++;
            Serial.println(WibbLevel);
            break;
          }
          WibbLevel = results.value;
          irrecv.resume();
    }
    LastStatusSensor = StatusSensor;
  }
}











