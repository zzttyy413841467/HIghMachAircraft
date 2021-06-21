#ifndef AIRFRAME_H_
#define AIRFRAME_H_

#include "Vector.h"
#include "AircraftBase.h"
#include "StandardAtmosphere.h"

class AircraftModel;
class Dynamics;
class Propulsion;
class AeroData;

class Airframe : public AircraftBase
{
public:
    Airframe();
    Airframe(AircraftModel *pObj);
    ~Airframe();

    void Initial();
    void UpdateState(double timeCur, AircraftModel *pAirObject);
    void UpdateOutput(double timeCur, AircraftModel *pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel *pAirObject);

    Dynamics *getDynamics() { return dynamics; }
    Propulsion *getPropulsion() { return propulsion; }
    AeroData *getAeroData() { return aerodata; }

    void getFileOutputItemName(vector<string> &FileOutItemName);
    friend ostream &operator<<(ostream &os, const Airframe &pObj);

private:
    AircraftModel *pAirObj;
    Dynamics *dynamics;
    Propulsion *propulsion;
    AeroData *aerodata;
    vector<AircraftBase *> AirframeModels;
};

class Dynamics : public AircraftBase
{
public:
    Dynamics();
    Dynamics(AircraftModel *pObj);
    ~Dynamics();

    void Initial();
    void UpdateState(double timeCur, AircraftModel *pAirObject);
    void UpdateOutput(double timeCur, AircraftModel *pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel *pAirObject);

    vec getPosition() const { return Position; }
    vec getVelocity() const { return Velocity; }
    vec getPositionDerivate() const { return PositionDerivate; }
    vec getVelocityDerivate() const { return VelocityDerivate; }
    double getAlpha() const { return Alpha; }
    double getBeta() const { return Beta; }
    double getSigma() const { return Sigma; }
    double getMa() const { return Ma; }
    double getG() const { return SA.getg(H / 1000); }
    double getH() const { return H; }
    double getQ() const { return Q; }
    double getVelScalar() const { return VelScalar; }
    double getrho() const { return rho; }

    vec getGravity() const { return Gravity; }
    vec getAcc() const { return m_acceleration; }

    void getFileOutputItemName(vector<string> &FileOutItemName);
    friend ostream &operator<<(ostream &os, const Dynamics &pObj);

private:
    AircraftModel *pAirObj;
    vec Position;
    vec Velocity;

    vec PositionDerivate;
    vec VelocityDerivate;

    double Alpha;
    double Beta;
    double Sigma;
    double Ma;
    double H;
    double Q;
    double rho;
    double VelScalar;
    vec AeroForce;
    vec ThrustForce;
    vec Gravity;

    double mass;
    double Sref;
    double Lref;

    vec m_Force;
    vec m_acceleration;
    StandardAtmosphere SA;
};

class Propulsion : public AircraftBase
{
public:
    Propulsion();
    Propulsion(AircraftModel *pObj);
    ~Propulsion();

    void Initial();
    void UpdateState(double timeCur, AircraftModel *pAirObject);
    void UpdateOutput(double timeCur, AircraftModel *pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel *pAirObject);

    double getMassflow() const { return massflow; }
    double getThrustTotal() const { return thrustTotal; }
    

    void getFileOutputItemName(vector<string> &FileOutItemName);
    friend ostream &operator<<(ostream &os, const Propulsion &pObj);

private:
    AircraftModel *pAirObj;

    int FlightPhase;
    double timeFlightNow;
    double massflow;
    double thrustTotal;
    int AeroStageFlag;

};

class AeroData : public AircraftBase
{
public:
    AeroData();
    AeroData(AircraftModel *pObj);
    ~AeroData();

    void Initial();
    void UpdateState(double timeCur, AircraftModel *pAirObject);
    void UpdateOutput(double timeCur, AircraftModel *pAirObject);
    void UpdateDerivate(double timeCur, AircraftModel *pAirObject);


    double getLref() const { return Lref; }
    double getSref() const { return Sref; }
    double getCl() const { return Cl; }
    double getCd() const { return Cd; }

    void getFileOutputItemName(vector<string> &FileOutItemName);
    friend ostream &operator<<(ostream &os, const AeroData &pObj);

private:
    AircraftModel *pAirObj;
    int AeroStageFlag;
    static const double Sref;
    static const double Lref;
    double Cl;
    double Cd;
};

#endif