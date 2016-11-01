/* 

    01_Egg_Step_Sequencer  
   http://pattvira.com/egg-step-sequencer
    

*/

// The number of rows and columns of the step sequencer
int rows = 3; 
int cols = 5;

// I use the arduino mega because it has 16 analog input pins 
const int sensorPins[15] = {A0, A1, A2, A3, A4,
                            A5, A6, A7, A8, A9,
                            A10,A11,A12,A13,A14};
                            
int sensorValues[15] =     {0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0};
                       
int sensorMin[15] =        {1023, 1023, 1023, 1023, 1023,
                            1023, 1023, 1023, 1023, 1023,
                            1023, 1023, 1023, 1023, 1023};
                        
int sensorMax[15] =        {0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0};
                                                   
int mappedValues[15] =     {0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0};                            
                           
void setup() {
  // Setting up serial communication
  Serial.begin(9600);
}

void loop() {
  
  for (int i=0; i<rows*cols; i++) {
    // The analog input pins read the brightness values from the light sensors
    sensorValues[i] = analogRead(sensorPins[i]);
    
    // Calibrating the maximum and minum values from the light sensors
    if (sensorValues[i] > sensorMax[i]) {
      sensorMax[i] = sensorValues[i];
    }
    if (sensorValues[i] < sensorMin[i]) {
      sensorMin[i] = sensorValues[i];
    }
    // Mapping the values from 0-1023 to 0-255
    mappedValues[i] = map(sensorValues[i], sensorMin[i], sensorMax[i], 0, 255);
  }
  
  // Sending the values to Max MSP through serial communication
  for (int i=0; i<rows*cols-1; i++) {
    Serial.print(mappedValues[i]);
    Serial.print("  ");
  }
  Serial.println(mappedValues[rows*cols-1]);
  
  delay(100);
 
}
