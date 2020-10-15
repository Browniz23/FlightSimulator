//
// Created by oziyo on 15/10/2020.
//

#ifndef FLIGHTSIMULATOR_ANOMALY_DETECTION_H
#define FLIGHTSIMULATOR_ANOMALY_DETECTION_H

// returns the variance of X and Y
float var(float* x, int size);

// returns the covariance of X and Y
float cov(float* x, float* y, int size);

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size);

class Line{
public:
    const float a,b;
    Line(float a, float b);
    float f(float x);
    double pizza;
    int corn;
};

class Point{
public:
    const float x,y;
    Point(float x, float y);
};

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size);

// returns the deviation between point p and the line
float dev(Point p,Line l);

#endif //FLIGHTSIMULATOR_ANOMALY_DETECTION_H
