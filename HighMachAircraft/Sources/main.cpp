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
    vec da{ 3,2,3 };
    vec aaaaa = { 1.0, 2.0, 34.0, 1.0, 1E-10 };
    cout << aaaaa.size() << "\t" << aaaaa[4] << endl;
    AircraftModel* Aircraft = NULL;
    cout << "China 大量" << endl;
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
                theta_ref = 25.0 / r2d;//23
            }
            else if (aircraftinfo.FlightTime < 235)
            {
                theta_ref = 6.3 / r2d;//4
            }
            else if (aircraftinfo.FlightTime < 312)
            {
                theta_ref = 6 / r2d;//5.8
            }
            else
            {
                theta_ref = 5 / r2d;//8.1 //4
            }
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - theta_ref);
        }
        if (Aircraft->getFlightPhase() == 3 && Aircraft->heightFlag == false)
        {
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - ((0.18 - 5) / 70 * (aircraftinfo.FlightTime - Aircraft->time_2) + 5) / r2d);//76.8
        }
        if (Aircraft->getFlightPhase() == 3 && Aircraft->heightFlag == true)
        {
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - 0.1 / r2d);
        }
        if (Aircraft->getFlightPhase() == 3 && Aircraft->velFlag == true)
        {
            Aircraft->e_v += Aircraft->getTimeStep() * (Vel[0] - 1800);
        }
        if (Aircraft->getFlightPhase() == 4)
        {
            if (aircraftinfo.FlightTime < Aircraft->time_4 + 370)
            {
                if (aircraftinfo.FlightTime < Aircraft->time_4 + 100)
                {
                    theta_ref = (-1.5 - 0) / 150 * (aircraftinfo.FlightTime - Aircraft->time_4) / r2d;
                }
                else
                {
                    theta_ref = -1.5 / r2d;
                }

            }
            else if (aircraftinfo.FlightTime < Aircraft->time_4 + 500)
            {
                theta_ref = -4.0 / r2d;
            }
            else if (aircraftinfo.FlightTime < Aircraft->time_4 + 600)
            {
                theta_ref = -7 / r2d;
            }
            else if (aircraftinfo.FlightTime < Aircraft->time_4 + 1000)
            {
                theta_ref = -8 / r2d;
            }
            else
            {
                theta_ref = -2 / r2d;
            }
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - theta_ref);
            if (aircraftinfo.Position[1] < 10)
            {
                *(AircarftFileOutObj) << (*Aircraft) << endl;
                cout << "结束\t" << aircraftinfo.FlightTime << endl;
            }

        }

        *(AircarftFileOutObj) << (*Aircraft) << endl;
    }

    system("pause");
    return 0;
}
