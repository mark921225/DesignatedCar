/***************************************************************************/
// File			  [track.h]
// Author		  [Erik Kuo]
// Synopsis		[Code used for tracking]
// Functions  [MotorWriting, MotorInverter, tracking, backTurn, lrTurn]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 1 & 6*/
/*feel free to add your own function for convenience*/
#ifndef track.h
#define track.h
/*===========================import variable===========================*/
int tempIR = 0;// 五個IR的讀值總和
/*===========================import variable===========================*/

void MotorWriting(double vL, double vR) {
  // TODO: use TB6612 to control motor voltage & direction
  analogWrite(MotorL_PWML, vL);
  analogWrite(MotorR_PWMR, vR);
}// MotorWriting

// Handle negative motor_PWMR value.
void MotorInverter() {
  //Hint: the value of motor_PWMR must between 0~255, cannot write negative value.
  digitalWrite(MotorR_I1, 0);
  digitalWrite(MotorR_I2, 1);
  digitalWrite(MotorL_I3, 1);
  digitalWrite(MotorL_I4, 0);
  MotorWriting(_Tp, _Tp);
}// MotorInverter

void MotorMove(){
  digitalWrite(MotorR_I1, 1);
  digitalWrite(MotorR_I2, 0);
  digitalWrite(MotorL_I3, 1);
  digitalWrite(MotorL_I4, 0);
  MotorWriting(_Tp, _Tp);
}

void backTurn(){
  MotorInverter();
  holdDelay(880);
  MotorMove();
}

void lrTurn(int n){
  MotorWriting(_Tp * (1 + (n%2)*2) / 2, _Tp * (1+((n+1)%2)*2) / 2);
  holdDelay(800);
}

void motionSwitch(char nextMo){
  switch(nextMo){
      case 'S':
        MotorWriting(0, 0);
        delay(100000);
        break;
      case 'M':
        MotorWriting(_Tp, _Tp);
        holdDelay(1000);
        break;
      case 'R':
        lrTurn(0);
        break;
      case 'L':
        lrTurn(1);
        break;
      case 'B':
        backTurn();
        break;
      default:
        break;
    }
}
#endif
