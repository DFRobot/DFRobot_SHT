/*!
 * @file temperatureAndHumidity.ino
 * @brief Measurement of temperature and humidity
 * @n The sensor can be used to detect temperature and humidity within temperature -40~125 ℃ and humidity 0~100 %RH. 
 * @n The sensor offers three measurement precisions(high, medium, and low) and three heating powers for the on-chip heater    
 * @n Application: 
 * @n 1、Removal of condensed / spray water on the sensor surface. Although condensed water is not a reliability / quality problem to the sensor, it will however make the sensor nonresponsive to RH changes in the air as long as there is liquid water on the surface.
 * @n 2、Creep-free operation in high humid environments. Periodic heating pulses allow for creepSTXfree high-humidity measurements for extended times.
 * @n Experiment Phenomenon: measure temperature and humidity and serial print every 1 second. When humidity exceeds 80%RH, enable heater once. 
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2021-03-19
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHT
 */
#include"DFRobot_SHT40.h"

/** 
 *  The library supports two types of SHT40 Sensor: SHT40_AD1B, and SHT40_BD1B. The two types have different IIC devices and they have been encapsulated. 
 * Users can pass the following two parameters: 
 *  For SHT40_AD1B:   SHT40_AD1B_IIC_ADDR
 *  For SHT40_AD1B:   SHT40_BD1B_IIC_ADDR
 */
DFRobot_SHT40 SHT40(SHT40_AD1B_IIC_ADDR); 


uint32_t id = 0;
float temperature, humidity;

void setup() {

  Serial.begin(9600);
  SHT40.begin();

  while((id = SHT40.getDeviceID()) == 0){
    Serial.println("ID retrieval error, please check whether the device is connected correctly!!!");
    delay(1000);
  }

  delay(1000);
  Serial.print("id :0x"); Serial.println(id, HEX);

}

void loop() {
  /**
   *    mode  For configuring sensor working mode 
   *                  PRECISION_HIGH                       measure T & RH with high precision (high repeatability) 
   *                  PRECISION_MID                        measure T & RH with medium precision (medium repeatability)
   *                  PRECISION_LOW                        measure T & RH with lowest precision (low repeatability) 
   */
  temperature = SHT40.getTemperature(/*mode = */PRECISION_HIGH);
  /**
   *    mode  For configuring sensor working mode 
   *                  PRECISION_HIGH                       measure T & RH with high precision (high repeatability) 
   *                  PRECISION_MID                        measure T & RH with medium precision (medium repeatability)
   *                  PRECISION_LOW                        measure T & RH with lowest precision (low repeatability) 
   */
  humidity = SHT40.getHumidity(/*mode = */PRECISION_HIGH);

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
   *    mode  For configuring sensor working mode
   *                  PRECISION_HIGH                       measure T & RH with high precision (high repeatability) 
   *                  PRECISION_MID                        measure T & RH with medium precision (medium repeatability)
   *                  PRECISION_LOW                        measure T & RH with lowest precision (low repeatability) 
   */
  //if(SHT40.getTemHum(temperature,humidity,PRECISION_HIGH)){
  //  Serial.print("Temperature :"); Serial.print(temperature); Serial.println(" C");
  //  Serial.print("Humidity :"); Serial.print(humidity); Serial.println(" %RH");
  //} else{
  //  Serial.println("Pattern configuration error");
  //}
  if(humidity > 80){
  /**
   *    mode  For configuring sensor working mode
   *                  POWER_CONSUMPTION_H_HEATER_1S                        activate highest heater power & high precis. meas. for 1s 
   *                  POWER_CONSUMPTION_H_HEATER_100MS                     activate highest heater power & high precis. meas. for 0.1s
   *                  POWER_CONSUMPTION_M_HEATER_1S                         activate medium heater power  & high precis. meas. for 1s 
   *                  POWER_CONSUMPTION_M_HEATER_100MS                      activate medium heater power  & high precis. meas. for 0.1s 
   *                  POWER_CONSUMPTION_L_HEATER_1S                         activate lowest heater power  & high precis. meas. for 1s 
   *                  POWER_CONSUMPTION_L_HEATER_100MS                      activate lowest heater power  & high precis. meas. for 0.1s 
   */
    SHT40.enHeater(/*mode = */POWER_CONSUMPTION_H_HEATER_1S);
  }
  delay(1000);

  Serial.println("----------------------------------------");
}
