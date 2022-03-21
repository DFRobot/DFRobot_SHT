/*!
 * @file DFRobot_SHTC3.h
 * @brief Define the class of DFRobot_SHTC3
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-03-19
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHT
 */
#ifndef __DFROBOT_SHTC3_H__
#define __DFROBOT_SHTC3_H__

#include "DFRobot_SHT.h"

class DFRobot_SHTC3: public DFRobot_SHT {

public:

  #define SHTC3_IIC_ADDR                             0x70
  #define COMMAND_SLEEP                              0xB098
  #define COMMAND_SOFTWARE_RESET                     0x805D
  #define COMMAND_WAKEUP                             0x3517
  #define COMMAND_DEVICE_ID                          0xEFC8
  #define PRECISION_HIGH_CLKSTRETCH_ON               0x7CA2
  #define PRECISION_HIGH_CLKSTRETCH_OFF              0x7866
  #define PRECISION_LOW_CLKSTRETCH_ON                0x6458
  #define PRECISION_LOW_CLKSTRETCH_OFF               0x609C

  sDev_t deviceinit[SHT_CONFIG_MAX];

public:

  /**
   * @brief  constructed function
   * @param  pWire  When instantiate this class, you can specify its twowire
   */
  DFRobot_SHTC3(TwoWire *pWire = &Wire);
  
  /**
   * @brief  Destructor
   */
  ~DFRobot_SHTC3(){};
  
  /**
   * @brief  Init Wire, and perform software reset of the sensor, let the sensor enter sleep mode, and wake it up when necessary 
   */
  void begin();



  /**
   * @brief  When in sleep mode, the sensor needs to be awakened before communicating
   */
  void wakeup();
  
  /**
   * @brief  Set sensor to sleep mode. When done, the sensor cannot obtain data before waking up
   */
  void sleep();

private:

  /**
   * @brief  Judge if the configured mode is correct
   * @param  mode  Normal mode 
   * @n                    PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled 
   * @n                    PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled 
   * @n                    PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
   * @n                    PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
   */
  bool isMode(uint16_t mode);
  
  /**
   * @brief  Superclass method setMode() corresponds to subclass “class callback function”, here use it to set delay
   * @param  ...  Changable parameter, no use 
   */
  static void setModeCB(...);

  /**
   * @brief Superclass method setMode() corresponds to subclass “class callback function”, here use it to set delay
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
