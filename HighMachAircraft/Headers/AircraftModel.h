#ifndef AIRCRAFTMODEL_H_
#define AIRCRAFTMODEL_H_

#include "AircraftBase.h"
#include "DataStructDef.h"
#include <vector>
#include "Ode.h"
#include <fstream>
#include <sstream>

class Airframe;
class FlightController;
using namespace std;
class AircraftModel : public AircraftBase
{
private:
    double t_flight;
    double FlightPhase;
    SysState *sysState;
    SysStateDerivate *sysStateDerivate;
    Airframe *airframe;
    FlightController *flightController;
    vector<AircraftBase *> MissleModels;
    ODEAlgorithm<AircraftModel> *ode;

    void convertVectorToSysState(const vec &sysstate);
    vec convertSysStateToVector();
    vec computeSysStateDerivate();

public:
    AircraftModel();
    ~AircraftModel();

    void AircraftStepOn();

    void Initial();
    void UpdateState(double timeCur, AircraftModel *pAirObject);
    void UpdateOutput(double timeCur, AircraftModel *pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel *pAirObject);

    Airframe *getAirframe() { return airframe; }
    FlightController *getFlightController() { return flightController; }
    SysState *getSysState() { return sysState; }

    vec operator()(double t, const vec &sysstate);
    friend ostream &operator<<(ostream &os, const AircraftModel &pAirObject);
};

#endif