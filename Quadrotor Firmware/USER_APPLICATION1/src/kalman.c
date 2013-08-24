#include "kalman.h"

void updateKalman(double newxangle, double newyangle, double newxrate, double newyrate)
{
	xrate = newxrate - xbias;
	yrate = newyrate - ybias;
	xangle += dt * xrate;
	yangle += dt * yrate;
	
	P00x += dt * (dt*P11x - P01x - P10x + Q_angle);
	P01x -= dt * P11x;
	P10x -= dt * P11x;
	P11x += Q_gyroBias * dt;
	
	P00y += dt * (dt*P11y - P01y - P10y + Q_angle);
	P01y -= dt * P11y;
	P10y -= dt * P11y;
	P11y += Q_gyroBias * dt;
	
	xinno = newxangle - xangle;
	yinno = newyangle - yangle;
	
	Sx = P00x + R_angle;
	Sy = P00y + R_angle;
	
	K0x = P00x / Sx;
	K1x = P10x / Sx;
	K0y = P00y / Sy;
	K1y = P10y / Sy;
	
	xangle += K0x * xinno;
	xbias += K1x * xinno;
	yangle += K0y * yinno;
	ybias += K1y * yinno;
	
	P00x -= K0x * P00x;
	P01x -= K0x * P01x;
	P10x -= K1x * P00x;
	P11x -= K1x * P01x;
	
	P00y -= K0y * P00y;
	P01y -= K0y * P01y;
	P10y -= K1y * P00y;
	P11y -= K1y * P01y;
	
	
}