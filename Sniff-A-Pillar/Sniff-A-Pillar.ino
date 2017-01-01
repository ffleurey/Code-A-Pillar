/*
MIT License

Copyright (c) 2016 Franck Fleurey

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

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t rx_cmd_rdy = 0;
volatile uint8_t rx_cmd[4];
void received_cmd(uint8_t dest_addr, uint8_t command, uint8_t params, uint8_t check) {
  rx_cmd[0] = dest_addr;
  rx_cmd[1] = command;
  rx_cmd[2] = params;
  rx_cmd[3] = check;
  rx_cmd_rdy = 1;
}

volatile uint8_t rx_resp_rdy = 0;
volatile uint8_t rx_resp[3];
void received_resp(uint8_t type, uint8_t args, uint8_t check) {
  rx_resp[0] = type;
  rx_resp[1] = args;
  rx_resp[2] = check;
  rx_resp_rdy = 1;
}

volatile uint8_t rx_ack_rdy = 0;
volatile uint8_t rx_ack;
void received_ack(uint8_t ack) {
  rx_ack = ack;
  rx_ack_rdy = 1;
}

volatile uint8_t rx_reset_rdy = 0;
void received_reset() {
  rx_reset_rdy = 1;
}

void loop() {

  if (rx_cmd_rdy) {
    rx_cmd_rdy = 0;
    Serial.print(rx_cmd[0], HEX);
    Serial.print(' ');
    Serial.print(rx_cmd[1], HEX);
    Serial.print(' ');
    Serial.print(rx_cmd[2], HEX);
    if (rx_cmd[3] != 0)  { 
      PORTD ^= _BV(PD4); // DEBUG: toggle PD4 when an error is detected (Arduino PIN 4)
      Serial.print(" ERR");
    }
    else Serial.print(" OK ");

    if (rx_cmd[1] == 1 && rx_cmd[3] == 0) {
      Serial.print("[ DISCOVER @");
      Serial.print(rx_cmd[0], HEX);
      Serial.print("]");
    }
    else if (rx_cmd[1] == 2  && rx_cmd[3] == 0) {
      Serial.print("[     PING @");
      Serial.print(rx_cmd[0], HEX);
      Serial.print("]");
    }
    if (rx_cmd[0] == 0) { // It is a broadcast
      Serial.println();
    }
    else Serial.print("..."); // It is a unicast, there should be a response or an ack
  }

  if (rx_resp_rdy) {
    rx_resp_rdy = 0;
    Serial.print(rx_resp[0], HEX);
    Serial.print(' ');
    Serial.print(rx_resp[1], HEX);
    if (rx_resp[2] != 0)  {
      if (rx_resp[0] != 0xFF || rx_resp[1] != 0xFF) PORTD ^= _BV(PD4); // DEBUG: toggle PD4 when an error is detected (Arduino PIN 4) - Ignore the case FF FF which is used to detect new blocks.
      Serial.print(" ERR");
    }
    else Serial.print(" OK ");

    if (rx_resp[2] == 0) {
      switch(rx_resp[0]) {
        case 1: Serial.print("[FORWARD]");break;
        case 2: Serial.print("[ RIGHT ]");break;
        case 4: Serial.print("[ LEFT  ]");break;
        case 8: Serial.print("[ MUSIC ]");break;
      }
    }
    Serial.println();
  }

  if (rx_ack_rdy) {
    rx_ack_rdy = 0;
    if (rx_ack)  Serial.print(" ACK ");
    else  Serial.print(" NOACK ");
    Serial.println();
  }

  if (rx_reset_rdy) {
    rx_reset_rdy = 0;
    Serial.println();
    Serial.println("RESET");
  }

}

void setup() {
  // set PB5 led as output and OFF (pin 13)
  DDRB |= _BV(PB5);   // Output
  PORTB &= ~_BV(PB5); // LED OFF

  // set PD4 as output (for debug)
  DDRD |= _BV(PD3);   // Output
  PORTD &= ~_BV(PD3); // LOW

  // set PD4 as output (for debug)
  DDRD |= _BV(PD4);   // Output
  PORTD &= ~_BV(PD4); // LOW

  // set PD5 as output (for debug)
  DDRD |= _BV(PD5);   // Output
  PORTD &= ~_BV(PD5); // LOW

  // Set up Timer2
  TCCR2A = 0;   // Normal port operation
  TCCR2B = 0;   // Timer is stopped (set to 2 to start counting)
  TCNT2 = 0;    // Counter set to 0
  TIMSK2 = 7;   // Enable interrupts for overflow and compare A and Compare B
  OCR2A = 18;   // 40 uS when counting from 0 with a /32 prescaling @16MHz
  OCR2B = 125;  // 250 uS

  // Setup interrupts in INT0 falling edge (connected to 1 wire bus)
  DDRD &= ~_BV(PD2);   // set PD2 as input
  PORTD &= ~_BV(PD2);  // no pullup
 
  EICRA = 0x02;        // set INT0 to trigger on falling edge
  EIMSK = 0x01;        // Turns on INT0

  Serial.begin(115200);

  sei();
 
}

volatile uint8_t tmp_bit = 0;
volatile uint8_t tmp_data = 0;
volatile uint8_t bit_cpt = 0;

volatile uint8_t isResponse = 0;
volatile uint8_t rxbuffer[4];     // The longest packet is 3 bytes and a 4bits checksum
volatile uint8_t rxbuffer_ptr = 0;

void received_4bits(uint8_t data) {
  rxbuffer[rxbuffer_ptr >> 1] += data << (4 * (1-(rxbuffer_ptr & 0x01)) );
  rxbuffer_ptr++;
}

void process_bit() {
  if ((tmp_bit & 0x02) > 0) { // There is a bit to process
    tmp_data += (tmp_bit & 0x01) << (3-bit_cpt);
    bit_cpt++;
    if (bit_cpt > 3) { // We have got 4 bits
      received_4bits(tmp_data);
      bit_cpt = 0;
      tmp_data = 0;
    }
    tmp_bit = 0;
  }
}

void process_packet() {

  if (rxbuffer_ptr == 5) { // This is a device response
    uint8_t rxchecksum = rxbuffer[0] + rxbuffer[1];
    rxchecksum &= 0x0F;
    uint8_t chk = (rxbuffer[2] == (rxchecksum << 4))?0:1;
    received_resp(rxbuffer[0], rxbuffer[1], chk);
  }
  else if (bit_cpt == 1) {  // This is an ack bit
   received_ack((tmp_data == 0)?1:0);
  }
  else { // This is a master packet (or a corrupted bunch of crap)
    uint8_t rxchecksum = rxbuffer[0] + rxbuffer[1] + rxbuffer[2];
    rxchecksum &= 0x0F;
    uint8_t chk = (rxbuffer[3] == (rxchecksum << 4))?0:1;
//    if (chk != 0) {
//      Serial.print("\nERR: ");
//      Serial.print(rxbuffer[3], HEX);
//      Serial.print(" != ");
//      Serial.println((rxchecksum << 4), HEX);
//      
//    }
    received_cmd(rxbuffer[0], rxbuffer[1], rxbuffer[2], chk);
  }

  // Reset everithing for the next packet
  reset_receiver();
}

void process_reset() {
  received_reset();
  reset_receiver();
}

void reset_receiver() {
  tmp_bit = 0;
  tmp_data = 0;
  bit_cpt = 0;

  for (rxbuffer_ptr = 0; rxbuffer_ptr<4; rxbuffer_ptr++) rxbuffer[rxbuffer_ptr] = 0;
  rxbuffer_ptr = 0;
  rxbuffer[0] = 0;
}
 
// Timer0 Overflow
ISR(TIMER2_OVF_vect)
{   

}

// Timer2 CompareB (250 uS after falling edge)
ISR(TIMER2_COMPB_vect)
{
      TCCR2B = 0; // stop the timer2
      if (PIND & _BV(PD2)) { // The bus is high => it is the end of a transmission
        process_bit();
        process_packet();
      }
      else { // The bus is low => It is a reset of the bus (low for 800uS)
        process_reset();
      }
}


// Timer2 CompareA (40 uS after falling edge)
ISR(TIMER2_COMPA_vect)
{
   PORTD ^= _BV(PD5); // DEBUG: toggle PD5 when reading the bit (Arduino PIN 5)
   if (PIND & _BV(PD2)) {
     tmp_bit = 3;
   }
   else tmp_bit = 2;
}
 
// Falling Edge on PB2 (PIN 2 of the arduino)
ISR (INT0_vect)
{
  
  if (TCCR2B > 0 && TCNT2 < 20) {
    isResponse = 1;
    PORTD ^= _BV(PD3); // toggle PD3 (Arduino PIN 3) -- Ignore this edge
  }
  else {
    
    TCCR2B = 0; // stop timer2
    TCNT2 = 0; // Reset timer2
    TCCR2B = 3;   // start counting with /32 prescaling (=> 2 usec period @16MHz)

    process_bit();
    
    PORTB ^= _BV(PB5); // toggle the LED
  }
}

