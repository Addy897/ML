#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>



#define n 16
#define num_weights 1
//Hours Of Study
double X[16][num_weights]={
    {0},{8},{6},{8},{1.5},{2},{4},{6},{7},{1},{2},{1},{2},{5},{6},{9}
};
// Result
double Y[16]={
    0,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1
};

double weigths[num_weights];
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
            y += ((X[i][j] * weigths[j] + bias[j]));
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
            y += ((X[i][j] * weigths[j] + bias[j]));
        sum += (Y[i] - sig(y));
    }
    sum = sum * (-2.0 / n);
    return sum;
}
double predict(double x[num_weights]){
    double y=0;
    for (int i = 0; i < num_weights; i++)
    {
        y+=x[i]*weigths[i]+bias[i];
    }
    
    return sig(y);
}
double accuracy() {
    int correct = 0;
    double threshold = 1e-2;
    for (int i = 0; i < n; i++) {
        if ((Y[i]-predict(X[i]))<threshold) {
            correct++;
        }
    }
    
    return ((double)correct / n) * 100;
}
double loss()
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double y = 0;
        for (int j = 0; j < num_weights; j++)
            y += ((X[i][j] * weigths[j] + bias[j]));
        if(Y[i]==0){
        sum += -log(1-sig(y));
        }else{
            sum+=-log(sig(y));
        }
    }
    
    return sum / n;
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
    double lr = 1e-1;

    int epoch = 10000;
    
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
    double ls = loss();

    
    
    for(int j=0;j<13;j++){
     
        double py=predict(X[j]);
        printf("Orginal Value: %f\tPredicted Value: %f\n",Y[j],py);
    }
    printf("\nloss after %d iterations = %f\n",epoch, ls);
    printf("accuracy after %d iterations = %f\n",epoch, accuracy());

    //Hours Of Study
    double in[][1]={2,12,1.5,5.5};
        for(int j=0;j<4;j++){
            double py=predict(in[j]);
            printf("Hourse Of Study: %f\tPredicted Result: %f\n",in[j][0],py);
        }
   

    return 0;
}
