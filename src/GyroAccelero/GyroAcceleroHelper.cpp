#include "GyroAcceleroHelper.h"
#include "Interfaces/BridgeInterface.h"

void GyroAcceleroHelper::setup()
{
    MN_DEBUGLN("Gyro Setup");
}

void GyroAcceleroHelper::loop()
{
    for (int i = 0; i < AG_REFRESH_RATE; i++)
    {
        if (accerlerogyro_mutex)
        {
            // accelerogyro_buffer[i][0];
            // accelerogyro_buffer[i][1];
            MN_DEBUG("Gyro Loop : ");
            MN_DEBUGLN(i);
            if (AG_REFRESH_RATE - 1 == i)
            {
                accerlerogyro_mutex = false;
            }
            delay(1000 / AG_REFRESH_RATE);
        }
        else
        {
            delay(10);
        }
    }
}