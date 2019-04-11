#include <M5Stack.h>

#define PicArray extern unsigned char 
PicArray whiteSpaceBigTop[];
PicArray whiteSpaceBigBot[];
PicArray whiteSpace[];
PicArray whiteSpaceSmall[];
PicArray separatingStrap[];
PicArray topArrow[];
PicArray botArrow[];
#define whiteSpaceBigTop whiteSpaceBigTop // 215 x 36
#define whiteSpaceBigBot whiteSpaceBigBot // 215 x 36
#define whiteSpace whiteSpace // 145 x 24
#define whiteSpaceSmall whiteSpaceSmall // 98 x 18
#define separatingStrap separatingStrap // 240 x 10
#define topArrow topArrow // 20x100
#define botArrow botArrow // 20x100


const unsigned int black = M5.Lcd.color565(0,0,0);
const unsigned int blue = M5.Lcd.color565(0,0,255);
const unsigned int red = M5.Lcd.color565(237,0,0);

char *names[] = {"Radek P", "Kasia O", "Igor J", "Justyna Z", "Lukasz D", "Magda W", "Iza M", "Oleh R", "Klaudia M", "Bartek B", "Magda Z"};
char *works[] = {"Lodowka", "Ciepla woda", "Wino", "Papierosy"};
int i = 0;
int j = 0;

void setup() {
  M5.begin();
  M5.Lcd.setBrightness(200);
  M5.Lcd.setRotation(2);
  loadingWholeBackground();
  printNames(i);
  printWorks(j);
}

void loop() {
  if(M5.BtnC.wasPressed()) {
    i += 1;
    if(i == 11) {
      i = 0;
    }
    cleaningTopPanel();
    printNames(i);
  }
  if(M5.BtnA.wasPressed()) {
    j += 1;
    if(j == 4) {
      j = 0;
    }
    cleaningBotPanel();
    printWorks(j);
  }
  M5.update();  
}


void loadingWholeBackground() {
  M5.Lcd.drawBitmap(0, 0, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 110, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 200, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 310, 240, 10, (uint8_t*)separatingStrap);
  
  M5.Lcd.drawBitmap(5, 15, 215, 36, (uint8_t*)whiteSpaceBigTop);
  M5.Lcd.drawBitmap(5, 57, 145, 24, (uint8_t*)whiteSpace);
  M5.Lcd.drawBitmap(5, 87, 98, 18, (uint8_t*)whiteSpaceSmall);
  
  M5.Lcd.drawBitmap(5, 269, 215, 36, (uint8_t*)whiteSpaceBigBot);
  M5.Lcd.drawBitmap(5, 239, 145, 24, (uint8_t*)whiteSpace);
  M5.Lcd.drawBitmap(5, 215, 98, 18, (uint8_t*)whiteSpaceSmall);

  M5.Lcd.drawBitmap(220, 10, 20, 100, (uint8_t*)topArrow);
  M5.Lcd.drawBitmap(220, 210, 20, 100, (uint8_t*)botArrow);  
}

void cleaningTopPanel() {
  M5.Lcd.drawBitmap(5, 15, 215, 36, (uint8_t*)whiteSpaceBigTop);
  M5.Lcd.drawBitmap(5, 57, 130, 24, (uint8_t*)whiteSpace);
  M5.Lcd.drawBitmap(5, 87, 98, 18, (uint8_t*)whiteSpaceSmall);
  M5.Lcd.drawBitmap(220, 10, 20, 100, (uint8_t*)topArrow);
}

void cleaningBotPanel() {
  M5.Lcd.drawBitmap(5, 269, 215, 36, (uint8_t*)whiteSpaceBigBot);
  M5.Lcd.drawBitmap(5, 239, 145, 24, (uint8_t*)whiteSpace);
  M5.Lcd.drawBitmap(5, 215, 98, 18, (uint8_t*)whiteSpaceSmall);
  M5.Lcd.drawBitmap(220, 210, 20, 100, (uint8_t*)botArrow);
}

void printName(int indexOfName, int textSize, int textColor, int xCursor ) {
  M5.Lcd.setTextColor(textColor);
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.setCursor( 9, xCursor);
  M5.Lcd.println(names[indexOfName]);  
}

void printNames(int indexOfMainName) {
  if(indexOfMainName == 10) {
    printName(10, 3, red, 22);
    printName(0, 2, black, 62);
    printName(1, 1, black, 92);    
  }
  if(indexOfMainName == 9) {
    printName(9, 3, red, 22);
    printName(10, 2, black, 62);
    printName(0, 1, black, 92);    
  }
  if(indexOfMainName != 10 && indexOfMainName != 9) {
    printName(indexOfMainName, 3, red, 22);
    printName(indexOfMainName + 1, 2, black, 62);
    printName(indexOfMainName + 2, 1, black, 92);    
  }
}

void printWork(int indexOfWork, int textSize, int textColor, int xCursor ) {
  M5.Lcd.setTextColor(textColor);
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.setCursor( 9, xCursor);
  M5.Lcd.println(works[indexOfWork]);  
}

void printWorks(int indexOfMainWork) {
  if(indexOfMainWork == 3) {
    printWork(3, 3, blue, 274);
    printWork(0, 2, black, 244);
    printWork(1, 1, black, 219);    
  }
  if(indexOfMainWork == 2) {
    printWork(2, 3, blue, 274);
    printWork(3, 2, black, 244);
    printWork(0, 1, black, 219);    
  }
  if(indexOfMainWork != 3 && indexOfMainWork != 2) {
    printWork(indexOfMainWork, 3, blue, 274);
    printWork(indexOfMainWork + 1, 2, black, 244);
    printWork(indexOfMainWork + 2, 1, black, 219);    
  }
}
