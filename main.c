#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dim  = 2;
//int dim  = 2;
float funct ( float x,float * y, int i )
{

    if (i == 0)
        //return y[1];
        return y[1];
        //return 1;
        //return expf(x);
        //return 0;
    if (i==1)
        return y[0];
    if(i>=dim)
        printf("Gde to kosyak\n");
  //      endl;
}
void init(float* k1, float* k2, float* k3, float* y, float h, float x,float*ynext)
{
   // float yper[dim];
//    float ynext[dim];
    int i;
    for (i = 0;i<dim;i++)
    {
        k1[i] = h*funct(x,y,i);
        ynext[i] = y[i]+k1[i]/2;
    }
    for (i = 0;i<dim;i++)
    {
        k2[i] = h*funct(x+h/2,ynext,i);
        ynext[i] = y[i] - k1[i] + 2*k2[i];
    }
    for (i = 0;i<dim;i++)
    {
        k3[i] = h*funct(x+h,ynext,i);
        ynext[i] = y[i] - k1[i] + 2*k2[i];
    }
    for(i = 0;i<dim;i++)
    {
        ynext[i] = y[i] + (k1[i]+4*k2[i]+k3[i])/6;
    }
 //   return ynext;
}
void init2(float* k1, float* k2, float* k3,float*k4, float* y, float h, float x,float*ynext)
{
   // float yper[dim];
//    float ynext[dim];
    int i;
    for (i = 0;i<dim;i++)
    {
        k1[i] = h*funct(x,y,i);
        ynext[i] = y[i]+k1[i]/2;
    }
    for (i = 0;i<dim;i++)
    {
        k2[i] = h*funct(x+h/2,ynext,i);
        ynext[i] = y[i] + k2[i]/2;
    }
    for (i = 0;i<dim;i++)
    {
        k3[i] = h*funct(x+h/2,ynext,i);
        ynext[i] = y[i] + k3[i];
    }
    for(i = 0;i<dim;i++)
    {
        k4[i] = h*funct(x+h,ynext,i);
    }
    for(i = 0;i<dim;i++)
    {
        ynext[i] = y[i] + (k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
    }
 //   return ynext;
}
float* init3(float* k1, float* k2, float* k3,float*k4,float*k5, float* y, float h, float x,float*ynext)
{
   // float yper[dim];
//    float ynext[dim];
    float* E;E = (float*)malloc(sizeof(float)*dim);
    int i;
    for (i = 0;i<dim;i++)
    {
        k1[i] = h*funct(x,y,i);
        ynext[i] = y[i]+k1[i]/3;
    }
    for (i = 0;i<dim;i++)
    {
        k2[i] = h*funct(x+h/3,ynext,i);
        ynext[i] = y[i] + (k2[i]+k1[i])/6;
    }
    for (i = 0;i<dim;i++)
    {
        k3[i] = h*funct(x+h/2,ynext,i);
        ynext[i] = y[i] + k1[i]/8 + 3*k3[i]/8;
    }
    for(i = 0;i<dim;i++)
    {
        k4[i] = h*funct(x+h/2,ynext,i);
        ynext[i] = y[i]+k1[i]/2 - 3*k3[i]/2 + 2*k4[i];
    }
    for(i = 0;i<dim;i++)
    {
        k5[i] = h*funct(x+h,ynext,i);
    }
    for(i = 0;i<dim;i++)
    {
        ynext[i] = y[i] + (k1[i]+4*k4[i]+k5[i])/6;
    }
    for(i=0;i<dim;i++)
    {
        E[i] = (2*k1[i] - 9*k3[i] + 8*k4[i] - k5[i])/30;
    }

    return E;
}
int main()
{
//    float y0[dim];
    float* y0;y0 = (float*)malloc(sizeof(float)*dim);//where were we
    float* ynext;ynext = (float*)malloc(sizeof(float)*dim);//mean after h
    float* ynexth1;ynexth1 = (float*)malloc(sizeof(float)*dim);//mean after h/2
    float* ynexth2;ynexth2 = (float*)malloc(sizeof(float)*dim);//mean after h/2+h/2;
//    float y[dim];
//   float x[dim];
    float k1[dim];
    float k2[dim];
    float k3[dim];
    float k4[dim];
    float k5[dim];
    float* E;E = (float*)malloc(sizeof(float)*dim);
    float a = 0;
    float b = 1;
    float h = b-a;
    float A = a;
    float s = 0;
//    float NN = 1 - 2^(1-2);
    float NN = 0.75;
    //если init2 то NN = 0.75, если init1 то NN = 0.5 если init3 NN =
    int i;
    int steps = 0;
    int cc = 3;// 1 2 3
    float eps = 0.001;
    y0[0]=1;y0[1]=1;
 //   scanf("%d",&cc);
    switch(cc)
    {
        case(1): NN = 0.5;
        case(2): NN = 0.75;
        case(3): NN = 1 - 1/8;
    }
    do
    {
        switch( cc)
        {
        case(1):
            init(k1,k2,k3,y0,h,A,ynext);
            init(k1,k2,k3,y0,h/2,A,ynexth1);
            init(k1,k2,k3,ynexth1,h/2,A+h/2,ynexth2);
        case(2):
            init(k1,k2,k3,y0,h,A,ynext);
            init2(k1,k2,k3,k4,y0,h,A,ynexth2);
        case(3):
            init3(k1,k2,k3,k4,k5,y0,h,A,ynext);
            init3(k1,k2,k3,k4,k5,y0,h/2,A,ynexth1);
    E  = init3(k1,k2,k3,k4,k5,ynexth1,h/2,A+h/2,ynexth2);
        }


/*     init(k1,k2,k3,y0,h,A,ynext);
       init(k1,k2,k3,y0,h/2,A,ynexth1);
       init(k1,k2,k3,ynexth1,h/2,A+h/2,ynexth2);
*/
/*     init2(k1,k2,k3,k4,y0,h,A,ynext);
       init2(k1,k2,k3,k4,y0,h/2,A,ynexth1);
       init2(k1,k2,k3,k4,ynexth1,h/2,A+h/2,ynexth2);

       init3(k1,k2,k3,k4,k5,y0,h,A,ynext);
       init3(k1,k2,k3,k4,k5,y0,h/2,A,ynexth1);
       E  = init3(k1,k2,k3,k4,k5,ynexth1,h/2,A+h/2,ynexth2);
*/
/*       for(i=0;i<dim;i++)
       {
           if(ynexth2[i]-ynext[i]>s) s = ynexth2[i]-ynext[i];
       }
       s = s/NN;
*/
        for(i=0;i<dim;i++)
        {
            s = s + powf((ynext[i]-ynexth2[i]),2);
        }
        s = powf(s,0.5);
        s = s/NN;
        if(cc==3)//s считается по дркугому
        {
            s = 0;
            for(i=0;i<dim;i++)
            {
                s = s + powf(E[i],2);
            }
            s = powf(s,0.5);
            s = s/NN;
        }
   // printf("s = %f, eps  = %f \n",s,eps*h/(b-a) );
  //  getchar();
       if(s<=eps*h/(b-a))//шаг годиться
       {
           for(i=0;i<dim;i++)
           {
               y0[i] = ynexth2[i];//сдинули у
           }
           A = A + h;//сдинули х
           if(A>=b) A = b;
           h = 2*h;
           steps = steps+1;

       }
       else
       {
           y0 = y0;//остались
           A = A;
           h = h/2;
       }
       s = 0;
       //printf("A = %f\n",A);
    }while(A<b);
    for(i=0;i<dim;i++)
    {
        printf("y[%d] in point %f = %f\n", i+1,b,ynext[i]);
         printf("steps = %d\n", steps);
    }
    for(i=0;i<dim;i++)
    {
        printf("E[%d] = %f\n", i,E[i]);

    }
    getchar();
    return 0;
}
