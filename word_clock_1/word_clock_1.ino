/*
 * TimeRTCSet.pde
 * example code illustrating Time library with Real Time Clock.
 *
 * RTC clock is set in response to serial port time message 
 * A Processing example sketch to set the time is included in the download
 * On Linux, you can use "date +T%s > /dev/ttyACM0" (UTC time zone)
 */

#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

// specify constants and pinouts
const int hour_1 = 22;
const int hour_2 = 23;
const int hour_3 = 24;
const int hour_4 = 25;
const int hour_5 = 26;
const int hour_6 = 27;
const int hour_7 = 28;
const int hour_8 = 29;
const int hour_9 = 30;
const int hour_10 = 31;
const int hour_11 = 32;
const int hour_12 = 33;
const int min_oh = 34;
const int min_1 = 35;
const int min_2 = 36;
const int min_3 = 37;
const int min_4 = 38;
const int min_5 = 39;
const int min_10 = 40;
const int min_quarter = 41;
const int min_20 = 42;
const int min_halfpast = 43;
const int min_30 = 44;
const int min_40 = 45;
const int min_50 = 46;
const int min_after = 47;
const int min_to = 48;
const int min_oclock = 49;
const int hr_buttonPin = 52;
const int minplus_buttonPin = 53;
const int minminus_buttonPin = 51;

const int FALSE = 0;
const int TRUE = 1;

// variables
int ihour = -1;
int iminute = -1;
int statechange = FALSE;

void setup()  {
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");  

  if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      RTC.set(t);   // set the RTC and the system time to the received value
      setTime(t);          
    }
  }
  setTime(0,0,0,11,5,1971);

  pinMode(hour_1, OUTPUT);    
  pinMode(hour_2, OUTPUT);    
  pinMode(hour_3, OUTPUT);    
  pinMode(hour_4, OUTPUT);    
  pinMode(hour_5, OUTPUT);    
  pinMode(hour_6, OUTPUT);    
  pinMode(hour_7, OUTPUT);    
  pinMode(hour_8, OUTPUT);    
  pinMode(hour_9, OUTPUT);    
  pinMode(hour_10, OUTPUT);    
  pinMode(hour_11, OUTPUT);    
  pinMode(hour_12, OUTPUT);    
  pinMode(min_oh, OUTPUT);    
  pinMode(min_1, OUTPUT);    
  pinMode(min_2, OUTPUT);    
  pinMode(min_3, OUTPUT);    
  pinMode(min_4, OUTPUT);    
  pinMode(min_5, OUTPUT);    
  pinMode(min_10, OUTPUT);    
  pinMode(min_quarter, OUTPUT);    
  pinMode(min_20, OUTPUT);    
  pinMode(min_halfpast, OUTPUT);    
  pinMode(min_30, OUTPUT);    
  pinMode(min_40, OUTPUT);    
  pinMode(min_50, OUTPUT);    
  pinMode(min_after, OUTPUT);
  pinMode(min_to, OUTPUT);
  pinMode(min_oclock, OUTPUT);
  pinMode(hr_buttonPin, INPUT);
  pinMode(minplus_buttonPin, INPUT);
  pinMode(minminus_buttonPin, INPUT);
  
}

void loop()
{
/*
  if (timeStatus() == timeSet) {
    digitalClockDisplay();
  } else {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
    Serial.println();
    delay(4000);
  }
  delay(1000);
*/

  digitalClockDisplay();
  delay(100);

  if (digitalRead(hr_buttonPin))
  {
    setHour();
  }
  if (digitalRead(minplus_buttonPin))
  {
    setMinPlus();
  }
  if (digitalRead(minminus_buttonPin))
  {
    setMinMinus();
  }

}

void digitalClockDisplay()
{
  // check for redisplay  put next in if statement
  if (iminute != minute() || ihour != hour() || statechange)
  {
    getPinoutDisplay();
  }
  statechange = FALSE;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void getPinoutDisplay()
{
  int temp_minute = 0;
  int temp_hour = 0;
  int temp_unitminute = 0;

  temp_minute = minute();
  temp_unitminute = temp_minute%10;
  temp_hour = hour();

  blankLED();
  if (temp_minute == 45) temp_hour++;
  if (temp_hour > 23) temp_hour = 0;
  if (temp_hour > 11) temp_hour -= 12;

  Serial.print(ihour); 
  Serial.print(":"); 
  Serial.print(temp_minute); 
  Serial.print(" ");

        
  switch (temp_hour) 
  {
  case 0:
    Serial.print("LED Hour_12 ");
    digitalWrite(hour_12, HIGH);
    break;
  case 1:
    Serial.print("LED Hour_1 ");
    digitalWrite(hour_1, HIGH);
    break;
  case 2:
    Serial.print("LED Hour_2 ");
    digitalWrite(hour_2, HIGH);
    break;
  case 3:
    Serial.print("LED Hour_3 ");
    digitalWrite(hour_3, HIGH);
    break;
  case 4:
    Serial.print("LED Hour_4 ");
    digitalWrite(hour_4, HIGH);
    break;
  case 5:
    Serial.print("LED Hour_5 ");
    digitalWrite(hour_5, HIGH);
    break;
  case 6:
    Serial.print("LED Hour_6 ");
    digitalWrite(hour_6, HIGH);
    break;
  case 7:
    Serial.print("LED Hour_7 ");
    digitalWrite(hour_7, HIGH);
    break;
  case 8:
    Serial.print("LED Hour_8 ");
    digitalWrite(hour_8, HIGH);
    break;
  case 9:
    Serial.print("LED Hour_9 ");
    digitalWrite(hour_9, HIGH);
    break;
  case 10:
    Serial.print("LED Hour_10 ");
    digitalWrite(hour_10, HIGH);
    break;
  case 11:
    Serial.print("LED Hour_11 ");
    digitalWrite(hour_11, HIGH);
    break;
  default: 
    // if nothing else matches, do the default
    // default is optional
  break;
  }

  if (temp_minute == 0)
  {
    Serial.print("LED min_oclock ");
    digitalWrite(min_oclock, HIGH);
  }
  else if (temp_minute > 0 && temp_minute < 10)
  {
    Serial.print("LED min_oh ");
    digitalWrite(min_oh, HIGH);
  }
  else if (temp_minute >= 15 && temp_minute < 20)
  {
    Serial.print("LED min_quarter ");
    digitalWrite(min_quarter, HIGH);
    Serial.print("LED min_after ");
    digitalWrite(min_after, HIGH);
  }
  else if (temp_minute == 30)
  {
    Serial.print("LED min_halfpast ");
    digitalWrite(min_halfpast, HIGH);
  }
  else if (temp_minute == 45)
  {
    Serial.print("LED min_quarter ");
    digitalWrite(min_quarter, HIGH);
    Serial.print("LED min_to ");
    digitalWrite(min_to, HIGH);
  }
  else
  {
    if (temp_minute >= 10 && temp_minute < 20)
    {
      Serial.print("LED min_10 ");
      digitalWrite(min_10, HIGH);
    }
    else if (temp_minute >= 20 && temp_minute < 30)
    {
      Serial.print("LED min_20 ");
      digitalWrite(min_20, HIGH);
    }
    else if (temp_minute >= 30 && temp_minute < 40)
    {
      Serial.print("LED min_30 ");
      digitalWrite(min_30, HIGH);
    }
    else if (temp_minute >= 40 && temp_minute < 50)
    {
      Serial.print("LED min_40 ");
      digitalWrite(min_40, HIGH);
    }
    else if (temp_minute >= 50 && temp_minute < 60)
    {
      Serial.print("LED min_50 ");
      digitalWrite(min_50, HIGH);
    }
  }

  if (temp_unitminute >= 5 && (temp_minute < 15 || temp_minute >= 20) && temp_minute != 45)
  {
    Serial.print("LED min_5 ");
    digitalWrite(min_5, HIGH);
  }

  switch (temp_unitminute)
  {
  case 4:
  case 9:
    Serial.print("LED min_4 ");
    digitalWrite(min_4, HIGH);
  case 3:
  case 8:
    Serial.print("LED min_3 ");
    digitalWrite(min_3, HIGH);
  case 2:
  case 7:
    Serial.print("LED min_2 ");
    digitalWrite(min_2, HIGH);
  case 1:
  case 6:
    Serial.print("LED min_1 ");
    digitalWrite(min_1, HIGH);
  default: 
    // if nothing else matches, do the default
    // default is optional
    break;
  }
  iminute = minute();
  ihour = hour();
  Serial.println("");
}


void blankLED()
{
      digitalWrite(hour_1, LOW);
      digitalWrite(hour_2, LOW);
      digitalWrite(hour_3, LOW);
      digitalWrite(hour_4, LOW);
      digitalWrite(hour_5, LOW);
      digitalWrite(hour_6, LOW);
      digitalWrite(hour_7, LOW);
      digitalWrite(hour_8, LOW);
      digitalWrite(hour_9, LOW);
      digitalWrite(hour_10, LOW);
      digitalWrite(hour_11, LOW);
      digitalWrite(hour_12, LOW);
      digitalWrite(min_oh, LOW);
      digitalWrite(min_1, LOW);
      digitalWrite(min_2, LOW);
      digitalWrite(min_3, LOW);
      digitalWrite(min_4, LOW);
      digitalWrite(min_5, LOW);
      digitalWrite(min_10, LOW);
      digitalWrite(min_quarter, LOW);
      digitalWrite(min_20, LOW);
      digitalWrite(min_halfpast, LOW);
      digitalWrite(min_30, LOW);
      digitalWrite(min_40, LOW);
      digitalWrite(min_50, LOW);
      digitalWrite(min_after, LOW);
      digitalWrite(min_to, LOW);
      digitalWrite(min_oclock, LOW);
}

void setHour()
{
  ihour = hour() + 1;
  if (ihour > 23)
  {
    ihour = 0;
  }
  setTime(ihour,iminute,0,11,5,1971);
  while (digitalRead(hr_buttonPin))
  {
    Serial.println("Still HR HIGH");
    delay(100);
  }
  statechange = TRUE;
}

void setMinPlus()
{
  iminute = minute() + 1;
  if (iminute > 59)
  {
    iminute = 0;
  }
  setTime(ihour,iminute,0,11,5,1971);  
  while (digitalRead(minplus_buttonPin))
  {
    Serial.println("Still MIN+ HIGH");
    delay(100);
  }
  statechange = TRUE;
}

void setMinMinus()
{
  iminute = minute() - 1;
  if (iminute < 0)
  {
    iminute = 59;
  }
  setTime(ihour,iminute,0,11,5,1971);  
  while (digitalRead(minminus_buttonPin))
  {
    Serial.println("Still MIN- HIGH");
    delay(100);
  }
  statechange = TRUE;
}

