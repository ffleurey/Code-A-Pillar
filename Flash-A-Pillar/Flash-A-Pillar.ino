/*
MIT License

Copyright (c) 2017 Franck Fleurey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

/*
 * Implementation of the Code-A-Pillar "master" protocol
 * - Data bus to arduino pin 2
 * - Enable of the firt block to arduino pin 3
 * 
 * This sketch will discover the tail periodically and flash 
 * the blocks.
 * 
 */

uint16_t send_discover(uint8_t addr) {
  send_message(addr, 0x01, 0);
  delayMicroseconds(500);
  return read_response();
}

uint8_t send_ping(uint8_t addr) {
  send_message(addr, 0x02, 0);
  delayMicroseconds(500);
  return !read_bit();
}

uint8_t send_led_on(uint8_t addr) {
  send_message(addr, 0x03, 0);
  delayMicroseconds(500);
  return !read_bit();
}

uint8_t send_led_off(uint8_t addr) {
  send_message(addr, 0x04, 0);
  delayMicroseconds(500);
  return !read_bit();
}

uint8_t send_led_blink(uint8_t addr) {
  send_message(addr, 0x0C, 0);
  delayMicroseconds(500);
  return !read_bit();
}


void setup() {

  DDRD |= _BV(PD3);   // set PD3 as output (Arduino pin 3)
  PORTD &= ~_BV(PD3);  // LOW
  
  bus_high();
  Serial.begin(115200);
  sei();
}

void loop() {

  int8_t i = 0;
  int8_t cpt = 0;
  uint16_t block;

  Serial.println("\nRESET\n");
  delay(100);
  reset_bus();
  delay(80);

  while(i<16) {
    Serial.print("DISCOVER ");
    Serial.print(i);
    Serial.print("...");
    block = send_discover(i);
    Serial.println(block, HEX);
    delay(10);
    i++;
    if (block == 0xFFFF) break;
  }
  cpt = i;

  for(i=cpt-1; i>=0; i--) {
    send_led_on(i);
    delay(250);
  }

  for(i=cpt-1; i>=0; i--) {
    send_led_off(i);
    delay(250);
  }

  for (i=0; i<cpt; i++) {
    send_led_blink(i);
    delay(10);
  }

  delay(2000);

  for(i=cpt-1; i>=0; i--) {
    send_led_off(i);
    delay(10);
  }
  delay(2000);

}

/********* LOW LEVEL IMPLEMENTATION OF THE 1-WIRE LIKE PROTOCOL **********/

// NOTE: The internal pullup of the uC is used to pull the line high. It works but it is a bit weak.
// A 2.2k resistor can be added to the circuit to pull the data line to VCC.
void bus_high() {
  DDRD &= ~_BV(PD2);   // set PD2 as input (Arduino pin 2)
  PORTD |= _BV(PD2);  // pull-up 
}

void bus_low() {
  PORTD &= ~_BV(PD2);  // LOW
  DDRD |= _BV(PD2);   // set PD2 as output (Arduino pin 2)
  
}

uint8_t read_bus() {
  if (PIND & _BV(PD2)) return 1;
  else return 0;
}

void reset_bus() {
  bus_low();
  delayMicroseconds(800);
  bus_high();
}

void send_bit_1() {
  bus_low();
  delayMicroseconds(10);
  bus_high();
  delayMicroseconds(90);
}

void send_bit_0() {
  bus_low();
  delayMicroseconds(60);
  bus_high();
  delayMicroseconds(40);
}

uint8_t read_bit() {
  bus_low();
  delayMicroseconds(10);
  bus_high();
  delayMicroseconds(30);
  uint8_t result = read_bus();
  delayMicroseconds(60);
  return result;
}

void send_bits(uint8_t b, uint8_t nb_bits) {
  int8_t i;
  for(i=nb_bits-1; i>=0; i--) {
    if (b & (1<<i)) send_bit_1();
    else send_bit_0();
  }
}

uint8_t read_bits(uint8_t nb_bits) {
  int8_t i;
  uint8_t result = 0;
  for(i=nb_bits-1; i>=0; i--) {
    if (read_bit()) result |= 1<<i;
  }
  return result;
}

void send_message(uint8_t a, uint8_t c, uint8_t p) {
  send_bits(a, 8);
  send_bits(c, 8);
  send_bits(p, 8);
  send_bits(a+c+p, 4); // Send Checksum  
}

uint16_t read_response() {
  uint8_t b1 = read_bits(8);
  uint8_t b2 = read_bits(8);
  uint8_t sum = read_bits(4);
  if (sum == ((b1+b2) & 0x0F)) return (b1<<8) + b2;
  else return 0xFFFF; // Checksum Error
}

