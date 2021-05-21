#pragma once

class AircraftBase
{
private:
public:
    AircraftBase() {}
    virtual ~AircraftBase() {}
    virtual void Initial() = 0;
    virtual void UpdateState() = 0;
    virtual void UpdateOutput() = 0;
    virtual void UpdateDerivate() = 0;
};