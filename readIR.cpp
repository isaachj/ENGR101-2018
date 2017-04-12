#include <stdio.h>
#include <time.h>
#include "E101.h"

// read 3 values from the IR sensor in the A0, A2, and A4 pins.
int readValues() {
	init();
	int adc_reading;
	adc_reading = read_analog(0);
	printf("%d\n", adc_reading);
	sleep1(1, 0);
	adc_reading = read_analog(2);
	printf("%d\n", adc_reading);
	sleep1(100, 0);
	adc_reading = read_analog(4);
	printf("%d\n", adc_reading);
	sleep1(0, 500000);
	
	return 0;
}

// read 10 values from the IR sensor (1 second apart) and return the maximum.
int getMax() {
	init();
	int adc_reading;
	int adc_greatest = 0;
	
	for(int i = 0; i < 10; i++) {
		adc_reading = read_analog(0);
		if(adc_greatest < adc_reading) {
			adc_greatest = adc_reading;
		}
		sleep1(1, 0);
	}
	printf("%d\n", adc_greatest);
	sleep1(0, 500000);
	return 0;
}

// Prints both the max and the min IR reading, taking 1 reading every 0.5s for 20s.
int getMaxAndMin() {
	init();
	int adc_reading;
	int adc_greatest = 0; // low to make SURE the first reading is higher
	int adc_min = 1024; // high to make SURE the first reading is lower
	
	for(int i = 0; i < 40; i++) {
		adc_reading = read_analog(0);
		if(adc_greatest < adc_reading) {
			adc_greatest = adc_reading;
		}
		if(adc_min > adc_reading) {
			adc_min = adc_reading;
		}
		printf("%d\n", adc_reading);
		sleep1(0, 500000);
	}
	printf("Highest: %d\n", adc_greatest);
	printf("Lowest: %d\n", adc_min);
	sleep1(0, 500000);
	return 0;
}

// Get the average reading from a string of 5 readngs.
int getAverage() {
	init();
	int adc_reading = 0;
	int num_readings = 5;
  
	for(int i = 0; i < num_readings; i++) {
		adc_reading += read_analog(0);
		sleep1(0, 200000);
	}
	adc_reading = adc_reading/num_readings;
	printf("%d\n", adc_reading);
	sleep1(0, 500000);
	return 0;
}

// Get the average reading and the half range.
int getAvgAndHalfRange() {
	init();
	int adc_reading = 0;
	int adc_readings = 5;
	int adc_max = 0;
	int adc_min = 1024;
	int lasteading;
	int halfrange;

	for(int i = 0; i < num_readings; i++) {
		lastreading = read_analog(0);
		adc_reading += lastreading;
		if(lastreading > adc_max) {
			adc_max = lastreading;
		}
		if(lastreading < adc_min) {
			adc_min = lastreading;
		}
		sleep1(0, 200000);
	}
	adc_reading = adc_reading/numreadings;
	halfrange = (adc_max - adc_min) / 2;
	printf("Half Range: %d\n Average: %d\n", halfrange, adc_reading);
	sleep1(0, 500000);
	return 0
}

// ---------------------------------MOTOR CONTROL---------------------------------------------

// Moves the robot forward at the specified speed (175/255 %)
int moveForward(){
	init();
  // One of these would actually be going the wrong way because the motors will be attacked backwards.
	set_motor(1, 175);
	set_motor(2, 175);
	sleep1(3, 0);
	stop(1);
	stop(2);
return 0; }

// Turns the robot left
int turn_left(int duration) {
	init();
	// Motor 1 will be the left motor.
	set_motor(1, -100);
	// Motor 2 will be the right motor.
	set_motor(2, 100);
	// This (sleep1) is what determines how far it turns, the speed difference between the motors (wheels) will as well,
	// but changing this is probably the more controlled way to do it. The distance between the wheels will also change the speed.
	sleep1(duration, 0);
	stop(1);
	stop(2);
return 0; }

// This makes it slowly speed up from 0 to full speed.
int main(){
	init();
	set_motor(1, 0);
	sleep1(0, 500000);
	
	set_motor(1, 51);
	sleep1(0, 500000);
	
	set_motor(1, 102);
	sleep1(0, 500000);
	
	set_motor(1, 153);
	sleep1(0, 500000);
	
	set_motor(1, 204);
	sleep1(0, 500000);
	
	set_motor(1, 254);
	sleep1(0, 500000);
	
	set_motor(1, 0);
	sleep1(0, 500000);
return 0; }

// The speed is controlled by the IR sensor's reading.
int speedByIR(){
	init();
	int t = 0;
	
	while(t<30) {
			double fraction = 1 - ((double)read_analog(0))/700;
			int speed = 254 * fraction;
			set_motor(1,speed);
			printf("%d\n", speed);
			sleep1(1,0);
			t++;
	}
	stop(1);
return 0; }
