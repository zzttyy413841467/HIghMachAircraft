#include "DataStructDef.h"

SysState::SysState()
{
    Position.assign(3, 0);
    Position[1] = 10;
    Velocity.assign(3, 0);
    m = 23000;
}
SysState::~SysState()
{
}

SysStateDerivate::SysStateDerivate()
{
    PositionDerivate.assign(3, 0);
    VelocityDerivate.assign(3, 0);
    mDerivate = 0;
}
SysStateDerivate::~SysStateDerivate()
{
}

AircraftInfo::AircraftInfo()
{
    FlightTime = 0.0;
    Position.assign(3, 0);
    Position[1] = 10;
    Velocity.assign(3, 0);
    m = 23000;
}
AircraftInfo::~AircraftInfo()
{
}