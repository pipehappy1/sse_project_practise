int OUTPUT_PIN = 8;
int INPUT_PIN = 7;
int send_bit = HIGH;
int receive_bit;

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Serial ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(OUTPUT_PIN, send_bit);

  if (send_bit == HIGH) {
    send_bit = LOW;
  } else if (send_bit == LOW) {
    send_bit = HIGH;
  }

  digitalWrite(OUTPUT_PIN, send_bit);
  receive_bit = digitalRead(INPUT_PIN);

  delay(500);

  Serial.println(send_bit);
  Serial.println(receive_bit);
  Serial.println("hehe");
}
