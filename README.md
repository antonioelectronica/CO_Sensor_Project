# CO Sensor Project

This project uses an Arduino to read CO (Carbon Monoxide) levels from a sensor, display the value on a 7-segment display, and indicate the level with LEDs and a buzzer.

## Components

- Arduino board
- CO sensor
- 7-segment display
- LEDs (red, orange, green)
- Buzzer

## Connections

- CO sensor to analog pin A0
- Red LED to digital pin 4
- Orange LED to digital pin 3
- Green LED to digital pin 2
- Buzzer to digital pin 5
- 7-segment display connected to pins 6, 7, 8, 9, and 15 to 21

## Code Explanation

- **setup()**: Initializes the display and configures the pins.
- **loop()**: Reads the CO sensor value, updates the LEDs, and refreshes the display.
- **inicializarDisplay()**: Configures the 7-segment display.
- **configurarPines()**: Sets the pin modes and initializes the LEDs.
- **leerSensorCO()**: Reads and converts the CO sensor value.
- **actualizarLEDs()**: Updates the LEDs based on the CO level.
- **mostrarValorPromedio()**: Shows the average CO level on the display.


