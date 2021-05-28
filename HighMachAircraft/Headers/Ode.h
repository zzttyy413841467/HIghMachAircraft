#ifndef ODE_H_
#define ODE_H_

#include "Vector.h"

template <class Object>
class ODEAlgorithm
{
public:
    ODEAlgorithm() {}
    virtual ~ODEAlgorithm() {}
    virtual void ODEstep(vec &InOutStateVec, double t, Object &PropagateFunc, double dt) = 0;
};

template <class Object>
class RungeKutta4 : public ODEAlgorithm<Object>
{
public:
    RungeKutta4() {}
    virtual ~RungeKutta4() {}
    virtual void ODEstep(vec &InOutStateVec, double t, Object &PropagateFunc, double dt);
};

template <class Object>
class Euler : public ODEAlgorithm<Object>
{
public:
    Euler() {}
    virtual ~Euler() {}
    virtual void ODEstep(vec &InOutStateVec, double t, Object &PropagateFunc, double dt);
};

template <class Object>
class RungeKutta2 : public ODEAlgorithm<Object>
{
public:
    RungeKutta2() {}
    virtual ~RungeKutta2() {}
    virtual void ODEstep(vec &InOutStateVec, double t, Object &PropagateFunc, double dt);
};

template <class Object>
void RungeKutta4<Object>::ODEstep(vec &InOutStateVec, double t, Object &PropagateFunc, double dt)
{
    int n = InOutStateVec.size();
    vec ytmp(n, 0.0);
    vec k(n, 0.0);
    vec yout(n, 0.0);

    yout = InOutStateVec;
    ytmp = InOutStateVec;

    k = PropagateFunc(t, ytmp);
    yout = yout + (dt / 6) * k;
    ytmp = InOutStateVec + 0.5 * dt * k;

    k = PropagateFunc(t + 0.5 * dt, ytmp);
    yout = yout + (dt / 3) * k;
    ytmp = InOutStateVec + 0.5 * dt * k;

    k = PropagateFunc(t + 0.5 * dt, ytmp);
    yout = yout + (dt / 3) * k;
    ytmp = InOutStateVec + dt * k;

    k = PropagateFunc(t + dt, ytmp);
    yout = yout + (dt / 6) * k;
    InOutStateVec = yout;
}

template <class Object>
void Euler<Object>::ODEstep(vec &InOutStateVec, double t, Object &PropagateFunc, double dt)
{
    int n = InOutStateVec.size();

    InOutStateVec = InOutStateVec + dt * PropagateFunc(t, InOutStateVec);
}

template <class Object>
void RungeKutta2<Object>::ODEstep(vec &InOutStateVec, double t, Object &PropagateFunc, double dt)
{
    int n = InOutStateVec.size();
    vec ytmp(n, 0);
    vec k(n, 0);
    ytmp = InOutStateVec;

    k = PropagateFunc(t, ytmp);
    ytmp = InOutStateVec + 0.5 * dt * k;

    k = PropagateFunc(t + 0.5 * dt, ytmp);
    InOutStateVec = InOutStateVec + dt * k;
}

#endif