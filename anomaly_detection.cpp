//
// Created by oziyo on 15/10/2020.
//
#include <iostream>
#include "anomaly_detection.h"

// returns the variance of X and Y
float var(float* x, int size);

// returns the covariance of X and Y
float cov(float* x, float* y, int size);

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size);


Line::Line(float a, float b):a(a),b(b){}
float Line::f(float x){
    return a*x+b;
}

Point::Point(float x, float y):x(x),y(x){}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size);

// returns the deviation between point p and the line
float dev(Point p,Line l);