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
    vec Vel;
    while (1)
    {
        Aircraft->AircraftStepOn();
        Aircraft->getAircraftInfo(aircraftinfo);
        if (aircraftinfo.FlightTime > 11)
        {
            a = 1;
        }
        if (aircraftinfo.FlightTime > 15.006)
        {
            a = 2;
            Vel = Aircraft->getSysState()->Velocity;
            Aircraft->e_theta += Aircraft->getTimeStep() * (Vel[1] - 5.0 / 180.0 * pi);
        }
        if (aircraftinfo.Position[1] > 25000)
        {
            *(AircarftFileOutObj) << (*Aircraft) << endl;
            break;
        }
    }

    system("pause");
    return 0;
}
