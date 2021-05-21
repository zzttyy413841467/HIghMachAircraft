#include "DataStructDef.h"

SysState::SysState()
{
    Position.assign(3, 0);
    Velocity.assign(3, 0);
}
SysState::~SysState()
{
}

SysStateDerivate::SysStateDerivate()
{
    PositionDerivate.assign(3, 0);
    VelocityDerivate.assign(3, 0);
}
SysStateDerivate::~SysStateDerivate()
{
}

AircraftInfo::AircraftInfo()
{
    Position.assign(3, 0);
    Velocity.assign(3, 0);
}
AircraftInfo::~AircraftInfo()
{
}