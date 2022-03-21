/*!
 * @file temperatureAndHumidity.ino
 * @brief Measurement of temperature and humidity
 * @n The sensor can be used to detect temperature and humidity within temperature -40~125 ℃ and humidity 0~100 %RH
 * @n The sensor supports four data measuring modes: clock stretching enabled, clock stretching disabled, clock Stretching Enabled & Low Power, clock Stretching Disabled & Low Power
 * @n Experiment Phenonmenon: measure temperature and humidity data every 1 second. 
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2021-03-19
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHT
 */

#include"DFRobot_SHTC3.h"

DFRobot_SHTC3 SHTC3;

uint32_t id = 0;
float temperature,  humidity;

void setup() {
  Serial.begin(9600);
  SHTC3.begin();
  SHTC3.wakeup();/*SHTC3 is set to sleep mode by default. Please wake it up before use. Use SHTC3.sleep() to let SHTC3 enter sleep mode; SHTC3 stops working in sleep mode*/

  while((id = SHTC3.getDeviceID()) == 0){
    Serial.println("ID retrieval error, please check whether the device is connected correctly!!!");
    delay(1000);
  }

  delay(1000);
  Serial.print("id :0x"); Serial.println(id, HEX);

}

void loop() {
  /**
   * 
   *    mode  Configure sensor working mode, vary among different sensors 
   *          SHTC3：
   *                  PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled 
   *                  PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled 
   *                  PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
   *                  PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
   */
  temperature = SHTC3.getTemperature(/*mode = */PRECISION_HIGH_CLKSTRETCH_ON);
  /**
   * 
   *    mode  Configure sensor working mode, vary among different sensors 
   *          SHTC3：
   *                  PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled 
   *                  PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled 
   *                  PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
   *                  PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
   */
  humidity = SHTC3.getHumidity(/*mode = */PRECISION_HIGH_CLKSTRETCH_OFF);
  if(temperature == MODE_ERR){
    Serial.println("Incorrect mode configuration to get temperature");
  } else{
    Serial.print("Temperature :"); Serial.print(temperature); Serial.println(" C");
  }
  if(humidity == MODE_ERR){
    Serial.println("The mode for getting humidity was misconfigured");
  } else{
    Serial.print("Humidity :"); Serial.print(humidity); Serial.println(" %RH");
  }
  /**
   *    mode  Configure sensor working mode
   *                  PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled 
   *                  PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled 
   *                  PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
   *                  PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
   */
  //if(SHTC3.getTemHum(temperature,humidity,PRECISION_HIGH_CLKSTRETCH_ON)){
  //  Serial.print("Temperature :"); Serial.print(temperature); Serial.println(" C");
  //  Serial.print("Humidity :"); Serial.print(humidity); Serial.println(" %RH");
  //} else{
  //  Serial.println("Pattern configuration error");
  //}
  delay(1000);

  Serial.println("----------------------------------------");
}
