#include <iostream>
#include "highmachaircraft.hpp"
#include "Vector.h"
#include "ceshi.h"
#include "Airframe.h"
#include "AircraftModel.h"
#include <sstream>
using namespace std;
//#include "armadillo"

int main()
{
    // ofstream SimuEndOut;
    // string Output2FilePathName;
    // stringstream ss;

    AircraftModel *Aircraft = NULL;

    ofstream *AircarftFileOutObj = NULL;

    AircraftInfo aircraftinfo;

    double a = 0;
    Aircraft = new AircraftModel;
    AircarftFileOutObj = new ofstream;
    Aircraft->CreateAirObjOutputFile(*AircarftFileOutObj);
    Aircraft->Initial();
    Aircraft->getAircraftInfo(aircraftinfo);
    bool flag1 = true;
    vec Vel;
    while (1)
    {
        Aircraft->AircraftStepOn();
        Aircraft->getAircraftInfo(aircraftinfo);
        if (Aircraft->getFlightPhase() == 2 && aircraftinfo.FlightTime > 15.006)
        {
            Vel = aircraftinfo.Velocity;
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - 5.0 / 180.0 * pi);
        }
        if (Aircraft->getFlightPhase() == 3 && Aircraft->heightFlag == true)
        {
            Vel = aircraftinfo.Velocity;
            if (flag1 && aircraftinfo.FlightTime > 700)
            {
                Aircraft->e_v = 0;
                flag1 = false;
            }

            Aircraft->e_v += Aircraft->getTimeStep() * (Vel[0] - 1800);
        }

        *(AircarftFileOutObj) << (*Aircraft) << endl;
    }

    system("pause");
    return 0;
}
