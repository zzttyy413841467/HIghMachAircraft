#include "FlightController.h"
#include "AircraftModel.h"
#include <iostream>
#include <fstream>
#include "Airframe.h"
#include <cmath>

FlightController::FlightController()
{
    pAirObj = 0;
    guidance = new Guidance;
    FlightControllerModels.push_back(guidance);
}

FlightController::FlightController(AircraftModel *pObj)
{
    pAirObj = pObj;
    guidance = new Guidance(pObj);
    FlightControllerModels.push_back(guidance);
}

FlightController::~FlightController()
{
    delete guidance;
}

void FlightController::Initial()
{
    guidance->Initial();
}

void FlightController::UpdateState(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < FlightControllerModels.size(); i++)
    {
        FlightControllerModels[i]->UpdateState(timeCur, pAirObject);
    }
}

void FlightController::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < FlightControllerModels.size(); i++)
    {
        FlightControllerModels[i]->UpdateOutput(timeCur, pAirObject);
    }
}

void FlightController::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < FlightControllerModels.size(); i++)
    {
        FlightControllerModels[i]->UpdateDerivate(timeCur, pAirObject);
    }
}

void FlightController::getFileOutputItemName(vector<string> &FileOutItemName)
{
    guidance->getFileOutputItemName(FileOutItemName);
}

ostream &operator<<(ostream &os, const FlightController &pObj)
{
    os << *(pObj.guidance);
    return os;
}

Guidance::Guidance()
{
    pAirObj = 0;
    GuidancePhase = 1;
    firstGuidance = new FirstGuidance;
    secondGuidance = new SecondGuidance;
    thirdGuidance = new ThirdGuidance;

    GuidanceModels.push_back(firstGuidance);
    GuidanceModels.push_back(secondGuidance);
    GuidanceModels.push_back(thirdGuidance);

    command.assign(2, 0);
}

Guidance::Guidance(AircraftModel *pObj)
{
    pAirObj = pObj;
    GuidancePhase = 1;
    firstGuidance = new FirstGuidance(pObj);
    secondGuidance = new SecondGuidance(pObj);
    thirdGuidance = new ThirdGuidance(pObj);

    GuidanceModels.push_back(firstGuidance);
    GuidanceModels.push_back(secondGuidance);
    GuidanceModels.push_back(thirdGuidance);

    command.assign(2, 0);
}

Guidance::~Guidance()
{
    delete firstGuidance;
    delete secondGuidance;
    delete thirdGuidance;
}
void Guidance::Initial()
{
    firstGuidance->Initial();
    secondGuidance->Initial();
    thirdGuidance->Initial();
}

void Guidance::UpdateState(double timeCur, AircraftModel *pAirObject)
{
    UpdateGuidancePhase(timeCur, pAirObject);
    switch (GuidancePhase)
    {
    case 1:
        firstGuidance->UpdateState(timeCur, pAirObject);
        //command = firstGuidance->getCommand();
        break;
    case 2:
        secondGuidance->UpdateState(timeCur, pAirObject);
        //command = secondGuidance->getCommand();
        break;
    case 3:
        thirdGuidance->UpdateState(timeCur, pAirObject);
        //command = thirdGuidance->getCommand();
        break;
    default:
        break;
    }
}

void Guidance::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
    switch (GuidancePhase)
    {
    case 1:
        firstGuidance->UpdateOutput(timeCur, pAirObject);
        command = firstGuidance->getCommand();
        break;
    case 2:
        secondGuidance->UpdateOutput(timeCur, pAirObject);
        command = secondGuidance->getCommand();
        break;
    case 3:
        thirdGuidance->UpdateOutput(timeCur, pAirObject);
        command = thirdGuidance->getCommand();
        break;
    default:
        break;
    }
}

void Guidance::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
    switch (GuidancePhase)
    {
    case 1:
        firstGuidance->UpdateDerivate(timeCur, pAirObject);
        //command = firstGuidance->getCommand();
        break;
    case 2:
        secondGuidance->UpdateDerivate(timeCur, pAirObject);
        //command = secondGuidance->getCommand();
        break;
    case 3:
        thirdGuidance->UpdateDerivate(timeCur, pAirObject);
        //command = thirdGuidance->getCommand();
        break;
    default:
        break;
    }
}

void Guidance::UpdateGuidancePhase(double timeCur, AircraftModel *pAirObject)
{
    double H = pAirObject->getSysState()->Position[1];
    double m = pAirObject->getSysState()->m;
    if (timeCur < 11.0)
    {
        GuidancePhase = 1;
    }
    else
    {
        if (GuidancePhase == 1)
        {
            GuidancePhase = 2;
            cout << "ÅÀÉý¶Î" << endl;
        }
        if (GuidancePhase == 2)
        {
            if (H > 25000)
            {
                GuidancePhase = 3;
                cout << "Ñ²º½¶Î" << endl;
            }
        }
        if (GuidancePhase == 3)
        {
            if (m < 3310)
            {
                GuidancePhase = 4;
                cout << "·µº½¶Î" << endl;
            }
        }
    }
}

void Guidance::getFileOutputItemName(vector<string> &FileOutItemName)
{
    FileOutItemName.push_back("GuidancePhase");
}

ostream &operator<<(ostream &os, const Guidance &pObj)
{
    os << pObj.GuidancePhase << "\t";
    return os;
}

FirstGuidance::FirstGuidance()
{
    pAirObj = 0;
    command.assign(2, 0);
}

FirstGuidance::FirstGuidance(AircraftModel *pObj)
{
    pAirObj = pObj;
    command.assign(2, 0);
}

FirstGuidance::~FirstGuidance()
{
}
void FirstGuidance::Initial()
{
}

void FirstGuidance::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void FirstGuidance::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
    command[0] = 0;
    command[1] = 0;
}

void FirstGuidance::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

SecondGuidance::SecondGuidance()
{
    pAirObj = 0;
    command.assign(2, 0);
}

SecondGuidance::SecondGuidance(AircraftModel *pObj)
{
    pAirObj = pObj;
    command.assign(2, 0);
}

SecondGuidance::~SecondGuidance()
{
}
void SecondGuidance::Initial()
{
}

double SecondGuidance::calcuAlpha(AircraftModel *pAirObject)
{
    double r2d = 180.0 / pi;
    double thrust = pAirObject->getAirframe()->getPropulsion()->getThrustTotal();
    double mass = pAirObject->getAirframe()->getPropulsion()->getMass();
    double g = pAirObject->getAirframe()->getDynamics()->getG();
    double Q = pAirObject->getAirframe()->getDynamics()->getQ();
    double S = pAirObject->getAirframe()->getAeroData()->getSref();
    double ma = pAirObject->getAirframe()->getDynamics()->getMa();
    double Cl1 = 0.008927 * ma - 0.03518;
    double Cl2 = -0.7577 * ma + 4.991;
    double Cl3 = -2.05 * ma + 7.619;
    vec Vel = pAirObject->getAirframe()->getDynamics()->getVelocity();
    double theta = 5.0 / r2d;
    double V = Vel[0];
    double x0 = 0.03;
    double x1 = 0.05;
    double Cl;
    double Cl_alpha;
    
    while (fabs(x1 - x0) / fabs(x1) > 1e-12)
    {
        x0 = x1;
        Cl = Cl1 * x0 * r2d * x0 * r2d + Cl2 * x0 * r2d + Cl3;
        Cl_alpha = 2 * Cl1 * x0 * r2d * r2d + Cl2 * r2d;
        x1 = x0 - ((thrust * sin(x0) + Q * S * Cl - mass * g * cos(Vel[1]))/mass/V+1.414*(Vel[1]-theta+pAirObject->e_theta)) / ((thrust * cos(x0) + Q * S * Cl_alpha)/mass/V);
        //x1 = x0 - (thrust * sin(x0) + Q * S * Cl - mass * g * cos(Vel[1])) / (thrust * cos(x0) + Q * S * Cl_alpha);
    }

    if (x1 >= 25.0 / 57.3)
    {
        x1 = 25.0 / 57.3;
    }
    if (x1 <= -25.0 / 57.3)
    {
        x1 = -25.0 / 57.3;
    }

    return x1;
}

void SecondGuidance::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void SecondGuidance::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
    double alpha0 = 4.89 / 57.3;
    double alpha1 = -2 / 57.3;
    double alpha2 = 2 / 57.3;
    double t0 = 15.006;
    double t1 = 300;
    double t2 = 410;
    double alpha = 0;

    if (timeCur < 15.006)
    {
        command[0] = 10.0 / 180 * pi;
        command[1] = 0;
    }
    else if (t0 <= timeCur < t1)
    {
        alpha = calcuAlpha(pAirObject);
        command[0] = (alpha1 - alpha0) / (t1 - t0) * (timeCur - t0) + alpha0;
        command[0] = alpha;
        command[1] = 0;
    }
    else
    {
        command[0] = (alpha2 - alpha1) / (t2 - t1) * (timeCur - t1) + alpha1;
        command[1] = 0;
    }
}

void SecondGuidance::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

ThirdGuidance::ThirdGuidance()
{
    pAirObj = 0;
    command.assign(2, 0);
}

ThirdGuidance::ThirdGuidance(AircraftModel *pObj)
{
    pAirObj = pObj;
    command.assign(2, 0);
}

ThirdGuidance::~ThirdGuidance()
{
}
void ThirdGuidance::Initial()
{
}

void ThirdGuidance::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void ThirdGuidance::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void ThirdGuidance::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}