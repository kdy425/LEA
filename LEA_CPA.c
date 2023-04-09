#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

double cov(float* x, float* y, int size) {
	double Sxy = 0, Sx = 0, Sy = 0;
	int i;
	for (i = 0; i < size; i++) {
		Sxy += x[i] * y[i];  //E(xy)
		Sx += x[i];
		Sy += y[i];
	}
	//return Sxy / (double)size - (Sx / (double)size) * (Sy / (double)size); // Covariance 
	return (Sxy - Sx * Sy / (double)size) / (double)size; // Covariance 공분산


}
double corr(float* x, float* y, int size) {
	double Sxy = 0, Sx = 0, Sy = 0, Sxx = 0, Syy = 0; //var(X) = E(X ^ 2) - E(X) ^ 2 분산
	int i;
	for (i = 0; i < size; i++) {
		Sxy += x[i] * y[i];  //E(xy)
		Sx += x[i];
		Sy += y[i];
		Sxx += x[i] * x[i];
		Syy += y[i] * y[i];
	}
	return ((double)size * Sxy - Sx * Sy) / sqrt(((double)size * Sxx - Sx * Sx) * ((double)size * Syy - Sy * Sy)); //상관계수(Correlation coefficient)
}