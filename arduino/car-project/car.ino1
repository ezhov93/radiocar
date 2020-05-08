// Pins ---------------------------
#define LT        6
#define RT        5
#define FRD       9
#define BCK       10
#define LIGHT     13
#define CAP        A4

// Macros ---------------------------
#define IS_MINUS(x)(x&0x80)
#define ABS(x)     (x&0x7F)
#define DUTY(x)    (x*(255/100))
#define SERIAL_CLEAR() while(Serial.available()) Serial.read();

// Variables ------------------------
bool recieveEvent = false;

// Functions ------------------------
void blink() {
  int cnt = 8;
  int state = HIGH;
  while (cnt--) {
    digitalWrite(LIGHT, state);
    state = state ? LOW : HIGH;
    delay(250);
  }
}

inline void controlTask() {
  struct Recieve {
    bool light : 1;
    byte       : 3;
    byte key   : 4;
    byte lr;
    byte fb;
  };
  const char key = 0xA;
  byte data[3] = {};
  Recieve *recieve = (Recieve*)data;

  if (Serial.available()) {
    data[0] = Serial.read();
    if (recieve->key == key) {
      bool read = true;
      unsigned  long timerRead = millis()+10;
      while (Serial.available() < 2) {
        if (millis()>timerRead) {
          read = false;
          break;
        }
      }

      if (read) {
        data[1] = Serial.read();
        data[2] = Serial.read();
        if (IS_MINUS(recieve->lr)) {
          analogWrite(LT, 0);
          analogWrite(RT, DUTY(ABS(recieve->lr)));
        } else {
          analogWrite(RT, 0);
          analogWrite(LT, DUTY(ABS(recieve->lr)));
        }
        if (IS_MINUS(recieve->fb)) {
          analogWrite(FRD, 0);
          analogWrite(BCK, DUTY(ABS(recieve->fb)));
        } else {
          analogWrite(BCK, 0);
          analogWrite(FRD, DUTY(ABS(recieve->fb)));
        };
        digitalWrite(LIGHT, recieve->light);
        recieveEvent = true;
      }
    }
  }
  SERIAL_CLEAR();
}


inline bool timerEvent() {
  static unsigned long timer = 0;
  unsigned long time = millis();
  bool temp;
  if (timer != time) {
    temp = true;
    timer = time;
  } else
    temp = false;
  return temp;
}

inline void capTask() {
  static int timerRead = 0;
  static int timerSend = 0;
  static float capArray[10] = {};
  static int cnt = 0;
  if (timerEvent()) {
    ++timerRead;
    ++timerSend;
  }
    
  if (timerRead>100) {
    const float max = 4.f;
    const float min = 3.f;

    float cap = analogRead(CAP) * 5.f / 1024.f;
    constrain(cap, min, max);
    cap = (cap - min) * 100.0f / (max - min);
    capArray[cnt] = cap;
    ++cnt;
    timerRead = 0;
  }

    if (timerSend>1000) {
    int avg = 0;
    for (int i = 0; i<cnt; i++)
     avg += capArray[i];
    avg /= cnt;
    Serial.write((byte)avg);
    cnt = 0;
    timerSend = 0;
  }
}

inline void  noSignalTask() {
  static int timer = 0;

  if (recieveEvent) {
    timer = 0;
    recieveEvent = false;
    return;
  }
  if (timerEvent())
    ++timer;
  if (timer > 1000) {
    analogWrite(LT, 0);
    analogWrite(RT, 0);
    analogWrite(FRD, 0);
    analogWrite(BCK, 0);
    timer = 0;
  }
}

void setup() {
  pinMode(LT, OUTPUT);
  pinMode(RT, OUTPUT);
  pinMode(FRD, OUTPUT);
  pinMode(BCK, OUTPUT);
  pinMode(LIGHT, OUTPUT);
  Serial.begin(9600);

  blink();
  SERIAL_CLEAR();
}

void loop() {
  controlTask();
  capTask();
}
