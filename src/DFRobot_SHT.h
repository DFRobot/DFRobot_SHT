/*!
 * @file DFRobot_SHT.h
 * @brief Includes the define of superclass of SHT series
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-03-19
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHT
 */
#ifndef _DFROBOT_SHT_H_
#define _DFROBOT_SHT_H_

#include <Arduino.h>
#include <Wire.h>



//Open the macro to see the program running details 
#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

/******************************************Create a struct for superclass accessing subclass data and methods****************************************/

typedef void (*funPtr)(...);
typedef struct dev{
  uint16_t addr;                           // Sensor register address or command 
  uint8_t len;                             // Length of sensor register address or command 
  funPtr fun;                              //Function corresponding to the register  
}sDev_t;

/* Number of the elements of struct array  */
#define SHT_CONFIG_MAX           5

#define SHT_CONFIG_ID            0       //The first element of the struct array, designated to the content relevant to ID
#define SHT_CONFIG_SOFT_RESET    1       //The second element of the struct array, designated to the content relevant to software reset
#define SHT_CONFIG_MODE          2       //The third element of the struct array, designated to the content relevant to sensor working mode settings 
#define SHT_CALCULATE_HUM        3       //The fourth element of the struct array, designated to the content relevant to the content relevant to humidity calculation
#define SHT_CALCULATE_TEM        4       //The fifth element of the struct array, designated to the content relevant to temperature calculation
/**********************************************************************************************************************/

class DFRobot_SHT{
public:
  #define MODE_ERR     -100
  /**
   * @brief  Constructor
   * @param  addr   Sensor I2C address 
   * @param  pWire  Pointer to I2C class
   * @param  dev   Pointer to sensor information 
   * @param  p     Void pointer to subclass address 
   */
  DFRobot_SHT(uint8_t addr, TwoWire *pWire, sDev_t * dev, void * p);
  ~DFRobot_SHT(){};

  /**
   * @brief  Init mainboard I2C 
   */
  void begin();

  /**
   * @brief  Get temperature data 
   * @param  mode   Sensor working mode 
   * @n            SHTC3：
   * @n                    PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled 
   * @n                    PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled 
   * @n                    PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
   * @n                    PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
   * @n            SHT40:
   * @n                    PRECISION_HIGH                                 measure T & RH with high precision (high repeatability) 
   * @n                    PRECISION_MID                                  measure T & RH with medium precision (medium repeatability)
   * @n                    PRECISION_LOW                                  measure T & RH with lowest precision (low repeatability) 
   * @return  Return  Temperature value, unit:℃  Return MODE_ERR: invalid mode 
   */
  float getTemperature(uint16_t mode);

  /**
   * @brief  Get humidity data
   * @param  mode  Sensor working mode 
   * @n            SHTC3：
   * @n                    PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled 
   * @n                    PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled 
   * @n                    PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
   * @n                    PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
   * @n            SHT40:
   * @n                    PRECISION_HIGH                                 measure T & RH with high precision (high repeatability) 
   * @n                    PRECISION_MID                                  measure T & RH with medium precision (medium repeatability)
   * @n                    PRECISION_LOW                                  measure T & RH with lowest precision (low repeatability) 
   * @return  Return  Humidity value, unit: %RH   Return MODE_ERR: invalid mode 
   */
  float getHumidity(uint16_t mode);

  /**
   * @brief  Get temperature and humidity data 
   * @param   tem  Reference for storing temperature data 
   * @param   hum  Reference for storing humidity data 
   * @param  mode   Sensor working mode 
   * @n            SHTC3：
   * @n                    PRECISION_HIGH_CLKSTRETCH_ON                              Clock Stretching Enabled 
   * @n                    PRECISION_HIGH_CLKSTRETCH_OFF                             Clock Stretching Disabled 
   * @n                    PRECISION_LOW_CLKSTRETCH_ON                               Clock Stretching Enabled & Low Power
   * @n                    PRECISION_LOW_CLKSTRETCH_OFF                              Clock Stretching Disabled & Low Power
   * @n            SHT40:
   * @n                    PRECISION_HIGH                                 measure T & RH with high precision (high repeatability) 
   * @n                    PRECISION_MID                                  measure T & RH with medium precision (medium repeatability)
   * @n                    PRECISION_LOW                                  measure T & RH with lowest precision (low repeatability) 
   * @return  Return true for success, flase for invalid mode setting 
   */
  bool  getTemHum(float &tem, float &hum,uint16_t mode);

  /**
   * @brief  Get sensor unique identifier 
   * @return Return identifier for success, 0 for failure 
   */
   uint32_t getDeviceID();

  /**
   * @brief  software reset
   */
   void softwareReset() ;

  /**
   * @brief  Obtain raw data of temperature and humidity
   * @param  temp Pointer to the address of the original value of the temperature
   * @param  hun   Pointer to the address of the original value of the humidity
   * @return Is the data obtained correct? return true  The data is correct ; return false  The data  is incorrect
   */
   bool getTandRHRawData(uint16_t *temp, uint16_t *hum);

protected:
  virtual bool isMode(uint16_t mode) = 0;
  /**
   * @brief  Recheck the obtained data to determine if they are correct 
   * @param  data1  High 8 bits to check value
   * @param  data2  LOW 8 bits to check value
   * @param  crcValue  Check value returned by the sensor
   * @return Check success return true ;Check failed return false
   */
  bool checkCrc(uint8_t data1, uint8_t data2, uint8_t crcValue);

  /**
   * @brief  Write sensor 
   * @param  command  Pointer to command 
   * @param  len      Length of command 
   */
   void writeCommand(uint8_t* command, uint8_t len);

  /**
   * @brief Read sensor data 
   * @param pBuf Storage cache for data to be written 
   * @param size Length of data to be written 
   * @return Return actual read length, 0 for failure 
   */
  uint8_t readValue(void* pBuf, size_t size);

protected:
  TwoWire *_pWire;
  void* _p;
  uint8_t _deviceAddr;
  sDev_t * _dev;
  uint16_t _mode;

};

#endif
