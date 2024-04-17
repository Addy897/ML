#include <stdio.h>
#include <math.h>
#define n 19
double data[][2]={
    {24,21.54945196},
{50,47.46446305},
{15,17.21865634},
{38,36.58639803},
{87,87.28898389},
{36,32.46387493},
{12,10.78089683},
{81,80.7633986},
{25,24.61215147},
{5,6.963319071},
{16,11.23757338},
{16,13.53290206},
{24,24.60323899},
{39,39.40049976},
{54,48.43753838},
{60,61.69900319},
{26,26.92832418},
{73,70.4052055},
{29,29.34092408}
};
double gradientDescentWeight(double w,double b){
     double sum=0;
     for(int i=0;i<n;i++){
            sum+=((data[i][0]*w+b)-data[i][1])*data[i][0];
    }
    sum=sum*(2.0/n);
    return sum;
    
}
double gradientDescentBiase(double w,double b){
     double sum=0;
     for(int i=0;i<n;i++){
            sum+=((data[i][0]*w+b)-data[i][1]);
    }
    sum=sum*(2.0/n);
    return sum;
    
}
double loss(double w,double b){
    double sum=0;
     for(int i=0;i<n;i++){
           double m=((data[i][0]*w+b)-data[i][1]);
            sum+=m*m;
    }
    return sum/n;
}

int main(int argc, char const *argv[])
{
    double w=0;
    double b=0;
    //double eps=1e-4;
    double lr=1e-4;
    int epoch=1000000;
    for(int i=0;i<epoch;i++){
        double w1=gradientDescentWeight(w,b)*lr;
        double b1=gradientDescentBiase(w,b)*lr;
        w-=w1;
        b-=b1;
        
    }
    double ls=loss(w,b);
    printf("w = %f\tb = %f\tloss = %f\n",w,b,ls);
    printf("%f %f",data[12][1],data[12][0]*w+b);
    return 0;
}
