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

    AircraftModel* Aircraft = NULL;

    ofstream* AircarftFileOutObj = NULL;

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
                theta_ref = 4.2 / r2d;
            }
            else if (aircraftinfo.FlightTime < 312)
            {
                theta_ref = 5.5 / r2d;
            }
            else if (aircraftinfo.FlightTime < 350)
            {
                theta_ref = 4 / r2d;
            }
            else
            {
                theta_ref = 4 / r2d;
            }
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - theta_ref);
        }
        if (Aircraft->getFlightPhase() == 3 && Aircraft->heightFlag == false)
        {
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - ((0.1 - 4) / 20 * (aircraftinfo.FlightTime - Aircraft->time_2) + 4) / r2d);
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

        if (Aircraft->getFlightPhase() == 4)
        {
            if (aircraftinfo.FlightTime > 4000)
            {
                *(AircarftFileOutObj) << (*Aircraft) << endl;
                cout << "finish!\t" << aircraftinfo.FlightTime << endl;
                break;
            }

        }
        if (aircraftinfo.FlightTime > 2299)
        {
            system("pause");
            break;
        }

        *(AircarftFileOutObj) << (*Aircraft) << endl;
    }

    system("pause");
    return 0;
}
