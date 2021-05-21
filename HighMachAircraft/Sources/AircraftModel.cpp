#include "AircraftModel.h"


AircraftModel::AircraftModel()
{

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