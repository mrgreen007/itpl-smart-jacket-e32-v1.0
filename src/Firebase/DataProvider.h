#ifndef DATA_PROVIDER_H
#define DATA_PROVIDER_H

#include "config.h"
#include <vector>

std::vector<double> vec;

double inside_points[6][2] = {{22.60254, 88.34518},
                              {22.60259, 88.34502},
                              {22.60252, 88.34495},
                              {22.60247, 88.34506},
                              {22.60237, 88.34510},
                              {22.60275, 88.34496}};

double outside_points[6][2] = {{22.60247, 88.34503},
                               {22.60263, 88.34513},
                               {22.60259, 88.34494},
                               {22.60260, 88.34509},
                               {22.60264, 88.34496},
                               {22.60270, 88.34499}};

uint8_t _counter = 0;
uint8_t _step = 1;

std::vector<double> getPoints()
{
    vec.clear();

    uint8_t i = random(0,6);

    if(_step == 1)
    {
        vec.push_back(outside_points[i][0]);
        vec.push_back(outside_points[i][1]);

        
        if(_counter == 2)
        {
            _counter = -1;
            _step = 2;
        }
        _counter++;

        return vec;
    }
    else if (_step == 2)
    {
        vec.push_back(inside_points[i][0]);
        vec.push_back(inside_points[i][1]);

        if(_counter == 2)
        {
            _counter = -1;
            _step = 1;
        }
        _counter++;

        return vec;
    }
    return vec;
}


#endif