
/*
  This program activates the stepper motor at specific times and specific amounts
  It uses on board timer

  startTime needs to be set each time you start the program again
  
 */
//[IMPORTANT]: set this to when you start the program (i.e 4:30AM would be 4.5) [0.5-24 range]
float startTime = 16.0f; 

#include <Stepper.h>
#define reset_time 24

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

RTC_DATA_ATTR float hour_count = 0;
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7);

void goToDeepSleep(){
  Serial.println("Going to sleep");
  uint64_t half_hour = 30*60*1000000;
  esp_sleep_enable_timer_wakeup(half_hour);
  esp_deep_sleep_start();
}
void spinStepper(int sixteen_of_rotation, int dir){
  //dir 1 = CW dir -1 = CCW
  for(int i = 0; i < sixteen_of_rotation; i++){
    myStepper.step(dir * stepsPerRevolution/16);
    Serial.print(i+1);
    Serial.println("/16th Rotation");
    vTaskDelay(1);
  }
}
void setup() {
  // initialize the serial port:
  vTaskDelay(1);
  Serial.begin(9600);
  myStepper.setSpeed(5);

  Serial.println("");
  Serial.println("");
  if (hour_count != 0){
    Serial.print("[Current Hour: ");
      Serial.print(hour_count);
        Serial.println("]");
  }
  if (hour_count == 0){
    //This only runs once
    Serial.println("[Starting program]");
    hour_count = startTime;
    spinStepper(10, -1);
  }
  else if (hour_count == 10){
    Serial.println("Feeding Fish");
    spinStepper(3, -1);
  }
  else if (hour_count == 16){
    Serial.println("Feeding Fish");
    spinStepper(3, -1);
  }
  else if (hour_count >= reset_time){
    Serial.println("Midnight");
    //This delay is to resync the time since the onboard timer runs fast
    //vTaskDelay(314*100000);
    hour_count = 0;
  }
  
  hour_count += 0.5f;
 
  goToDeepSleep();
}

void loop() {
}
