#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "Arduino.h"
// Software SPI (slower updates, more flexible pin options):
// pin 3 - Serial clock out (SCLK)
// pin 4 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 6 - LCD chip select (CS)
// pin 7 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);
# define LED_1_PIN 10
# define LED_2_PIN 11
# define LED_3_PIN 12
# define LED_4_PIN 13
# define LED_5_PIN 14
# define LED_6_PIN 15
# define LED_7_PIN 16
# define BUTTON_PIN1 2
# define BUTTON_PIN2 8
# define BUTTON_PIN3 9

int n = 25; //tacts
int selectdrive=0;
int selectrepeat=1;

int asd[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //cycle array

int asd1[] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //cycle array
int asd2[] = {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0}; //cycle array
int asd3[] = {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0}; //cycle array
int asd4[] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}; //cycle array
int asd5[] = {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}; //cycle array
int asd6[] = {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0}; //cycle array
int asd7[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}; //cycle array
boolean cycle = true; //ready to start
int page = 1;
int menuitem = 1;
int i;
int xArray = 0;
class Button {
  private:
    byte _pin;
  public:

    int lastButtonState;
  boolean click;
  void checkPress() {

    if (digitalRead(_pin) != lastButtonState) {

      if (digitalRead(_pin) == 0) {
        click = true;
      }
      delay(50);
    }
    lastButtonState = digitalRead(_pin);
  }
  void setPin(byte pin) {
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);

  }

}
;Button down
;Button select
;Button back;

void setup() {

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(LED_5_PIN, OUTPUT);
  pinMode(LED_6_PIN, OUTPUT);
  pinMode(LED_7_PIN, OUTPUT);
  display.begin();
  display.setContrast(40); //Set contrast to 40
  display.clearDisplay();
  display.print("  Loading");
  delay(1000);
  display.display();
  down.setPin(BUTTON_PIN1);
  select.setPin(BUTTON_PIN2);
  back.setPin(BUTTON_PIN3);

}

void loop() {
    down.checkPress();
    select.checkPress();
    back.checkPress();
    drawMenu();//Drive select
    if (back.click && page == 1 && menuitem == 1) {
      back.click = false;
      selectdrive++;
      if (selectdrive == 7) {
        selectdrive = 0;
        }
    }
    if (select.click && page == 1 && menuitem == 1) {
      select.click = false;
      page = 2;
    }
//углубление
    if (down.click && page == 1) {
      down.click = false;
      menuitem++;
      if (menuitem == 4) {
        menuitem = 1;
      }
    }
    // переключение ON вывод в исходную позицию
    if (select.click && back.click && menuitem == 2) {
      if (cycle == false){cycle = true;} 
      select.click = false;
      back.click = false; 
      delay(500);
      digitalWrite(LED_1_PIN, LOW);
      delay(1000);
      digitalWrite(LED_2_PIN, LOW);
      delay(1000);
      digitalWrite(LED_3_PIN, LOW);
      delay(1000);
      digitalWrite(LED_4_PIN, LOW);
      delay(1000);
      digitalWrite(LED_5_PIN, LOW);
      delay(1000); 
      digitalWrite(LED_6_PIN, LOW);
      delay(1000);  
      digitalWrite(LED_7_PIN, LOW);
      delay(1000);    
        
    }
   // выбор числа повторений 
    if (select.click && page == 1 && menuitem == 2) {
      select.click = false;
      selectrepeat++;
      if (selectrepeat == 50) {
        selectrepeat = 1;
        }
    }  
     if (back.click && page == 1 && menuitem == 2) {
      back.click = false;
      selectrepeat--;
      if (selectrepeat == 0) {
        selectrepeat = 49;
        }
    }      
        
        if (select.click && back.click && menuitem == 2) {
      if (cycle == true){cycle = false;} 
      select.click = false;
      back.click = false;
       
      delay(500);
    }
    if (cycle && select.click && menuitem == 3) {
      select.click = false;
       for(int i = 0; i < selectrepeat; i++){
        
        startcycle();
        }
      
    }
//2ая страница 
    if (page == 2 && down.click) {
      down.click = false;
      xArray++;
      if (xArray == n) {
        xArray = 0;
        page = 1;
      }
    }

  } // void loop

void drawMenu() {

    if (page == 1) {
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(BLACK, WHITE);
      display.setCursor(15, 0);
      display.print("MAIN MENU");
      display.drawFastHLine(0, 10, 83, BLACK);
      display.setCursor(0, 15);

      if (menuitem == 1) {
        display.setTextColor(WHITE, BLACK);
      } else {
        display.setTextColor(BLACK, WHITE);
      }
      display.print(">Setup Drive");//Drivesetup
      display.setCursor(75, 15); // print Drive select
      display.print(selectdrive);
      
      display.setCursor(0, 25);

      if (menuitem == 2) {
        display.setTextColor(WHITE, BLACK);
      } else {
        display.setTextColor(BLACK, WHITE);
      }
      display.print(">Turn");

      if (cycle) {
        display.print("ON");
      }
      if (cycle == false) {
        display.print("OFF");
      }
      display.setCursor(50, 25); // print Drive select
      display.print("Re=");
      display.print(selectrepeat);
      if (menuitem == 3) {
        display.setTextColor(WHITE, BLACK);
      } else {
        display.setTextColor(BLACK, WHITE);
      }
      display.setCursor(0, 35);
      display.print(">Start ");
    }
    if (page == 2) {
      setupCycle();
    } //page 2
    //page 2
    display.display();
  } //drawmenu


void setupCycle() {
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(10, 0);
  display.print("SetupDrive");
  display.setCursor(75, 0);
  display.print(selectdrive);//selectdrive
  display.drawFastHLine(0, 10, 83, BLACK);
  display.setCursor(0, 15);

    switch (selectdrive){
    case 0:
   for(int i = 0; i < n; i++){
    asd[i] = asd1[i];
    
   }
      
      break;
    case 1:
    for(int i = 0; i < n; i++){
    asd[i] = asd2[i];
   }
      break;
    case 2:
    for(int i = 0; i < n; i++){
    asd[i] = asd3[i];
   }
      break;  
    case 3:
     for(int i = 0; i < n; i++){
    asd[i] = asd4[i];
   }
      break;
      case 4:
     for(int i = 0; i < n; i++){
    asd[i] = asd5[i];
   }
      break;
      case 5:
     for(int i = 0; i < n; i++){
    asd[i] = asd6[i];
   }
      break; 
      case 6:
     for(int i = 0; i < n; i++){
    asd[i] = asd7[i];
   }
      break;
        
    }

  for (i = 0; i < n; i++) {
    display.print(asd[i]);
  } 
  display.setCursor(0, 35);
  switch (xArray) {
  case 0:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 1:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 2:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 3:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 4:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 5:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 6:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 7:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 8:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 9:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 10:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 11:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 12:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 13:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 14:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 15:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
  case 16:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 17:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 18:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 19:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 20:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 21:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 22:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 23:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 24:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;
 case 25:
    if (select.click) {
      asd[xArray] = 1;
      select.click = false;
    }
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      asd[xArray] = 0;
    }
    display.print(asd[xArray]);
    display.setCursor(35, 35);
    display.print("tact");
    display.setCursor(15, 35);
    display.print(xArray+1);
    break;


  case 26:
    display.setCursor(25, 35);
    display.print("return");
    if (asd[xArray] == 1 && back.click) {
      back.click = false;
      page = 1;
      xArray = 0;
    }
    break;
  }
  switch (selectdrive){
    case 0:
   for(int i = 0; i < n; i++){
    asd1[i] = asd[i];
    
   }
      
      break;
    case 1:
    for(int i = 0; i < n; i++){
    asd2[i] = asd[i];
   }
      break;
    case 2:
    for(int i = 0; i < n; i++){
    asd3[i] = asd[i];
   }
      break;  
    case 3:
     for(int i = 0; i < n; i++){
    asd4[i] = asd[i];
   }
      break; 
      case 4:
     for(int i = 0; i < n; i++){
    asd5[i] = asd[i];
   }
      break;
      case 5:
     for(int i = 0; i < n; i++){
    asd6[i] = asd[i];
   }
      break;
       case 6:
     for(int i = 0; i < n; i++){
    asd7[i] = asd[i];
   }
      break;              
    }

}
void startcycle() // функция старт цикла
  {
    if (cycle == false) return;
 
   
    for (i = 0; i < n; i++) {
  
   
    down.checkPress();
    select.checkPress();
    back.checkPress();
    if (down.click || select.click || back.click){
     cycle = false;
     page = 1;
     return;}

      if (asd1[i] == 1) {
        digitalWrite(LED_1_PIN, HIGH);
       
        
      } else {
        digitalWrite(LED_1_PIN, LOW);
        
      }
    if (asd2[i] == 1) {
        digitalWrite(LED_2_PIN, HIGH);
        
      } else {
        digitalWrite(LED_2_PIN, LOW);
        
      }
     if (asd3[i] == 1) {
        digitalWrite(LED_3_PIN, HIGH);
        
      } else {
        digitalWrite(LED_3_PIN, LOW);
        
      }
    if (asd4[i] == 1) {
        digitalWrite(LED_4_PIN, HIGH);
        
      } else {
        digitalWrite(LED_4_PIN, LOW);
        
      }
  if (asd5[i] == 1) {
     digitalWrite(LED_5_PIN, HIGH);
        
      } else {
        digitalWrite(LED_5_PIN, LOW);
        
    }
    if (asd6[i] == 1) {
     digitalWrite(LED_6_PIN, HIGH);
        
      } else {
        digitalWrite(LED_6_PIN, LOW);
        
    }
    if (asd7[i] == 1) {
     digitalWrite(LED_7_PIN, HIGH);
        
      } else {
        digitalWrite(LED_7_PIN, LOW);
        
    }
    delay(2000);
    
    }

    return cycle = false;
  }

