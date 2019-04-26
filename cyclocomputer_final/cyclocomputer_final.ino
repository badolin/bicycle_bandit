
/*
 * W kazdym m5 stacku nalezy ustawić(w razie problemów ze znalezieniem gorąco polecem ctrl+ f):
 * IPAddress outIp  <--IP na który wysyłamy dane
 * IPAddress localIp  <-- Nasze IP
 * outPort  <- port na który wysyłamy dane
 * localPort <- port na którym nasłuchujemy OSC
 * names[] <-- tabela z imionami uczestnikow
 * targets[] <-- tabela z celami 
 * bikeId  <-- nr maszyny
 * ewentualnie zalecam też sprawdzić ssid oraz password( nazwa i hasło sieci)
 * 
 * kitchen:
 * IPAddress outIp = 192.168.1.20;
 * IPAddress localIp = 192.168.1.216;
 * outPort = 
 * localPort = 
 * char *names[] = {"Radek", "Kasia", "Igor", "Justyna", "Lukasz", "Magda W", "Iza", "Oleh", "Bartek", "Magda Z", "Kuba", "Angelika"};   /// gdy ktos odpadnie nalezy skasowac
 * char *targets[] ={"Lodowka", "Woda w kuch"};
 * int bikeId = 1
 * 
 * 
 * TVRoom:
 * IPAddress outIp = 192.168.1.20;
 * IPAddress localIp = 192.168.1.217;
 * outPort = 
 * localPort = 
 * char *names[] = {"Radek", "Kasia", "Igor", "Justyna", "Lukasz", "Magda W", "Iza", "Oleh", "Bartek", "Magda Z", "Kuba", "Angelika"};   /// gdy ktos odpadnie nalezy skasowac
 * char *targets[] ={"Prysznic"};
 * int bikeId = 2
 * 
 * 
 * Backup <- w backupie wgrane ponizsze dane, w razie ostatecznej podmiany nalezy ustawić któreś z powyższych danych
 * IPAddress outIp = 192.168.1.20;
 * IPAddress localIp = 192.168.1.218;
 * outPort = 
 * localPort = 
 * char *names[] = {"Radek", "Kasia", "Igor", "Justyna", "Lukasz", "Magda W", "Iza", "Oleh", "Bartek", "Magda Z", "Kuba", "Angelika"};   /// gdy ktos odpadnie nalezy skasowac
 * char *targets[] ={"Prysznic","Lodowka", "Woda w kuch"};
 * int bikeId = 3
 * 
 * 
 * 
 * podlaczenie kabli:
 * 
 * 
 * bialy kabel - 3v3
 * czarny kabel - AD 35
 * brazowy kabel - G
 * 
 * 
 * 
 * karta SD:
 * 
 * na karcie SD powinny byc dwa pliki o nazwach currentDate.txt oraz idRide.txt    . W tym pierwszym aktualna data w formacie DDMMRR np: 200419 dla 20 kwietnia 2019 roku, a w drugim wartość 0.
 * 
 * W BUCKUPIE NIE MA KARTY
 * 
 * karty SD pomalowane, docelowo: zielona w kitchenn czarna w tw room
 * 
 * w razie problemów dzwonic do Bartka lub Pszemka
 * 
 * 
 * 
 */


#include <M5Stack.h>

// WiFi includes
#include <WiFi.h>
#include <WiFiUdp.h>

// OSC includes
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

// ###########################################################################################################

// -----------------------
//  SPEEDOMETER VARIABLES
// -----------------------

long previous = 0; // time
long previousCircle = 0;
long timeInterval = 0;
long impulses = 0;
long tripTime = 0;
long firstTimeNoImpulses = 0;
long noImpulsesTimer = 0;
long firstTimeSameImpulses = 0;
long sameImpulsesTimer = 0;

bool redCircle = false;


int distance = 0;
int timerCounter = 0;
int writeDistance = 0;

//impulses
int previousImpulse = 0;
int currentImpulse = 0;
int impulseDifference = 0;
int zeroVelocityInterval = 3500;

float velocity, velocityKMH, meanSpeed, distanceGoal;
float speedThr = 1.4;
float timeIntervalSeconds = 0;


int contactIN = 35;


int wheelSpinThr = 300; //warunek obrotu kola
float wheelCircuit = 2.1;

int day = 4;
int month = 4;

int logNum = 0; // number of a bike ride upon which an action is being taken
int logSum = 0; // number of bike rides made that day

bool rideRegistered = false;
bool goalAchieved = false;


// ###########################################################################################################
// ###########################################################################################################

// ------------------
//  Network Settings
// ------------------

WiFiUDP Udp;

const char* ssid ="UF-LP-RnD";
const char* password = "1234qwer";

const IPAddress outIp(192,168,1,21);  // komp na 19
const IPAddress localIp(192,168,1,218); // 216 <- Rower w kuchni, 217 <- Rower w TV, 218 <- BuckUp
const IPAddress gateway(192,168,1,254); 
const IPAddress subnet(255,255,255,0);

const unsigned int outPort = 8150; //pytanie do jezu
const unsigned int localPort = 8100; // pytanie do jezu


String M5STACK_DATA;

// ###########################################################################################################

// -------------------------------
//  Arrays functions
// -------------------------------

template<typename T, size_t N> size_t ArraySize(T(&)[N]){ return N; }

// ###########################################################################################################

// ---------------------------
//  Background defines
// ---------------------------

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
#define greenButton greenButton // 240x108
#define blackSpace blackSpace // 240x108


// ###########################################################################################################

// -----------------------
//  Colors
// -----------------------

const unsigned int black = M5.Lcd.color565(0,0,0);
const unsigned int blue = M5.Lcd.color565(0,0,255);
const unsigned int red = M5.Lcd.color565(237,0,0);


// ###########################################################################################################

// -----------------------
//  Tabels
// -----------------------

char *names[] = {"Radek", "Kasia", "Igor", "Justyna", "Lukasz", "Magda W", "Iza", "Oleh", "Bartek", "Magda Z", "Kuba", "Angelika"};
char *targets[] ={"Lodowka", "Woda w kuch", "Prysznic"};
int sizeOfNames = ArraySize(names);
int sizeOfTargets = ArraySize(targets);
int currentPositionName = 0;
int currentPositionTarget = 0;

// ###########################################################################################################

// -----------------------
//  SD card
// -----------------------

File plik;
int idRide;
char srednik[] = ";";
int currentTime = 999999;           // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int currentDate;
bool positionLog = false; //false <- mozna zapisac pierwsza czesc

void writeStartOfLog(){
  readIdRide();
  String s = "/" + String(currentDate) + ".csv";
  plik = SD.open( s, FILE_APPEND);
  plik.print(idRide);
  plik.print(srednik);
  plik.print(names[currentPositionName]);
  plik.print(srednik);
  plik.print(targets[currentPositionTarget]);
  plik.print(srednik);
  plik.print(millis());
  plik.print(srednik);
  plik.close();  
}

void writeEndOfLog(){
  String s = "/" + String(currentDate) + ".csv";
  plik = SD.open( s, FILE_APPEND);
  plik.print(writeDistance);
  plik.print(srednik);
  plik.print(millis());
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
void readDate(){
  plik = SD.open("/currentDate.txt", FILE_READ);
  currentDate = plik.parseInt();
  plik.close();
}


void createNewFileWithLog(int currentDate){
  String nameFile = "/" + String(currentDate) + ".csv";
  if(SD.exists(nameFile) == false){
    plik = SD.open(nameFile, FILE_WRITE);
    plik.close();
  }
}

void resetIdRide(){
  plik = SD.open("/idRide.txt", FILE_WRITE);
  plik.close();
  plik = SD.open("/idRide.txt", FILE_APPEND);
  plik.print(0); 
  plik.close(); 
}




// ###########################################################################################################

// ---------------------------
//  OSC Settings & Functions
// ---------------------------

// Settings
unsigned int bikeID = 3;
String bikeName;
String msg_preSystem = "/" + String(bikeID) + "/";
String ip_str = WiFi.localIP().toString();
String speedometerArgument = "speed";
String systemArgument = "system";

int lastVelocityValue = 1;

void oscSendInt(String topic, String dataType, int data)
{
  String dataS = String(data);
  String msg_prefix;
  if(topic == speedometerArgument)
  {
    msg_prefix = "/" + String(bikeID) + "/"  + String(names[currentPositionName]) +"/" + String(targets[currentPositionTarget]) + "/";
  }
  else if(topic == systemArgument)
  {
    msg_prefix = msg_preSystem;
  }
  else if(topic == "changeDate"){
    msg_prefix = "/" + String(bikeID) + "/";
  }
	OSCMessage msg((msg_prefix + dataType).c_str());
  msg.add(data);
	Udp.beginPacket(outIp, outPort);
  	msg.send(Udp);
  	Udp.endPacket();
  	msg.empty();
}

void oscSendFloat(String topic, String dataType, float data)
{
  String dataS = String(data);
  String msg_prefix;
  if(topic == speedometerArgument)
  {
    msg_prefix = "/" + String(bikeID) + "/"  + String(names[currentPositionName]) +"/" + String(targets[currentPositionTarget]) + "/";
  }
  else if(topic == systemArgument)
  {
    msg_prefix = msg_preSystem;
  }
	OSCMessage msg((msg_prefix + dataType).c_str());
  msg.add(data);
	Udp.beginPacket(outIp, outPort);
  	msg.send(Udp);
  	Udp.endPacket();
  	msg.empty();
}

void oscSendString(String topic, String dataType, String data)
{
  String dataS = String(data);
  String msg_prefix;
  if(topic == speedometerArgument)
  {
    msg_prefix = "/" + String(bikeID) + "/"  + String(names[currentPositionName]) +"/" + String(targets[currentPositionTarget]) + "/";
  }
  else if(topic == systemArgument)
  {
    msg_prefix = msg_preSystem;
  }
  
	OSCMessage msg((msg_prefix + dataType).c_str());
  msg.add((data).c_str());
	Udp.beginPacket(outIp, outPort);
  	msg.send(Udp);
  	Udp.endPacket();
  	msg.empty();
}

void oscSendValues(float velocity, float distance)
{ 
  if(velocity > 0){
    oscSendFloat("speed", "velocity", velocity);
    oscSendInt("speed", "distance", distance);
    if(positionLog == false){
        writeStartOfLog();
        positionLog = true;
    }
    lastVelocityValue = velocity;
  }
  if(lastVelocityValue != 0){  
	  oscSendFloat("speed", "velocity", velocity);
	  oscSendInt("speed", "distance", distance);
    if(velocity ==0){
         if(positionLog == true){
         writeEndOfLog();
         positionLog = false;
    }  
   }
    lastVelocityValue = velocity;
  }

}

// ###########################################################################################################

// -----------------
//   OSC Callbacks
// -----------------

void check(OSCMessage &msg)
{
	int checkVal = msg.getInt(0);
	if(checkVal == 5000)
	{
		oscSendInt("system", "check", 1);
	}
	else if(checkVal == 5001)
	{
		oscSendInt("system", "check", 0);
	}
	else
	{
		oscSendInt("system", "check", 404);
	}
}

void greenButtonn(OSCMessage &msg)
{
	int checkVal = msg.getInt(0);
  if(checkVal == 1){
    displayGreenButton();   
  }
  else if(checkVal == 0){
    displayBlackSpace();
  }
}

void makeNewFile(OSCMessage &msg)
{
  int checkVal = msg.getInt(0);
	if(checkVal == 1)
  {
    
  }
}

void changeDate(OSCMessage &msg)
{
	int a = msg.getInt(0);
  plik = SD.open("/currentDate.txt", FILE_WRITE);
  plik.close();
  plik = SD.open("/currentDate.txt", FILE_APPEND);
  plik.print(a); 
  plik.close();
  readDate();
  oscSendInt("changeDate", "new_date", currentDate);
  createNewFileWithLog(currentDate);
  resetIdRide();
}

void changeTime(OSCMessage &msg)
{
	currentTime = msg.getInt(0);
  oscSendInt("changeDate", "new_time", currentTime);
  
}

void listFiles(OSCMessage &msg)
{
	// lista plikow       niech zwraca liste plikow fileList i wysyla ja przez OSC                      //%%%%%%%%%%%%%%%%%%%%%%%%%%% ZRUP
  String fileList;
  oscSendString("system", "filelist", fileList);
}



void sendCsv(OSCMessage &msg){
  int a = msg.getInt(0);
  String nameCsv = "/" + String(a) + ".csv";
  String dataString; 
  int character = 0;
  int countOfWords = 0;
  plik = SD.open(nameCsv , FILE_READ);
  while(plik.available()){
    character = plik.read();
    if(character == 59){
      countOfWords ++;
    }
    dataString += char(character);
    if(countOfWords == 120){
      oscSendString("system","log", dataString);
      dataString = "";
      countOfWords = 0;
    }
  }
  oscSendString("system","log", dataString);  
  plik.close();
  
}
// -------
//  GUI
// -------

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

// ###########################################################################################################

// -------
//  SETUP
// -------
void setup() {
  M5.begin();
// WiFi setup
  WiFi.config(localIp, gateway, subnet);
  WiFi.mode(WIFI_STA);
  dacWrite(25,0);
  M5.Speaker.end();
  
  WiFi.begin(ssid,password);
/*
  while(WiFi.waitForConnectResult() != WL_CONNECTED) 
	{
	  delay(500);
	}
 */
// Begin WiFiUDP
  Udp.begin(localPort);
  delay(100);
// Speedometer setup
  pinMode(contactIN, INPUT);
  M5.Lcd.setBrightness(100);
  M5.Lcd.setRotation(8);
  loadingGui();
  printNames(currentPositionName);
  printTarget(currentPositionTarget);
  readDate();
  oscSendInt("system", "date", 1); // %%%%%%%%%%%% wysylamy request do Piotrka; jesli nam wysle to nadpisze nam sie data, jesli nie to pozostanie taka jak na poczatku
                                    //%%%%%%%%%%%% info dla Piotrka: request o date: /1/
}

// ###########################################################################################################

// -------------
//   MAIN LOOP
// -------------
void loop() {
  M5.update();
  
  if(impulses == 0){
  if(M5.BtnA.wasPressed()) {
      impulses = 0;
      distance = 0;
      displayBlackSpace();
      currentPositionName += 1;
      if(currentPositionName == sizeOfNames) {
        currentPositionName = 0;
      }
      cleaningTopPanel();
      printNames(currentPositionName);
      
    }
    if(M5.BtnC.wasPressed()) {
      impulses = 0;
      distance = 0;
      displayBlackSpace();
      currentPositionTarget += 1;
      if(currentPositionTarget == sizeOfTargets) {
        currentPositionTarget = 0;
      }
      cleaningBotPanel();
      printTarget(currentPositionTarget);
    }
  }
  OSCMessage bundle;
  int size = Udp.parsePacket();



//OSC dispatcher
  if (size > 0) {
      while (size--) {
        bundle.fill(Udp.read());
      }
      if (!bundle.hasError()) {
      	bundle.dispatch("/td/check", check);
  		  bundle.dispatch("/td/greenbutton", greenButtonn);
  		  bundle.dispatch("/td/new", makeNewFile);
  		  bundle.dispatch("/td/date", changeDate);
  		  bundle.dispatch("/td/time", changeTime);
  		  bundle.dispatch("/td/list", listFiles);
        bundle.dispatch("/td/dump", sendCsv);
      } 
   }
  
  int aRead;
  int bRead;
  
  aRead = analogRead(contactIN);
  
  
  currentImpulse = analogRead(contactIN);
  if (currentImpulse < 625) {
    currentImpulse = 0;
  }
  
  
  if(currentImpulse == 0 && noImpulsesTimer == 0)
  {
  	firstTimeNoImpulses = millis();
  	noImpulsesTimer = millis();
  }
  else if(currentImpulse == 0 && noImpulsesTimer != 0)
  {
  	noImpulsesTimer = millis();
  }
  else
  {
  	noImpulsesTimer = 0;
  }
  
  if(currentImpulse == previousImpulse && sameImpulsesTimer == 0)
  {
  	firstTimeSameImpulses = millis();
  	sameImpulsesTimer = millis();
  }
  else if(currentImpulse == previousImpulse && sameImpulsesTimer != 0)
  {
  	sameImpulsesTimer = millis();
  }
  else
  {
  	sameImpulsesTimer = 0;
  }
  
  impulseDifference = currentImpulse - previousImpulse;
  if(millis() - previous > 100){
    M5.Lcd.fillCircle(225,135,15,black);
    redCircle = false;
  }
  
  if(impulseDifference>4000)
  {
  	  impulses++;
    	//count turn time
    	timeInterval = (millis()-previous); // time between impulses
    	//count speed
    	timeIntervalSeconds = timeInterval / 1000.00;
    	velocity = (wheelCircuit / timeIntervalSeconds);
    	velocityKMH = velocity * 3.6;
    	previous = millis();
    	distance = impulses * wheelCircuit;
  	  oscSendValues(velocityKMH, distance);  
      M5.Lcd.fillCircle(225,135,15,red);
      redCircle = true;
      
      writeDistance = distance;
  } 
  else if(((currentImpulse == 0) && ((noImpulsesTimer - firstTimeNoImpulses) > zeroVelocityInterval)) || ((currentImpulse == previousImpulse) && ((sameImpulsesTimer - firstTimeSameImpulses) > zeroVelocityInterval)))
	{
    impulses = 0;
    distance = 0;
		oscSendValues(0, distance);
    
	}
 
	previousImpulse = currentImpulse;
}
