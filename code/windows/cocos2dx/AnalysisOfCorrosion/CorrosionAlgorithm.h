#pragma once

#include "CommonAlgorithm.h"

inline double cl_densityOfLinearMechanism_OneDModel(
	double m, double Cs, double Co, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b, double N,
	double k,
	double t, double x);

inline double getError_CL(double m, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b, double N,
	double k,
	double t, double pos);

inline double cl_densityOfFangmuirMechanism(
	double m, double Cs, double Co, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b,
	double Fa, double Fb,
	double t, double x);

inline double cl_densityOfLangmuirMechanism(
	double m, double Cs, double Co, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b,
	double La, double Lb,
	double t, double x);

inline double f1(double U, double R, double To, double T);
inline double f2(double H, double Hc);
inline double f3(double to, double t, double m);
inline double f4(double a, double b, double N);
inline double f5_linear(double k);
inline double f5_Fangmuir(double Fa, double Fb);
inline double f6_Langmuir(double La, double Lb);

inline double cl_densityOfLinearMechanism_OneDModel(
	double m, double Cs, double Co, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b, double N,
	double k,
	double t, double x) {

	double __f1__ = f1(U, R, To, T);
	double __f2__ = f2(H, Hc);
	double __f3__ = f3(to, t, m);
	double __f4__ = f4(a, b, N);
	double __f5__ = f5_linear(k);

	double db = MyMath::Sqrt(__f1__*__f2__*__f3__*__f4__*__f5__*Do / (1 - m));
	double db2 = 1 - MyMath::Erf(x / 2 / db);

	return Co + (Cs - Co)*db2;
}

inline double getError_CL (double m,  double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b, double N,
	double k,
	double t, double pos){
	double __f1__ = f1(U, R, To, T);
	double __f2__ = f2(H, Hc);
	double __f3__ = f3(to, t, m);
	double __f4__ = f4(a, b, N);
	double __f5__ = f5_linear(k);

	double db = MyMath::Sqrt(__f1__*__f2__*__f3__*__f4__*__f5__*Do / (1 - m));
	double db2 = MyMath::Erf(pos / 2 / db);

	return db2;
}


/*
inline double cl_densityOfFangmuirMechanism(
	double m, double Cs, double Co, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b,
	double Fa, double Fb,
	double t, double x) {

}

inline double cl_densityOfLangmuirMechanism(
	double m, double Cs, double Co, double Do, double to,
	double H, double Hc, double U, double R, double To, double T, double a, double b,
	double La, double Lb,
	double t, double x) {


}*/

inline double f1(double U, double R, double To, double T) {
	return MyMath::Exp(U / R * (1 / To - 1 / T));
}

inline double f2(double H, double Hc) {
	return 1 / (1 + MyMath::Pow((1 - H) / (1 - Hc), 4));
}

inline double f3(double to, double t, double m) {
	return MyMath::Pow(to / t, m);
}

inline double f4(double a, double b, double N) {
	double d1 = MyMath::Exp(-b * N);
	double d2 = MyMath::Exp(a - a * d1);
	return d2;
}

inline double f5_linear(double k) {
	return 1 / (1 + k);
}

/*
inline double f5_Fangmuir(double Fa, double Fb,double Cf) {
	return 0;
}

inline double f6_Langmuir(double La, double Lb, double Cf){
	return 0;
}
*/