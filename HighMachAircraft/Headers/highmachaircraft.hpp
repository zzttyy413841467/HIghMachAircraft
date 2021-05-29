#ifndef HIGHMACHAIRCRAFT_H_
#define HIGHMACHAIRCRAFT_H_

#include <iostream>
using namespace std;

class HighMachAircraft
{
public:
    HighMachAircraft();
    HighMachAircraft(HighMachAircraft &&) = default;
    HighMachAircraft(const HighMachAircraft &) = default;
    HighMachAircraft &operator=(HighMachAircraft &&) = default;
    HighMachAircraft &operator=(const HighMachAircraft &) = default;
    ~HighMachAircraft();
};
#endif