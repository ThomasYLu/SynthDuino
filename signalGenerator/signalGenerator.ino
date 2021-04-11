// Hack TJ 8.0
// Thomas Lu
// R-2R Circuit Test

// signal array - sine wave
// python:  s = [(m.sin(2*m.pi*t/40)+1)/2 for t in range(0,40)]
const double sig[] = {0.5, 0.5626666167821521, 0.6243449435824274, 0.684062276342339, 0.7408768370508576, 0.7938926261462366, 0.8422735529643444, 0.8852566213878946, 0.9221639627510075, 0.9524135262330098, 0.9755282581475768, 0.9911436253643443, 0.9990133642141358, 0.9990133642141358, 0.9911436253643444, 0.9755282581475768, 0.9524135262330098, 0.9221639627510074, 0.8852566213878946, 0.8422735529643444, 0.7938926261462367, 0.7408768370508576, 0.6840622763423391, 0.6243449435824276, 0.5626666167821522, 0.5000000000000001, 0.43733338321784787, 0.3756550564175727, 0.31593772365766104, 0.2591231629491423, 0.20610737385376365, 0.1577264470356558, 0.11474337861210532, 0.07783603724899235, 0.0475864737669901, 0.024471741852423234, 0.00885637463565564, 0.0009866357858642205, 0.0009866357858642205, 0.00885637463565564, 0.02447174185242318, 0.047586473766990045, 0.07783603724899252, 0.1147433786121052, 0.15772644703565553, 0.20610737385376332, 0.25912316294914195, 0.31593772365766104, 0.37565505641757235, 0.43733338321784765};
int sigLen;

// hardware constants
const int bits = 6;
const int LSBPin = 4; // ASSUMES ALL FOLLOWING CONSECUTIVE DIGITAL PINS ARE USED FOR FOLLOWING BITS
const int res = pow(2,bits);

// step control variables
int sigIdx = 0;
// timing
unsigned long lastT = 0;
unsigned long currT = 0;
int freq = 300;
double period; // in microseconds
double stepT; // in microseconds


void setup() {
  
  Serial.begin(9600);

  // pin set-up
  for (int i = LSBPin; i < LSBPin + bits; i++) {
    pinMode(i, OUTPUT);
  }

  // signal
  sigLen = sizeof(sig) / sizeof(sig[0]);

  // timing vars
  period = (1.0 / freq) * 1000000;
  stepT = period / sigLen;
  
}

void loop() {

  currT = micros();
  if(currT - lastT > stepT){

    lastT = micros();
    
    //unsigned long startT = micros();
    int output = (int)(sig[sigIdx] * res); // possibly replace with hardcoded array -- there is around 25 microseconds of speed-up
  
    for (int b = 0; b < bits; b++) {
      digitalWrite(LSBPin + b, (output >> b) & 1); // bitwise AND to find pin state
    }
    //Serial.println(micros()-startT); // This function takes around 50 microseconds
  
    sigIdx += 1;
    if (sigIdx == sigLen) sigIdx = 0;

  }
  
}
