#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct trainingdata {
  double widthheightratio;
  double lightreflectio;
};

struct trainingdata human[4];
struct trainingdata car[4];

double expectedhuman=0;
double expectedcar=1;
double learningrate=0.1;

void populate(){
  FILE *file;
  file = fopen("human.csv", "r");
  char line[100];
  int i = 0;
  while (fgets(line, sizeof(line), file) != NULL) {
    sscanf(line, "%lf,%lf", &(human[i].widthheightratio), &(human[i].lightreflectio));
    i++;
  }
  
  file = fopen("car.csv","r");
  i=0;
  while (fgets(line,sizeof(line),file)!=NULL) {
    sscanf(line, "%lf,%lf",&(car[i].widthheightratio),&(car[i].lightreflectio));
    i++;
  }
  fclose(file);
}

float rand_float(){
  return ((float)rand()/(float) RAND_MAX);
}
float activation(double input){
  if(input>0.5){
    return 1.00;
  }
  else{
    return 0;
  }
}
void trainondata(double *w1,double *w2){
  for(int i=0;i<3;++i){
    double humanresult=*w1*human[i].widthheightratio+*w2*human[i].lightreflectio;
    double result=activation(humanresult);
    if (result!=expectedhuman) {
      int error=expectedhuman-result;
      double changeinweight1=learningrate*human[i].widthheightratio*error;
      *w1=*w1+changeinweight1;
      double changeinweight2=learningrate*human[i].lightreflectio*error;
      *w2=*w2+changeinweight2;
    }
    else{
      printf("All set\n");
    }
    
    double carresult=*w1*car[i].widthheightratio+*w2*car[i].lightreflectio;
    double result1=activation(carresult);
    if (result1!=expectedcar) {
      int error1=expectedcar-result1;
      double changeinweight1=learningrate*human[i].widthheightratio*error1;
      *w1=*w1+changeinweight1;
      double changeinweight2=learningrate*human[i].lightreflectio*error1;
      *w2=*w2+changeinweight2;
    }
    else{
      printf("All set\n");
    }
  }
  printf("Finally:%f,%f\n",*w1,*w2);
}
void Showyourmoves(double *w1,double *w2){
  double widthheight;
  double reflection;
  printf("Enter widthheightratio and lightreflection:");
  scanf("%lf%lf",&widthheight,&reflection);
  int result = activation(*w1*widthheight+*w2*reflection);
  if(result){
    printf("It is car\n");
  }
  else{
    printf("It is human\n");
  }

}
void Learn(){
  srand(time(0));
  double w1=rand_float();
  double w2=rand_float();
  printf("initially:%f,%f\n",w1,w2);
  trainondata(&w1,&w1);
  Showyourmoves(&w1,&w2);
}
int main(){
  populate();
  Learn();
  return 0;
}
