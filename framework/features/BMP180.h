#ifndef BMP180_SENSOR_H
#define BMP180_SENSOR_H

#include "Feature.h"
#include <Libraries/BMP180/BMP180.h>

template<const char* const name, const int scl_gpio = 14, const int sda_gpio = 12>
class BMP180Sensor : public Feature<name> {

protected:
    using Feature<name>::LOG;
    BMP180 bmp180;

public:

    BMP180Sensor(Device* device) :
        Feature<name>(device) {

        Wire.begin(scl_gpio, sda_gpio);

        if(!bmp180.EnsureConnected()) {
            Serial.println("Could not detect a BMP180 sensor, check wiring!");
            abort();
        }

        bmp180.Initialize();
        bmp180.PrintCalibrationData();

        this->updateTimer.initializeMs(15000, TimerDelegate(&BMP180Sensor::publishCurrentState, this));
        this->updateTimer.start(true);
    }

protected:
    virtual void publishCurrentState() {
        const long pressure = bmp180.GetPressure();
        LOG.log("Pressure:", pressure);
        this->publish("pressure", String(pressure), true);

        const float temperature = bmp180.GetTemperature();
        LOG.log("Temperature:", temperature);
        this->publish("temperature", String(temperature), true);
    }

private:
    Timer updateTimer;

};


#endif
