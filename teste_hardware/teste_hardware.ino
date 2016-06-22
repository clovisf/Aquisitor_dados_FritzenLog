const int buttonPin = 5;    
const int ledVermelho = 4;
const int ledVerde = 2;

int ledState = HIGH;        
int buttonState;             
int lastButtonState = LOW;   

long lastDebounceTime = 0;  
long debounceDelay = 50;  

unsigned long timet;
unsigned long previousTime;
boolean enterFunction= true;

boolean verde = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // set initial LED state
  digitalWrite(ledVermelho, ledState);
  digitalWrite(ledVerde, HIGH);
}

void loop() {

 timet = micros();
  if (enterFunction == true){
    previousTime= timet;
    Serial.println(previousTime); // for debugging

    // Start your code below 
    //-----------------------

    if (verde == false) {
      digitalWrite(ledVerde, HIGH);
      verde = true;
    } else {
      digitalWrite(ledVerde, LOW);
      verde = false;
    }
    

    //-----------------------
    // End of your code
  }
  
  // The DELAY time is adjusted in the constant below >> 
  if (timet - previousTime < 999990){ // 1 million microsencods= 1 second delay
    /* I have actually used 0.999990 seconds, in a trial to compensate the time that
       this IF function takes to be executed. this is really a point that
       need improvement in my code */   
    enterFunction= false;
  } 
  else {
    enterFunction= true;
  }


  
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(ledVermelho, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;  
}

