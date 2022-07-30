# MM-Team-2

#define Rmotor 5
#define Lmotor 6
int x=0;
int y=0;
int head=0;
long int Rdistance=0;
long int Ldistance=0;

float kp=.5;
float kd=55;
float ki=.00001;

float Lspeed=150;
float Rspeed=150;

float correction;
float diffError;

void loop() {
  vlx1 = digitalRead //left sensor
  vlx2 = digitalRead //forward sensor
  vlx3 = digitalRead //right sensor
}

void heading()
{
  if(head==0)
y++;
else if(head==90||head==-270)
x++;
else if(abs(head)==180)
y--;
else if(head==270||head==-90)
x--;

}

void right()
{
  while(Ldistance<1000)
  {
    analogWrite(Lmotor,150);
    analogWrite(Rmotor,0);
  }
  head=(head+90)%360;
  Rdistance=Ldistance=0;
}

void left()
{
  while(Rdistance<1000)
  {
    analogWrite(Rmotor,150);
    analogWrite(Lmotor,0);
  }
  head=(head-90)%360;
  Rdistance=Ldistance=0
}

void forward()
{
  while(Rdistance<1000){
  milliNew=millis();

diffError=Rdistance-Ldistance;

correction = getCorrection(diffError);

Rspeed=Rspeed+correction;
Lspeed=Lspeed-correction;

heading();

analogWrite(Rmotor,Rspeed);
analogWrite(Lmotor,Lspeed);

delay(100);
  }
  Rdistance=Ldistance=0;
}

float getCorrection(float diffError)
{
float correction;
  
float milliOld;
float dt;

float diffTarget=0;
float diffErrorOld;
float diffErrorChange;
float diffErrorSlope=0;
float diffErrorArea=0;
milliOld=milliNew;
milliNew=millis();
dt=milliNew-milliOld;

diffErrorOld=diffError;
diffErrorChange=diffError-diffErrorOld;
diffErrorSlope=diffErrorChange/dt;
diffErrorArea=diffErrorArea+diffError*dt; //error integral
correction=kp*diffError+kd*diffErrorSlope+ki*diffErrorArea;

return correction;
}

void reading ()
{

  if (vlx1 == LOW && vlx2 == HIGH && vlx3 == LOW)//Straight path or using pid
    {
     Forward();
    }

  if (vlx1 == HIGH && vlx2 == LOW && vlx3 == LOW)//Left turn or using pid
    {
     Left();

    }

  if (vlx1 == LOW && vlx2 == LOW && vlx3 == HIGH)//Right Turn or using pid
    {
      Right();

    }

  if (vlx1 == HIGH && vlx2 == LOW && vlx3 == HIGH)//T Intersection
    {
      Left(); // As left is possible
      MAZE_ARRAY[size]='L';
      size++;
    }

  if (vlx1 == HIGH && vlx2 == HIGH && vlx3 == LOW)//Left T Intersection
    {
      Left();// As Left is possible
      MAZE_ARRAY[size]='L';
      size++;
    }

  if (vlx1 == LOW && vlx2 == HIGH && vlx3 == HIGH)//Right T Tntersection
    {
     Forward();//As Straight path is possible
     MAZE_ARRAY[size]='S';
     size++;
    }

  if (vlx1 == LOW && vlx2 ==LOW && vlx3 == LOW)//Dead End
    {
     U_Turn(); //As no other direction is possible
     MAZE_ARRAY[size]='B';
     size++;
    }

  if (vlx1 == HIGH && vlx2 == HIGH && vlx3 == HIGH)//4 Lane intersection
    {
     Left(); //As no other direction is possible
     MAZE_ARRAY[size]='L';
     size++;
    }
  /* if(x=x1&&y=y1 ||x=x2 && y=y2)
    {
      MAZE_ARRAY[size]= null;
    }*/
}
void minimize_array(char MAZE_ARRAY[], int *SIZE_OF_ARRAY,int x,int y)
{
    MAZE_ARRAY[x]=MAZE_ARRAY[y];
    for(int i = y; i <= *SIZE_OF_ARRAY-2 ; i++)
      {
      MAZE_ARRAY[i]=MAZE_ARRAY[i+2];
      }
    *SIZE_OF_ARRAY=*SIZE_OF_ARRAY-2;
}

void SHORTEST_PATH(char MAZE_ARRAY[], int *SIZE_OF_ARRAY)
{
  /*
  LBL = S
  LBR = B
  LBS = R
  RBL = B
  SBL = R
  SBS = B
  LBL = S */

  char ACTION;

  for(int i = 0; i <= *SIZE_OF_ARRAY-2; i++)
    {
      ACTION = MAZE_ARRAY[i];

      if(ACTION == 'B')
        {
          if(MAZE_ARRAY[i-1]== 'L' && MAZE_ARRAY[i+1] == 'R')
            {
              MAZE_ARRAY[i] = 'B';
              minimize_array(MAZE_ARRAY,SIZE_OF_ARRAY,i-1,i);
            }

           if(MAZE_ARRAY[i-1]== 'L' && MAZE_ARRAY[i+1] == 'S')
            {
              MAZE_ARRAY[i] = 'R';
              minimize_array(MAZE_ARRAY,SIZE_OF_ARRAY,i-1,i);
            }

            if(MAZE_ARRAY[i-1]== 'R' && MAZE_ARRAY[i+1] == 'L')
            {
              MAZE_ARRAY[i] = 'B';
              minimize_array(MAZE_ARRAY,SIZE_OF_ARRAY,i-1,i);
            }

            if(MAZE_ARRAY[i-1]== 'S' && MAZE_ARRAY[i+1] == 'L')
            {
              MAZE_ARRAY[i] = 'R';
              minimize_array(MAZE_ARRAY,SIZE_OF_ARRAY,i-1,i);
            }

            if(MAZE_ARRAY[i-1]== 'S' && MAZE_ARRAY[i+1] == 'S')
            {
              MAZE_ARRAY[i] = 'B';
              minimize_array(MAZE_ARRAY,SIZE_OF_ARRAY,i-1,i);
            }

            if(MAZE_ARRAY[i-1]== 'L' && MAZE_ARRAY[i+1] == 'L')
            {
              MAZE_ARRAY[i] = 'S';
              minimize_array(MAZE_ARRAY,SIZE_OF_ARRAY,i-1,i);
            }

          i = -1;
        }

    }
}
void return_back (char MAZE_ARRAY[], int *SIZE_OF_ARRAY)
{
   for (int i=*SIZE_OF_ARRAY;i>=-1;)
    {
    if ((vlx1 == HIGH && vlx2 == HIGH && vlx3 == HIGH)||
    (vlx1 == LOW && vlx2 == HIGH && vlx3 == HIGH)||
    (vlx1 == HIGH && vlx2 == LOW && vlx3 == HIGH)||
    (vlx1 == HIGH && vlx2 == HIGH && vlx3 == LOW))
    {
      if (MAZE_ARRAY[i]=='R')
      {
        Left();
        i--;
      }
      if (MAZE_ARRAY[i]=='L')
      {
        Right();
        i--;
      }
      if (MAZE_ARRAY[i]=='S')
      {
        Forward();
        i--;
      }
      
    }
    else if (vlx1 == LOW && vlx2 == HIGH && vlx3 == LOW)//Straight path or using pid
    {
     Forward();
    }

    else if (vlx1 == HIGH && vlx2 == LOW && vlx3 == LOW)//Left turn or using pid
    {
     
      Right();
    }

    else if (vlx1 == LOW && vlx2 == LOW && vlx3 == HIGH)//Right Turn or using pid
    {
      
      Left();

    }
  }
}
void second_trail (char MAZE_ARRAY[], int *SIZE_OF_ARRAY)
{
   for (int i=0;i<=*SIZE_OF_ARRAY+1;)
    {
    if ((vlx1 == HIGH && vlx2 == HIGH && vlx3 == HIGH)||
    (vlx1 == LOW && vlx2 == HIGH && vlx3 == HIGH)||
    (vlx1 == HIGH && vlx2 == LOW && vlx3 == HIGH)||
    (vlx1 == HIGH && vlx2 == HIGH && vlx3 == LOW))
    {
      if (MAZE_ARRAY[i]=='R')
      {
        Right();
        i++;
      }
      if (MAZE_ARRAY[i]=='L')
      {
        Left();
        i++;
      }
      if (MAZE_ARRAY[i]=='S')
      {
        Forward();
        i++;
      }
      
    }
    else if (vlx1 == LOW && vlx2 == HIGH && vlx3 == LOW)//Straight path or using pid
    {
     Forward();
    }

    else if (vlx1 == HIGH && vlx2 == LOW && vlx3 == LOW)//Left turn or using pid
    {
     Left();

    }

    else if (vlx1 == LOW && vlx2 == LOW && vlx3 == HIGH)//Right Turn or using pid
    {
      Right();

    }
  }
}
/*int main() {
 // char array[]={'L', 'B', 'L', 'L', 'B', 'L', 'S', 'B', 'L', 'L', 'L', 'B','S','B', 'L','L','\0'};
  int size_array = sizeof(array)/sizeof(char)-1;
  SHORTEST_PATH(array,&size_array);
  for (int i =0 ; i<= size_array;i++)
  {
    printf("%c",array[i]);
  }
  printf("\n");


  return 0;
}*/
