#ifndef FLIGHTCONTROLLER_H_
#define FLIGHTCONTROLLER_H_

#include "Vector.h"
#include "AircraftBase.h"
#include "DataStructDef.h"

class AircraftModel;
class Guidance;

class FirstGuidance;
class SecondGuidance;
class ThirdGuidance;

class FlightController : public AircraftBase
{
public:
    FlightController();
    FlightController(AircraftModel* pObj);
    ~FlightController();

    void Initial();
    void UpdateState(double timeCur, AircraftModel* pAirObject);
    void UpdateOutput(double timeCur, AircraftModel* pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel* pAirObject);

    Guidance* getGuidance() { return guidance; }

    void getFileOutputItemName(vector<string>& FileOutItemName);
    friend ostream& operator<<(ostream& os, const FlightController& pObj);

private:
    AircraftModel* pAirObj;
    Guidance* guidance;
    vector<AircraftBase*> FlightControllerModels;
};

class Guidance : public AircraftBase
{
public:
    Guidance();
    Guidance(AircraftModel* pObj);

    ~Guidance();
    void Initial();
    void UpdateState(double timeCur, AircraftModel* pAirObject);
    void UpdateOutput(double timeCur, AircraftModel* pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel* pAirObject);

    void UpdateGuidancePhase(double timeCur, AircraftModel* pAirObject);

    FirstGuidance* getFirstGuidance() { return firstGuidance; }
    SecondGuidance* getSecondGuidance() { return secondGuidance; }
    ThirdGuidance* getThirdGuidance() { return thirdGuidance; }

    vec getCommand() const { return command; }
    int getGuidancePhase() const { return GuidancePhase; }

    void getFileOutputItemName(vector<string>& FileOutItemName);
    friend ostream& operator<<(ostream& os, const Guidance& pObj);

private:
    AircraftModel* pAirObj;
    int GuidancePhase;
    FirstGuidance* firstGuidance;
    SecondGuidance* secondGuidance;
    ThirdGuidance* thirdGuidance;
    vector<AircraftBase*> GuidanceModels;
    vec command;
};

class FirstGuidance : public AircraftBase
{
public:
    FirstGuidance();
    FirstGuidance(AircraftModel* pObj);
    ~FirstGuidance();

    void Initial();
    void UpdateState(double timeCur, AircraftModel* pAirObject);
    void UpdateOutput(double timeCur, AircraftModel* pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel* pAirObject);

    vec getCommand() const { return command; }

private:
    AircraftModel* pAirObj;
    vec command;
};
class SecondGuidance : public AircraftBase
{
public:
    SecondGuidance();
    SecondGuidance(AircraftModel* pObj);
    ~SecondGuidance();

    void Initial();
    void UpdateState(double timeCur, AircraftModel* pAirObject);
    void UpdateOutput(double timeCur, AircraftModel* pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel* pAirObject);

    vec getCommand() const { return command; }
    double calcuAlpha(double timeCur, AircraftModel* pAirObject);

private:
    AircraftModel* pAirObj;
    vec command;
};
class ThirdGuidance : public AircraftBase
{
public:
    ThirdGuidance();
    ThirdGuidance(AircraftModel* pObj);
    ~ThirdGuidance();

    void Initial();
    void UpdateState(double timeCur, AircraftModel* pAirObject);
    void UpdateOutput(double timeCur, AircraftModel* pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel* pAirObject);

    vec getCommand() const { return command; }
    vec calcuControl(double timeCur, AircraftModel* pAirObject);

private:
    AircraftModel* pAirObj;
    vec command;
    vec t_command;
    vec n_command;
};
#endif