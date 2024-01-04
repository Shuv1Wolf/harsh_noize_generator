// Variables
int osc0;                      // First oscillator 
int osc1;                      // Second oscillator
int oscOut;                    // Output
int intensity;                 
long density;                  
long now;                        
long before0 = 0;     
long before1 = 0;    
long timeOscillator0;   
long timeOscillator1;
int brownNoise = 0; 
int lastOutput = 0;
int pinkNoise = 0; 
int noiseBuffer[16]; 
int bufferIndex = 0;
int blueNoise = 0; 


void setup() {
  pinMode(0, INPUT);
  pinMode(2, INPUT);      
  pinMode(3, INPUT);      
  pinMode(1, OUTPUT); 
}

void loop()
{
  if (analogRead(0) >= 0  && analogRead(0) <=  150 ) Double();
  if (analogRead(0) > 150  && analogRead(0) <=  300 ) Randome();
  if (analogRead(0) > 300  && analogRead(0) <=  450 ) BrownNoise();
  if (analogRead(0) > 450  && analogRead(0) <=  600 ) PinkNoise();
  if (analogRead(0) > 600  && analogRead(0) <=  750 ) BlueNoise();
}

void Double() {
  now = micros();         
    timeOscillator0 = map(analogRead(2),0,1023,50000,1400) + random(1000); 
    timeOscillator1 = map(analogRead(3),0,1023,50000,1400) + random(1000); 
    if(now - before0 > timeOscillator0) {
      before0 = now;       
      osc0 =!osc0; 
    }
    if(now - before1 > timeOscillator1) {
      before1 = now;       
      osc1 = !osc1;
    }
    oscOut = (osc0 ^ osc1);          
    digitalWrite (1,oscOut);
}

void Randome() {
  density = map (analogRead(3),0,1024,1014,10);            
    for (long i = 0; i < (random (density)*100); i++) {   
      intensity = map(analogRead(2),0,1023,1,255);          
      int x = random(intensity);                          
      analogWrite(1, x);
    } 
    analogWrite(1,0);
    delay(random(density)*3);
}

void BrownNoise() {
  density = map(analogRead(3), 0, 1024, 1014, 10);
  for (long i = 0; i < (random(density) * 100); i++) {
    intensity = map(analogRead(2), 0, 1023, 1, 255);
    int x = random(intensity);
    
    // Генерация коричневого шума
    brownNoise = (lastOutput + x) / 2;
    lastOutput = brownNoise;
    
    analogWrite(1, brownNoise);
  }
  
  analogWrite(1, 0);
  delay(random(density) * 3);
}

void PinkNoise() {
  density = map(analogRead(3), 0, 1024, 1014, 10);
  for (long i = 0; i < (random(density) * 100); i++) {
    intensity = map(analogRead(2), 0, 1023, 1, 255);
    int x = random(intensity);

    // Генерация розового шума
    int delta = x - noiseBuffer[bufferIndex];
    pinkNoise = lastOutput - delta;
    lastOutput = pinkNoise;
    noiseBuffer[bufferIndex] = x;
    bufferIndex = (bufferIndex + 1) % 16;

    analogWrite(1, pinkNoise);
  }

  analogWrite(1, 0);
  delay(random(density) * 3);
}

void BlueNoise() {
  density = map(analogRead(3), 0, 1024, 1014, 10);
  for (long i = 0; i < (random(density) * 100); i++) {
    intensity = map(analogRead(2), 0, 1023, 1, 255);
    int x = random(intensity);

    // Генерация синего шума
    blueNoise = x;
    lastOutput = blueNoise;

    analogWrite(1, blueNoise);
  }

  analogWrite(1, 0);
  delay(random(density) * 3);
}





