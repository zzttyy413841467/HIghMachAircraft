#pragma once

#include "Vector.h"

static const double pi = 3.141592653589793115998;

class SysState
{
public:
    vec Position;
    vec Velocity;

    SysState();
    ~SysState();
};

class SysStateDerivate
{
public:
    vec PositionDerivate;
    vec VelocityDerivate;

    SysStateDerivate();
    ~SysStateDerivate();
};

class AircraftInfo
{
private:
    
public:
    double FlightTime;
    vec Position;
    vec Velocity;
    vec Acceleration;
    AircraftInfo(/* args */);
    ~AircraftInfo();
};

