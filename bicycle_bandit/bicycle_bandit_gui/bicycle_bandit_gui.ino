#include <M5Stack.h>
/////////////////////////////////////
//to check the length of the tables//
/////////////////////////////////////

template<typename T, size_t N> size_t ArraySize(T(&)[N]){ return N; }
/////////////////////////////////////////////////////////
// HOW TO USE: int sizeArray = ArraySize(nameOfTable); //
/////////////////////////////////////////////////////////

/////////////////////////////////////
//             end                 //
/////////////////////////////////////

/////////////////
// background  //
/////////////////
#define PicArray extern unsigned char 
PicArray whiteSpaceBigTop[];
PicArray whiteSpaceBigBot[];
PicArray whiteSpace[];
PicArray whiteSpaceSmall[];
PicArray separatingStrap[];
PicArray topArrow[];
PicArray botArrow[];
PicArray greenButton[];
PicArray blackSpace[];

#define whiteSpaceBigTop whiteSpaceBigTop // 215 x 36
#define whiteSpaceBigBot whiteSpaceBigBot // 215 x 36
#define whiteSpace whiteSpace // 145 x 24
#define whiteSpaceSmall whiteSpaceSmall // 98 x 18
#define separatingStrap separatingStrap // 240 x 10
#define topArrow topArrow // 20x100
#define botArrow botArrow // 20x50
#define greenButton greenButton // 240x128
#define blackSpace blackSpace // 240x128
/////////////////
//     end     //
/////////////////

//////////
//colors//
//////////
const unsigned int black = M5.Lcd.color565(0,0,0);
const unsigned int blue = M5.Lcd.color565(0,0,255);
const unsigned int red = M5.Lcd.color565(237,0,0);
//////////
// end  //
//////////

//////////
//tabels//
//////////
char *names[] = {"Radek P", "Kasia O", "Igor J", "Justyna Z", "Lukasz D", "Magda W", "Iza M", "Oleh R", "Klaudia M", "Bartek B", "Magda Z"};
char *works[] = {"Lodowka", "Ciepla woda"};
int sizeOfNames = ArraySize(names);
int sizeOfWorks = ArraySize(works);
int currentPositionName = 0;
int currentPositionWork = 0;
//////////
// end  //
//////////

bool displayTheGreenButton = false;

void setup() {
  M5.begin();
  M5.Lcd.setBrightness(100);
  M5.Lcd.setRotation(2);
  loadingGui();
  printNames(currentPositionName);
  printWork(currentPositionWork);
}

void loop() {
  if(M5.BtnC.wasPressed()) {
    displayBlackSpace();
    displayTheGreenButton = false;
    currentPositionName += 1;
    if(currentPositionName == sizeOfNames) {
      currentPositionName = 0;
    }
    cleaningTopPanel();
    printNames(currentPositionName);
    
  }
  if(M5.BtnA.wasPressed()) {
    displayBlackSpace();
    displayTheGreenButton = false;
    currentPositionWork += 1;
    if(currentPositionWork == sizeOfWorks) {
      currentPositionWork = 0;
    }
    cleaningBotPanel();
    printWork(currentPositionWork);
  }
  if(M5.BtnB.wasPressed()) {
     displayTheGreenButton = !displayTheGreenButton;
     if(displayTheGreenButton == true){
      displayGreenButton();
     }
     if(displayTheGreenButton == false){
      displayBlackSpace();
     }
  }
  M5.update();  
}


void loadingGui() {
  M5.Lcd.drawBitmap(0, 0, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 110, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 248, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 310, 240, 10, (uint8_t*)separatingStrap);
  
  M5.Lcd.drawBitmap(5, 15, 215, 36, (uint8_t*)whiteSpaceBigTop);
  M5.Lcd.drawBitmap(5, 57, 145, 24, (uint8_t*)whiteSpace);
  M5.Lcd.drawBitmap(5, 87, 98, 18, (uint8_t*)whiteSpaceSmall);
  
  M5.Lcd.drawBitmap(5, 269, 215, 36, (uint8_t*)whiteSpaceBigBot);

  M5.Lcd.drawBitmap(220, 10, 20, 100, (uint8_t*)topArrow);
  M5.Lcd.drawBitmap(220, 260, 20, 50, (uint8_t*)botArrow);
  M5.Lcd.drawBitmap(0, 120, 240, 128, (uint8_t*)blackSpace);  
}

void cleaningTopPanel() {
  M5.Lcd.drawBitmap(5, 15, 215, 36, (uint8_t*)whiteSpaceBigTop);
  M5.Lcd.drawBitmap(5, 57, 130, 24, (uint8_t*)whiteSpace);
  M5.Lcd.drawBitmap(5, 87, 98, 18, (uint8_t*)whiteSpaceSmall);
  M5.Lcd.drawBitmap(220, 10, 20, 100, (uint8_t*)topArrow);
}

void cleaningBotPanel() {
  M5.Lcd.drawBitmap(5, 269, 215, 36, (uint8_t*)whiteSpaceBigBot);
  M5.Lcd.drawBitmap(220, 260, 20, 50, (uint8_t*)botArrow);
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

void printWork(int indexOfWork) {
  M5.Lcd.setTextColor(blue);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor( 9, 275);
  M5.Lcd.println(works[indexOfWork]);  
}

void displayGreenButton() {
  M5.Lcd.drawBitmap(0, 120, 240, 128, (uint8_t*)greenButton);
  M5.Lcd.setTextColor(black);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor( 62, 174);
  M5.Lcd.println("Eco Go!");  
}
void displayBlackSpace(){
  M5.Lcd.drawBitmap(0, 120, 240, 128, (uint8_t*)blackSpace);
}
