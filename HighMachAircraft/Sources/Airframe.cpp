#include <fstream>
#include <cmath>
#include "Airframe.h"
#include "AircraftModel.h"
#include "FlightController.h"

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
    g = 0;
    rho = 0;
    VelScalar = 0;
    AeroForce.assign(2, 0);
    ThrustForce = 0;

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
    g = 0;
    rho = 0;
    VelScalar = 0;
    AeroForce.assign(2, 0);
    ThrustForce = 0;

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
    VelScalar = Velocity[0];

    vec commmand = pAirObject->getFlightController()->getGuidance()->getCommand();
    Alpha = commmand[0];
    Sigma = commmand[1];

    H = Position[1];
    Ma = VelScalar / SA.geta(H / 1000);
    Q = 0.5 * SA.getrho(H / 1000) * VelScalar * VelScalar;
    rho = SA.getrho(H / 1000);
}

void Dynamics::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
    Lref = pAirObject->getAirframe()->getAeroData()->getLref();
    Sref = pAirObject->getAirframe()->getAeroData()->getSref();
    ThrustForce = pAirObject->getAirframe()->getPropulsion()->getThrustTotal();
    mass = pAirObject->getAirframe()->getPropulsion()->getMass();
    g = SA.getg(H / 1000.0);
    AeroForce[0] = Q * Sref * (pAirObject->getAirframe()->getAeroData()->getCd());
    AeroForce[1] = Q * Sref * (pAirObject->getAirframe()->getAeroData()->getCl());
}

void Dynamics::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
    PositionDerivate[0] = Velocity[0] * cos(Velocity[1]) * cos(Velocity[2]);
    PositionDerivate[1] = Velocity[0] * sin(Velocity[1]);
    PositionDerivate[2] = -Velocity[0] * cos(Velocity[1]) * sin(Velocity[2]);
    VelocityDerivate[0] = (ThrustForce * cos(Alpha) - AeroForce[0] - mass * g * sin(Velocity[1])) / mass;
    VelocityDerivate[1] = (ThrustForce * sin(Alpha) * cos(Sigma) + AeroForce[1] * cos(Sigma) - mass * g * cos(Velocity[1])) / mass / Velocity[0];
    VelocityDerivate[2] = -(ThrustForce * sin(Alpha) * sin(Sigma) + AeroForce[1] * sin(Sigma)) / mass / Velocity[0] / cos(Velocity[1]);
    if(timeCur<11)
    {
        VelocityDerivate[0] = (ThrustForce * cos(Alpha) - AeroForce[0]) / mass;
        VelocityDerivate[1] = 0;
        VelocityDerivate[2] = 0;
    }
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
    mass = 23000;
    massflow = 0;
}

Propulsion::Propulsion(AircraftModel *pObj)
{
    pAirObj = pObj;
    mass = 23000;
    massflow = 0;
}

Propulsion::~Propulsion()
{
}

void Propulsion::Initial()
{
}

void Propulsion::UpdateState(double timeCur, AircraftModel *pAirObject)
{
    double h, alpha, ma;
    h = pAirObject->getAirframe()->getDynamics()->getH() / 1000;
    //alpha = pAirObject->getAirframe()->getDynamics()->getAlpha() * 180 / pi;
    ma = pAirObject->getAirframe()->getDynamics()->getMa();
    double rho = pAirObject->getAirframe()->getDynamics()->getrho();
    double V = pAirObject->getAirframe()->getDynamics()->getVelScalar();

    mass = pAirObject->getSysState()->m;

    AeroStageFlag = pAirObject->getFlightPhase();

    double Is;
    switch (AeroStageFlag)
    {
    case 1:
        thrustTotal = 4.803e4 - 2231 * h - 1.322e4 * ma - 200.3 * h * h + 809.2 * h * ma + 3.035e4 * ma * ma + 9.583 * pow(h, 3) + 157 * pow(h, 2) * ma - 3500 * h * pow(ma, 2) + 3483 * pow(ma, 3) - 0.06638 * pow(h, 4) - 5.22 * pow(h, 3) * ma + 67.72 * pow(h, 2) * pow(ma, 2) + 34.75 * h * pow(ma, 3) - 426.6 * pow(ma, 4);
        massflow = 4.998 - 0.3946 * h + 0.2715 * ma - 0.00191 * h * h - 0.005939 * h * ma + 1.988 * ma * ma + 0.0003694 * pow(h, 3) + 0.01403 * pow(h, 2) * ma - 0.276 * h * pow(ma, 2) + 0.4432 * pow(ma, 3) - 2.863e-8 * pow(h, 4) - 4.763e-4 * pow(h, 3) * ma + 0.00623 * pow(h, 2) * pow(ma, 2) - 0.004347 * h * pow(ma, 3) - 0.03359 * pow(ma, 4);
        thrustTotal = 4 * thrustTotal;
        massDerivate = -4*massflow;
        if (mass < 14000)
            massDerivate = 0;
        break;
    case 2:
        thrustTotal = 4.803e4 - 2231 * h - 1.322e4 * ma - 200.3 * h * h + 809.2 * h * ma + 3.035e4 * ma * ma + 9.583 * pow(h, 3) + 157 * pow(h, 2) * ma - 3500 * h * pow(ma, 2) + 3483 * pow(ma, 3) - 0.06638 * pow(h, 4) - 5.22 * pow(h, 3) * ma + 67.72 * pow(h, 2) * pow(ma, 2) + 34.75 * h * pow(ma, 3) - 426.6 * pow(ma, 4);
        massflow = 4.998 - 0.3946 * h + 0.2715 * ma - 0.00191 * h * h - 0.005939 * h * ma + 1.988 * ma * ma + 0.0003694 * pow(h, 3) + 0.01403 * pow(h, 2) * ma - 0.276 * h * pow(ma, 2) + 0.4432 * pow(ma, 3) - 2.863e-8 * pow(h, 4) - 4.763e-4 * pow(h, 3) * ma + 0.00623 * pow(h, 2) * pow(ma, 2) - 0.004347 * h * pow(ma, 3) - 0.03359 * pow(ma, 4);
        thrustTotal = 4 * thrustTotal;
        massDerivate = -4 * massflow;
        if (mass < 14000)
            massDerivate = 0;
        break;
    default:
        massflow = 0.55 * V * rho / 14.9;
        massDerivate = -massflow;
        Is = (-68 * ma * ma + 454 * ma) * 9.8;
        thrustTotal = massflow * Is;
        if (mass < 3300)
            massDerivate = 0;
        break;
    }
}

void Propulsion::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void Propulsion::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}
void Propulsion::getFileOutputItemName(vector<string> &FileOutItemName)
{
    FileOutItemName.push_back("Massflow");
    FileOutItemName.push_back("ThrustTotal");
}

ostream &operator<<(ostream &os, const Propulsion &pObj)
{
    os << pObj.massflow << "\t" << pObj.thrustTotal << "\t";
    return os;
}

const double AeroData::Lref = 1;
const double AeroData::Sref = 1;

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

    double h, alpha, ma;
    h = pAirObject->getAirframe()->getDynamics()->getH();
    alpha = pAirObject->getAirframe()->getDynamics()->getAlpha() * 180.0 / pi;
    ma = pAirObject->getAirframe()->getDynamics()->getMa();

    AeroStageFlag = pAirObject->getFlightPhase();

    switch (AeroStageFlag)
    {
    case 1:
        Cl = (0.008927 * ma - 0.03518) * alpha * alpha + (-0.7577 * ma + 4.991) * alpha + (-2.05 * ma + 7.619);
        Cd = (0.0002439 * ma - 0.000694) * alpha * alpha * alpha + (-0.01328 * ma + 0.08511) * alpha * alpha + (-0.03909 * ma + 0.1584) * alpha + (-0.1592 * ma + 2.354);
        Cl_alpha = (2 * (0.008927 * ma - 0.03518) * alpha + (-0.7577 * ma + 4.991)) * 180.0 / pi;
        break;
    case 2:
        Cl = (0.008927 * ma - 0.03518) * alpha * alpha + (-0.7577 * ma + 4.991) * alpha + (-2.05 * ma + 7.619);
        Cd = (0.0002439 * ma - 0.000694) * alpha * alpha * alpha + (-0.01328 * ma + 0.08511) * alpha * alpha + (-0.03909 * ma + 0.1584) * alpha + (-0.1592 * ma + 2.354);
        Cl_alpha = (2 * (0.008927 * ma - 0.03518) * alpha + (-0.7577 * ma + 4.991)) * 180.0 / pi;
        break;
    case 3:
        Cl = (-0.001833 * ma + 0.01119) * alpha * alpha + (-0.1373 * ma + 1.164) * alpha + (-0.007293 * ma + 0.1055);
        Cd = (-3.646e-5 * ma + 0.0002542) * alpha * alpha * alpha + (-0.002206 * ma + 0.01945) * alpha * alpha + (0.0004566 * ma + 0.0001816) * alpha + (-0.02079 * ma + 0.3597);
        Cl_alpha = (2 * (-0.001833 * ma + 0.01119) * alpha + (-0.1373 * ma + 1.164)) * 180.0 / pi;
        break;
    case 4:
        Cl = (-0.001833 * ma + 0.01119) * alpha * alpha + (-0.1373 * ma + 1.164) * alpha + (-0.007293 * ma + 0.1055);
        Cd = (-3.646e-5 * ma + 0.0002542) * alpha * alpha * alpha + (-0.002206 * ma + 0.01945) * alpha * alpha + (0.0004566 * ma + 0.0001816) * alpha + (-0.02079 * ma + 0.4172);
        Cl_alpha = (2 * (-0.001833 * ma + 0.01119) * alpha + (-0.1373 * ma + 1.164)) * 180.0 / pi;
        break;
    default:
        break;
    }
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