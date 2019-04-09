#include <M5Stack.h>

#define background back
#define PicArray extern unsigned char 
PicArray background[];

const unsigned int red = M5.Lcd.color565(255,0,0);
const unsigned int black = M5.Lcd.color565(0,0,0);

char *names[] = {"Radek P", "Kasia O", "Igor J", "Justyna Z", "Lukasz D", "Magda W", "Iza M", "Oleh R", "Klaudia M", "Bartek B", "Magda Z"};
char *activity[] = {"Otwarta Lodowka", "Ciepla Woda", "Butelka Wina", "Paczka papierosow"};
int i = 0;
int j = 0;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setBrightness(200);
  
  displayBackground();
  printMainName(i);
  printEarlierName(i);
  printLaterName(i);
  printMainActivity(j);
  printEarlierActivity(j);
  printLaterActivity(j);
}

void loop() {
  
  if(M5.BtnA.wasPressed()) {
    i += 1;
    if( i == 11)
    {
     i = 0;
    }
    displayBackground();
    printMainName(i);
    printEarlierName(i);
    printLaterName(i);
    printMainActivity(j);
    printEarlierActivity(j);
    printLaterActivity(j);   
  }
  if(M5.BtnB.wasPressed()) {
    j += 1;
    if( j == 4)
    {
     j = 0;
    }
    displayBackground();
    printMainName(i);
    printEarlierName(i);
    printLaterName(i);
    printMainActivity(j);
    printEarlierActivity(j);
    printLaterActivity(j);   
  }
  
  M5.update();
  

}

void displayBackground(){
  M5.Lcd.drawBitmap(0, 0, 320, 240, (uint8_t*)back); 
}

void printMainName(int index) {
  M5.Lcd.setTextColor(black);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor( 55, 48);
  M5.Lcd.println(names[index]);  
}

void printEarlierName(int index) {
  M5.Lcd.setTextColor(black);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( 62, 15);
  if(index == 0){
    M5.Lcd.println(names[10]);   
  }
  if( index !=  0){
    M5.Lcd.println(names[index - 1]);
  }
}

void printLaterName(int index) {
  M5.Lcd.setTextColor(black);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( 62, 83);
  if(index == 10){
    M5.Lcd.println(names[0]);   
  }
  if( index !=  10){
    M5.Lcd.println(names[index + 1]);
  }
}

void printMainActivity(int index){
  M5.Lcd.setTextColor(black);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( 55, 48 + 120);
  M5.Lcd.println(activity[index]);  
}

void printEarlierActivity(int index) {
  M5.Lcd.setTextColor(black);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( 62 , 15 + 120);
  if(index == 0){
    M5.Lcd.println(activity[3]);   
  }
  if( index !=  0){
    M5.Lcd.println(activity[index - 1]);
  }
}

void printLaterActivity(int index) {
  M5.Lcd.setTextColor(black);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( 62, 83+ 120);
  if(index == 3){
    M5.Lcd.println(activity[0]);   
  }
  if( index !=  3){
    M5.Lcd.println(activity[index + 1]);
  }
}
