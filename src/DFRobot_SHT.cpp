/*!
 * @file DFRobot_SHT.cpp
 * @brief Implementation of DFRobot_SHT class
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @SKU SEN0414
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-03-19
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHT
 */
#include "DFRobot_SHT.h"

DFRobot_SHT::DFRobot_SHT(uint8_t addr, TwoWire *pWire, sDev_t * dev, void *p):
_pWire(pWire),_deviceAddr(addr),_p(p)
{
  _dev = dev;
  _mode = 0;
}

void DFRobot_SHT::begin()
{
  _pWire->begin();
}

float DFRobot_SHT::getTemperature(uint16_t mode)
{
  uint16_t tem,  hum;
  _mode = mode;
  if(!isMode(mode)){
    return MODE_ERR;
  }
  while(!getTandRHRawData(&tem, &hum)){
    DBG("ERR:Checksum error!!!");
    delay(1000);
  }

  float temperature = tem;
  _dev[SHT_CALCULATE_TEM].fun((void *)&temperature);
  return temperature;
}

float DFRobot_SHT::getHumidity(uint16_t mode)
{
  uint16_t tem, hum;
  _mode = mode;
  if(!isMode(mode)){
    return MODE_ERR;
  }
  while(!getTandRHRawData(&tem, &hum)){
    DBG("ERR:Checksum error!!!");
    delay(1000);
  }

  float humidity = hum;
  _dev[SHT_CALCULATE_HUM].fun((void *)&humidity);
  return humidity;
}

bool DFRobot_SHT::getTemHum(float &temperature, float &humidity,uint16_t mode)
{
  uint16_t tem,  hum;
  if(!isMode(mode)){
    return false;
  }
  while(!getTandRHRawData(&tem, &hum)){
    DBG("ERR:Checksum error!!!");
    delay(1000);
  }

  _dev[SHT_CALCULATE_HUM].fun((void *)&humidity);
  _dev[SHT_CALCULATE_TEM].fun((void *)&temperature);
  return true;
}

uint32_t DFRobot_SHT::getDeviceID()
{
  uint32_t id = 0;
  _dev[SHT_CONFIG_ID].fun((void *)_p, (void *)&id);
  
  return id;
}

void DFRobot_SHT::softwareReset()
{
  writeCommand(( uint8_t * )&_dev[SHT_CONFIG_SOFT_RESET].addr, _dev[SHT_CONFIG_SOFT_RESET].len);
  _dev[SHT_CONFIG_SOFT_RESET].fun();

}

bool DFRobot_SHT::getTandRHRawData(uint16_t* temp, uint16_t* rh)
{
  uint8_t data[6];
  uint16_t command, time;
  bool ret = false;

  writeCommand(  (uint8_t * )&_mode, _dev[2].len);
  _dev[SHT_CONFIG_MODE].fun( ( void * )_p, (uint16_t)_mode);
  readValue( ( void* )data, 6);

  if(checkCrc(data[0], data[1], data[2]) && checkCrc(data[3], data[4], data[5])){
    *temp = ( data[0] << 8 ) | data[1];
    *rh = ( data[3] << 8 ) | data[4];
    ret =  true;
  }

  return ret;
}

void DFRobot_SHT:: writeCommand(uint8_t* command, uint8_t len)
{
  _pWire->beginTransmission(_deviceAddr);

  for(int i = len-1; i > -1; i--){
    _pWire->write(command[i]);
  }

  _pWire->endTransmission();
}

uint8_t DFRobot_SHT::readValue(void* pBuf, size_t size)
{
  uint8_t * _pBuf = (uint8_t *)pBuf;

  _pWire->requestFrom(_deviceAddr, (uint8_t)size);

  for(uint16_t i = 0; i < size; i++){
    _pBuf[i] = _pWire->read();
  }
  return size;
}

bool DFRobot_SHT::checkCrc(uint8_t data1, uint8_t data2, uint8_t crcValue)
{
  uint8_t crc = 0xFF;
  uint8_t crcData[2];
  crcData[0] = data1;
  crcData[1] = data2;
  bool ret = true;

  for(int i = 0; i < 2; i++ ){
    crc ^= crcData[i];
    for(uint8_t bit = 8; bit > 0; --bit){
      if(crc & 0x80){
        crc = ( crc << 1 ) ^ 0x31;
      } else{
        crc = ( crc << 1 );
      }
    }
  }

  if(crc != crcValue){
    ret = false;
  }
  return ret;
}
