const int OUTPUT_PIN = 8;
const int INPUT_PIN = 7;
int send_bit = HIGH;
int receive_bit;
const char DATA[] = "Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, ‘and what is the use of a book,’ thought Alice ‘without pictures or conversations?’ \n So she was considering in her own mind (as well as she could, for the hot day made her feel very sleepy and stupid), whether the pleasure of making a daisy-chain would be worth the trouble of getting up and picking the daisies, when suddenly a White Rabbit with pink eyes ran close by her. \n There was nothing so VERY remarkable in that; nor did Alice think it so VERY much out of the way to hear the Rabbit say to itself, ‘Oh dear! Oh dear! I shall be late!’ (when she thought it over afterwards, it occurred to her that she ought to have wondered at this, but at the time it all seemed quite natural); but when the Rabbit actually TOOK A WATCH OUT OF ITS WAISTCOAT-POCKET, and looked at it, and then hurried on, Alice started to her feet, for it flashed across her mind that she had never before seen a rabbit with either a waistcoat-pocket, or a watch to take out of it, and burning with curiosity, she ran across the field after it, and fortunately was just in time to see it pop down a large rabbit-hole under the hedge.";
const int DATA_N = 12;
int data_index = 0;
int bit_index = 0;
const int RING_SIZE = 16;
int send_ring[RING_SIZE];
int receive_ring[RING_SIZE];
int ring_index = 0;
int ring_bit_index = 0;
float best_error_rate = 1.0;


void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);

  for (int i = 0; i < RING_SIZE; i++) {
    send_ring[i] = random(-32768, 32768);
    receive_ring[i] = random(-32768, 32768);
  }
  
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Serial ready!");
}

void loop() {
  // grab the data
  send_bit = DATA[data_index];
  send_bit = (send_bit>>bit_index) & 0x1;
  bit_index ++;
  if (bit_index == 16) {
    data_index ++;
    bit_index = 0;
  }
  if (data_index == DATA_N) {
    data_index = 0;
  }


  // send out and receive.
  send_ring[ring_index] = send_ring[ring_index] << 0x1;
  send_ring[ring_index] = send_ring[ring_index] | send_bit;
  digitalWrite(OUTPUT_PIN, send_bit);

  delay(50);
  
  receive_bit = digitalRead(INPUT_PIN);
  receive_ring[ring_index] = receive_ring[ring_index] << 0x1;
  receive_ring[ring_index] = receive_ring[ring_index] | receive_bit;

  ring_bit_index++;
  if (ring_bit_index == 16) {
    ring_index++;
    ring_index %= RING_SIZE;
  }
  ring_bit_index %= 16;

  // report 
  int counter = 0;
  for (int i = 0; i < RING_SIZE; i++) 
  {
    int diff = send_ring[i] ^ receive_ring[i];
    for (int j = 0; j < 16; j++) {
      if (diff & 0x1 == 1) {
        counter ++;
      }
      diff = diff >> 0x1;
    }
  }
  float error_rate = counter / 16.0 / RING_SIZE;
  Serial.println(error_rate);

  // best
  if (error_rate < best_error_rate) {
    best_error_rate = error_rate;
  }
  Serial.print("Best error rate: ");
  Serial.print(best_error_rate);
  Serial.println();

}
