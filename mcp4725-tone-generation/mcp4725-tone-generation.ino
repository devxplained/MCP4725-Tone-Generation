#include <Adafruit_MCP4725.h>

// DAC
const int I2C_ADDR = 0x60;
Adafruit_MCP4725 dac;

// Frequencies (in Hz)
const int F = 349;
const int G = 392;
const int A = 440;
const int BB = 466;
const int C = 523;

// Measure the communication speed with the DAC
unsigned long usPerCommand;
void calibrate() {
  usPerCommand = micros();
  for(int i = 0; i < 10; i++) {
    dac.setVoltage(0, false);  
  }
  usPerCommand = (micros() - usPerCommand)/10;
}

// Precalculated Voltage Buffer
const int BUFFER_SIZE = 128;
unsigned int voltages[BUFFER_SIZE];

void dacTone(unsigned long freq, int durationMs) {
  // Start time to keep track of the duration
  int startTime = millis();
 
  // Steps need to be a multiple of 4 to keep the sine form
  int raw_steps = 1000000 / (freq * usPerCommand);
  unsigned char steps = (raw_steps / 4) * 4;
  if(steps > BUFFER_SIZE) steps = BUFFER_SIZE;

  // Fill the rest of the time with an delay to achieve the frequency
  int delayUs = 1000000/freq/steps - usPerCommand;

  // Precalculate Sine Values (1 - 4095)
  for(unsigned char i = 0; i < steps; i++) {
    voltages[i] = (sin(i*3.14*2/steps) + 1) * 2047 + 1;
  }

  // Start Output
  while(millis()-startTime < durationMs) {
    for(unsigned char i = 0; i < steps; i++) {
      dac.setVoltage(voltages[i], false);
      delayMicroseconds(delayUs);
    }
  }

  dac.setVoltage(0, false);
}

// Play notes and add a small delay between them
void playNote(int freq, int duration) {
  dacTone(freq, duration-25);
  delay(25);
}

void setup() {
  dac.begin(I2C_ADDR);

  calibrate();

  playNote(A, 250);
  playNote(A, 250);
  playNote(BB, 250);
  playNote(C, 250);

  playNote(C, 250);
  playNote(BB, 250);
  playNote(A, 250);
  playNote(G, 250);

  playNote(F, 250);
  playNote(F, 250);
  playNote(G, 250);
  playNote(A, 250);

  playNote(A, 250);
  playNote(G, 250);
  playNote(G, 500);


  playNote(A, 250);
  playNote(A, 250);
  playNote(BB, 250);
  playNote(C, 250);

  playNote(C, 250);
  playNote(BB, 250);
  playNote(A, 250);
  playNote(G, 250);

  playNote(F, 250);
  playNote(F, 250);
  playNote(G, 250);
  playNote(A, 250);

  playNote(G, 250);
  playNote(F, 250);
  playNote(F, 500);
}

void loop() {
}
