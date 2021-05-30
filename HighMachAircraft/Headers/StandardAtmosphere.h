#ifndef STANDARDATMOSPHERE_H_
#define STANDARDATMOSPHERE_H_

class StandardAtmosphere
{
private:
    //高度限制
    static double h_restrict(double h);
    //高度情况定义
    static int h_case(double h);
    //位势高度
    static double getH(double h);

    const static double R0;     //地球半径
    const static double p_sl;   //海平面大气压
    const static double rho_sl; //海平面大气密度
    const static double g0;     //海平面重力加速度

public:
    StandardAtmosphere(/* args */);
    ~StandardAtmosphere();

    //计算温度
    static double getT(double h);
    //计算大气压
    static double getp(double h);
    //计算密度
    static double getrho(double h);
    //计算声速
    static double geta(double h);
    //计算g
    static double getg(double h);
};

StandardAtmosphere::StandardAtmosphere(/* args */)
{
}

StandardAtmosphere::~StandardAtmosphere()
{
}

#endif