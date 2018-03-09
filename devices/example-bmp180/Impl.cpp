#include "../features/BMP180.h"
#include "Device.h"


constexpr const char BMP180_NAME[] = "bmp180";

class Bmp180Device : public Device {
public:
    Bmp180Device() :
            bmp180(this)
    {
        this->add(&(this->bmp180));
    }

private:
    BMP180Sensor<BMP180_NAME> bmp180;
};


Device* createDevice() {
    return new Bmp180Device();
}


