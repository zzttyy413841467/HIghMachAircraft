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
}

void FlightController::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void FlightController::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void FlightController::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

Guidance::Guidance()
{
}

Guidance::Guidance(AircraftModel *pObj)
{
}

Guidance::~Guidance()
{
}
void Guidance::Initial()
{
}

void Guidance::UpdateState(double timeCur, AircraftModel *pAirObject)
{
}

void Guidance::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
}

void Guidance::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
}

FirstGuidance::FirstGuidance()
{
}

FirstGuidance::FirstGuidance(AircraftModel *pObj)
{
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
}

SecondGuidance::SecondGuidance(AircraftModel *pObj)
{
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
}

ThirdGuidance::ThirdGuidance(AircraftModel *pObj)
{
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