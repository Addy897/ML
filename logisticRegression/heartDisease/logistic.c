#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"
#include "output.h"

#define total 297
#define n  146
#define num_weights 13
 
int seed;

double weights[num_weights];
double bias[num_weights];

double sig(double x){
    return 1/(1+exp(-x));
}
double gradientDescentWeight(int index)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        double y = 0;
        for (int j = 0; j < num_weights; j++)
            y += ((X[i][j] * weights[j] + bias[j]));
        sum += (Y[i] - sig(y)) * X[i][index];
    }
    sum = sum * (-2.0 / n);
    return sum;
}

double gradientDescentBias()
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double y = 0;
        for (int j = 0; j < num_weights; j++)
            y += ((X[i][j] * weights[j] + bias[j]));
        sum += (Y[i] - sig(y));
    }
    sum = sum * (-2.0 / n);
    return sum;
}
double predict(double x[num_weights]){
    double y=0;
    for (int i = 0; i < num_weights; i++)
    {
        y+=x[i]*weights[i]+bias[i];
    }
    
    return sig(y);
}
double accuracy() {
    int correct = 0;
    double threshold=1e-2;
    for (int i = 0; i < total; i++) {
        if ((fabs(Y[i]-predict(X[i]))<threshold)) {
            correct++;
        }
    }
    
    return ((double)correct / total) * 100;
}
double loss()
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double y = 0;
        for (int j = 0; j < num_weights; j++)
            y += ((X[i][j] * weights[j] + bias[j]));
        if(Y[i]==0){
        sum += -log(1-sig(y) + 1e-9);
        }else{
            sum+=-log(sig(y)+1e-9);
        }
    }
    
    return sum / n;
}

void initBW()
{
    seed=time(0);
    srand(seed);
    for (int i = 0; i < num_weights; i++)
    {
        weights[i] = 0;
        bias[i] = rand()%10;
    }
}
int main(int argc, char const *argv[])
{
    initBW();
    double lr = 5e-2;

    int epoch = 1e5;
    
    for (int i = 0; i < epoch; i++)
    {
        double dws[num_weights];
        double db = gradientDescentBias() * lr;

        for (int j = 0; j < num_weights; j++)
        {
            double dw1 = gradientDescentWeight(j) * lr;
            dws[j] = dw1;
        }
        for (int j = 0; j < num_weights; j++)
        {
            weights[j] -= dws[j];
            bias[j] -= db;
        }
            
    }
    for (int j = 0; j < num_weights; j++)
    {
        printf("w%d = %f b%d = %f\n", j + 1, weights[j], j + 1, bias[j]);
    }
    double ls = loss();

    
    // Untrained Data
    for(int j=total-10;j<total;j++){
     
        double py=predict(X[j]);
        printf("Orginal Value: %f\tPredicted Value: %f\n",Y[j],py);
    }

    printf("\nloss after %d iterations = %f\n",epoch, ls);
    printf("Total accuracy = %f\nSeed = %d", accuracy(),seed);

    
   

    return 0;
}
