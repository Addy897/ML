#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"
#include "output.h"
#define n 800
#define num_weights 8
double weigths[num_weights];
double bias[num_weights];
double gradientDescentWeight(int index)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        double y = 0;
        for (int j = 0; j < num_weights; j++)
            y += ((X[i][j] * weigths[j] + bias[j]));
        sum += (Y[i] - y) * X[i][index];
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
            y += ((X[i][j] * weigths[j] + bias[j]));
        sum += (Y[i] - y);
    }
    sum = sum * (-2.0 / n);
    return sum;
}
double loss()
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        double y = 0;
        for (int j = 0; j < num_weights; j++)
            y += ((X[i][j] * weigths[j] + bias[j]));
        y -= Y[i];
        sum += y * y;
    }
    return sum / n;
}
void clipGradients(double *gradients, double max_norm)
{
    double total_norm = 0;
    for (int i = 0; i < num_weights; i++)
    {
        total_norm += gradients[i] * gradients[i];
    }
    total_norm = sqrt(total_norm);
    if (total_norm > max_norm)
    {
        double clip_factor = max_norm / total_norm;
        for (int i = 0; i < num_weights; i++)
        {
            gradients[i] *= clip_factor;
        }
    }
}
void initBW()
{
    for (int i = 0; i < num_weights; i++)
    {
        weigths[i] = 0;
        bias[i] = 0;
    }
}
int main(int argc, char const *argv[])
{
    initBW();
    double lr = 1e-2;
    double max_gradient_norm = 1e-5;

    int epoch = 10e5;
    double ls = loss();

    printf("loss after %d iterations = %f\n",0, ls);
    for (int i = 0; i < epoch; i++)
    {
        double dbs[num_weights];
        double dws[num_weights];
        double db = gradientDescentBias() * lr;
        for (int j = 0; j < num_weights; j++)
        {
            double dw1 = gradientDescentWeight(j) * lr;

            dbs[j] = db;
            dws[j] = dw1;
        }
        clipGradients(dws, max_gradient_norm);
        clipGradients(dbs, max_gradient_norm);
        for (int j = 0; j < num_weights; j++)
        {
            weigths[j] -= dws[j];
            bias[j] -= dbs[j];
        }
            
    }
    for (int j = 0; j < num_weights; j++)
    {
        printf("w%d = %f b%d = %f\t", j + 1, weigths[j], j + 1, bias[j]);
    }
    ls = loss();

    printf("\nloss after %d iterations = %f\n",epoch, ls);
    
    for(int j=290;j<299;j++){
        double py=0;
        for (size_t i = 0; i < num_weights; i++)
        {
            py+=X[j][i]*weigths[i]+bias[i];
        }
        printf("Orginal Value: %f\tPredicted Value: %f\n",Y[j],py);
    }

    return 0;
}
