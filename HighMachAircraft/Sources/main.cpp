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
    double theta_ref = 0;
    while (1)
    {
        Aircraft->AircraftStepOn();
        Aircraft->getAircraftInfo(aircraftinfo);
        if (Aircraft->getFlightPhase() == 2 && aircraftinfo.FlightTime > 15.006)
        {
            Vel = aircraftinfo.Velocity;
            if (aircraftinfo.FlightTime < 40)
            {
                theta_ref = 10.0 / r2d;
            }
            else if (aircraftinfo.FlightTime < 70)
            {
                theta_ref = 25.0 / r2d;
            }
            else if (aircraftinfo.FlightTime < 235)
            {
                theta_ref = 6.3 / r2d;
            }
            else if (aircraftinfo.FlightTime < 312)
            {
                theta_ref = 4.7 / r2d;
            }
            else if (aircraftinfo.FlightTime < 350)
            {
                theta_ref = 3.5 / r2d;
            }
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - theta_ref);
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

        if (Aircraft->getFlightPhase() == 3)
        {
            a = 1;
        }
        *(AircarftFileOutObj) << (*Aircraft) << endl;
    }

    system("pause");
    return 0;
}
