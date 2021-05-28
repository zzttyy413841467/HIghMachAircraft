#ifndef AIRCRAFTBASE_H_
#define AIRCRAFTBASE_H_

#include <string>

class AircraftModel;
class AircraftBase
{
private:
public:
    AircraftBase() {}
    virtual ~AircraftBase() {}
    virtual void Initial() = 0;
    virtual void UpdateState(double timeCur, AircraftModel *pAirObject) = 0;
    virtual void UpdateOutput(double timeCur, AircraftModel *pAirObject) = 0;
    virtual void UpdateDerivate(double timeCur, AircraftModel *pAirObject) = 0;
};
#endif