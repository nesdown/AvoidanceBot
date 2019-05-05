#include "BatReader.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// Ініціалізуємо датчик Bat-взаємодії
BatReader::BatReader() {
}

// Отримуємо бітове значення напруги
double BatReader::readBatVoltage(void) {
	double readed = (double)(analogRead(BAT_PIN)*ANA_REF)/1024;
	if(readed > BAT_MAX) return BAT_MAX;
	else return readed;
}

// Отримуємо відсоткове значення напруги
double BatReader::readBatPercent(void) {
	double value = (SLOPE*readBatVoltage()) - OFFSET;
	if(value < 0) return 0;
	else return value;
}

