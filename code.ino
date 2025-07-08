#include <SoftwareSerial.h>  // Include SoftwareSerial library for GSM module communication

// Create a SoftwareSerial object to talk to the GSM module.
// Connect GSM TX to Arduino pin 7, and GSM RX to Arduino pin 8.
SoftwareSerial gsm(7, 8);

void setup() {
  // Start communication with Serial Monitor (for debugging)
  Serial.begin(9600);

  // Start communication with GSM module
  gsm.begin(9600);

  delay(1000);  // Give GSM time to initialize

  Serial.println("Initializing GSM module...");

  // Send "AT" command to check if GSM is responding
  gsm.println("AT");
  delay(1000);

  // Set GSM to SMS text mode
  gsm.println("AT+CMGF=1");
  delay(1000);
}

void loop() {
  // Here we just send one SMS and one call when the Arduino starts.

  // Send SMS command to GSM
  gsm.println("AT+CMGS=\"+91XXXXXXXXXX\"");  // Replace with farmer’s mobile number
  delay(1000);

  // Write the SMS content
  gsm.print("Alert: Wild animal detected in farm!");
  delay(1000);

  // Send CTRL+Z to signal end of SMS (ASCII code 26)
  gsm.write(26);
  delay(5000);

  // Dial the farmer’s number
  gsm.println("ATD+91XXXXXXXXXX;");  // Replace with farmer’s mobile number
  delay(20000);  // Wait for 20 seconds while call is active

  // Hang up the call
  gsm.println("ATH");

  // Stop here — the loop does nothing more
  while (1);  // Infinite loop to halt program after one alert
}

