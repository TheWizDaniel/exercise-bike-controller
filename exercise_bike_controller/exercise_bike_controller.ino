/* Exercise Bike Controller
 * by Jaymis - htp://jaymis.com
 * Project Details - http://jaymis.com/2016/06/exercise-bike-controller
 * 
 * Based on and requires the library from:
 * Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 * The example code is in the public domain.
 */

#include <Encoder.h>
long newPosition;
long oldPosition = 0;
long newTime;
long oldTime = 0;
long vel;							
long speedMultiplier = 1000;		// change this number to increase/decrease the speed you need to pedal to hit full joystick axis.
long joyPosition; 					// joystick x axis position
long joyCenter = 512;				// default value for center of joystick
long readDelay = 50; 				// Delay before reading next encoder travel - set to 50-100 for testing, lower number (5-10) for better controller latency

Encoder myEnc(5, 6); // encoder attached to pins 5 and 6
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(19200);						// Serial will write speed and joystick position for testing
  Serial.println("Basic Encoder Test:"); 	// Start test serial output
}


void loop() {
  newPosition = myEnc.read();  
  newTime = millis();
  vel = (newPosition-oldPosition) * speedMultiplier / (newTime-oldTime);	// Velocity is how far we've moved since oldTime, divided by how much time has passed. Change speedMultiplier value to increase/decrease the speed you need to pedal to hit full joystick axis
  vel = constrain(vel, -512, 512);											// If vel is outside of joystick range, constrain to +-512
  joyPosition = joyCenter + vel;											// Joystick position is generally 0-1024 center at 512.
  Joystick.X(joyPosition);													// Write joystick position to joystick device
  Serial.print ("Speed and Joystick = ");									// Print debug information
  Serial.print (vel);
  Serial.print (" ");
  Serial.print (joyPosition);
  Serial.print ("\n");

  oldPosition = 0;															// Reset both to 0 so we can read the 
  newPosition = 0;															// velocity after delay
  myEnc.write(0);															// Reset encoder travel
  oldTime = newTime;														// Set time before waiting
  delay(readDelay);															// Delay before reading next encoder travel - set to 50-100 for ease of multiplier testing, lower number (5-10) for better controller latency once you've got multiplier figured out
  
}