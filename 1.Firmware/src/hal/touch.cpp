#include "hal/hal.h"
#include "touch.h"

bool HAL::touch_read(int *x, int *y) 
{
  byte data_raw[7];
  i2c_read(0x15, 0x02, data_raw, 7);

  int event = data_raw[1] >> 6;

  if (event == 2)
  {
    *x = (int)data_raw[2] + (int)(data_raw[1] & 0x0f) * 256;
    *y = (int)data_raw[4] + (int)(data_raw[3] & 0x0f) * 256;

    return true;
  }
  return false;
}

void HAL::touch_init(void) {
  Wire.begin(TOUCH_SDA, TOUCH_SCL);
}

int i2c_read(uint16_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length)
{
  Wire.beginTransmission(addr);
  Wire.write(reg_addr);
  if (Wire.endTransmission(true))
  {
    return -1;
  }
  Wire.requestFrom(addr, length, true);
  for (int i = 0; i < length; i++)
  {
    *reg_data++ = Wire.read();
  }
  return 0;
}

int i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length)
{
  Wire.beginTransmission(addr);
  Wire.write(reg_addr);
  for (int i = 0; i < length; i++)
  {
    Wire.write(*reg_data++);
  }
  if (Wire.endTransmission(true))
  {
    return -1;
  }
  return 0;
}