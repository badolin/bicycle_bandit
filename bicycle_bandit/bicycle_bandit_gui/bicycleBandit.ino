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
char *names[] = {"Radek", "Kasia", "Igor", "Justyna", "Lukasz", "Magda W", "Iza", "Oleh", "Bartek", "Magda Z", "Kuba", "Andzelika"};
char *targets[] = {"Lodowka", "Woda w kuch"};
int sizeOfNames = ArraySize(names);
int sizeOfTargets = ArraySize(targets);
int currentPositionName = 0;
int currentPositionTarget = 0;
//////////
// end  //
//////////

/////////////////////
//read and write sd//
/////////////////////
File plik;
int idRide;
char srednik[] = ";";
int datastart = 131313;
int dystans = 5100;
int datakoniec = 141414;
int character = 0;
////////////////////
//      end       //
////////////////////



bool displayTheGreenButton = false;

void setup() {
  M5.begin();
  M5.Lcd.setBrightness(100);
  M5.Lcd.setRotation(8);
  loadingGui();
  printNames(currentPositionName);
  printTarget(currentPositionTarget);
}

void loop() {
  if(M5.BtnA.wasPressed()) {
    displayBlackSpace();
    displayTheGreenButton = false;
    currentPositionName += 1;
    if(currentPositionName == sizeOfNames) {
      currentPositionName = 0;
    }
    cleaningTopPanel();
    printNames(currentPositionName);
    
  }
  if(M5.BtnC.wasPressed()) {
    displayBlackSpace();
    displayTheGreenButton = false;
    currentPositionTarget += 1;
    if(currentPositionTarget == sizeOfTargets) {
      currentPositionTarget = 0;
    }
    cleaningBotPanel();
    printTarget(currentPositionTarget);
  }
  if(M5.BtnB.wasPressed()) {
    /*
     displayTheGreenButton = !displayTheGreenButton;
     if(displayTheGreenButton == true){
      displayGreenButton();
     }
     if(displayTheGreenButton == false){
      displayBlackSpace();
     }*/
  }
  //writeStartOfLog();//to tez wrzuc
  //writeEndOfLog();  //to tez wrzuc
  
  M5.update();  
}


void loadingGui() {
  //straps
  M5.Lcd.drawBitmap(0, 0, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 110, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 248, 240, 10, (uint8_t*)separatingStrap);
  M5.Lcd.drawBitmap(0, 310, 240, 10, (uint8_t*)separatingStrap);

  //top
  M5.Lcd.drawBitmap(20, 15, 215, 36, (uint8_t*)whiteSpaceBigTop);
  M5.Lcd.drawBitmap(20, 57, 145, 24, (uint8_t*)whiteSpace);
  M5.Lcd.drawBitmap(20, 87, 98, 18, (uint8_t*)whiteSpaceSmall);

  //mid
  M5.Lcd.drawBitmap(0, 120, 240, 128, (uint8_t*)blackSpace); 

  //bot
  M5.Lcd.drawBitmap(20, 269, 215, 36, (uint8_t*)whiteSpaceBigBot);

  //arrows
  M5.Lcd.drawBitmap(0, 10, 20, 100, (uint8_t*)topArrow);
  M5.Lcd.drawBitmap(0, 260, 20, 50, (uint8_t*)botArrow);   
}

void cleaningTopPanel() {
  M5.Lcd.drawBitmap(20, 15, 215, 36, (uint8_t*)whiteSpaceBigTop);
  M5.Lcd.drawBitmap(20, 57, 130, 24, (uint8_t*)whiteSpace);
  M5.Lcd.drawBitmap(20, 87, 98, 18, (uint8_t*)whiteSpaceSmall);
  M5.Lcd.drawBitmap(0, 10, 20, 100, (uint8_t*)topArrow);
}

void cleaningBotPanel() {
  M5.Lcd.drawBitmap(20, 269, 215, 36, (uint8_t*)whiteSpaceBigBot);
  M5.Lcd.drawBitmap(0, 260, 20, 50, (uint8_t*)botArrow);
}

void printName(int indexOfName, int textSize, int textColor, int xCursor ) {
  M5.Lcd.setTextColor(textColor);
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.setCursor( 24, xCursor);
  M5.Lcd.println(names[indexOfName]);  
}

void printNames(int indexOfMainName) {
  if(indexOfMainName == sizeOfNames - 1) {
    printName(sizeOfNames - 1, 3, red, 22);
    printName(0, 2, black, 62);
    printName(1, 1, black, 92);    
  }
  if(indexOfMainName == sizeOfNames - 2) {
    printName(sizeOfNames - 2, 3, red, 22);
    printName(sizeOfNames - 1, 2, black, 62);
    printName(0, 1, black, 92);    
  }
  if(indexOfMainName != sizeOfNames - 1 && indexOfMainName != sizeOfNames - 2) {
    printName(indexOfMainName, 3, red, 22);
    printName(indexOfMainName + 1, 2, black, 62);
    printName(indexOfMainName + 2, 1, black, 92);    
  }
}

void printTarget(int indexOfTarget) {
  M5.Lcd.setTextColor(blue);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor( 24, 275);
  M5.Lcd.println(targets[indexOfTarget]);  
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
void writeStartOfLog(){
  readIdRide();
  plik = SD.open("/170419.csv", FILE_APPEND);
  plik.print(idRide);
  plik.print(srednik);
  plik.print(names[currentPositionName]);
  plik.print(srednik);
  plik.print(targets[currentPositionTarget]);
  plik.print(srednik);
  plik.print(datastart);
  plik.print(srednik);
  plik.close();  
}

void writeEndOfLog(){
  plik = SD.open("/170419.csv", FILE_APPEND);
  plik.print(dystans);
  plik.print(srednik);
  plik.print(datakoniec);
  plik.print(srednik);
  plik.println();
  plik.close();  
}

void readIdRide(){
  plik = SD.open("/idRide.txt", FILE_READ);
  idRide = plik.parseInt();
  idRide++;
  plik.close();
  plik = SD.open("/idRide.txt", FILE_WRITE);
  plik.close();
  plik = SD.open("/idRide.txt", FILE_APPEND);
  plik.print(idRide);
  plik.close();
}

void resetIdRide(){
  plik = SD.open("/idRide.txt", FILE_WRITE);
  plik.close();
  plik = SD.open("/idRide.txt", FILE_APPEND);
  plik.print(0); 
  plik.close(); 
}
