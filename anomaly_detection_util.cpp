//
// Created by Hod Amar on 23/10/2021.
//
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

float average(float *x, int size){
    float mu = 0;
    for (int i = 0; i < size; ++i) {
        mu += x[i];
    }
    return (mu / size);
}

// returns the variance of X and Y
float var(float* x, int size){
    if (nullptr == x || size <= 0){
        ////add if size of x != size
        return 0;
    }
    float sum = 0;
    float mu = average(x, size);
    for (int i = 0; i < size; ++i) {
        sum += std:: powf((x[i] - mu), 2.0);
    }
    float var = (sum / size);
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
    float x[] = {1.0 ,2.0, 3.0, 4.0, 5.0, 6.0};
    int size = 6;
    float j = var(x, size);
    std:: cout << j;
    return 0;
}


