#include "FlightController.h"
#include "AircraftModel.h"
#include <iostream>
#include <fstream>
#include "Airframe.h"

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

    command.assign(3, 0);
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

    command.assign(3, 0);
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
        break;
    case 2:
        secondGuidance->UpdateState(timeCur, pAirObject);
        break;
    case 3:
        thirdGuidance->UpdateState(timeCur, pAirObject);
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
        break;
    case 2:
        secondGuidance->UpdateDerivate(timeCur, pAirObject);
        break;
    case 3:
        thirdGuidance->UpdateDerivate(timeCur, pAirObject);
        break;
    default:
        break;
    }
}

void Guidance::UpdateGuidancePhase(double timeCur, AircraftModel *pAirObject)
{
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
    command.assign(3, 0);
}

FirstGuidance::FirstGuidance(AircraftModel *pObj)
{
    pAirObj = pObj;
    command.assign(3, 0);
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
}

void FirstGuidance::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

SecondGuidance::SecondGuidance()
{
    pAirObj = 0;
    command.assign(3, 0);
}

SecondGuidance::SecondGuidance(AircraftModel *pObj)
{
    pAirObj = pObj;
    command.assign(3, 0);
}

SecondGuidance::~SecondGuidance()
{
}
void SecondGuidance::Initial()
{
}

void SecondGuidance::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void SecondGuidance::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void SecondGuidance::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

ThirdGuidance::ThirdGuidance()
{
    pAirObj = 0;
    command.assign(3, 0);
}

ThirdGuidance::ThirdGuidance(AircraftModel *pObj)
{
    pAirObj = pObj;
    command.assign(3, 0);
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