//
// Created by Hod Amar on 23/10/2021.
//
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

// returns the variance of X and Y
float var(float* x, int size){
    if (nullptr == x || size <= 0){
        return 0;
    }
    float sumOfPwrx = 0;
    float mu = 0;
    for (int i = 0; i < size; ++i) {
        mu += x[i];
        sumOfPwrx += std:: powf(x[i], 2.0);
    }
    float var = (sumOfPwrx / size) - std:: powf(mu, 2.0);
    return var;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
return 0.0;
}
// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
return 0.0;
}

//
//// performs a linear regression and return s the line equation
//Line linear_reg(Point** points, int size){
//
//}
//// returns the deviation between point p and the line equation of the points
//float dev(Point p,Point** points, int size){
//
//}
//// returns the deviation between point p and the line
//float dev(Point p,Line l){
//
//}


int main(){
    float x[] = {2.0, 3.0, 4.0, 5.0};
    int size = 4;
    float j = var(x, 4);
    std:: cout << j;
    return 0;
}


