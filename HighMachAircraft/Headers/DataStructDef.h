#pragma once

#include "Vector.h"

static const double pi = 3.141592653589793115998;

class SysState
{
public:
    vec Position;
    vec Velocity;
    double m;

    SysState();
    ~SysState();
    void setm(double m1) { m = m1; }
};

class SysStateDerivate
{
public:
    vec PositionDerivate;
    vec VelocityDerivate;
    double mDerivate;

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
    double m;
    AircraftInfo(/* args */);
    ~AircraftInfo();
};
