#ifndef FILES
#define FILES
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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


//relate humidity adjustmnt to duty cycle of fan on ardiuno PWM pin
int HumidToOutputFan(double humid)
{
    double PWM = humid*255;
    return (int) PWM;
}
//return new sensor history reading array
double * SensorHistory(double *val[], int col, int row, double *newVal[])//need to pass 4 values
{
    //tweak this
    for(int i=1;i<=col;i++)
    {
        for (int j=1;j<=row;j++)
        {
            val[col*i+j-1]=val[col*i+j];
        }
       val[col*i+row] = newVal[i-1];
    }
return *val;

}
//return new updated history array
bool * HumidOnHistory(bool *state[], int count, bool *curState)
{
    for(int i=1;i<=count;i++)
    {
        state[i-1]= state[i];
    }
    state[count]=curState;
    return *state;
}


// Initialize PID
void PID_Init(PID_Controller *pid, double Kp, double Ki, double Kd, double outMin, double outMax) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->prevError = 0.0;
    pid->integral = 0.0;
    pid->outputMin = outMin;
    pid->outputMax = outMax;
}

// Compute PID output
double PID_Compute(PID_Controller *pid, double setpoint, double measured, double dt) {
    double error = setpoint - measured;

    // Integral term with anti-windup
    pid->integral += error * dt;
    if (pid->integral > pid->outputMax) pid->integral = pid->outputMax;
    else if (pid->integral < pid->outputMin) pid->integral = pid->outputMin;

    // Derivative term
    double derivative = (error - pid->prevError) / dt;

    // PID output
    double output = (pid->Kp * error) + (pid->Ki * pid->integral) + (pid->Kd * derivative);

    // Clamp output
    if (output > pid->outputMax) output = pid->outputMax;
    else if (output < pid->outputMin) output = pid->outputMin;

    pid->prevError = error;
    return output;
}

// Simulated humidity sensor (replace with real sensor read)
double readHumiditySensor(double array[]) {
    // In real application, replace with actual sensor reading
    double humidity = 45.0;
    for(int i=0;i<=3;i++)
    {
      humidity += (double) array[i];

    }
   // humidity += ((rand() % 100) / 100.0 - 0.5); // simulate noise
    return humidity/4;
}



#endif


