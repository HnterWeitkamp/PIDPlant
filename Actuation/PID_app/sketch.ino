/*
This code is a main sketch for local operations on the ardiuno uno q with sensor inputs and outputs
there is a digital PID and kalman filter to assist in updates and calculations as well
all outputs will be stored in a .csv file that will communicate with the UI which will grab the values
*/


//arrays for sensor reads and history tracking
#include <DHT.h>
#include "function.h"
//changes to Pi platform will change everything here
char analogPinIn[]={A0,A1,A2,A3};
int sensorInVal[]={0,0,0,0};
int sensorHistory[4][10]={0};
bool hOutHistory[10];
FILE *file *filerw;

//values for PID reads and writes
double avgSensorVal = 0;

void setup() 
{
  file = fopen("history.csv", w);
  file = fopen("history.csv", rw);
//humidity sensor setup 
  for(int i=0;i<=3;i++)
    {
      pinMode(analogPin[i],INPUT);
    }

//PWM pin setup
  pinMode(3, OUTPUT);

//Humidity sensor pin setup
  pinMode (A4, OUTPUT);


  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //reads analog sensor inputs
  for(int i=0;i<=3;i++)
    {
      sensorInVal[i] = analogRead(analogPin[i]);
      avgSensorVal += (double) sensorInVal[i];
    }
  
  avgSensorVal /= 4;
  // start of PID section




  //start of history updates section
  
HOutHistory = HumidOnHistory(HOutHistory, 10,hOuthistory[] );
sensorHistory = SensorHistory(sensorHistory,10,4,sensorInVal[] );


for(int i=0;i<10, i++)
{
  fprintf(file, "\n humid on?: %d, sensor vals: ", hOutHitsory[i]);
  fclose();
  for (int j=0;j<4;j++)
  {
    fprintf(filerw, "%d ", sensorHistory[i][j]);
    fclose();
  }
}

  //set outputs for cycle






  // Kalman filter 


  

  //tv app. to be inserted if time constraints allow
  delay (30000)
  
}
