#include "StandardAtmosphere.h"
#include <cmath>

const double StandardAtmosphere::R0 = 6371000;
const double StandardAtmosphere::p_sl = 101325;
const double StandardAtmosphere::rho_sl = 1.225;
const double StandardAtmosphere::g0 = 9.8;

StandardAtmosphere::StandardAtmosphere(/* args */)
{
}

StandardAtmosphere::~StandardAtmosphere()
{
}

double StandardAtmosphere::h_restrict(double h)
{
    if (h < 0)
    {
        return 0;
    }
    else if (h > 91)
    {
        return 91;
    }
    else
    {
        return h;
    }
}

int StandardAtmosphere::h_case(double h)
{
    h = h_restrict(h);
    if (0 <= h && h <= 11.0191)
    {
        return 1;
    }
    else if (h <= 20.0631)
    {
        return 2;
    }
    else if (h <= 32.1619)
    {
        return 3;
    }
    else if (h <= 47.3501)
    {
        return 4;
    }
    else if (h <= 51.4125)
    {
        return 5;
    }
    else if (h <= 71.8020)
    {
        return 6;
    }
    else if (h <= 86.0)
    {
        return 7;
    }
    else
    {
        return 8;
    }
}

double StandardAtmosphere::getH(double h)
{
    h = h_restrict(h);
    return h / (1 + h / R0);
}

double StandardAtmosphere::getT(double h)
{
    h = h_restrict(h);
    double H = getH(h);
    double W, T;
    switch (h_case(h))
    {
    case 1:
        W = 1 - H / 44.3308;
        T = 288.15 * W;
        break;
    case 2:
        T = 216.65;
        break;
    case 3:
        W = 1 + (H - 24.9021) / 221.552;
        T = 221.552 * W;
        break;
    case 4:
        W = 1 + (H - 39.7499) / 84.4107;
        T = 250.35 * W;
        break;
    case 5:
        W = exp((48.6252 - H) / 7.9223);
        T = 270.650 * W;
        break;
    case 6:
        W = 1 - (H - 59.439) / 88.2218;
        T = 270.021 * W;
        break;
    case 7:
        W = 1 - (H - 78.0303) / 100.295;
        T = 200.5901 * W;
        break;
    case 8:
        W = exp((87.2818 - H) / 5.47);
        T = 186.87 * W;
    }
    return T;
}

double StandardAtmosphere::getp(double h)
{
    h = h_restrict(h);
    double H = getH(h);
    double W, p;
    switch (h_case(h))
    {
    case 1:
        W = 1 - H / 44.3308;
        p = p_sl * pow(W, 5.2559);
        break;
    case 2:
        W = exp((14.9647 - H) / 6.3416);
        p = p_sl * 1.1953e-1 * W;
        break;
    case 3:
        W = 1 + (H - 24.9021) / 221.552;
        p = p_sl * 2.5158e-2 * pow(W, -34.1629);
        break;
    case 4:
        W = 1 + (H - 39.7499) / 84.4107;
        p = p_sl * 2.8338e-3 * pow(W, -12.2011);
        break;
    case 5:
        W = exp((48.6252 - H) / 7.9223);
        p = p_sl * 8.9155e-4 * W;
        break;
    case 6:
        W = 1 - (H - 59.439) / 88.2218;
        p = p_sl * 2.1671e-4 * pow(W, 12.2011);
        break;
    case 7:
        W = 1 - (H - 78.0303) / 100.295;
        p = p_sl * 1.2274e-5 * pow(W, 17.0816);
        break;
    case 8:
        W = exp((87.2818 - H) / 5.47);
        p = p_sl * (2.2730 + 1.042e-3 * H) * 1e-6 * W;
    }
    return p;
}

double StandardAtmosphere::getrho(double h)
{
    h = h_restrict(h);
    double H = getH(h);
    double W, rho;
    switch (h_case(h))
    {
    case 1:
        W = 1 - H / 44.3308;
        rho = rho_sl * pow(W, 4.2559);
        break;
    case 2:
        W = exp((14.9647 - H) / 6.3416);
        rho = rho_sl * 1.5895e-1 * W;
        break;
    case 3:
        W = 1 + (H - 24.9021) / 221.552;
        rho = rho_sl * 3.3722e-2 * pow(W, -35.1629);
        break;
    case 4:
        W = 1 + (H - 39.7499) / 84.4107;
        rho = rho_sl * 3.2618e-3 * pow(W, -13.2011);
        break;
    case 5:
        W = exp((48.6252 - H) / 7.9223);
        rho = rho_sl * 9.4920e-4 * W;
        break;
    case 6:
        W = 1 - (H - 59.439) / 88.2218;
        rho = rho_sl * 2.528e-4 * pow(W, 11.2011);
        break;
    case 7:
        W = 1 - (H - 78.0303) / 100.295;
        rho = rho_sl * 1.7632e-5 * pow(W, 16.0816);
        break;
    case 8:
        W = exp((87.2818 - H) / 5.47);
        rho = rho_sl * 3.6411e-6 * W;
    }
    return rho;
}

double StandardAtmosphere::geta(double h)
{
    h = h_restrict(h);
    return 20.0468 * sqrt(getT(h));
}

double StandardAtmosphere::getg(double h)
{
    h = h_restrict(h);
    return g0 * R0 * R0 / (R0 + h) / (R0 + h);
}