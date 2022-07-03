# MM-Team-2
*/

#include <stdio.h>
#include <stdlib.h>
/*
void reading ()
{
  vlx1 = digitalRead //left sensor
  vlx2 = digitalRead //forward sensor
  vlx3 = digitalRead //right sensor

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
}*/
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


int main() {
  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  char array[]={'L', 'B', 'L', 'L', 'B', 'L', 'S', 'B', 'L', 'L', 'L', 'B','S','B', 'L','L','\0'};
  int size_array = sizeof(array)/sizeof(char)-1;
  SHORTEST_PATH(array,&size_array);
  for (int i =0 ; i<= size_array;i++)
  {
    printf("%c",array[i]);
  }
  printf("\n");


  return 0;
}
