/*!
 * @file DFRobot_SHT40.cpp
 * @brief Implementation of DFRobot_SHT40 class
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @SKU SEN0428
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-03-19
 * @url  https://github.com/DFRobot/DFRobot_SHT
 */

#include "DFRobot_SHT40.h"

DFRobot_SHT40::DFRobot_SHT40(uint8_t addr, TwoWire *pWire):
DFRobot_SHT(addr, pWire, deviceinit, this)
{
  deviceinit[SHT_CONFIG_ID].addr = COM_READ_SERIAL;
  deviceinit[SHT_CONFIG_SOFT_RESET].addr = COM_SOFT_RESET;
  deviceinit[SHT_CONFIG_MODE].addr = 0;
  deviceinit[SHT_CALCULATE_HUM].addr = 0;
  deviceinit[SHT_CALCULATE_TEM].addr = 0;
  deviceinit[SHT_CONFIG_ID].len = 1;
  deviceinit[SHT_CONFIG_SOFT_RESET].len = 1;
  deviceinit[SHT_CONFIG_MODE].len  = 1;
  deviceinit[SHT_CALCULATE_HUM].len  = 1;
  deviceinit[SHT_CALCULATE_TEM].len = 1;
  deviceinit[SHT_CONFIG_ID].fun = (void(*)(...))&DFRobot_SHT40::getDeviceIDCB;
  deviceinit[SHT_CONFIG_SOFT_RESET].fun = (void(*)(...))&DFRobot_SHT40::softwareResetCB;
  deviceinit[SHT_CONFIG_MODE].fun = (void (*)(...))&DFRobot_SHT40::setModeCB;
  deviceinit[SHT_CALCULATE_HUM].fun = (void (*)(...))&DFRobot_SHT40::getHumValueCB;
  deviceinit[SHT_CALCULATE_TEM].fun = (void (*)(...))&DFRobot_SHT40::getTemValueCB;


}

void DFRobot_SHT40::begin()
{
  DFRobot_SHT::begin();
  softwareReset();
}
bool DFRobot_SHT40::isMode(uint16_t mode)
{
  bool ret =false;
  switch(mode){
  case PRECISION_HIGH:
    ret  = true;
    break;
  case PRECISION_MID:
    ret  = true;
    break;
  case PRECISION_LOW:
    ret  = true;
    break;
  default :
    ret  = false;
    break;
  }
  return ret;
}

void DFRobot_SHT40::enHeater(uint8_t mode)
{
  uint16_t time;
  uint8_t buff[6];
  switch(mode){
  case POWER_CONSUMPTION_H_HEATER_1S:
    time = 1200;
    break;
  case POWER_CONSUMPTION_H_HEATER_100MS:
    time = 110;
    break;
  case POWER_CONSUMPTION_M_HEATER_1S:
    time = 1100;
    break;
  case POWER_CONSUMPTION_M_HEATER_100MS:
    time = 110;
    break;
  case POWER_CONSUMPTION_L_HEATER_1S:
    time = 1100;
    break;
  case POWER_CONSUMPTION_L_HEATER_100MS:
    time = 110;
    break;
  default :
    time = 9;
    break;
  }
  writeCommand((uint8_t *)&mode, 1);
  delay(time);
  readValue((void*)buff, 6);
}

void DFRobot_SHT40::setModeCB(void * calssPtr, uint16_t mode){
  uint16_t time;
  DFRobot_SHT40 * temp = (DFRobot_SHT40 *)calssPtr;

  switch(mode){
  case PRECISION_HIGH:
    time = 9;
    break;
  case PRECISION_MID:
    time = 5;
    break;
  case PRECISION_LOW:
    time = 2;
    break;
  case POWER_CONSUMPTION_H_HEATER_1S:
    time = 1200;
    break;
  case POWER_CONSUMPTION_H_HEATER_100MS:
    time = 110;
    break;
  case POWER_CONSUMPTION_M_HEATER_1S:
    time = 1100;
    break;
  case POWER_CONSUMPTION_M_HEATER_100MS:
    time = 110;
    break;
  case POWER_CONSUMPTION_L_HEATER_1S:
    time = 1100;
    break;
  case POWER_CONSUMPTION_L_HEATER_100MS:
    time = 110;
    break;
  default :
    time = 9;
    break;
  }
  delay(time);
}

void DFRobot_SHT40::softwareResetCB(...)
{
  delayMicroseconds(1000);
}

void DFRobot_SHT40::getDeviceIDCB(void * classPtr, void * id)
{
  DFRobot_SHT40 * temp = (DFRobot_SHT40 *)classPtr;
  uint8_t idArray[6];

  temp->writeCommand((uint8_t *)&temp->deviceinit[SHT_CONFIG_ID].addr, temp->deviceinit[SHT_CONFIG_ID].len);
  delay(8);
  temp->readValue((void*)idArray, 6);

  if(temp->checkCrc(idArray[0], idArray[1], idArray[2]) && temp->checkCrc(idArray[3], idArray[4], idArray[5])){
    *(uint32_t *)id= ((uint32_t)idArray[0] << 24) | ((uint32_t)idArray[1] << 16) | ((uint32_t)idArray[3] << 8) | idArray[4];
  } else{
    *(uint32_t *)id = 0;
  }
}

void DFRobot_SHT40::getHumValueCB(void * hum)
{
  *(float *)hum =  -6 + 125*((*(float *)hum)/65535); 
}

void DFRobot_SHT40::getTemValueCB(void * tem)
{
  *(float *)tem =  -45 + 175*((*(float *)tem)/65535);
}