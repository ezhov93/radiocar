 
#define LT 6
#define RT 5
#define FRD 9
#define BCK 10
#define LEFT_LIGHT 8
#define RIGHT_LIGHT 7
#define CAP A4v

#include "test/testfrontlight.h"
#include "test/testlight.h"

 TestFrontLight test(LEFT_LIGHT, RIGHT_LIGHT);
//TestLight test(LEFT_LIGHT);

void setup() {
  // Serial.begin(9600);
  test.begin();
}

void loop() { test.update(); }
