enum ledStates {INCREASE, STEADIER3, STEADIER2, STEADIER1, RANDOM , DECREASE, STAY, STAY1, STAY2, STAY3, WAVE, OFF, ON,}; // Here we make nicknames for the different states our program supports.
enum ledStates ledState; // We define 'ledState' as type ledStates'
enum ledStates previousLedState = ledState;


unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;

int buttonPin = 2;
int buttonState = 0;
int blinkInterval = 0; //time between swithcing states
int distance = 0; //distance to the target

int target;
int brightness = 0; // our main variable for setting the brightness of the LED
float velocity = 1.0; // the speed at which we change the brightness.
int ledPin = 9; // we use pin 9 for PWM
int p = 0; // use to keep track how often we plot
int plotFrequency = 3; // how often we plot, every Nth time.

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(ledPin, OUTPUT); // set ledPin as an output.
  Serial.begin(9600); // initiate the Serial monitor so we can use the Serial Plotter to graph our patterns
  generateNumber();
}

void loop() {
  // put your main code here, to run repeatedly:
  compose();
  delay(10);
  analogWrite(ledPin, brightness);
  currentMillis = millis(); //store the current time since the program started
  
  int sensor = analogRead(A0);
  Serial.print(sensor);
  Serial.print(" ");
  Serial.print(target);
 
  
 
  
 distance = target - sensor;
 if (distance < 0) {
   distance = distance * -1 ;
 }
blinkInterval = distance;
/*
  if (sensor <= 50) {
    changeState(INCREASE);
  } else if (sensor <= 255) {
    changeState(STEADIER3);
  } else if (255 < sensor && sensor <= 510) { 
    changeState(STEADIER2);
    } else if (510 < sensor && sensor <= 775) {
      changeState(STEADIER1);
      } else {
        changeState(RANDOM);
        }
        */
    
        if (sensor > (target - 5) && sensor < (target + 5)) {
          Serial.println("hit");
        
          digitalWrite(9, HIGH);
          /*if (currentMillis - startMillis >= 10000){
            generateNumber();
          }*/
          } else if ((target - sensor) >= 5 && (target - sensor) <= 1000) {
            Serial.println("close");
            changeState(STEADIER3);
            } 

            Serial.println(distance);
   
}


void generateNumber(){
  target = random(0,1024);
  }

void compose() {
  // this is a state machine which allows us to decouple the various operations from timed loops. 
  // instead we just switch from state to state when particular conditions are met.
  // we switch states by calling the changeState() function.


  
  switch (ledState){

  
  case STEADIER3: 
   plot("STEADIER3", brightness);
   brightness = 50;
   if (currentMillis - startMillis >= blinkInterval) {
    changeState (STAY3);
   }
  break;
   case STAY3:
    plot("STAY3", brightness);
    brightness = 20;
    if (currentMillis - startMillis >= blinkInterval ){
      changeState(STEADIER3);
      }
    break;

  }
}

void changeState(ledStates newState){
    // call to change state, will keep track of time since last state
    startMillis = millis();
    ledState = newState;
  }
  
void plot(char *state, int brightness){
    // use this function to plot a graph
    // it will normalize the auto-scaling plotter

    if ((p % plotFrequency) == 0){
      Serial.print(state);
      Serial.print(", ");
      Serial.print(brightness);
      Serial.println(", 0, 300");
    }
    p++;
  }

int increase_brightness (int brightness, float velocity){
    return brightness = 1 + brightness * velocity;
  }

int decrease_brightness (int brightness, float velocity){
    return brightness = brightness - 1 * velocity;
  }
