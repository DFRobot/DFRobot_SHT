/*!
 * @file DFRobot_SHTC3.cpp
 * @brief Implementation of DFRobot_SHTC3 class
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @SKU SEN0414
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-02-20
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_SHT
 */
#include "DFRobot_SHTC3.h"
DFRobot_SHTC3::DFRobot_SHTC3(TwoWire *pWire):
DFRobot_SHT(SHTC3_IIC_ADDR, pWire, deviceinit, this)
{
  deviceinit[SHT_CONFIG_ID].addr = COMMAND_DEVICE_ID;
  deviceinit[SHT_CONFIG_SOFT_RESET].addr = COMMAND_SOFTWARE_RESET;
  deviceinit[SHT_CONFIG_MODE].addr = 0;
  deviceinit[SHT_CALCULATE_HUM].addr = 0;
  deviceinit[SHT_CALCULATE_TEM].addr = 0;
  deviceinit[SHT_CONFIG_ID].len = deviceinit[SHT_CONFIG_SOFT_RESET].len = deviceinit[SHT_CONFIG_MODE].len = deviceinit[SHT_CALCULATE_HUM].len  = deviceinit[SHT_CALCULATE_TEM].len = 2;
  deviceinit[SHT_CONFIG_ID].fun = (void(*)(...))&DFRobot_SHTC3::getDeviceIDCB;
  deviceinit[SHT_CONFIG_SOFT_RESET].fun = (void (*)(...))&DFRobot_SHTC3::softwareResetCB;
  deviceinit[SHT_CONFIG_MODE].fun = (void (*)(...))&DFRobot_SHTC3::setModeCB;
  deviceinit[SHT_CALCULATE_HUM].fun = (void (*)(...))&DFRobot_SHTC3::getHumValueCB;
  deviceinit[SHT_CALCULATE_TEM].fun = (void (*)(...))&DFRobot_SHTC3::getTemValueCB;
}

void DFRobot_SHTC3::begin()
{
  DFRobot_SHT::begin();
  wakeup();
  softwareReset();
  sleep();
}

bool DFRobot_SHTC3::isMode(uint16_t mode)
{
  bool ret =false;
  switch(mode){
  case PRECISION_HIGH_CLKSTRETCH_ON:
    ret  = true;
    break;
  case PRECISION_HIGH_CLKSTRETCH_OFF:
    ret  = true;
    break;
  case PRECISION_LOW_CLKSTRETCH_ON:
    ret  = true;
    break;
  case PRECISION_LOW_CLKSTRETCH_OFF:
    ret  = true;
    break;
  default :
    ret  = false;
    break;
  }
  return ret;
}

void DFRobot_SHTC3::softwareResetCB(...)
{
  delayMicroseconds(173);
}

void DFRobot_SHTC3::wakeup()
{
  uint16_t addr = COMMAND_WAKEUP;
  writeCommand((uint8_t *)&addr, 2);
  delayMicroseconds(500);
}

void DFRobot_SHTC3::sleep()
{ 
  uint16_t addr = COMMAND_SLEEP;
  writeCommand((uint8_t *)&addr, 2);
  delayMicroseconds(230);
}

void DFRobot_SHTC3::setModeCB(...)
{
  delayMicroseconds(12000);
}

void DFRobot_SHTC3::getDeviceIDCB(void * classPtr, void * id)
{
  DFRobot_SHTC3 * temp = (DFRobot_SHTC3 *)classPtr;
  uint8_t idArray[3];
  uint16_t id1=0;

  temp->writeCommand((uint8_t *)&temp->deviceinit[SHT_CONFIG_ID].addr, temp->deviceinit[SHT_CONFIG_ID].len);
  delayMicroseconds(12000);
  temp->readValue((void*)idArray, 3);

  if(temp->checkCrc(idArray[0], idArray[1], idArray[2])){
    id1 = (idArray[0] << 8 ) | idArray[1];
    if((id1 & 0x807) == 0x807){
      *(uint16_t *)id = id1;
    } else{
      *(uint16_t *)id = 0;
    }
  } else{
    *(uint16_t *)id = 0 ;
  }
}
void DFRobot_SHTC3::getHumValueCB(void * hum)
{
  *(float *)hum =  ((*(float *)hum) * 100.0) / 65536;
}

void DFRobot_SHTC3::getTemValueCB(void * tem)
{
  *(float *)tem =  -45 + 175*((*(float *)tem)/65536);
}
