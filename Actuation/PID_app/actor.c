#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <DHT.h>
#include <Python.h>
#include <wiringPi.h>
#include <stdint.h>
#include <softPwm.h>
#include "function.h"
//pin definitions
#define sens1 1
#define sens2 2
#define sens3 3
#define sens4 4
#define humo 5
#define fanpwm 6

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


int read_dht22(int pin) {
    uint8_t lastState = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    // Send start signal
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18); // 18 ms low
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    // Read the data
    for (i = 0; i < MAX_TIMINGS; i++) {
        counter = 0;
        while (digitalRead(pin) == lastState) {
            counter++;
            delayMicroseconds(1);
            if (counter == 255) break;
        }
        lastState = digitalRead(pin);

        if (counter == 255) break;

        // Ignore first 3 transitions
        if ((i >= 4) && (i % 2 == 0)) {
            data[j / 8] <<= 1;
            if (counter > 50) data[j / 8] |= 1;
            j++;
        }
    }

    // Verify checksum
    if ((j >= 40) &&
        (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))) {
        return 1; // Success
    }
    return 0; // Failure
}


//changes to Pi platform will change everything






FILE *file *filer;

   int main (void)
  { 
    srand((unsigned)time(NULL));

    PID_Controller pid;
    PID_Init(&pid, 2.0, 0.5, 1.0, -100.0, 100.0); // Tune gains for your system

    double setpoint = 50.0; // Desired humidity (%)
    double dt = 30.0;        // Loop time in seconds

//values for PID reads and writes
double avgSensorVal = 0;

  file = fopen("history.csv", w);
  filer = fopen("history.csv", rw);


 

//setup
wiringPiSetupGpio();
double humidity;
double controlSignal;
double temprature;
pinMode(sens1, INPUT);
pinMode(sens2, INPUT);
pinMode(sens3, INPUT);
pinMode(sens4, INPUT);

pinMode(humo, OUTPUT);
pinMode(fanpwm,OUTPUT);
softPwmCreate(fanpwm, 1000);

int sensor[]={sens1,sens2,sens3,sens4};
double sensorinVal[]={0, 0, 0, 0};
int sensorHistory[4][10]={0};
int hOutHistory[10];
double data[5] = {0, 0, 0, 0, 0};
while()
{
      //reads analog sensor inputs
  for(int i=0;i<=3;i++)
    {
      sensorInVal[i] = digitalRead(sensor[i]);
      avgSensorVal +=  sensorInVal[i];
    

  read_dht22(sensorInVal[i]);
             humidity = data[0] * 256 + data[1];
            humidity /= 10;
             temperature = (data[2] & 0x7F) * 256 + data[3];
            temperature /= 10.0;

    }
  
  avgSensorVal /= 4;
  // start of PID section

         humidity = readHumiditySensor(sensorInVal);
         controlSignal = PID_Compute(&pid, setpoint, humidity, dt);
        
  

  //start of history updates section
  
HOutHistory = HumidOnHistory(HOutHistory, 10,hOuthistory[] );
sensorHistory = SensorHistory(sensorHistory,10,4,sensorInVal[] );


for(int i=0;i<10, i++)
{
  fprintf(file, "\n humid on?: %d, sensor vals: %f", hOutHitsory[i], sensorHistory[i]);
  fclose(file);
  for (int j=0;j<4;j++)
  {
    fprintf(filer, "%d ", sensorHistory[i][j]);
    fclose(filer);
  }
}

  //set outputs for cycle

  if(controlSignal)
  {
    digitalWrite(humo, HIGH);

    digitalWrite(fanpwm, HIGH);

    delay(5);
    digitalWrite(humo,LOW);

  }
  else
  {
    softPwmWrite(fanpwm, 500);
    delay(10);
    softPwmWrite(fanpwm, 0);
  }





  // Kalman filter 


  

 // Simulate wait for next cycle
        struct timespec ts = { (time_t)dt, 0 };
        nanosleep(&ts, NULL);
}
return 0;
}