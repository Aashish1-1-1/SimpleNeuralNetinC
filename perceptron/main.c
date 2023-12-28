#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Data
#define train_count (sizeof(data)/sizeof(data[0]))
float data[][2]={
  {0,0},
  {1,2},
  {2,4},
  {3,6},
  {4,8}, 
};
//Random weight
float rand_float(){
  return ((float)rand()/(float) RAND_MAX);
}

//Calculating costFunction
float cost_func(float w){
  float result=0.0f;
  for (size_t i=0;i<train_count; ++i) {
      float x=data[i][0];
      float y=w*x;
      float d=y-data[i][1];
    //Mean square error
      result+=d*d;
  }
  result/=train_count;
  return result;
}
int main(){
  srand(69);
  float w=rand_float()*10.0f;
  float eps= 1e-3;
  float rate= 1e-3;
  //Backtracking
  for (int i=0; i<764; i++) {
      //Approxiamating the derivative 
      float dcost = (cost_func(w+eps)-cost_func(w))/eps; 
      printf("Weight:%f , Cost:%f , iteration:%d\n",w,cost_func(w),i);
    //Increases weight if first order derivative is -ve and Decreases if it is +ve
      w -= rate*dcost;
  }
  for (int i=0;i<11; ++i) {
      printf("%f*%d=%f\n",w,i,w*i);
  }
  return 0;
}
