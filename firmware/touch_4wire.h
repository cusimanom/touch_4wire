// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License
//
// ported for Spark Core by ScruffR Nov. 2014 

#ifndef _ADAFRUIT_TOUCH4WIRE_H_
#define _ADAFRUIT_TOUCH4WIRE_H_
#include <stdint.h>

#if defined (SPARK)
#define ADC_MAX_VALUE (0x0FFF)
#define XY_TOLERANCE 15

// direct pin manipulation macros - where speed is required
#define pinSetHigh(pin) PIN_MAP[pin].gpio_peripheral->BSRR = PIN_MAP[pin].gpio_pin
#define pinSetLow(pin)  PIN_MAP[pin].gpio_peripheral->BRR = PIN_MAP[pin].gpio_pin
#define pinSet(pin, HILO) (HILO) ? pinSetHigh(pin) : pinSetLow(pin)
#else
#define ADC_MAX_VALUE (0x03FF)
#define XY_TOLERANCE 5
#endif

typedef enum TOUCH_ACTIONS {
  TOUCH_UNDEF,
  TOUCH_X,
  TOUCH_Y,
  TOUCH_PRESSURE
};

class TSPoint {
 public:
  TSPoint(void);
  TSPoint(int16_t x, int16_t y, int16_t z);

  bool operator==(TSPoint);
  bool operator!=(TSPoint);

  int16_t x, y, z;
};

class TouchScreen {
 public:
  TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym);
  TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx);

  bool isTouching(void);
  uint16_t pressure(void);
  int readTouchY();
  int readTouchX();
  TSPoint getPoint();
  TSPoint getPoint(bool withPressure);
  int16_t pressureThreshhold;

private:
  uint8_t _yp, _ym, _xm, _xp;
  uint16_t _rxplate;
  TOUCH_ACTIONS _prevAction = TOUCH_UNDEF;
};

#endif
