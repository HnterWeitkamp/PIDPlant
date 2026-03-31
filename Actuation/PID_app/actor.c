#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <DHT.h>
#include "function.h"

// PID structure
typedef struct {
    double Kp;       // Proportional gain
    double Ki;       // Integral gain
    double Kd;       // Derivative gain
    double prevError;
    double integral;
    double outputMin; // Output lower limit
    double outputMax; // Output upper limit
} PID_Controller;




//changes to Pi platform will change everything here

int sensorInVal[]={0,0,0,0};
int sensorHistory[4][10]={0};
bool hOutHistory[10];
FILE *file *filerw;

//values for PID reads and writes
double avgSensorVal = 0;

  file = fopen("history.csv", w);
  filer = fopen("history.csv", rw);


  int main (void)
  {

//setup
wiringpigpio();
char PinIn[]={0,1,2,3};



while()
{
      //reads analog sensor inputs
  for(int i=0;i<=3;i++)
    {
      sensorInVal[i] = analogRead(analogPin[i]);
      avgSensorVal += (double) sensorInVal[i];
    }
  
  avgSensorVal /= 4;
  // start of PID section


    srand((unsigned)time(NULL));

    PID_Controller pid;
    PID_Init(&pid, 2.0, 0.5, 1.0, -100.0, 100.0); // Tune gains for your system

    double setpoint = 50.0; // Desired humidity (%)
    double dt = 1.0;        // Loop time in seconds

   /* for (int i = 0; i < 30; i++) { // Simulate 30 control cycles
        double humidity = readHumiditySensor();
        double controlSignal = PID_Compute(&pid, setpoint, humidity, dt);
        
    }*/
        printf("Time %2d | Humidity: %.2f%% | Control: %.2f\n", i + 1, humidity, controlSignal);
                controlHumidifier(controlSignal);

  //start of history updates section
  
HOutHistory = HumidOnHistory(HOutHistory, 10,hOuthistory[] );
sensorHistory = SensorHistory(sensorHistory,10,4,sensorInVal[] );


for(int i=0;i<10, i++)
{
  fprintf(file, "\n humid on?: %d, sensor vals: ", hOutHitsory[i]);
  fclose();
  for (int j=0;j<4;j++)
  {
    fprintf(filer, "%d ", sensorHistory[i][j]);
    fclose();
  }
}

  //set outputs for cycle






  // Kalman filter 


  

 // Simulate wait for next cycle
        struct timespec ts = { (time_t)dt, 0 };
        nanosleep(&ts, NULL);
}
return 0;
}