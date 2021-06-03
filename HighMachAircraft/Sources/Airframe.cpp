#include <fstream>
#include <cmath>
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
    for (size_t i = 0; i < AirframeModels.size(); i++)
    {
        AirframeModels[i]->Initial();
    }
}

void Airframe::UpdateState(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < AirframeModels.size(); i++)
    {
        AirframeModels[i]->UpdateState(timeCur, pAirObject);
    }
}

void Airframe::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < AirframeModels.size(); i++)
    {
        AirframeModels[i]->UpdateOutput(timeCur, pAirObject);
    }
}

void Airframe::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < AirframeModels.size(); i++)
    {
        AirframeModels[i]->UpdateDerivate(timeCur, pAirObject);
    }
}

void Airframe::getFileOutputItemName(vector<string> &FileOutItemName)
{
    dynamics->getFileOutputItemName(FileOutItemName);
    propulsion->getFileOutputItemName(FileOutItemName);
    aerodata->getFileOutputItemName(FileOutItemName);
}

ostream &operator<<(ostream &os, const Airframe &pObj)
{
    os << *(pObj.dynamics)
       << *(pObj.propulsion)
       << *(pObj.aerodata);
    return os;
}

Dynamics::Dynamics()
{
    pAirObj = 0;
    Position.assign(3, 0);
    Velocity.assign(3, 0);
    PositionDerivate.assign(3, 0);
    VelocityDerivate.assign(3, 0);

    Alpha = 0;
    Beta = 0;
    Sigma = 0;
    Ma = 0;
    H = 0;
    Q = 0;
    VelScalar = 0;
    AeroForce.assign(3, 0);
    ThrustForce.assign(3, 0);

    mass = 0;
    Sref = 0;
    m_Force.assign(3, 0);
    m_acceleration.assign(3, 0);
}

Dynamics::Dynamics(AircraftModel *pObj)
{
    pAirObj = pObj;
    Position.assign(3, 0);
    Velocity.assign(3, 0);
    PositionDerivate.assign(3, 0);
    VelocityDerivate.assign(3, 0);

    Alpha = 0;
    Beta = 0;
    Sigma = 0;
    Ma = 0;
    H = 0;
    Q = 0;
    VelScalar = 0;
    AeroForce.assign(3, 0);
    ThrustForce.assign(3, 0);

    mass = 0;
    Sref = 0;
    m_Force.assign(3, 0);
    m_acceleration.assign(3, 0);
}

Dynamics::~Dynamics()
{
}

void Dynamics::Initial()
{
}

void Dynamics::UpdateState(double timeCur, AircraftModel *pAirObject)
{
    Position = pAirObject->getSysState()->Position;
    Velocity = pAirObject->getSysState()->Velocity;
    VelScalar = Velocity.norm2();
    Alpha = atan2(-Velocity[1], Velocity[0]);
    Beta = asin(Velocity[2] / VelScalar);
    Sigma = atan2(Velocity[2], Velocity[0]);

    H = Position[1];
    Ma = VelScalar / SA.geta(H / 1000);
    Q = 0.5 * SA.getrho(H / 1000) * VelScalar * VelScalar;
}

void Dynamics::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void Dynamics::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

void Dynamics::getFileOutputItemName(vector<string> &FileOutItemName)
{
    FileOutItemName.push_back("PositionX");
    FileOutItemName.push_back("PositionY");
    FileOutItemName.push_back("PositionZ");
    FileOutItemName.push_back("VelocityX");
    FileOutItemName.push_back("VelocityY");
    FileOutItemName.push_back("VelocityZ");
    FileOutItemName.push_back("Alpha");
    FileOutItemName.push_back("Beta");
    FileOutItemName.push_back("Sigma");
    FileOutItemName.push_back("Ma");
}

ostream &operator<<(ostream &os, const Dynamics &pObj)
{
    os << pObj.Position[0] << "\t" << pObj.Position[0] << "\t" << pObj.Position[0] << "\t"
       << pObj.Velocity[0] << "\t" << pObj.Velocity[0] << "\t" << pObj.Velocity[0] << "\t"
       << pObj.Alpha << "\t" << pObj.Beta << "\t" << pObj.Sigma << "\t" << pObj.Ma << "\t";

    return os;
}

Propulsion::Propulsion()
{
    pAirObj = 0;
}

Propulsion::Propulsion(AircraftModel *pObj)
{
    pAirObj = pObj;
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
void Propulsion::getFileOutputItemName(vector<string> &FileOutItemName)
{
    FileOutItemName.push_back("Mass");
    FileOutItemName.push_back("ThrustTotal");
}

ostream &operator<<(ostream &os, const Propulsion &pObj)
{
    os << pObj.mass << "\t" << pObj.thrustTotal << "\t";
    return os;
}
AeroData::AeroData()
{
    pAirObj = 0;
}

AeroData::AeroData(AircraftModel *pObj)
{
    pAirObj = pObj;
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
void AeroData::getFileOutputItemName(vector<string> &FileOutItemName)
{
}

ostream &operator<<(ostream &os, const AeroData &pObj)
{
    return os;
}