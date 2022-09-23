/*************************************************************************/
/****************** Calibrate step in testing day  ***********************/
/*************************************************************************/
void testStep()
{
  int distance;
  if (FirstStep)
  {
    distance = DistanceCM(30);
    FirstStep = 0;
  }
  else
  {
    distance = DistanceCM(35);
  }

  while (pos_r != distance)
  {
    forward_step();
    //      Serial.print("yaw out");
    //      Serial.println(P.angZ);
    Serial.print(pos_l); Serial.print("\t\t"); Serial.println(pos_r);

  }
  stopModified();

  STOP();
  pos_r = 0;
  pos_l = 0;
  delay(5000);
}

/*************************************************************************/
/****************** Calibrate vlx in testing day  ************************/
/*************************************************************************/
void testMotionWithVlx()
{
  // NOT no wall

  seeVlx(&leftVlx, &centreVlx, &rightVlx);
  // two walls beside robot
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Straight path or using pid
  {
    stepNextCell();
    delay(500);
  }
  // three walls around robot
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    right_180();
  }
  //No walls
  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Right Turn or using pid
  {
    left_90();
    stepNextCell();
    delay(500);
  }
  //no wall left and no wall centre
  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    left_90();
    stepNextCell();
    delay(500);
  }
  //no wall left and no wall centre
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && !(centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    stepNextCell();
    delay(500);
  }
//no wall left 
  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && (rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    left_90();
    stepNextCell();
    delay(500);
  }
  //no wall left and no wall right
  if (!(leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    left_90();
    stepNextCell();
    delay(500);
  }
//no wall right 
  if ((leftVlx > LOWER_LEFT_VLX_VALUE && leftVlx < UPPER_LEFT_VLX_VALUE) && !(rightVlx > LOWER_RIGHT_VLX_VALUE && rightVlx < UPPER_RIGHT_VLX_VALUE)
      && (centreVlx > LOWER_FRONT_VLX_VALUE && centreVlx < UPPER_FRONT_VLX_VALUE))//Left turn or using pid
  {
    right_90();
    stepNextCell();
    delay(500);
  }  
  
}

/*************************************************************************/
/****************** Reading vlx in testing day  **************************/
/*************************************************************************/
void testReadingVlx()
{
  seeVlx(&leftVlx, &centreVlx, &rightVlx);
  Serial.print(leftVlx); Serial.print("\t\t"); Serial.print(centreVlx); Serial.print("\t\t"); Serial.println(rightVlx);
}

/*************************************************************************/
/********************* Testing Shortest Path  ****************************/
/*************************************************************************/
void testShortestPath()
{
  int path[]={'R','L','L'};

  for (int i = 0; i <= 2 ;)
  {
     if (path[i] == 'R')
      {
        right_90();
        changeHeading('r');
        stepNextCell();
        delay(500);
        updateXY();
        i++;
      }
      if (path[i] == 'L')
      {
        left_90();
        changeHeading('l');
        stepNextCell();
        delay(500);
        updateXY();
        i++;
      }
      if (path[i] == 'S')
      {
        stepNextCell();
        delay(500);
        updateXY();
        i++;
      }
      Serial.print('(');Serial.print(x);Serial.print('(');Serial.print(y);Serial.println(')');
  }
  STOP();
  delay(10000);
}
