#pragma once

#include "AircraftBase.h"

class AircraftModel : public AircraftBase
{
private:
    double t_flight;
    double FlightPhase;

public:
    AircraftModel();
    ~AircraftModel();
    void AircraftStepOn();
};