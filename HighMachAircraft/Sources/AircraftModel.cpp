#include "AircraftModel.h"
#include "Airframe.h"
#include "FlightController.h"

AircraftModel::AircraftModel()
{
    t_flight = 0;
    FlightPhase = 1;
    TimeStep = 0.01;
    sysState = new SysState;
    sysStateDerivate = new SysStateDerivate;

    airframe = new Airframe(this);
    flightController = new FlightController(this);
    ode = new RungeKutta4<AircraftModel>;
    phaseChangeFlag = true;
    AircraftModels.push_back(airframe);
    AircraftModels.push_back(flightController);
}

AircraftModel::~AircraftModel()
{
    delete airframe;
    delete flightController;
    delete ode;
}

void AircraftModel::Initial()
{
    t_flight = 0;
    sysState->Position.assign(3, 0);
    sysState->Velocity.assign(3, 0);
    airframe->Initial();
    flightController->Initial();
}

void AircraftModel::UpdateState(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < AircraftModels.size(); i++)
    {
        AircraftModels[i]->UpdateState(timeCur, pAirObject);
    }
    FlightPhase = pAirObject->getFlightController()->getGuidance()->getGuidancePhase();
}

void AircraftModel::UpdateOutput(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < AircraftModels.size(); i++)
    {
        AircraftModels[i]->UpdateOutput(timeCur, pAirObject);
    }
}

void AircraftModel::UpdateDerivate(double timeCur, AircraftModel *pAirObject)
{
    for (size_t i = 0; i < AircraftModels.size(); i++)
    {
        AircraftModels[i]->UpdateDerivate(timeCur, pAirObject);
    }
}

void AircraftModel::AircraftStepOn()
{
    TimeStep = 0.01;
    double TimeStepTemp = TimeStep;

    if (phaseChangeFlag == true)
    {
        if (FlightPhase > 1)
            this->getSysState()->setm(6500);
        phaseChangeFlag = false;
    }

    if (t_flight == 0)
    {
        UpdateState(t_flight, this);
        UpdateOutput(t_flight, this);
        UpdateDerivate(t_flight, this);
    }
    vec x0 = convertSysStateToVector();
    ode->ODEstep(x0, t_flight, *this, TimeStepTemp);
    convertVectorToSysState(x0);
}

vec AircraftModel::operator()(double t, const vec &sysstate)
{
    t_flight = t;
    convertVectorToSysState(sysstate);
    UpdateState(t_flight, this);
    UpdateOutput(t_flight, this);
    UpdateDerivate(t_flight, this);
    vec derivateRtn = computeSysStateDerivate();
    return derivateRtn;
}

void AircraftModel::convertVectorToSysState(const vec &sysstate)
{
    int i = 0;
    for (int j = 0; j < sysState->Position.size(); j++, i++)
        sysState->Position[j] = sysstate[i];
    for (int j = 0; j < sysState->Velocity.size(); j++, i++)
        sysState->Velocity[j] = sysstate[i];
    sysState->m = sysstate[i];
    i++;
}

vec AircraftModel::convertSysStateToVector()
{
    vec StateRtn;
    vector<double> state;
    vec temp = sysState->Position;
    for (size_t i = 0; i < temp.size(); i++)
    {
        state.push_back(temp[i]);
    }
    temp = sysState->Velocity;
    for (size_t i = 0; i < temp.size(); i++)
    {
        state.push_back(temp[i]);
    }
    state.push_back(sysState->m);
    StateRtn = state;
    return StateRtn;
}

vec AircraftModel::computeSysStateDerivate()
{
    vec DerivateRtn;
    vector<double> derivate;
    vec temp = this->getAirframe()->getDynamics()->getPositionDerivate();
    for (size_t i = 0; i < temp.size(); i++)
    {
        derivate.push_back(temp[i]);
    }
    temp = this->getAirframe()->getDynamics()->getVelocityDerivate();
    for (size_t i = 0; i < temp.size(); i++)
    {
        derivate.push_back(temp[i]);
    }
    derivate.push_back(this->getAirframe()->getPropulsion()->getMassflow());
    DerivateRtn = derivate;
    return DerivateRtn;
}
void AircraftModel::getFileOutoutItemName(vector<string> &FileOutputItemName)
{
    FileOutputItemName.push_back("t_flight");
    airframe->getFileOutputItemName(FileOutputItemName);
    flightController->getFileOutputItemName(FileOutputItemName);
}

void AircraftModel::CreateAirObjOutputFile(ofstream &AirFileOutputObj)
{
    string Output2FilePathName;
    stringstream ss;
    ss << "../Sim/aircraft.txt";
    Output2FilePathName = ss.str();
    AirFileOutputObj.open(Output2FilePathName);

    vector<string> sd;
    getFileOutoutItemName(sd);
    for (size_t i = 0; i < sd.size(); i++)
    {
        AirFileOutputObj << sd[i] << "\t";
    }
    AirFileOutputObj << endl;
}

ostream &operator<<(ostream &os, const AircraftModel &pAirObject)
{
    os << (pAirObject.t_flight) << "\t"
       << *(pAirObject.airframe)
       << *(pAirObject.flightController);
    return os;
}