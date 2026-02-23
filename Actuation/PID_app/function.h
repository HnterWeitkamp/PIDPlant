#ifndef FILES
#define FILES
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

void waitUntil()
{

}


#endif


