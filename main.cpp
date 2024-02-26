#define DangWarmTempPIN A1
#define WarmTempPIN A2
#define NormalTempPIN A3
#define BuzzerPIN A0
#define LEDPIN 10
#define StopPBPIN 11
#define MotorPIN 9
#define C 3
#define D 3

enum {Idle, CollectX, Classify, TempState};
int current = Idle;

mtx_type x[D];
mtx_type scores[C];
mtx_type Wb[C][D] = {{-7.27, 9.39, -1.27},
                    {-16.21, 7.88, 7.35},
                    {-14.09,  4.12, 6.81}};

int predicted_class;
int previousStopPB = 0, currentStopPB = 1;

enum {Normal, Warm, DangerouslyWarm};

int SVM(){
    MatrixMath matrixMath; 
    matrixMath.Multiply((mtx_type*)Wb,(mtx_type*)x,C,D,1,(mtx_type*)scores);
    int MaxIndex = 0; int Max = scores[0];
    for (int i = 0 ; i < C ; i++)
    if(scores[i] > Max)
      {
        Max = scores[i];
        MaxIndex = i; 
      }
    return MaxIndex; 
}

void output(int BuzzerState, int LEDState) {
    tone(BuzzerPIN, BuzzerState, 100);
    digitalWrite(LEDPIN, LEDState);
}

void MotorSpeed(int Speed) {
    Speed = constrain(Speed, 0, 255);
    analogWrite(MotorPIN, Speed);
}

void setup() {
    Serial.begin(9600);
    pinMode(BuzzerPIN, OUTPUT);
    pinMode(LEDPIN, OUTPUT);
    pinMode(MotorPIN, OUTPUT);
    pinMode(StopPBPIN, INPUT_PULLUP);
}

void loop() {
    switch (current) {
        case Idle:
          Serial.println("System Started");
          current = CollectX;
        break;
        
        case CollectX:
          x[0] = map(analogRead(NormalTempPIN), 0, 1023, -40, 125);
          x[1] = map(analogRead(WarmTempPIN), 0, 1023, -40, 125);
          x[2] = map(analogRead(DangWarmTempPIN), 0, 1023, -40, 125);
          Serial.print(x[0]); Serial.println(",");
          Serial.print(x[1]); Serial.println(",");
          Serial.print(x[2]); Serial.println(",");
          current = Classify;
        break;
        
        case Classify:
          predicted_class = SVM();
          current = TempState;
        break;
        
        case TempState:
          currentStopPB = digitalRead(StopPBPIN);
        
          switch (predicted_class) {
            case Normal:
              Serial.println("Cool");
              output(0, 0);
              MotorSpeed(255);
              current = CollectX;
             break;
        
            case Warm:
              Serial.println("Warm");
              MotorSpeed(150);
        
              for (int i = 0; i < 3; i++) {
                output(300, 1);
                delay(500);
                output(0, 0);
                delay(500);
              }
              current = CollectX;
            break;
        
            case DangerouslyWarm:
              Serial.println("Dangerously Warm");
              Serial.println();
              Serial.println("Medicine is Discarded");
              MotorSpeed(60);
              if (currentStopPB == 0 && previousStopPB == 1) {
                current = Idle;
              }
            break;
          }
          break;
        }
    previousStopPB = currentStopPB;
}
