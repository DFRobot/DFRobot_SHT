/*!
 * @file DFRobot_SHT40.h
 * @brief Define the class of DFRobot_SHT40
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-03-19
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHT
 */
#ifndef __DFROBOT_SHT40_H__
#define __DFROBOT_SHT40_H__


#include"DFRobot_SHT.h"
class DFRobot_SHT40:public DFRobot_SHT{
public:

  #define  SHT40_AD1B_IIC_ADDR                     0x44
  #define  SHT40_BD1B_IIC_ADDR                     0x45

  #define  COM_READ_SERIAL                   0x89
  #define  COM_SOFT_RESET                    0x94

  #define  PRECISION_HIGH                                    0xFD               /* measure T & RH with high precision (high repeatability) */
  #define  PRECISION_MID                                     0xF6               /* measure T & RH with medium precision (medium repeatability) */
  #define  PRECISION_LOW                                     0xE0               /* measure T & RH with lowest precision (low repeatability) */
  #define  POWER_CONSUMPTION_H_HEATER_1S                     0x39               /* activate highest heater power & high precis. meas. for 1s */
  #define  POWER_CONSUMPTION_H_HEATER_100MS                  0x32               /* activate highest heater power & high precis. meas. for 0.1s */
  #define  POWER_CONSUMPTION_M_HEATER_1S                     0x2F               /* activate medium heater power  & high precis. meas. for 1s */
  #define  POWER_CONSUMPTION_M_HEATER_100MS                  0x24               /* activate medium heater power  & high precis. meas. for 0.1s */
  #define  POWER_CONSUMPTION_L_HEATER_1S                     0x1E               /* activate lowest heater power  & high precis. meas. for 1s */
  #define  POWER_CONSUMPTION_L_HEATER_100MS                  0x15               /* activate lowest heater power  & high precis. meas. for 0.1s */
  sDev_t deviceinit[SHT_CONFIG_MAX];
public:

  /**
   * @brief  constructed function
   * @param  pWire  When instantiate this class, you can specify its twowire
   */
  DFRobot_SHT40(uint8_t addr, TwoWire *pWire = &Wire);

  /**
   * @brief  Init Wire, and perform software reset for the sensor 
   */
  void begin();

  /**
   * @brief  Enable heater 
   * @param  mode  Heating mode 
   * @n                    POWER_CONSUMPTION_H_HEATER_1S                                  activate highest heater power & high precis. meas. for 1s 
   * @n                    POWER_CONSUMPTION_H_HEATER_100MS                               activate highest heater power & high precis. meas. for 0.1s
   * @n                    POWER_CONSUMPTION_M_HEATER_1S                                   activate medium heater power  & high precis. meas. for 1s 
   * @n                    POWER_CONSUMPTION_M_HEATER_100MS                                activate medium heater power  & high precis. meas. for 0.1s 
   * @n                    POWER_CONSUMPTION_L_HEATER_1S                                   activate lowest heater power  & high precis. meas. for 1s 
   * @n                    POWER_CONSUMPTION_L_HEATER_100MS                                activate lowest heater power  & high precis. meas. for 0.1s 
   */
  void enHeater(uint8_t mode);

private:
  /**
   * @brief  Judge if the configured mode is correct 
   * @param  mode  Normal mode 
   * @n                    PRECISION_HIGH                                 measure T & RH with high precision (high repeatability) 
   * @n                    PRECISION_MID                                  measure T & RH with medium precision (medium repeatability)
   * @n                    PRECISION_LOW                                  measure T & RH with lowest precision (low repeatability) 
   */
  bool isMode(uint16_t mode);
  /**
   * @brief  Superclass method setMode() corresponds to subclass “class callback function”, here use it to set delay 
   * @param   classPtr  Pointer to subclass 
   * @param   mode  User-defined device working mode 
   */
  static void setModeCB(void * calssPtr, uint16_t mode);

  /**
   * @brief  Superclass method softwareReset() corresponds to subclass "class callback function", here use it to set delay
   * @param  ...  Changable parameter, no use 
   */
  static void softwareResetCB(...);

  /**
   * @brief   Superclass method getDeviceIDCB() corresponds to subclass “class callback function”, here use it to get sensor ID 
   * @param   classPtr  Pointer to subclass
   * @param   id  Pointer to device ID 
   */
  static void getDeviceIDCB(void * classPtr, void * id);

  /**
   * @brief   Superclass method getDeviceIDCB() corresponds to subclass “class callback function”, here use it to get the calculated humidity
   * @param   hum  Pointer to humidity 
   */
  static void getHumValueCB(void * hum);

  /**
   * @brief   Superclass method getDeviceIDCB() corresponds to subclass “class callback function”, here use it to get the calculated temperature
   * @param   tem  Pointer to temperature 
   */
  static void getTemValueCB(void * tem);
};

#endif
