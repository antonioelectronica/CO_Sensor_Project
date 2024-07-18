#include "SevSeg.h"
SevSeg sevseg; // Library for the display

// Pin definitions for LEDs and CO sensor
const int coSensorPin = A0;  // Analog pin for the CO sensor
const int redLedPin = 4;     // Digital pin for the red LED
const int orangeLedPin = 3;  // Digital pin for the orange LED
const int greenLedPin = 2;   // Digital pin for the green LED
const int BUZZ = 5;          // Digital pin for the buzzer

int contador = 0;
long suma = 0;
int resultado;

void setup() {
  inicializarDisplay();  // Initialize the display
  configurarPines();     // Configure the pins as inputs or outputs
  Serial.begin(9600);    // Start serial communication
}

void loop() {
  if (suma < 20000) {
    // Counter to give the display a "delay" to read the digits without an actual delay
    contador++;
    int ppm = leerSensorCO();  // Read the CO sensor value
    actualizarLEDs(ppm);       // Evaluate the CO ppm level and turn on the corresponding LED
    sevseg.refreshDisplay();   // Must be executed constantly for the display to work
    // Print the CO sensor value to the screen
    Serial.print("CO Value: ");
    Serial.println(ppm);
  } else {
    mostrarValorPromedio();  // Show the average of all values on the display
  }
}

void inicializarDisplay() {
  byte numDigits = 4; // 4 digits
  byte digitPins[] = {6, 7, 8, 9}; // Pins that light up each digit
  byte segmentPins[] = {15, 16, 17, 18, 19, 20, 21}; // Pins that light up each segment
  bool resistorsOnSegments = false; // No resistors on the display
  byte hardwareConfig = COMMON_ANODE; // The display is common anode
  bool updateWithDelays = true; 
  bool leadingZeros = false; // No leading zeros, e.g., display 987 instead of 0987
  bool disableDecPoint = true; // No decimal point
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint); // Set parameters
  sevseg.setBrightness(80); // Brightness level
}

void configurarPines() {
  // Configure the pins as inputs or outputs
  pinMode(coSensorPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(orangeLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  // Initialize LEDs off
  digitalWrite(greenLedPin, LOW);
  digitalWrite(orangeLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

int leerSensorCO() {
  // Read the CO sensor value
  float coValue = analogRead(coSensorPin);
  // Convert the value to voltage (0-5V)
  float voltage = coValue * (5.0 / 1023.0);
  // The sensor measures up to 2100ppm, corresponding to 5V
  int ppm = voltage * 2100 / 5;
  // Add the measured ppm values to later show an average
  suma += ppm;
  return ppm;
}

void actualizarLEDs(int ppm) {
  // Evaluate the CO ppm level and turn on the corresponding LED
  // The criteria for choosing the 3 CO levels were seen in the presentation
  if (ppm < 1000) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(orangeLedPin, LOW);
    digitalWrite(redLedPin, LOW);
  } else if (ppm < 1500) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(orangeLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  } else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(orangeLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    tone(BUZZ, 1000, 250); // Library used to make the buzzer work: vibrates for 250 ms at 1kHz
  }
}

void mostrarValorPromedio() {
  resultado = suma / contador; // Calculate the average
  sevseg.setNumber(resultado); // Show it on the display
  sevseg.refreshDisplay();
  // Reset the sum and counter
  suma = 0;
  contador = 0;
}
