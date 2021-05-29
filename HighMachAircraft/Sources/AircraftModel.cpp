#include "AircraftModel.h"
#include "Airframe.h"
#include "FlightController.h"

AircraftModel::AircraftModel()
{
    sysState = new SysState;
    sysStateDerivate = new SysStateDerivate;

    airframe = new Airframe(this);
    flightController = new FlightController(this);
    ode = new RungeKutta4<AircraftModel>;

    AircraftModels.push_back(airframe);
    AircraftModels.push_back(flightController);
}

AircraftModel::~AircraftModel()
{
    delete airframe;
    delete flightController;
    delete ode;
}

void AircraftModel::Initial()
{
}

void AircraftModel::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void AircraftModel::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void AircraftModel::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

void AircraftModel::AircraftStepOn()
{
}

vec AircraftModel::operator()(double t, const vec &sysstate)
{
}

void AircraftModel::convertVectorToSysState(const vec &sysstate)
{
}

vec AircraftModel::convertSysStateToVector()
{
}

vec AircraftModel::computeSysStateDerivate()
{
}

ostream &operator<<(ostream &os, const AircraftModel &pAirObject)
{
}