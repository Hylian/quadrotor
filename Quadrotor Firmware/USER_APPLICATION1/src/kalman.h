#ifndef _KALMAN_H
#define _KALMAN_H

double xrate, yrate, xangle, yangle, xbias, ybias;

const double Q_angle = 0.001;
const double Q_gyroBias = 0.003;
const double R_angle = 0.03;

void updateKalman(double newxangle, double newyangle, double newxrate, double newyrate);

#endif