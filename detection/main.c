#include <stdio.h>
#include <stdlib.h>

struct trainingdata {
  double widthheightratio;
  double lightreflectio;
};
//Declaring data globally which can be used by every func I do think oop way would be better but it's okay 
struct trainingdata human[4];
struct trainingdata car[4];
double expectedhuman=0;//0 for human 
double expectedcar=1;//1 for car
double learningrate=0.1;//learningrate




void populate(){
  FILE *file;
  file = fopen("./data/human.csv", "r");//opening data file in read mode 
  char line[100];
  int i = 0;
  while (fgets(line, sizeof(line), file) != NULL) {
    sscanf(line, "%lf,%lf", &(human[i].widthheightratio), &(human[i].lightreflectio));
    i++;
  }
  
  file = fopen("./data/car.csv","r");
  i=0;
  while (fgets(line,sizeof(line),file)!=NULL) {
    sscanf(line, "%lf,%lf",&(car[i].widthheightratio),&(car[i].lightreflectio));
    i++;
  }
  fclose(file);
}



//Generates reandom nums 0-1
float rand_float(){
  return ((float)rand()/(float) RAND_MAX);
}



float activation(double input){//activation func in this cenerio
  if(input>0.5){
    return 1.00;
  }
  else{
    return 0;
  }
}


//Model training using delta rule 
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
  printf("Finally:%f,%f\n",*w1,*w2);//final value of weight
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
 // srand(69);//random weight
  double w1=rand_float();//random weight
  double w2=rand_float();
  printf("initially:%f,%f\n",w1,w2);//initial value of weights
  trainondata(&w1,&w1);
  Showyourmoves(&w1,&w2);
}


int main(){
  populate();//populate our array of struct 
  Learn();//Learningprocess
  return 0;
}
