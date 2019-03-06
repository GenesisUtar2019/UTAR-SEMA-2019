#define High_SideA 9
#define High_SideB 10
#define High_SideC 11
#define Low_SideA 5
#define Low_SideB 6
#define Low_SideC 7



int HallState1=0; //Variables for the three hall sensors (3,2,1)
int HallState2=0;
int HallState3=0;
int Hall_AN1;
int Hall_AN2;
int Hall_AN3;
int HallVal = 1; //binary value of all 3 hall sensors

int mSpeed = 0; //speed level of the motor
int bSpeed = 0; //braking level
int throttle = 0; //this variable is used with analog in to measure the position of the throttle potentiometer

int Hall_Flag=0;
int Hall_Previous=0;
int Hall_Pre_Init=0;
int Enable_Pin;

//@@@@@@@@@@@@@@@@@@@@
void setup() {

// Outputs for the  Motor Driver
  pinMode(High_SideA,OUTPUT);   // 
  pinMode(High_SideB,OUTPUT);  // 
  pinMode(High_SideC,OUTPUT);  //  
  pinMode(Low_SideA,OUTPUT);   //  
  pinMode(Low_SideB,OUTPUT);   // 
  pinMode(Low_SideC,OUTPUT);   //     

  Serial.begin(9600);

  
  // Set PWM for pins 9,10 to 32 kHz
  //First clear all three prescaler bits:
  int prescalerVal = 0x07; //create a variable called prescalerVal and set it equal to the binary number "00000111"                                                                                               number "00000111"
  TCCR1B &= ~prescalerVal; //AND the value in TCCR0B with binary number "11111000"

  //Now set the appropriate prescaler bits:
  int prescalerVal2 = 1; //set prescalerVal equal to binary number "00000001"
  TCCR1B |= prescalerVal2; //OR the value in TCCR0B with binary number "00000001"
  
  // Set PWM for pins 3,11 to 32 kHz (Only pin 11 is used in this program)
  //First clear all three prescaler bits:
  TCCR2B &= ~prescalerVal; //AND the value in TCCR0B with binary number "11111000"

  //Now set the appropriate prescaler bits:
 
  TCCR2B |= prescalerVal2; //OR the value in TCCR0B with binary number "00000001"//First clear all three prescaler bits:

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void loop() {

  throttle = analogRead(0); //value of the throttle potentiometer
  mSpeed = map(throttle, 0, 1023, 0, 255); //motoring is mapped to the top half of potentiometer
  Serial.println(mSpeed );
  /*HallState1 = digitalRead(2);  // read input value from Hall 1
  HallState2  = digitalRead(3);  // read input value from Hall 2
  HallState3  = digitalRead(4);  // read input value from Hall 3*/

 Hall_AN1=analogRead(1);
 Hall_AN2=analogRead(2);
 Hall_AN3=analogRead(3);

 if(Hall_AN1>164)//if(Hall_AN1>471)
    HallState1=1;
    else if (Hall_AN1<=164)
    HallState1=0;
    
  if(Hall_AN2>164)
    HallState2=1;
    else if (Hall_AN2<=164)
    HallState2=0;

  if(Hall_AN3>164)
    HallState3=1;
    else if (Hall_AN3<=164)
    HallState3=0;

  HallVal = (4*HallState1) + (2*HallState2) + (HallState3); //Computes the binary value of the 3 Hall sensors
  
  if(Hall_Pre_Init==0)
  {
    Hall_Previous=HallVal;
    Hall_Pre_Init++;
  }
  
  if(Hall_Previous!=HallVal)
  {
      //Hall_Flag=1;*
      digitalWrite(High_SideA,0);
      digitalWrite(Low_SideA,0);
      
      digitalWrite(High_SideB,0);        
      digitalWrite(Low_SideB,0);
      
      digitalWrite(High_SideC,0);
      digitalWrite(Low_SideC,0);
      
      delayMicroseconds(5);
      Hall_Previous=HallVal;
  }

  //if(

 // if(Hall_Flag==0)
  if (throttle > 0){  
      //CW direction
      switch (HallVal) 
       {
          case 4: //100
              digitalWrite(High_SideA,0);
              digitalWrite(Low_SideA,0);
              
              digitalWrite(High_SideB,0);
              digitalWrite(Low_SideB,1);
              
              analogWrite(High_SideC,mSpeed);
              digitalWrite(Low_SideC,0);
              
              break;
              
          case 5: //101
              digitalWrite(High_SideA,0);
              digitalWrite(Low_SideA,1);
              
              digitalWrite(High_SideB,0);
              digitalWrite(Low_SideB,0);
              
              analogWrite(High_SideC,mSpeed);
              digitalWrite(Low_SideC,0);
              break;

          case 1: //001
              digitalWrite(High_SideA,0);
              digitalWrite(Low_SideA,1);
              
              analogWrite(High_SideB,mSpeed);
              digitalWrite(Low_SideB,0);
              
              digitalWrite(High_SideC,0);
              digitalWrite(Low_SideC,0);
              break;
         
          case 3: //011
              digitalWrite(High_SideA,0);
              digitalWrite(Low_SideA,0);
              
              analogWrite(High_SideB,mSpeed);
              digitalWrite(Low_SideB,0);
              
              digitalWrite(High_SideC,0);
              digitalWrite(Low_SideC,1);
              break;
              
          case 2: //010
              analogWrite(High_SideA,mSpeed);
              digitalWrite(Low_SideA,0);
              
              digitalWrite(High_SideB,0);
              digitalWrite(Low_SideB,0);
              
              digitalWrite(High_SideC,0);
              digitalWrite(Low_SideC,1);;
              break;

            case 6: //110
              analogWrite(High_SideA,mSpeed);
              digitalWrite(Low_SideA,0);
              
              digitalWrite(High_SideB,0);
              digitalWrite(Low_SideB,1);
              
              digitalWrite(High_SideC,0);
              digitalWrite(Low_SideC,0);
              break;
              
       }  
     }
     else if (throttle<=0)
     {
      digitalWrite(High_SideA,0);
      digitalWrite(Low_SideA,0);
      
      digitalWrite(High_SideB,0);        
      digitalWrite(Low_SideB,0);
      
      digitalWrite(High_SideC,0);
      digitalWrite(Low_SideC,0);
        Hall_Pre_Init=0;
      }

     /*if (throttle > 0){  
      //CCW direction
      switch (HallVal) 
       {
          case 4: //100
              digitalWrite(Low_SideA,0);
              analogWrite(High_SideA,mSpeed);
              
              digitalWrite(Low_SideB,1);
              digitalWrite(High_SideB,0);

              digitalWrite(Low_SideC,0);
              digitalWrite(High_SideC,0);
              break;
              
          case 6: //110
              digitalWrite(Low_SideA,0);
              analogWrite(High_SideA,mSpeed);
              
              digitalWrite(Low_SideB,0);
              digitalWrite(High_SideB,0);

              digitalWrite(Low_SideC,1);
              digitalWrite(High_SideC,0);
              break;

          case 2: //010
              digitalWrite(Low_SideA,0);
              digitalWrite(High_SideA,0);
              
              digitalWrite(Low_SideB,0);
              analogWrite(High_SideB,mSpeed);

              digitalWrite(Low_SideC,1);
              digitalWrite(High_SideC,0);
              break;
         
          case 3: //011
              digitalWrite(Low_SideA,1);
              digitalWrite(High_SideA,0);
              
              digitalWrite(Low_SideB,0);
              analogWrite(High_SideB,mSpeed);

              digitalWrite(Low_SideC,0);
              digitalWrite(High_SideC,0);
              break;
              
          case 1: //001
              digitalWrite(Low_SideA,1);
              digitalWrite(High_SideA,0);
              
              digitalWrite(Low_SideB,0);
              digitalWrite(High_SideB,0);

              digitalWrite(Low_SideC,0);
              analogWrite(High_SideC,mSpeed);
              break;

            case 5: //101
              digitalWrite(Low_SideA,0);
              digitalWrite(High_SideA,0);
              
              digitalWrite(Low_SideB,1);
              digitalWrite(High_SideB,0);

              digitalWrite(Low_SideC,0);
              analogWrite(High_SideC,mSpeed);
              break;
              
       }  
     }
     else if (throttle<=0)
     {}*/
     
}
