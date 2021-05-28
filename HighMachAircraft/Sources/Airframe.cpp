#include <fstream>

#include "Airframe.h"
#include "AircraftModel.h"


Airframe::Airframe()
{
    pAirObj = 0;
    dynamics = new Dynamics;
    propulsion = new Propulsion;
    aerodata = new AeroData;

    AirframeModels.push_back(dynamics);
    AirframeModels.push_back(propulsion);
    AirframeModels.push_back(aerodata);
}

Airframe::Airframe(AircraftModel *pObj)
{
    pAirObj = pObj;
    dynamics = new Dynamics(pObj);
    propulsion = new Propulsion(pObj);
    aerodata = new AeroData(pObj);

    AirframeModels.push_back(dynamics);
    AirframeModels.push_back(propulsion);
    AirframeModels.push_back(aerodata);
}

Airframe::~Airframe()
{
    delete dynamics;
    delete propulsion;
    delete aerodata;
}

void Airframe::Initial()
{
}

void Airframe::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void Airframe::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void Airframe::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

Dynamics::Dynamics()
{

}

Dynamics::Dynamics(AircraftModel *pObj)
{

}

Dynamics::~Dynamics()
{

}

void Dynamics::Initial()
{
}

void Dynamics::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void Dynamics::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void Dynamics::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

Propulsion::Propulsion()
{
}

Propulsion::Propulsion(AircraftModel *pObj)
{
}

Propulsion::~Propulsion()
{
}

void Propulsion::Initial()
{
}

void Propulsion::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void Propulsion::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void Propulsion::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

AeroData::AeroData()
{
}

AeroData::AeroData(AircraftModel *pObj)
{
}

AeroData::~AeroData()
{
}

void AeroData::Initial()
{
}

void AeroData::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void AeroData::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void AeroData::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}