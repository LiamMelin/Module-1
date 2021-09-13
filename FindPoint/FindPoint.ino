enum ledStates {INCREASE, DECREASE};
enum ledStates ledState;


unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;


int target;
int brightness = 0;
int ledPin = 9;
int p = 0;
int plotFrequency = 0.5;
int previousSensor;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  generateNumber();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int sensor = analogRead(A0);
  
 /* unsigned int mapValue = map(target - sensor, 0, 1024, 0, 255);
  analogWrite(ledPin, 255 - mapValue);
  */
  
  if (previousSensor < sensor) {
    changeState(INCREASE);
    Serial.println("<working");
  } else if (previousSensor > sensor) {
    changeState(DECREASE);
    Serial.println(">working");
  } if (previousSensor == sensor) {
    Serial.println("=working");
  }
  
  previousSensor = sensor; 
  Serial.println(sensor);
  Serial.println(" ");
  Serial.println(target);
}

void generateNumber(){
  target = random(0,1024); 
}

void compose() {
  

  switch (ledState) {

  case INCREASE:
    plot("INCREASE", brightness);
    brightness = increase_brightness(brightness, 1);
     if (brightness > 250) {
      ledState = INCREASE; 
      changeState(INCREASE);
     }
  break;

  case DECREASE:
    plot("DECREASING", brightness);
    brightness = decrease_brightness(brightness, 0.9);
    if (brightness < 250) {
      ledState = DECREASE;
      changeState(DECREASE);
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
