/* With this code we are using the photo sensor as if it was a solar panel charging a battery that is being use and constantly losing energy. I use different color lights to show if charging, loosing 
energy, or dead*/

// Variable list
int sensorPin = A0;
int sensorValue = 0;
unsigned int batteryCapacity = 1000;
int batteryLevel = 1;
int red = 2;
int yellow = 3;
int green = 4;
int energyLost = 50;


void PrintBatteryPercentage(){ // this fuction is to get the percentage the battery is at
 if (batteryLevel > 0) { // this is to check we don't get a negative percentage
  Serial.print(((double)batteryLevel/ (double)batteryCapacity)*100);
  Serial.println("%");
 }else {
  Serial.println("0.00%");
 }
}


void setup() {
  // we initialized all the lights here 
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  

}

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(sensorPin);// to check the input we get by teh sensot
  sensorValue -= energyLost;// this is the energy being lost after each loop

 if (batteryLevel >= 0 ){ // to make sure the batter doesn't lose energy at 0% or gain at 100%
    batteryLevel += sensorValue;
 }
 if (batteryLevel < 0){ // so the battery level doesn't go to negative numbers 
  batteryLevel = 0;
 }
  if (sensorValue > 0 ){// turn green light to show is charging 
  digitalWrite (green, HIGH);
 }else {
  digitalWrite(green, LOW);
 }
  if (sensorValue < 0 && batteryLevel > 0){// turn yellow light to show is losing energy 
  digitalWrite (yellow, HIGH);
 }else {
  digitalWrite(yellow , LOW);
 }
  if (batteryLevel <= 0 ){// turn red light to show the battery is at 0 (dead) 
  digitalWrite (red, HIGH);
  Serial.println("Charge Battery!");
 }else {
  digitalWrite(red, LOW);
 }
 if (batteryLevel >= batteryCapacity){// This tells us when the battery is full
  Serial.println("Fully Charged!");
  batteryLevel = batteryCapacity;
 }
PrintBatteryPercentage();// prints the percentage after every loop
delay (500); // delays the code so we can read the data

 
}
