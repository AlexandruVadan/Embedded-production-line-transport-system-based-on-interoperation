
#define ledPin 13
#define ledPmotorPin2 12
//#define DEBUG_
int state = 0;

#define motorPin1 6
#define motorPin2 7
#define motorPin3 8
#define motorPin4 9
#define enA 5
#define enB 10

int M1_Speed = 150; // speed of motor 1
int M2_Speed = 150; // speed of motor 2
int stangaRotationSpeed = 210;  // stanga Rotation Speed
int dreaptaRotationSpeed = 210; // dreapta Rotation Speed



void inainte()
{
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void inapoi()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void dreapta()
{
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);

  analogWrite(enA, stangaRotationSpeed);
  analogWrite(enB, dreaptaRotationSpeed);
}

void stanga()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
//#ifdef DEBUG_
//Serial.print("stanga");
//#endif
  analogWrite(enA, stangaRotationSpeed);
  analogWrite(enB, dreaptaRotationSpeed);
}

void setup() {

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(A0, INPUT); // initialize stanga sensor as an input
  pinMode(A1, INPUT); // initialize dreapta sensor as an input



  pinMode(ledPin, OUTPUT);
   pinMode(ledPmotorPin2, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
  int stanga_SENSOR = digitalRead(A0);
  int dreapta_SENSOR = digitalRead(A1);


 
  if (Serial.available() > 0) { // if data available at serial port
    state = Serial.read(); // assign incoming data to variable state
    Serial.write(state);
  }
  // Controlling the LED
  if (state == '1') {
    digitalWrite(ledPin, HIGH);
     digitalWrite(ledPmotorPin2, LOW);// LED ON

    if (dreapta_SENSOR == 0 && stanga_SENSOR == 0) {
      inainte(); //inainte
      
    }

    else if (dreapta_SENSOR == 0 && stanga_SENSOR == 1) {
      dreapta(); //Move dreapta
    }

    else if (dreapta_SENSOR == 1 && stanga_SENSOR == 0) {
      stanga(); //Move stanga
    }

    else if (dreapta_SENSOR == 1 && stanga_SENSOR == 1) {
      dreapta();  //STOP
    }



   //state = 0;
  }
  
  else if (state == '0') {
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPmotorPin2, HIGH);// LED ON

   if (dreapta_SENSOR == 0 && stanga_SENSOR == 0) {
      inainte(); //inainte
      ;
    }

   else if (dreapta_SENSOR == 0 && stanga_SENSOR == 1) {
      dreapta(); //Move dreapta
    
    }

    else if (dreapta_SENSOR == 1 && stanga_SENSOR == 0) {
      stanga(); //Move stanga
      
    }

   else if (dreapta_SENSOR == 1 && stanga_SENSOR == 1) {
      stanga();  //STOP
     ;
    }

    //state = 0;
  }

}
