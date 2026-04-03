#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
double readHumiditySensor() {
    // In real application, replace with actual sensor reading
    static double humidity = 45.0;
    humidity += ((rand() % 100) / 100.0 - 0.5); // simulate noise
    return humidity;
}

// Simulated actuator control (replace with real hardware control)
void controlHumidifier(double controlSignal) {
    printf("Actuator control signal: %.2f\n", controlSignal);
}

int main() {
    srand((unsigned)time(NULL));

    PID_Controller pid;
    PID_Init(&pid, 2.0, 0.5, 1.0, -100.0, 100.0); // Tune gains for your system

    double setpoint = 50.0; // Desired humidity (%)
    double dt = 1.0;        // Loop time in seconds

    for (int i = 0; i < 30; i++) { // Simulate 30 control cycles
        double humidity = readHumiditySensor();
        double controlSignal = PID_Compute(&pid, setpoint, humidity, dt);

       // printf("Time %2d | Humidity: %.2f%% | Control: %.2f\n", i + 1, humidity, controlSignal);
        controlHumidifier(controlSignal);

        // Simulate wait for next cycle
        struct timespec ts = { (time_t)dt, 0 };
        nanosleep(&ts, NULL);
    }

    return 0;
}


