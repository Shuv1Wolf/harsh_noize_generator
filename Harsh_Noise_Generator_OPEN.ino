// Variables
int mode=0;                    // Working mode 
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


void setup() {
  pinMode(2, INPUT);      
  pinMode(3, INPUT);      
  pinMode(1, OUTPUT); 
  if (analogRead(2)>1010 & analogRead(3)>1010) mode=1;   // Switch on with potentiometers in full CW position to select random noise mode
}

void loop()
{
  if (mode == 0)              // Double oscillator mode 
  {
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

  if (mode == 1)      //Random noise
  {
    density = map (analogRead(3),0,1024,1014,10);            
    for (long i = 0; i < (random (density)*100); i++) {   
      intensity = map(analogRead(2),0,1023,1,255);          
      int x = random(intensity);                          
      analogWrite(1, x);
    } 
    analogWrite(1,0);
    delay(random(density)*3);
  }
}







