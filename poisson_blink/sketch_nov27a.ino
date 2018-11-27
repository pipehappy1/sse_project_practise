int LED_OUTPUT = 8;
int HIGH_INTERVAL = 500;
int RATE = 500;
float i = 0;
int interval = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_OUTPUT, OUTPUT);

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Serial ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_OUTPUT, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(HIGH_INTERVAL);                       // wait for a second
  digitalWrite(LED_OUTPUT, LOW);    // turn the LED off by making the voltage LOW

  i = random(1, 256);
  i = - RATE * log(i/256.0);
  interval = i;
  Serial.println(interval);
  delay(interval); 
}
