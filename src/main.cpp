#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor DriveLHD = motor(PORT8, ratio18_1, true);

motor DriveLT = motor(PORT9, ratio18_1, false);

motor DriveLB = motor(PORT10, ratio18_1, false);

motor DriveRHD = motor(PORT3, ratio18_1, false);

motor DriveRT = motor(PORT2, ratio18_1, true);

motor DriveRB = motor(PORT1, ratio18_1, true);

motor gate = motor(PORT11, ratio18_1, false);

motor shotgunMotor = motor(PORT12, ratio18_1, false);

motor intakeMotor = motor(PORT13, ratio18_1, false);

controller Controller1 = controller(primary);
motor armMotorA = motor(PORT20, ratio18_1, false);
motor armMotorB = motor(PORT4, ratio18_1, false);
motor_group arm = motor_group(armMotorA, armMotorB);

controller Controller2 = controller(partner);


// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

// ----------------------------------------------------------------------------
//                                                                            
//    Project:                                               
//    Author:
//    Created:
//    Configuration:        
//                                                                            
// ----------------------------------------------------------------------------

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;

// Begin project code
//motor_group intakeMotors = motor_group(intakeLeft, intakeRight);

bool INTAKE_ON = false;

bool SG_FLOW = false;

bool GATE_OPEN = false;

bool INTAKE_TOGGLE = false;

//bool wheelIntake = false;
// 0 - (-60) degrees 
void open_gate(){
  gate.setVelocity(50, percent);
  gate.spinToPosition(220, degrees);
  GATE_OPEN = true;
}

void close_gate(){
  gate.setVelocity(50, percent);
  gate.spinToPosition(0, degrees);
  GATE_OPEN = false;
}

void intake_run(bool doReverse){
  intakeMotor.setVelocity(150, percent);
  intakeMotor.setMaxTorque(100, percent);

  if(doReverse){
    intakeMotor.spin(reverse);
  } else {
    intakeMotor.spin(forward);
  }

  INTAKE_ON = true;
}

void shotgun_push(bool direction){
  shotgunMotor.setVelocity(100, percent);
  if (direction){
    shotgunMotor.spin(forward);
  } else {
    shotgunMotor.spin(reverse);
  }

  SG_FLOW = true;
}

void shotgun_return(){
  SG_FLOW = false;
  
  shotgunMotor.spinToPosition(0,degrees);
}

void shotgun_stop(){
  shotgunMotor.stop();
}

void intake_stop(){
  intakeMotor.stop();
  INTAKE_ON = false;
}

void shotgunControl(){
  if (!Controller1.ButtonR2.pressing() && !Controller1.ButtonL2.pressing()){
    if (shotgunMotor.position(degrees) != 0){
      shotgun_return();
      shotgun_stop();
    }

  } else {
    if (Controller1.ButtonR2.pressing())
      shotgun_push(false);
    if (Controller1.ButtonL2.pressing())
      shotgun_push(true);
  }
}


// may need to nerf the speed if it flings up immediately
void arm_up(){
  arm.setVelocity(15, percent);
  //armMotor.setVelocity(100, percent);
  arm.spin(forward);
}

void arm_down(){
  arm.setVelocity(-15, percent);
  //armMotor.setVelocity(100, percent);
  arm.spin(forward);
}

void arm_stop() {
  arm.setStopping(hold);
  arm.stop();
}

void stop_gate() {
  gate.stop();
}




void ntk(){
  /*while(true){
    Controller1.ButtonA.pressed(intakePressed);
    Controller1.ButtonB.pressed(intakeStop);
    shotgunControl(); 
  }*/
 
  //shotgunControl();
  //Controller1.ButtonA.pressed(intakePressed);
  //Controller1.ButtonB.pressed(intakeStop);

  shotgunControl(); 

}

/*void armControl(){
  Controller1.ButtonUp.pressed(armUp);
  Controller1.ButtonDown.pressed(armDown);
  Controller1.ButtonUp.released(armStop);
  Controller1.ButtonDown.released(armStop);

  intakeRight.setVelocity(100, percent);
  intakeRight.spin(reverse);
} */

void arm_control(){
  arm_up();

}

void preAutonomous(void) {
  // actions to do when the program starts
  Brain.Screen.clearScreen();
  Brain.Screen.print("pre auton code");
  wait(1, seconds);
}

void autonomous(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.print("autonomous code");
  // place automonous code here
  // parking plan 
}

void userControl(void) {
  Brain.Screen.clearScreen();
  // place driver control in this while loop
  int LeftPercent;
  int RightPercent;
  /*
  DriveRHD
  DriveRT
  DriveRB

  DriveLHD
  DriveLT
  DriveLB
  */
  DriveRHD.setMaxTorque(100, percent);
  DriveRT.setMaxTorque(100, percent);
  DriveRB.setMaxTorque(100, percent);

  DriveLHD.setMaxTorque(100, percent);
  DriveLT.setMaxTorque(100, percent);
  DriveLB.setMaxTorque(100, percent);
  



  while (true) {
    //wait(20, msec);
    //leftDrive.setVelocity(Controller1.Axis3.position());
    //DriveLHD.setVelocity(50, percent);
    

    if (INTAKE_ON){
      RightPercent = (Controller1.Axis2.position()/3);
      LeftPercent = (Controller1.Axis3.position()/3);
    } else {
      RightPercent = Controller1.Axis2.position();
      LeftPercent = Controller1.Axis3.position();
    }
    
    Brain.Screen.clearScreen();
    Brain.Screen.print(RightPercent);

 


    DriveRHD.setVelocity(RightPercent, percent);
    DriveRT.setVelocity(RightPercent, percent);
    DriveRB.setVelocity(RightPercent, percent);

    DriveLHD.setVelocity(LeftPercent, percent);
    DriveLT.setVelocity(LeftPercent, percent);
    DriveLB.setVelocity(LeftPercent, percent);

    DriveRHD.spin(forward);
    DriveRT.spin(forward);
    DriveRB.spin(forward);

    DriveLHD.spin(forward);
    DriveLT.spin(forward);
    DriveLB.spin(forward);

   // thread ArmControl = thread(armControl);
    //Controller1.ButtonA.pressed(intakePressed);
    //Controller1.ButtonB.pressed(intakeStop);

    
    
    //thread ShotgunControl = thread(shotgunControl);

    //Controller1.ButtonR2.pressed(shotgunL);
    //Controller1.ButtonL2.pressed(shotgunR);

    //Controller1.ButtonLeft.pressed(openShot);
    //Controller1.ButtonRight.pressed(closeShot);

    //if (!Controller1.ButtonLeft.pressing() && !Controller1.ButtonRight.pressing()){
    //  stopGate();
    //}

    /*if (!Controller1.ButtonR2.pressing() && !Controller1.ButtonL2.pressing()){
      if (shotgunMotor.position(degrees) != 0){
        shotgunReturn();
        shotgunStop();
      }

    } else {
      if (Controller1.ButtonR2.pressing())
        shotgunR();
      if (Controller1.ButtonL2.pressing())
        shotgunL();
    }*/
    //Controller1.ButtonR2.released();
    thread shotgun = thread(shotgunControl);

    if (Controller1.ButtonUp.pressing()){
      thread ArmControl = thread(arm_control);
      //start intake in reverse to unclog
      thread unclog = thread(intake_run);
    }
    if (!Controller1.ButtonUp.pressing()){
      //stop intake
      intake_stop();
    }

    //thread allIntake = thread(ntk);
    /*if (Controller1.ButtonA.pressing()){
      intake();
    }*/
    //Controller1.ButtonA.pressed(intake);
    if (Controller1.ButtonA.pressing()){
      if (!INTAKE_ON) {
        INTAKE_TOGGLE = true;
        intake_pressed();
        INTAKE_ON = true;
       
        //wait(1, seconds);
      }
      else {
        //wait(1, seconds);
        INTAKE_TOGGLE = false;
        intake_stop();
        INTAKE_ON = false;
    
      }
      
    }
   
    Controller1.ButtonB.pressed(intake_stop);
   
   // Controller1.Screen.print(intakeRight.velocity(percent));
    
    
    //Controller1.ButtonA.pressed(intake);
    //Controller1.ButtonB.pressed(intak)

    

    //Controller1.ButtonUp.pressed(armUp);
    Controller1.ButtonDown.pressed(arm_down);

    //Controller1.ButtonUp.released(armStop);
    Controller1.ButtonDown.released(arm_stop);
    

 


  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  // Run the pre-autonomous function.
  preAutonomous();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}