#include <Wire.h>
#include <VL53L0X.h>
#include <SparkFun_TB6612.h>
#include <Encoder.h>
#include "src/CircularBufferQueue/CircularBufferQueue.h"

// --- MACROS & CONFIG [cite: 3] ---
#define ROWS 16
#define COLS 16
#define WALL_THRESHOLD 150 // mm

// Bitwise wall mapping
#define markWall(loc, dir) floodArray[loc].neighbours |= 1 << dir
#define wallExists(loc, dir) bitRead(floodArray[loc].neighbours, dir)
#define getNeighbourLoc(loc, dir) (byte)((short)loc + dirOffsets[dir])

// Directions: 0=N, 1=E, 2=S, 3=W
short dirOffsets[4] = { -ROWS, 1, ROWS, -1 }; 

// --- HARDWARE PINS ---
// Motors (TB6612FNG) 
#define AIN1 4
#define BIN1 7
#define AIN2 5
#define BIN2 8
#define PWMA 3
#define PWMB 9
#define STBY 2

// Encoders [cite: 2]
#define ENC1_A 2
#define ENC1_B 10 // Changed to avoid PWM conflict
#define ENC2_A 12 // Changed for standard Nano
#define ENC2_B 13

// Sensors (XSHUT pins)
#define XSHUT_L 10
#define XSHUT_F 11
#define XSHUT_R 12

// --- OBJECTS ---
Motor motorL = Motor(AIN1, AIN2, PWMA, 1, STBY);
Motor motorR = Motor(BIN1, BIN2, PWMB, 1, STBY);
Encoder encL(ENC1_A, ENC1_B);
Encoder encR(ENC2_A, ENC2_B);
VL53L0X sensorL, sensorF, sensorR;

// --- MAZE DATA [cite: 5, 6] ---
struct cell {
  byte flood;
  byte neighbours; // 4 bits for walls
  bool visited;
};

cell floodArray[ROWS * COLS];
CircularBufferQueue floodQueue(512); 

byte currentCell = 0;
byte currentDir = 0; // 0=North
byte targetCell = 0x77; // Center of 16x16

// --- SETUP ---
void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Sensor Initialization (Address Reassignment)
  pinMode(XSHUT_L, OUTPUT); pinMode(XSHUT_F, OUTPUT); pinMode(XSHUT_R, OUTPUT);
  digitalWrite(XSHUT_L, LOW); digitalWrite(XSHUT_F, LOW); digitalWrite(XSHUT_R, LOW);
  delay(10);

  // Init Sensor L
  digitalWrite(XSHUT_L, HIGH); delay(10);
  sensorL.init();
  sensorL.setAddress(0x30);
  
  // Init Sensor F
  digitalWrite(XSHUT_F, HIGH); delay(10);
  sensorF.init();
  sensorF.setAddress(0x31);
  
  // Init Sensor R
  digitalWrite(XSHUT_R, HIGH); delay(10);
  sensorR.init();
  sensorR.setAddress(0x32);
  
  // Start continuous ranging
  sensorL.startContinuous(); sensorF.startContinuous(); sensorR.startContinuous();

  // Initialize Maze
  for (int i = 0; i < ROWS * COLS; i++) {
    floodArray[i].flood = 255;
    floodArray[i].neighbours = 0;
  }
}

// --- MAIN LOOP [cite: 17] ---
void loop() {
  updateWalls();
  floodFill(); 
  
  // Simple navigation logic
  byte bestDir = getBestDirection();
  
  if (bestDir == currentDir) {
    moveForward();
  } else {
    turnTo(bestDir);
  }
  
  // Update cell position based on movement
  currentCell = getNeighbourLoc(currentCell, currentDir);
}

// --- FLOOD FILL ALGO [cite: 19-23] ---
void floodFill() {
  floodQueue.enqueue(targetCell);
  floodArray[targetCell].flood = 0;
  
  while (!floodQueue.isEmpty()) {
    byte now = *floodQueue.dequeue();
    byte dist = floodArray[now].flood;
    
    // Check all 4 neighbours
    for (byte i = 0; i < 4; i++) {
      if (!wallExists(now, i)) { // Only if no wall
        byte next = getNeighbourLoc(now, i);
        if (floodArray[next].flood == 255) { // If unvisited/unflooded
          floodArray[next].flood = dist + 1;
          floodQueue.enqueue(next);
        }
      }
    }
  }
}

// --- HELPER FUNCTIONS ---

void updateWalls() {
  // Read Lasers
  int dL = sensorL.readRangeContinuousMillimeters();
  int dF = sensorF.readRangeContinuousMillimeters();
  int dR = sensorR.readRangeContinuousMillimeters();

  // Map walls relative to current orientation
  if (dL < WALL_THRESHOLD) markWall(currentCell, (currentDir + 3) % 4); // Left
  if (dF < WALL_THRESHOLD) markWall(currentCell, currentDir);           // Front
  if (dR < WALL_THRESHOLD) markWall(currentCell, (currentDir + 1) % 4); // Right
  
  floodArray[currentCell].visited = true;
}

byte getBestDirection() {
  byte bestDir = currentDir;
  byte minDist = 255;
  
  for (byte i = 0; i < 4; i++) {
    if (!wallExists(currentCell, i)) {
      byte next = getNeighbourLoc(currentCell, i);
      if (floodArray[next].flood < minDist) {
        minDist = floodArray[next].flood;
        bestDir = i;
      }
    }
  }
  return bestDir;
}

void moveForward() {
  // PID Logic Placehoder [cite: 84]
  long target = encL.read() + 500; // Approx 1 cell
  while(encL.read() < target) {
    // Simple P-Controller
    int error = (encL.read() - encR.read());
    int correction = error * 1; 
    motorL.drive(150 - correction);
    motorR.drive(150 + correction);
  }
  motorL.brake(); motorR.brake();
}

void turnTo(byte targetDir) {
  // Turn logic placeholder [cite: 102]
  // Calculate difference and rotate
  int diff = (targetDir - currentDir);
  if (diff == 1 || diff == -3) { 
    // Turn Right
    motorL.drive(100); motorR.drive(-100);
    delay(300); // Replace with encoder count
  } else { 
    // Turn Left
    motorL.drive(-100); motorR.drive(100);
    delay(300);
  }
  motorL.brake(); motorR.brake();
  currentDir = targetDir;
}
