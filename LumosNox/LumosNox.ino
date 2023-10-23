
/* TO DO: define the pins like in the notepad and test it and delete comments
          also add the timer and check if it works*/

/*
// ****************************************************************************
// the timer settings
#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int nint;
int pinLed=13;

volatile boolean f_wdt=1;

// ***************************************************************************
*/

// **nRF MODULE**
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// **light sensor **
#include <DFRobot_B_LUX_V30B.h>

// **LED MATRIX**
// Rows 
//#define R1 2
#define R2 4
#define R3 4
//#define R4 5
#define R5 5
#define R6 6
#define R7 9
//#define R8 9
//Columns
//#define C1 10
#define C2 A0
#define C3 A1
#define C4 A2
#define C5 A3
#define C6 A1
#define C7 10
//#define C8 A3


  int smile [8] [8] ={
  {1,1,1,1,1,1,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,1,1,1,1,1,1},
  {1,0,1,1,1,1,0,1},
  {1,1,0,1,1,0,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,1,1,1,1,1,1},
  };

  int sad [8] [8] ={
  {1,1,1,1,1,1,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,0,1,1,0,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,0,1,1,0,1,1},
  {1,0,1,1,1,1,0,1},
  {1,1,1,1,1,1,1,1},
  };

void SelectRow(int row){
  //if (row==1) digitalWrite(R1,HIGH); else digitalWrite(R1,LOW);
  if (row==2) digitalWrite(R2,HIGH); else digitalWrite(R2,LOW);
  if (row==3) digitalWrite(R3,HIGH); else digitalWrite(R3,LOW);
  //if (row==4) digitalWrite(R4,HIGH); else digitalWrite(R4,LOW);
  if (row==5) digitalWrite(R5,HIGH); else digitalWrite(R5,LOW);
  if (row==6) digitalWrite(R6,HIGH); else digitalWrite(R6,LOW);
  if (row==7) digitalWrite(R7,HIGH); else digitalWrite(R7,LOW);
  //if (row==8) digitalWrite(R8,HIGH); else digitalWrite(R8,LOW);
}

void SelectColumn(int column){
  if (column==0) {
  //digitalWrite(C1,HIGH);
  digitalWrite(C2,HIGH);
  digitalWrite(C3,HIGH);
  digitalWrite(C4,HIGH);
  digitalWrite(C5,HIGH);
  digitalWrite(C6,HIGH);
  digitalWrite(C7,HIGH);
  //digitalWrite(C8,HIGH);
  }
}

void Set_LED_in_Active_Row(int column, int state){
  //if (column==1) digitalWrite(C1,state); 
  if (column==2) digitalWrite(C2,state); 
  if (column==3) digitalWrite(C3,state); 
  if (column==4) digitalWrite(C4,state); 
  if (column==5) digitalWrite(C5,state); 
  if (column==6) digitalWrite(C6,state); 
  if (column==7) digitalWrite(C7,state); 
  //if (column==8) digitalWrite(C8,state); 
}

// **nRF MODULE**
RF24 radio(7, 8); // CE, CSN
int flag = 0;
const byte address[6] = "00009";
// **light sensor **
DFRobot_B_LUX_V30B myLux(13, A5, A4);//The sensor chip is set to 13 pins, SCL and SDA adopt default configuration

float intensity; // this will be the light intensity detected
float threshold = 150; // we define the maximum of light before its too much


void setup() {
  // **LED MATRIX**
  // set all the LED's on output
  //pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  //pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  //pinMode(R8, OUTPUT);
  //pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(C5, OUTPUT);
  pinMode(C6, OUTPUT);
  pinMode(C7, OUTPUT);
  //pinMode(C8, OUTPUT);
  // Turn off all lights
  //digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);
  digitalWrite(R3,LOW);
  //digitalWrite(R4,LOW);
  digitalWrite(R5,LOW);
  digitalWrite(R6,LOW);
  digitalWrite(R7,LOW);
  //digitalWrite(R8,LOW);
  //digitalWrite(C1,HIGH);
  digitalWrite(C2,HIGH);
  digitalWrite(C3,HIGH);
  digitalWrite(C4,HIGH);
  digitalWrite(C5,HIGH);
  digitalWrite(C6,HIGH);
  digitalWrite(C7,HIGH);
  //digitalWrite(C8,HIGH);

  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  // **nRF module**
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  //Serial.println("setup done");

  // **light sensor**
  myLux.begin();
  Serial.println("setup finished");

/*
  // Here we need these for the watchdog timer:
  //???????????????????????????????????????????????
  delay(3000); // 3s delay because it is needed for arduino to see if there is a new code being uploaded
  pinMode(pinLed,OUTPUT);
  Serial.println("Setup watchdog");

  // CPU Sleep Modes
  // SM2 SM1 SM0 Sleep Mode
  // 0    0  0 Idle
  // 0    0  1 ADC Noise Reduction
  // 0    1  0 Power-down
  // 0    1  1 Power-save
  // 1    0  0 Reserved
  // 1    0  1 Reserved
  // 1    1  0 Standby(1)

  cbi( SMCR,SE );     // sleep enable, power down mode
  cbi( SMCR,SM0 );     // power down mode
  sbi( SMCR,SM1 );     // power down mode
  cbi( SMCR,SM2 );     // power down mode

  setup_watchdog(9); // for 8 secs sleep
 
//??????????????????????????????????????????????????
*/
}

/* watchdog stuff
//byte del;
//int cnt;
int counter = 75; // timer for counting watchdog cicles of 8 sec. 75 is for 10 mins
long time = 0;

int runtime = 0;
*/

// ***************************************************************************
// ***************************************************************************

// Code without timer
void loop() {
  Serial.println("loop start");
  // **nRF MODULE**
  // If the button is pressed on the sensor, the switch will turn off the lights
  char text = '0';
  if(digitalRead(2) == LOW) {
    Serial.println("button 2 pressed");
    if(flag == 0) {
      text = '1';
      flag = 1;
      radio.write(&text, sizeof(text));
    }else{
      text = '0';
    }
    //Serial.println("button is pressed");
   
  }else {
    flag = 0;
    text = '2';
    //Serial.println("button is  not pressed");
  }
  //radio.write(&text, sizeof(text));

  if(digitalRead(3) == LOW ) {
    Serial.println("button 3 pressed");
    for (int k =1; k <= 358;k++)
    {
      for (int j=1;j<7;j++){
      SelectRow(j+1);
      //SelectColumn(0);
      for (int i=1;i<7;i++){
        Set_LED_in_Active_Row(i+1 ,smile[j][i]);
      }
      delay(2);
      }
    }
    
    //delay(5000);
  }

  // **light sensor** + **LED MATRIX**
  intensity = myLux.lightStrengthLux(); // intensity is what the sensor detects
  // if the intensity is over the threshold, we show a sad face
  if(intensity > threshold) {
    for (int j=1;j<7;j++){
    SelectRow(j+1);
    //SelectColumn(0);
      for (int i=1;i<7;i++){
        Set_LED_in_Active_Row(i+1 ,sad[j][i]);
      }
      delay(2);
    }
  } else {
    SelectColumn(0);
    SelectRow(0);
  }
  //delay(1000);
}

/* Code with the timer
void loop() {

  if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
    f_wdt=0;     // reset flag

    ///// debuging purpose only /////
    time = millis();
    Serial.print(counter);
    Serial.print(" ");
    Serial.println(time);
    delay(2); //needed for serial.print operation to finish
    /////////////////////////////////////

    if(counter==75)  // if ==10 -> this will be true every 10x8 = 80seconds; set to 225 to get 225x8=1800s = 30min
    {
      runtime = 0;

     //////////////// put code inside this IF ////////

      //the next while will make it run for 60 seconds
      while(runtime < 60) {
        // **nRF MODULE**
        // If the button is pressed on the sensor, the switch will turn off the lights
        char text = '0';
        if(digitalRead(2) == LOW) {
          if(flag == 0) {
            text = '1';
            flag = 1;
          }else{
            text = '0';
          }
          //Serial.println("button is pressed");
        }else {
          flag = 0;
          text = '2';
        }
        radio.write(&text, sizeof(text));

        // **light sensor** + **LED MATRIX**
        intensity = myLux.lightStrengthLux(); // intensity is what the sensor detects
        // if the intensity is over the threshold, we show a sad face
        if(intensity > threshold) {
          for (int j=0;j<8;j++){
          SelectRow(j+1);
          SelectColumn(0);
            for (int i=0;i<8;i++){
              Set_LED_in_Active_Row(i+1 ,sad[j][i]);
            }
            delay(2);
          }
        }
        delay(1000);
        runtime++;
      }

      counter = 0;
    }else {
      counter++;

      system_sleep()
    }
  }
}


//****************************************************************
// set system into the sleep state
// system wakes up when wtchdog is timed out
void system_sleep() {


  cbi(ADCSRA,ADEN);                 // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                    // System sleeps here

    sleep_disable();                  // System continues execution here when watchdog timed out
  sbi(ADCSRA,ADEN);                 // switch Analog to Digitalconverter ON

}

//****************************************************************
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {

  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;
  Serial.println(ww);


  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);

}
//****************************************************************
// Watchdog Interrupt Service / is executed when  watchdog timed out
ISR(WDT_vect) {
  f_wdt=1;  // set global flag
}*/