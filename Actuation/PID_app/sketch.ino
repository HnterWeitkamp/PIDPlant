
//arrays for sensor reads and history tracking
char analogPinIn[]={A0,A1,A2,A3};
int sensorInVal[]={0,0,0,0};
int sensorHistory[4][10]={0};
bool hOutHistory[10];

//values for PID reads and writes
double avgSensorVal = 0;

void setup() 
{
//humidity sensor setup 
  for(int i=0;i<=3;i++)
    {
      pinMode(analogPin[i],INPUT);
    }

//PWM pin setup
  pinMode(3, OUTPUT);

//Humidity sensor pin setup
  pinMode (A4, OUTPUT);


  //set up serial communication for MATLAB
  serial.begin(9600);

  
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
  
//HOutHistory = HumidOnHistory(HOutHistory, 10, #);
//sensorHistory = SensorHistory(sensorHistory,10,4,sensorInVal[] )

  //set outputs for cycle






  // Kalman filter deploys info to MATLAB via serial com and reads info back

//serial.println(#whatever needs passed);
  /*
  may need to give direct sensor readings or deploy to hardware from matlab to ARM instead of through serial port
  */
//serial.read
  

  //tv app. to be inserted if time constraints allow
  delay (30000)
  
}
