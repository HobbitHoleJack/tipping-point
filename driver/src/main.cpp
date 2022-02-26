#include "main.h"
using namespace pros;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	#define Ldrive_1 14 // reverse
	#define Ldrive_2 10
	#define Rdrive_1 4 // reverse
	#define Rdrive_2 20

	#define arm_port 8 // reverse
	#define clamp_port 9
	#define blamp_port 19

	Motor drive_left1_initializer (Ldrive_1, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor drive_left2_initializer (Ldrive_2, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);

	Motor drive_right1_initializer (Rdrive_1, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor drive_right2_initializer (Rdrive_2, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);

	Motor arm_initializer (arm_port, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
	Motor clamp_initializer (clamp_port, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor blamp_initializer (blamp_port, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	#define Ldrive_1 14 //reverse
	#define Ldrive_2 10
	#define Rdrive_1 4 //reverse
	#define Rdrive_2 20

	#define arm_port 8 // reverse
	#define clamp_port 9
	#define blamp_port 19

	Motor drive_left1 (Ldrive_1);
	Motor drive_left2 (Ldrive_2);
	Motor drive_right1 (Rdrive_1);
	Motor drive_right2 (Rdrive_2);

	Motor arm (arm_port);
	arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	Motor clamp (clamp_port);
	clamp.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	Motor blamp (blamp_port);
	blamp.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	Controller master (CONTROLLER_MASTER);


	while (true) {

	// drivebase stuff	
		int power = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_LEFT_X);
		int left = power + turn;
		int right = power - turn;

		drive_left1.move(left);
		drive_left2.move(left);
		drive_right1.move(right);
		drive_right2.move(right);


	// arm shi
		if (master.get_digital(DIGITAL_L1)) {
			arm.move_velocity(100);
		}
		else if (master.get_digital(DIGITAL_L2)) {
			arm.move_velocity(-100);
		}
		else {
			arm.move_velocity(0);
		}

	// clamp and blamp !?
		if (master.get_digital(DIGITAL_R1)){
			if (clamp.get_position() <= 200){
				clamp.move_relative(400, 100);
			}
			else {
				clamp.move_relative(0, 100);
			}
		}
		
		if (master.get_digital(DIGITAL_R2)){
			if (blamp.get_position() <= 200){
				blamp.move_relative(400, 100);
			}
			else {
				blamp.move_relative(0, 100);
			}

			// Wait and give up the time we don't need to other tasks.
			// joystick values, motor telemetry, etc. all updates every 10 ms.
			pros::delay(10);
				}
}