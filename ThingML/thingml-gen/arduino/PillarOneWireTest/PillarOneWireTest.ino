/*****************************************************************************
 * Headers for type : PillarOneWireLogger
 *****************************************************************************/

// Definition of the instance struct:
struct PillarOneWireLogger_Instance {

// Instances of different sessions
bool active;
// Variables for the ID of the ports of the instance
uint16_t id_onewire;
// Variables for the current instance state
int PillarOneWireLogger_PillarOneWireLoggerSC_State;
// Variables for the properties of the instance
// CEP stream pointers

};
// Declaration of prototypes outgoing messages:
void PillarOneWireLogger_PillarOneWireLoggerSC_OnEntry(int state, struct PillarOneWireLogger_Instance *_instance);
void PillarOneWireLogger_handle_onewire_pillar_command_with_ack(struct PillarOneWireLogger_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t ack);
void PillarOneWireLogger_handle_onewire_pillar_command_with_response(struct PillarOneWireLogger_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t rsp0, uint8_t rsp1, uint8_t rsum);
void PillarOneWireLogger_handle_onewire_pillar_command(struct PillarOneWireLogger_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum);
void PillarOneWireLogger_handle_onewire_pillar_reset(struct PillarOneWireLogger_Instance *_instance);
void PillarOneWireLogger_handle_onewire_pillar_error(struct PillarOneWireLogger_Instance *_instance);
// Declaration of callbacks for incoming messages:

// Definition of the states:
#define PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_STATE 0
#define PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE 1


/*****************************************************************************
 * Headers for type : PillarOneWire
 *****************************************************************************/


// BEGIN: Code from the c_header annotation PillarOneWire

// END: Code from the c_header annotation PillarOneWire

// Definition of the instance struct:
struct PillarOneWire_Instance {

// Instances of different sessions
bool active;
// Variables for the ID of the ports of the instance
uint16_t id_clock;
uint16_t id_onewire;
// Variables for the current instance state
int PillarOneWire_PillarOneWireSC_State;
// Variables for the properties of the instance
uint8_t * PillarOneWire_rxbuffer_var;
uint16_t PillarOneWire_rxbuffer_var_size;
uint8_t PillarOneWire_rxindex_var;
// CEP stream pointers

};
// Declaration of prototypes outgoing messages:
void PillarOneWire_PillarOneWireSC_OnEntry(int state, struct PillarOneWire_Instance *_instance);
void PillarOneWire_handle_clock_timer_timeout(struct PillarOneWire_Instance *_instance, uint8_t id);
// Declaration of callbacks for incoming messages:
void register_PillarOneWire_send_clock_timer_start_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint32_t));
void register_external_PillarOneWire_send_clock_timer_start_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint32_t));
void register_PillarOneWire_send_clock_timer_cancel_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t));
void register_external_PillarOneWire_send_clock_timer_cancel_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t));
void register_PillarOneWire_send_onewire_pillar_reset_listener(void (*_listener)(struct PillarOneWire_Instance *));
void register_external_PillarOneWire_send_onewire_pillar_reset_listener(void (*_listener)(struct PillarOneWire_Instance *));
void register_PillarOneWire_send_onewire_pillar_command_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t));
void register_external_PillarOneWire_send_onewire_pillar_command_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t));
void register_PillarOneWire_send_onewire_pillar_command_with_ack_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t));
void register_external_PillarOneWire_send_onewire_pillar_command_with_ack_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t));
void register_PillarOneWire_send_onewire_pillar_command_with_response_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t));
void register_external_PillarOneWire_send_onewire_pillar_command_with_response_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t));
void register_PillarOneWire_send_onewire_pillar_error_listener(void (*_listener)(struct PillarOneWire_Instance *));
void register_external_PillarOneWire_send_onewire_pillar_error_listener(void (*_listener)(struct PillarOneWire_Instance *));

// Definition of the states:
#define PILLARONEWIRE_PILLARONEWIRESC_STATE 0
#define PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE 1
#define PILLARONEWIRE_PILLARONEWIRESC_BLINK_STATE 2



//timer0
/* Adds and instance to the runtime and returns its id */
uint16_t add_instance(void * instance_struct);
/* Returns the instance with id */
void * instance_by_id(uint16_t id);

/* Returns the number of byte currently in the fifo */
int fifo_byte_length();
/* Returns the number of bytes currently available in the fifo */
int fifo_byte_available();
/* Returns true if the fifo is empty */
int fifo_empty();
/* Return true if the fifo is full */
int fifo_full();
/* Enqueue 1 byte in the fifo if there is space
   returns 1 for sucess and 0 if the fifo was full */
int fifo_enqueue(byte b);
/* Enqueue 1 byte in the fifo without checking for available space
   The caller should have checked that there is enough space */
int _fifo_enqueue(byte b);
/* Dequeue 1 byte in the fifo.
   The caller should check that the fifo is not empty */
byte fifo_dequeue();

#define MAX_INSTANCES 4
#define FIFO_SIZE 256

/*********************************
 * Instance IDs and lookup
 *********************************/

void * instances[MAX_INSTANCES];
uint16_t instances_count = 0;

void * instance_by_id(uint16_t id) {
  return instances[id];
}

uint16_t add_instance(void * instance_struct) {
  instances[instances_count] = instance_struct;
  return instances_count++;
}

/******************************************
 * Simple byte FIFO implementation
 ******************************************/

byte fifo[FIFO_SIZE];
int fifo_head = 0;
int fifo_tail = 0;

// Returns the number of byte currently in the fifo
int fifo_byte_length() {
  if (fifo_tail >= fifo_head)
    return fifo_tail - fifo_head;
  return fifo_tail + FIFO_SIZE - fifo_head;
}

// Returns the number of bytes currently available in the fifo
int fifo_byte_available() {
  return FIFO_SIZE - 1 - fifo_byte_length();
}

// Returns true if the fifo is empty
int fifo_empty() {
  return fifo_head == fifo_tail;
}

// Return true if the fifo is full
int fifo_full() {
  return fifo_head == ((fifo_tail + 1) % FIFO_SIZE);
}

// Enqueue 1 byte in the fifo if there is space
// returns 1 for sucess and 0 if the fifo was full
int fifo_enqueue(byte b) {
  int new_tail = (fifo_tail + 1) % FIFO_SIZE;
  if (new_tail == fifo_head) return 0; // the fifo is full
  fifo[fifo_tail] = b;
  fifo_tail = new_tail;
  return 1;
}

// Enqueue 1 byte in the fifo without checking for available space
// The caller should have checked that there is enough space
int _fifo_enqueue(byte b) {
  fifo[fifo_tail] = b;
  fifo_tail = (fifo_tail + 1) % FIFO_SIZE;
  return 0; // Dummy added by steffend
}

// Dequeue 1 byte in the fifo.
// The caller should check that the fifo is not empty
byte fifo_dequeue() {
  if (!fifo_empty()) {
    byte result = fifo[fifo_head];
    fifo_head = (fifo_head + 1) % FIFO_SIZE;
    return result;
  }
  return 0;
}

/*****************************************************************************
 * Implementation for type : PillarOneWire
 *****************************************************************************/


// BEGIN: Code from the c_global annotation PillarOneWire
struct PillarOneWire_Instance *_pillar_instance;
// END: Code from the c_global annotation PillarOneWire

// Declaration of prototypes:
//Prototypes: State Machine
void PillarOneWire_PillarOneWireSC_OnExit(int state, struct PillarOneWire_Instance *_instance);
//Prototypes: Message Sending
void PillarOneWire_send_clock_timer_start(struct PillarOneWire_Instance *_instance, uint8_t id, uint32_t time);
void PillarOneWire_send_clock_timer_cancel(struct PillarOneWire_Instance *_instance, uint8_t id);
void PillarOneWire_send_onewire_pillar_reset(struct PillarOneWire_Instance *_instance);
void PillarOneWire_send_onewire_pillar_command(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum);
void PillarOneWire_send_onewire_pillar_command_with_ack(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t ack);
void PillarOneWire_send_onewire_pillar_command_with_response(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t rsp0, uint8_t rsp1, uint8_t rsum);
void PillarOneWire_send_onewire_pillar_error(struct PillarOneWire_Instance *_instance);
//Prototypes: Function
void f_PillarOneWire_timer2_initialize(struct PillarOneWire_Instance *_instance);
void f_PillarOneWire_reset_rxbuffer(struct PillarOneWire_Instance *_instance);
void f_PillarOneWire_timer2_start(struct PillarOneWire_Instance *_instance);
void f_PillarOneWire_timer2_stop(struct PillarOneWire_Instance *_instance);
ISR(TIMER2_COMPA_vect);
ISR(TIMER2_COMPB_vect);
ISR(TIMER2_OVF_vect);
void f_PillarOneWire_int0_initialize(struct PillarOneWire_Instance *_instance);
ISR (INT0_vect);
void f_PillarOneWire_initialize(struct PillarOneWire_Instance *_instance);
// Declaration of functions:
// Definition of function timer2_initialize
void f_PillarOneWire_timer2_initialize(struct PillarOneWire_Instance *_instance) {
TCCR2A = 0;
TCCR2B = 0;
TIMSK2 = 7;
OCR2A = 7;
OCR2B = 62;
}
// Definition of function reset_rxbuffer
void f_PillarOneWire_reset_rxbuffer(struct PillarOneWire_Instance *_instance) {
;uint8_t i = 0;
while(i < 6) {
_instance->PillarOneWire_rxbuffer_var[i] = 0;
i = i + 1;

}
_instance->PillarOneWire_rxindex_var = 0;
}
// Definition of function timer2_start
void f_PillarOneWire_timer2_start(struct PillarOneWire_Instance *_instance) {
TCNT2 = 0; TCCR2B = 4;
}
// Definition of function timer2_stop
void f_PillarOneWire_timer2_stop(struct PillarOneWire_Instance *_instance) {
TCCR2B = 0;
}
// Definition of function timer2_interrupt_compare_A
ISR(TIMER2_COMPA_vect) {
PORTD ^= _BV(PD4);
if(PIND & _BV(PD2)) {
_pillar_instance->PillarOneWire_rxbuffer_var[_pillar_instance->PillarOneWire_rxindex_var / 8] |= 1 << (7 - (_pillar_instance->PillarOneWire_rxindex_var % 8));

}
_pillar_instance->PillarOneWire_rxindex_var = _pillar_instance->PillarOneWire_rxindex_var + 1;
}
// Definition of function timer2_interrupt_compare_B
ISR(TIMER2_COMPB_vect) {
PORTB ^= _BV(PB1);
if( !(PIND & _BV(PD2))) {
f_PillarOneWire_timer2_stop(_pillar_instance);
PillarOneWire_send_onewire_pillar_reset(_pillar_instance);
f_PillarOneWire_reset_rxbuffer(_pillar_instance);

}
}
// Definition of function timer2_interrupt_overflow
ISR(TIMER2_OVF_vect) {
PORTB ^= _BV(PB0);
f_PillarOneWire_timer2_stop(_pillar_instance);
if(_pillar_instance->PillarOneWire_rxbuffer_var[0]
 > 16) {
PORTD ^= _BV(PD6);

}
if(_pillar_instance->PillarOneWire_rxindex_var == 28) {
PillarOneWire_send_onewire_pillar_command(_pillar_instance, _pillar_instance->PillarOneWire_rxbuffer_var[0]
, _pillar_instance->PillarOneWire_rxbuffer_var[1]
, _pillar_instance->PillarOneWire_rxbuffer_var[2]
, _pillar_instance->PillarOneWire_rxbuffer_var[3]
 / 16);

} else {
if(_pillar_instance->PillarOneWire_rxindex_var == 29) {
PillarOneWire_send_onewire_pillar_command_with_ack(_pillar_instance, _pillar_instance->PillarOneWire_rxbuffer_var[0]
, _pillar_instance->PillarOneWire_rxbuffer_var[1]
, _pillar_instance->PillarOneWire_rxbuffer_var[2]
, _pillar_instance->PillarOneWire_rxbuffer_var[3]
 / 16, (0x08 & _pillar_instance->PillarOneWire_rxbuffer_var[3]
) >> 3);

} else {
if(_pillar_instance->PillarOneWire_rxindex_var == 48) {
PillarOneWire_send_onewire_pillar_command_with_response(_pillar_instance, _pillar_instance->PillarOneWire_rxbuffer_var[0]
, _pillar_instance->PillarOneWire_rxbuffer_var[1]
, _pillar_instance->PillarOneWire_rxbuffer_var[2]
, _pillar_instance->PillarOneWire_rxbuffer_var[3]
 / 16, _pillar_instance->PillarOneWire_rxbuffer_var[3]
 * 16 + _pillar_instance->PillarOneWire_rxbuffer_var[4]
 / 16, _pillar_instance->PillarOneWire_rxbuffer_var[4]
 * 16 + _pillar_instance->PillarOneWire_rxbuffer_var[5]
 / 16, 0x0F & _pillar_instance->PillarOneWire_rxbuffer_var[5]
);

} else {
PORTD ^= _BV(PD6);
PillarOneWire_send_onewire_pillar_error(_pillar_instance);

}

}

}
f_PillarOneWire_reset_rxbuffer(_pillar_instance);
}
// Definition of function int0_initialize
void f_PillarOneWire_int0_initialize(struct PillarOneWire_Instance *_instance) {
DDRD &= ~_BV(PD2);
PORTD &= ~_BV(PD2);
EICRA = 0x02;
EIMSK = 0x01;
}
// Definition of function int0_interrupt_falling
ISR (INT0_vect) {
PORTD ^= _BV(PD5);
if(TCCR2B > 0 && TCNT2 < 14) {
PORTD ^= _BV(PD7);

} else {
f_PillarOneWire_timer2_stop(_pillar_instance);
f_PillarOneWire_timer2_start(_pillar_instance);

}
}
// Definition of function initialize
void f_PillarOneWire_initialize(struct PillarOneWire_Instance *_instance) {
f_PillarOneWire_timer2_initialize(_instance);
f_PillarOneWire_int0_initialize(_instance);
f_PillarOneWire_reset_rxbuffer(_instance);
// set PB5 led as output and OFF (pin 13)
	  DDRB |= _BV(PB5);   // Output
	  PORTB &= ~_BV(PB5); // LED OFF
	
	  // set PD3 as output
	  DDRD |= _BV(PD3);   // Output
	  PORTD &= ~_BV(PD3); // LOW
	
	  // set PD4 as output (for debug)
	  DDRD |= _BV(PD4);   // Output
	  PORTD &= ~_BV(PD4); // LOW
	
	  // set PD5 as output (for debug)
	  DDRD |= _BV(PD5);   // Output
	  PORTD &= ~_BV(PD5); // LOW
	  
	  // set PD6 as output (for debug)
	  DDRD |= _BV(PD6);   // Output
	  PORTD &= ~_BV(PD6); // LOW
	  
	  // set PD7 as output (for debug)
	  DDRD |= _BV(PD7);   // Output
	  PORTD &= ~_BV(PD7); // LOW
	  
	  // set PB0 as output (for debug)
	  DDRB |= _BV(PB0);   // Output
	  PORTB &= ~_BV(PB0); // LOW
	  
	  // set PB1 as output (for debug)
	  DDRB |= _BV(PB1);   // Output
	  PORTB &= ~_BV(PB1); // LOW
	
	  sei();
}

// Sessions functionss:


// On Entry Actions:
void PillarOneWire_PillarOneWireSC_OnEntry(int state, struct PillarOneWire_Instance *_instance) {
switch(state) {
case PILLARONEWIRE_PILLARONEWIRESC_STATE:{
_instance->PillarOneWire_PillarOneWireSC_State = PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE;
_pillar_instance = _instance;
pinMode(13, OUTPUT);
f_PillarOneWire_initialize(_instance);
PillarOneWire_PillarOneWireSC_OnEntry(_instance->PillarOneWire_PillarOneWireSC_State, _instance);
break;
}
case PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE:{
PillarOneWire_send_clock_timer_start(_instance, 0, 500);
break;
}
case PILLARONEWIRE_PILLARONEWIRESC_BLINK_STATE:{
digitalWrite(13, HIGH);
PillarOneWire_send_clock_timer_start(_instance, 0, 250);
break;
}
default: break;
}
}

// On Exit Actions:
void PillarOneWire_PillarOneWireSC_OnExit(int state, struct PillarOneWire_Instance *_instance) {
switch(state) {
case PILLARONEWIRE_PILLARONEWIRESC_STATE:{
PillarOneWire_PillarOneWireSC_OnExit(_instance->PillarOneWire_PillarOneWireSC_State, _instance);
break;}
case PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE:{
break;}
case PILLARONEWIRE_PILLARONEWIRESC_BLINK_STATE:{
digitalWrite(13, LOW);
break;}
default: break;
}
}

// Event Handlers for incoming messages:
void PillarOneWire_handle_clock_timer_timeout(struct PillarOneWire_Instance *_instance, uint8_t id) {
if(!(_instance->active)) return;
//Region PillarOneWireSC
uint8_t PillarOneWire_PillarOneWireSC_State_event_consumed = 0;
if (_instance->PillarOneWire_PillarOneWireSC_State == PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE) {
if (PillarOneWire_PillarOneWireSC_State_event_consumed == 0 && 1) {
PillarOneWire_PillarOneWireSC_OnExit(PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE, _instance);
_instance->PillarOneWire_PillarOneWireSC_State = PILLARONEWIRE_PILLARONEWIRESC_BLINK_STATE;
PillarOneWire_PillarOneWireSC_OnEntry(PILLARONEWIRE_PILLARONEWIRESC_BLINK_STATE, _instance);
PillarOneWire_PillarOneWireSC_State_event_consumed = 1;
}
}
else if (_instance->PillarOneWire_PillarOneWireSC_State == PILLARONEWIRE_PILLARONEWIRESC_BLINK_STATE) {
if (PillarOneWire_PillarOneWireSC_State_event_consumed == 0 && 1) {
PillarOneWire_PillarOneWireSC_OnExit(PILLARONEWIRE_PILLARONEWIRESC_BLINK_STATE, _instance);
_instance->PillarOneWire_PillarOneWireSC_State = PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE;
PillarOneWire_PillarOneWireSC_OnEntry(PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE, _instance);
PillarOneWire_PillarOneWireSC_State_event_consumed = 1;
}
}
//End Region PillarOneWireSC
//End dsregion PillarOneWireSC
//Session list: 
}

// Observers for outgoing messages:
void (*external_PillarOneWire_send_clock_timer_start_listener)(struct PillarOneWire_Instance *, uint8_t, uint32_t)= 0x0;
void (*PillarOneWire_send_clock_timer_start_listener)(struct PillarOneWire_Instance *, uint8_t, uint32_t)= 0x0;
void register_external_PillarOneWire_send_clock_timer_start_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint32_t)){
external_PillarOneWire_send_clock_timer_start_listener = _listener;
}
void register_PillarOneWire_send_clock_timer_start_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint32_t)){
PillarOneWire_send_clock_timer_start_listener = _listener;
}
void PillarOneWire_send_clock_timer_start(struct PillarOneWire_Instance *_instance, uint8_t id, uint32_t time){
if (PillarOneWire_send_clock_timer_start_listener != 0x0) PillarOneWire_send_clock_timer_start_listener(_instance, id, time);
if (external_PillarOneWire_send_clock_timer_start_listener != 0x0) external_PillarOneWire_send_clock_timer_start_listener(_instance, id, time);
;
}
void (*external_PillarOneWire_send_clock_timer_cancel_listener)(struct PillarOneWire_Instance *, uint8_t)= 0x0;
void (*PillarOneWire_send_clock_timer_cancel_listener)(struct PillarOneWire_Instance *, uint8_t)= 0x0;
void register_external_PillarOneWire_send_clock_timer_cancel_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t)){
external_PillarOneWire_send_clock_timer_cancel_listener = _listener;
}
void register_PillarOneWire_send_clock_timer_cancel_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t)){
PillarOneWire_send_clock_timer_cancel_listener = _listener;
}
void PillarOneWire_send_clock_timer_cancel(struct PillarOneWire_Instance *_instance, uint8_t id){
if (PillarOneWire_send_clock_timer_cancel_listener != 0x0) PillarOneWire_send_clock_timer_cancel_listener(_instance, id);
if (external_PillarOneWire_send_clock_timer_cancel_listener != 0x0) external_PillarOneWire_send_clock_timer_cancel_listener(_instance, id);
;
}
void (*external_PillarOneWire_send_onewire_pillar_reset_listener)(struct PillarOneWire_Instance *)= 0x0;
void (*PillarOneWire_send_onewire_pillar_reset_listener)(struct PillarOneWire_Instance *)= 0x0;
void register_external_PillarOneWire_send_onewire_pillar_reset_listener(void (*_listener)(struct PillarOneWire_Instance *)){
external_PillarOneWire_send_onewire_pillar_reset_listener = _listener;
}
void register_PillarOneWire_send_onewire_pillar_reset_listener(void (*_listener)(struct PillarOneWire_Instance *)){
PillarOneWire_send_onewire_pillar_reset_listener = _listener;
}
void PillarOneWire_send_onewire_pillar_reset(struct PillarOneWire_Instance *_instance){
if (PillarOneWire_send_onewire_pillar_reset_listener != 0x0) PillarOneWire_send_onewire_pillar_reset_listener(_instance);
if (external_PillarOneWire_send_onewire_pillar_reset_listener != 0x0) external_PillarOneWire_send_onewire_pillar_reset_listener(_instance);
;
}
void (*external_PillarOneWire_send_onewire_pillar_command_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void (*PillarOneWire_send_onewire_pillar_command_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void register_external_PillarOneWire_send_onewire_pillar_command_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t)){
external_PillarOneWire_send_onewire_pillar_command_listener = _listener;
}
void register_PillarOneWire_send_onewire_pillar_command_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t)){
PillarOneWire_send_onewire_pillar_command_listener = _listener;
}
void PillarOneWire_send_onewire_pillar_command(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum){
if (PillarOneWire_send_onewire_pillar_command_listener != 0x0) PillarOneWire_send_onewire_pillar_command_listener(_instance, addr, cmd0, cmd1, csum);
if (external_PillarOneWire_send_onewire_pillar_command_listener != 0x0) external_PillarOneWire_send_onewire_pillar_command_listener(_instance, addr, cmd0, cmd1, csum);
;
}
void (*external_PillarOneWire_send_onewire_pillar_command_with_ack_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void (*PillarOneWire_send_onewire_pillar_command_with_ack_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void register_external_PillarOneWire_send_onewire_pillar_command_with_ack_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)){
external_PillarOneWire_send_onewire_pillar_command_with_ack_listener = _listener;
}
void register_PillarOneWire_send_onewire_pillar_command_with_ack_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)){
PillarOneWire_send_onewire_pillar_command_with_ack_listener = _listener;
}
void PillarOneWire_send_onewire_pillar_command_with_ack(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t ack){
if (PillarOneWire_send_onewire_pillar_command_with_ack_listener != 0x0) PillarOneWire_send_onewire_pillar_command_with_ack_listener(_instance, addr, cmd0, cmd1, csum, ack);
if (external_PillarOneWire_send_onewire_pillar_command_with_ack_listener != 0x0) external_PillarOneWire_send_onewire_pillar_command_with_ack_listener(_instance, addr, cmd0, cmd1, csum, ack);
;
}
void (*external_PillarOneWire_send_onewire_pillar_command_with_response_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void (*PillarOneWire_send_onewire_pillar_command_with_response_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)= 0x0;
void register_external_PillarOneWire_send_onewire_pillar_command_with_response_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)){
external_PillarOneWire_send_onewire_pillar_command_with_response_listener = _listener;
}
void register_PillarOneWire_send_onewire_pillar_command_with_response_listener(void (*_listener)(struct PillarOneWire_Instance *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)){
PillarOneWire_send_onewire_pillar_command_with_response_listener = _listener;
}
void PillarOneWire_send_onewire_pillar_command_with_response(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t rsp0, uint8_t rsp1, uint8_t rsum){
if (PillarOneWire_send_onewire_pillar_command_with_response_listener != 0x0) PillarOneWire_send_onewire_pillar_command_with_response_listener(_instance, addr, cmd0, cmd1, csum, rsp0, rsp1, rsum);
if (external_PillarOneWire_send_onewire_pillar_command_with_response_listener != 0x0) external_PillarOneWire_send_onewire_pillar_command_with_response_listener(_instance, addr, cmd0, cmd1, csum, rsp0, rsp1, rsum);
;
}
void (*external_PillarOneWire_send_onewire_pillar_error_listener)(struct PillarOneWire_Instance *)= 0x0;
void (*PillarOneWire_send_onewire_pillar_error_listener)(struct PillarOneWire_Instance *)= 0x0;
void register_external_PillarOneWire_send_onewire_pillar_error_listener(void (*_listener)(struct PillarOneWire_Instance *)){
external_PillarOneWire_send_onewire_pillar_error_listener = _listener;
}
void register_PillarOneWire_send_onewire_pillar_error_listener(void (*_listener)(struct PillarOneWire_Instance *)){
PillarOneWire_send_onewire_pillar_error_listener = _listener;
}
void PillarOneWire_send_onewire_pillar_error(struct PillarOneWire_Instance *_instance){
if (PillarOneWire_send_onewire_pillar_error_listener != 0x0) PillarOneWire_send_onewire_pillar_error_listener(_instance);
if (external_PillarOneWire_send_onewire_pillar_error_listener != 0x0) external_PillarOneWire_send_onewire_pillar_error_listener(_instance);
;
}



/*****************************************************************************
 * Implementation for type : PillarOneWireLogger
 *****************************************************************************/

// Declaration of prototypes:
//Prototypes: State Machine
void PillarOneWireLogger_PillarOneWireLoggerSC_OnExit(int state, struct PillarOneWireLogger_Instance *_instance);
//Prototypes: Message Sending
//Prototypes: Function
// Declaration of functions:

// Sessions functionss:


// On Entry Actions:
void PillarOneWireLogger_PillarOneWireLoggerSC_OnEntry(int state, struct PillarOneWireLogger_Instance *_instance) {
switch(state) {
case PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_STATE:{
_instance->PillarOneWireLogger_PillarOneWireLoggerSC_State = PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE;
Serial.begin(115200);
					Serial.println("READY");
PillarOneWireLogger_PillarOneWireLoggerSC_OnEntry(_instance->PillarOneWireLogger_PillarOneWireLoggerSC_State, _instance);
break;
}
case PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE:{
break;
}
default: break;
}
}

// On Exit Actions:
void PillarOneWireLogger_PillarOneWireLoggerSC_OnExit(int state, struct PillarOneWireLogger_Instance *_instance) {
switch(state) {
case PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_STATE:{
PillarOneWireLogger_PillarOneWireLoggerSC_OnExit(_instance->PillarOneWireLogger_PillarOneWireLoggerSC_State, _instance);
break;}
case PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE:{
break;}
default: break;
}
}

// Event Handlers for incoming messages:
void PillarOneWireLogger_handle_onewire_pillar_command_with_ack(struct PillarOneWireLogger_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t ack) {
if(!(_instance->active)) return;
//Region PillarOneWireLoggerSC
uint8_t PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 0;
if (_instance->PillarOneWireLogger_PillarOneWireLoggerSC_State == PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE) {
if (PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed == 0 && 1) {
Serial.print(addr,HEX);
Serial.print(" ");
Serial.print(cmd0,HEX);
Serial.print(" ");
Serial.print(cmd1,HEX);
Serial.print(" S");
Serial.print(csum,HEX);
Serial.print(" A");
Serial.print(ack,HEX);
Serial.println();
PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 1;
}
}
//End Region PillarOneWireLoggerSC
//End dsregion PillarOneWireLoggerSC
//Session list: 
}
void PillarOneWireLogger_handle_onewire_pillar_command_with_response(struct PillarOneWireLogger_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t rsp0, uint8_t rsp1, uint8_t rsum) {
if(!(_instance->active)) return;
//Region PillarOneWireLoggerSC
uint8_t PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 0;
if (_instance->PillarOneWireLogger_PillarOneWireLoggerSC_State == PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE) {
if (PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed == 0 && 1) {
Serial.print(addr,HEX);
Serial.print(" ");
Serial.print(cmd0,HEX);
Serial.print(" ");
Serial.print(cmd1,HEX);
Serial.print(" S");
Serial.print(csum,HEX);
Serial.print(" ");
Serial.print(rsp0,HEX);
Serial.print(" ");
Serial.print(rsp1,HEX);
Serial.print(" S");
Serial.print(rsum,HEX);
Serial.println();
PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 1;
}
}
//End Region PillarOneWireLoggerSC
//End dsregion PillarOneWireLoggerSC
//Session list: 
}
void PillarOneWireLogger_handle_onewire_pillar_command(struct PillarOneWireLogger_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum) {
if(!(_instance->active)) return;
//Region PillarOneWireLoggerSC
uint8_t PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 0;
if (_instance->PillarOneWireLogger_PillarOneWireLoggerSC_State == PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE) {
if (PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed == 0 && 1) {
Serial.print(addr,HEX);
Serial.print(" ");
Serial.print(cmd0,HEX);
Serial.print(" ");
Serial.print(cmd1,HEX);
Serial.print(" S");
Serial.print(csum,HEX);
Serial.println();
PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 1;
}
}
//End Region PillarOneWireLoggerSC
//End dsregion PillarOneWireLoggerSC
//Session list: 
}
void PillarOneWireLogger_handle_onewire_pillar_reset(struct PillarOneWireLogger_Instance *_instance) {
if(!(_instance->active)) return;
//Region PillarOneWireLoggerSC
uint8_t PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 0;
if (_instance->PillarOneWireLogger_PillarOneWireLoggerSC_State == PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE) {
if (PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed == 0 && 1) {
Serial.println("RESET");
PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 1;
}
}
//End Region PillarOneWireLoggerSC
//End dsregion PillarOneWireLoggerSC
//Session list: 
}
void PillarOneWireLogger_handle_onewire_pillar_error(struct PillarOneWireLogger_Instance *_instance) {
if(!(_instance->active)) return;
//Region PillarOneWireLoggerSC
uint8_t PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 0;
if (_instance->PillarOneWireLogger_PillarOneWireLoggerSC_State == PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE) {
if (PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed == 0 && 1) {
Serial.println("ERROR");
PillarOneWireLogger_PillarOneWireLoggerSC_State_event_consumed = 1;
}
}
//End Region PillarOneWireLoggerSC
//End dsregion PillarOneWireLoggerSC
//Session list: 
}

// Observers for outgoing messages:



#define timer0_NB_SOFT_TIMER 4
uint32_t timer0_timer[timer0_NB_SOFT_TIMER];
uint32_t  timer0_prev_1sec = 0;



void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id);

uint8_t timer0_interrupt_counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
timer0_interrupt_counter++;
if(timer0_interrupt_counter >= 0) {
timer0_interrupt_counter = 0;
}
}



struct timer0_instance_type {
    uint16_t listener_id;
    /*INSTANCE_INFORMATION*/
} timer0_instance;

void timer0_setup() {
	// Plugging into timer0 
               OCR0A = 0xAF;
               TIMSK0 |= _BV(OCIE0A);


	timer0_prev_1sec = millis() + 1000;
}

void timer0_set_listener_id(uint16_t id) {
	timer0_instance.listener_id = id;
}

void timer0_timer_start(uint8_t id, uint32_t ms) {
if(id <timer0_NB_SOFT_TIMER) {
timer0_timer[id] = ms + millis();
}
}

void timer0_timer_cancel(uint8_t id) {
if(id <timer0_NB_SOFT_TIMER) {
timer0_timer[id] = 0;
}
}

void timer0_timeout(uint8_t id) {
uint8_t enqueue_buf[3];
enqueue_buf[0] = (1 >> 8) & 0xFF;
enqueue_buf[1] = 1 & 0xFF;
enqueue_buf[2] = id;
externalMessageEnqueue(enqueue_buf, 3, timer0_instance.listener_id);
}





void timer0_read() {
    uint32_t tms = millis();
    uint8_t t;
for(t = 0; t < 4; t++) {
if((timer0_timer[t] > 0) && (timer0_timer[t] < tms)) {
timer0_timer[t] = 0;
timer0_timeout(t);
}
}

    if (timer0_prev_1sec < tms) {
        timer0_prev_1sec += 1000;
    }
    
}
// Forwarding of messages timer0::PillarOneWire::clock::timer_start
void forward_timer0_PillarOneWire_send_clock_timer_start(struct PillarOneWire_Instance *_instance, uint8_t id, uint32_t time){
timer0_timer_start(id, time);}

// Forwarding of messages timer0::PillarOneWire::clock::timer_cancel
void forward_timer0_PillarOneWire_send_clock_timer_cancel(struct PillarOneWire_Instance *_instance, uint8_t id){
timer0_timer_cancel(id);}




/*****************************************************************************
 * Definitions for configuration : PillarOneWireTest
 *****************************************************************************/

uint8_t array_pillar_PillarOneWire_rxbuffer_var[6];
//Declaration of instance variables
//Instance logger
// Variables for the properties of the instance
struct PillarOneWireLogger_Instance logger_var;
// Variables for the sessions of the instance
//Instance pillar
// Variables for the properties of the instance
struct PillarOneWire_Instance pillar_var;
// Variables for the sessions of the instance


// Enqueue of messages PillarOneWire::onewire::pillar_command_with_ack
void enqueue_PillarOneWire_send_onewire_pillar_command_with_ack(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t ack){
if ( fifo_byte_available() > 9 ) {

_fifo_enqueue( (2 >> 8) & 0xFF );
_fifo_enqueue( 2 & 0xFF );

// ID of the source port of the instance
_fifo_enqueue( (_instance->id_onewire >> 8) & 0xFF );
_fifo_enqueue( _instance->id_onewire & 0xFF );

// parameter addr
union u_addr_t {
uint8_t p;
byte bytebuffer[1];
} u_addr;
u_addr.p = addr;
_fifo_enqueue(u_addr.bytebuffer[0] & 0xFF );

// parameter cmd0
union u_cmd0_t {
uint8_t p;
byte bytebuffer[1];
} u_cmd0;
u_cmd0.p = cmd0;
_fifo_enqueue(u_cmd0.bytebuffer[0] & 0xFF );

// parameter cmd1
union u_cmd1_t {
uint8_t p;
byte bytebuffer[1];
} u_cmd1;
u_cmd1.p = cmd1;
_fifo_enqueue(u_cmd1.bytebuffer[0] & 0xFF );

// parameter csum
union u_csum_t {
uint8_t p;
byte bytebuffer[1];
} u_csum;
u_csum.p = csum;
_fifo_enqueue(u_csum.bytebuffer[0] & 0xFF );

// parameter ack
union u_ack_t {
uint8_t p;
byte bytebuffer[1];
} u_ack;
u_ack.p = ack;
_fifo_enqueue(u_ack.bytebuffer[0] & 0xFF );
}
}
// Enqueue of messages PillarOneWire::onewire::pillar_command_with_response
void enqueue_PillarOneWire_send_onewire_pillar_command_with_response(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum, uint8_t rsp0, uint8_t rsp1, uint8_t rsum){
if ( fifo_byte_available() > 11 ) {

_fifo_enqueue( (3 >> 8) & 0xFF );
_fifo_enqueue( 3 & 0xFF );

// ID of the source port of the instance
_fifo_enqueue( (_instance->id_onewire >> 8) & 0xFF );
_fifo_enqueue( _instance->id_onewire & 0xFF );

// parameter addr
union u_addr_t {
uint8_t p;
byte bytebuffer[1];
} u_addr;
u_addr.p = addr;
_fifo_enqueue(u_addr.bytebuffer[0] & 0xFF );

// parameter cmd0
union u_cmd0_t {
uint8_t p;
byte bytebuffer[1];
} u_cmd0;
u_cmd0.p = cmd0;
_fifo_enqueue(u_cmd0.bytebuffer[0] & 0xFF );

// parameter cmd1
union u_cmd1_t {
uint8_t p;
byte bytebuffer[1];
} u_cmd1;
u_cmd1.p = cmd1;
_fifo_enqueue(u_cmd1.bytebuffer[0] & 0xFF );

// parameter csum
union u_csum_t {
uint8_t p;
byte bytebuffer[1];
} u_csum;
u_csum.p = csum;
_fifo_enqueue(u_csum.bytebuffer[0] & 0xFF );

// parameter rsp0
union u_rsp0_t {
uint8_t p;
byte bytebuffer[1];
} u_rsp0;
u_rsp0.p = rsp0;
_fifo_enqueue(u_rsp0.bytebuffer[0] & 0xFF );

// parameter rsp1
union u_rsp1_t {
uint8_t p;
byte bytebuffer[1];
} u_rsp1;
u_rsp1.p = rsp1;
_fifo_enqueue(u_rsp1.bytebuffer[0] & 0xFF );

// parameter rsum
union u_rsum_t {
uint8_t p;
byte bytebuffer[1];
} u_rsum;
u_rsum.p = rsum;
_fifo_enqueue(u_rsum.bytebuffer[0] & 0xFF );
}
}
// Enqueue of messages PillarOneWire::onewire::pillar_command
void enqueue_PillarOneWire_send_onewire_pillar_command(struct PillarOneWire_Instance *_instance, uint8_t addr, uint8_t cmd0, uint8_t cmd1, uint8_t csum){
if ( fifo_byte_available() > 8 ) {

_fifo_enqueue( (4 >> 8) & 0xFF );
_fifo_enqueue( 4 & 0xFF );

// ID of the source port of the instance
_fifo_enqueue( (_instance->id_onewire >> 8) & 0xFF );
_fifo_enqueue( _instance->id_onewire & 0xFF );

// parameter addr
union u_addr_t {
uint8_t p;
byte bytebuffer[1];
} u_addr;
u_addr.p = addr;
_fifo_enqueue(u_addr.bytebuffer[0] & 0xFF );

// parameter cmd0
union u_cmd0_t {
uint8_t p;
byte bytebuffer[1];
} u_cmd0;
u_cmd0.p = cmd0;
_fifo_enqueue(u_cmd0.bytebuffer[0] & 0xFF );

// parameter cmd1
union u_cmd1_t {
uint8_t p;
byte bytebuffer[1];
} u_cmd1;
u_cmd1.p = cmd1;
_fifo_enqueue(u_cmd1.bytebuffer[0] & 0xFF );

// parameter csum
union u_csum_t {
uint8_t p;
byte bytebuffer[1];
} u_csum;
u_csum.p = csum;
_fifo_enqueue(u_csum.bytebuffer[0] & 0xFF );
}
}
// Enqueue of messages PillarOneWire::onewire::pillar_reset
void enqueue_PillarOneWire_send_onewire_pillar_reset(struct PillarOneWire_Instance *_instance){
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (5 >> 8) & 0xFF );
_fifo_enqueue( 5 & 0xFF );

// ID of the source port of the instance
_fifo_enqueue( (_instance->id_onewire >> 8) & 0xFF );
_fifo_enqueue( _instance->id_onewire & 0xFF );
}
}
// Enqueue of messages PillarOneWire::onewire::pillar_error
void enqueue_PillarOneWire_send_onewire_pillar_error(struct PillarOneWire_Instance *_instance){
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (6 >> 8) & 0xFF );
_fifo_enqueue( 6 & 0xFF );

// ID of the source port of the instance
_fifo_enqueue( (_instance->id_onewire >> 8) & 0xFF );
_fifo_enqueue( _instance->id_onewire & 0xFF );
}
}


//New dispatcher for messages
void dispatch_pillar_command_with_ack(uint16_t sender, uint8_t param_addr, uint8_t param_cmd0, uint8_t param_cmd1, uint8_t param_csum, uint8_t param_ack) {
if (sender == pillar_var.id_onewire) {
PillarOneWireLogger_handle_onewire_pillar_command_with_ack(&logger_var, param_addr, param_cmd0, param_cmd1, param_csum, param_ack);

}

}


//New dispatcher for messages
void dispatch_pillar_command_with_response(uint16_t sender, uint8_t param_addr, uint8_t param_cmd0, uint8_t param_cmd1, uint8_t param_csum, uint8_t param_rsp0, uint8_t param_rsp1, uint8_t param_rsum) {
if (sender == pillar_var.id_onewire) {
PillarOneWireLogger_handle_onewire_pillar_command_with_response(&logger_var, param_addr, param_cmd0, param_cmd1, param_csum, param_rsp0, param_rsp1, param_rsum);

}

}


//New dispatcher for messages
void dispatch_timer_timeout(uint16_t sender, uint8_t param_id) {
if (sender == timer0_instance.listener_id) {
PillarOneWire_handle_clock_timer_timeout(&pillar_var, param_id);

}

}


//New dispatcher for messages
void dispatch_pillar_command(uint16_t sender, uint8_t param_addr, uint8_t param_cmd0, uint8_t param_cmd1, uint8_t param_csum) {
if (sender == pillar_var.id_onewire) {
PillarOneWireLogger_handle_onewire_pillar_command(&logger_var, param_addr, param_cmd0, param_cmd1, param_csum);

}

}


//New dispatcher for messages
void dispatch_pillar_reset(uint16_t sender) {
if (sender == pillar_var.id_onewire) {
PillarOneWireLogger_handle_onewire_pillar_reset(&logger_var);

}

}


//New dispatcher for messages
void dispatch_pillar_error(uint16_t sender) {
if (sender == pillar_var.id_onewire) {
PillarOneWireLogger_handle_onewire_pillar_error(&logger_var);

}

}


int processMessageQueue() {
if (fifo_empty()) return 0; // return 0 if there is nothing to do

uint8_t mbufi = 0;

// Read the code of the next port/message in the queue
uint16_t code = fifo_dequeue() << 8;

code += fifo_dequeue();

// Switch to call the appropriate handler
switch(code) {
case 2:{
byte mbuf[9 - 2];
while (mbufi < (9 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_pillar_command_with_ack = 2;
union u_pillar_command_with_ack_addr_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_ack_addr;
u_pillar_command_with_ack_addr.bytebuffer[0] = mbuf[mbufi_pillar_command_with_ack + 0];
mbufi_pillar_command_with_ack += 1;
union u_pillar_command_with_ack_cmd0_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_ack_cmd0;
u_pillar_command_with_ack_cmd0.bytebuffer[0] = mbuf[mbufi_pillar_command_with_ack + 0];
mbufi_pillar_command_with_ack += 1;
union u_pillar_command_with_ack_cmd1_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_ack_cmd1;
u_pillar_command_with_ack_cmd1.bytebuffer[0] = mbuf[mbufi_pillar_command_with_ack + 0];
mbufi_pillar_command_with_ack += 1;
union u_pillar_command_with_ack_csum_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_ack_csum;
u_pillar_command_with_ack_csum.bytebuffer[0] = mbuf[mbufi_pillar_command_with_ack + 0];
mbufi_pillar_command_with_ack += 1;
union u_pillar_command_with_ack_ack_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_ack_ack;
u_pillar_command_with_ack_ack.bytebuffer[0] = mbuf[mbufi_pillar_command_with_ack + 0];
mbufi_pillar_command_with_ack += 1;
dispatch_pillar_command_with_ack((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_pillar_command_with_ack_addr.p /* addr */ ,
 u_pillar_command_with_ack_cmd0.p /* cmd0 */ ,
 u_pillar_command_with_ack_cmd1.p /* cmd1 */ ,
 u_pillar_command_with_ack_csum.p /* csum */ ,
 u_pillar_command_with_ack_ack.p /* ack */ );
break;
}
case 3:{
byte mbuf[11 - 2];
while (mbufi < (11 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_pillar_command_with_response = 2;
union u_pillar_command_with_response_addr_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_response_addr;
u_pillar_command_with_response_addr.bytebuffer[0] = mbuf[mbufi_pillar_command_with_response + 0];
mbufi_pillar_command_with_response += 1;
union u_pillar_command_with_response_cmd0_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_response_cmd0;
u_pillar_command_with_response_cmd0.bytebuffer[0] = mbuf[mbufi_pillar_command_with_response + 0];
mbufi_pillar_command_with_response += 1;
union u_pillar_command_with_response_cmd1_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_response_cmd1;
u_pillar_command_with_response_cmd1.bytebuffer[0] = mbuf[mbufi_pillar_command_with_response + 0];
mbufi_pillar_command_with_response += 1;
union u_pillar_command_with_response_csum_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_response_csum;
u_pillar_command_with_response_csum.bytebuffer[0] = mbuf[mbufi_pillar_command_with_response + 0];
mbufi_pillar_command_with_response += 1;
union u_pillar_command_with_response_rsp0_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_response_rsp0;
u_pillar_command_with_response_rsp0.bytebuffer[0] = mbuf[mbufi_pillar_command_with_response + 0];
mbufi_pillar_command_with_response += 1;
union u_pillar_command_with_response_rsp1_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_response_rsp1;
u_pillar_command_with_response_rsp1.bytebuffer[0] = mbuf[mbufi_pillar_command_with_response + 0];
mbufi_pillar_command_with_response += 1;
union u_pillar_command_with_response_rsum_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_with_response_rsum;
u_pillar_command_with_response_rsum.bytebuffer[0] = mbuf[mbufi_pillar_command_with_response + 0];
mbufi_pillar_command_with_response += 1;
dispatch_pillar_command_with_response((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_pillar_command_with_response_addr.p /* addr */ ,
 u_pillar_command_with_response_cmd0.p /* cmd0 */ ,
 u_pillar_command_with_response_cmd1.p /* cmd1 */ ,
 u_pillar_command_with_response_csum.p /* csum */ ,
 u_pillar_command_with_response_rsp0.p /* rsp0 */ ,
 u_pillar_command_with_response_rsp1.p /* rsp1 */ ,
 u_pillar_command_with_response_rsum.p /* rsum */ );
break;
}
case 1:{
byte mbuf[5 - 2];
while (mbufi < (5 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_timer_timeout = 2;
union u_timer_timeout_id_t {
uint8_t p;
byte bytebuffer[1];
} u_timer_timeout_id;
u_timer_timeout_id.bytebuffer[0] = mbuf[mbufi_timer_timeout + 0];
mbufi_timer_timeout += 1;
dispatch_timer_timeout((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_timer_timeout_id.p /* id */ );
break;
}
case 4:{
byte mbuf[8 - 2];
while (mbufi < (8 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_pillar_command = 2;
union u_pillar_command_addr_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_addr;
u_pillar_command_addr.bytebuffer[0] = mbuf[mbufi_pillar_command + 0];
mbufi_pillar_command += 1;
union u_pillar_command_cmd0_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_cmd0;
u_pillar_command_cmd0.bytebuffer[0] = mbuf[mbufi_pillar_command + 0];
mbufi_pillar_command += 1;
union u_pillar_command_cmd1_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_cmd1;
u_pillar_command_cmd1.bytebuffer[0] = mbuf[mbufi_pillar_command + 0];
mbufi_pillar_command += 1;
union u_pillar_command_csum_t {
uint8_t p;
byte bytebuffer[1];
} u_pillar_command_csum;
u_pillar_command_csum.bytebuffer[0] = mbuf[mbufi_pillar_command + 0];
mbufi_pillar_command += 1;
dispatch_pillar_command((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_pillar_command_addr.p /* addr */ ,
 u_pillar_command_cmd0.p /* cmd0 */ ,
 u_pillar_command_cmd1.p /* cmd1 */ ,
 u_pillar_command_csum.p /* csum */ );
break;
}
case 5:{
byte mbuf[4 - 2];
while (mbufi < (4 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_pillar_reset = 2;
dispatch_pillar_reset((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
}
case 6:{
byte mbuf[4 - 2];
while (mbufi < (4 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_pillar_error = 2;
dispatch_pillar_error((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
}
}
return 1;
}

void forward_PillarOneWire_send_clock_timer_start(struct PillarOneWire_Instance *_instance, uint8_t id, uint32_t time){
if(_instance->id_clock == pillar_var.id_clock) {
forward_timer0_PillarOneWire_send_clock_timer_start(_instance, id, time);
}
}
void forward_PillarOneWire_send_clock_timer_cancel(struct PillarOneWire_Instance *_instance, uint8_t id){
if(_instance->id_clock == pillar_var.id_clock) {
forward_timer0_PillarOneWire_send_clock_timer_cancel(_instance, id);
}
}

//external Message enqueue
void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id) {
if ((msgSize >= 2) && (msg != NULL)) {
uint8_t msgSizeOK = 0;
switch(msg[0] * 256 + msg[1]) {
case 1:
if(msgSize == 3) {
msgSizeOK = 1;}
break;
}

if(msgSizeOK == 1) {
if ( fifo_byte_available() > (msgSize + 2) ) {
	uint8_t i;
	for (i = 0; i < 2; i++) {
		_fifo_enqueue(msg[i]);
	}
	_fifo_enqueue((listener_id >> 8) & 0xFF);
	_fifo_enqueue(listener_id & 0xFF);
	for (i = 2; i < msgSize; i++) {
		_fifo_enqueue(msg[i]);
	}
}
}
}
}

void initialize_configuration_PillarOneWireTest() {
// Initialize connectors
register_external_PillarOneWire_send_clock_timer_start_listener(&forward_PillarOneWire_send_clock_timer_start);
register_external_PillarOneWire_send_clock_timer_cancel_listener(&forward_PillarOneWire_send_clock_timer_cancel);
register_PillarOneWire_send_onewire_pillar_reset_listener(&enqueue_PillarOneWire_send_onewire_pillar_reset);
register_PillarOneWire_send_onewire_pillar_command_listener(&enqueue_PillarOneWire_send_onewire_pillar_command);
register_PillarOneWire_send_onewire_pillar_command_with_ack_listener(&enqueue_PillarOneWire_send_onewire_pillar_command_with_ack);
register_PillarOneWire_send_onewire_pillar_command_with_response_listener(&enqueue_PillarOneWire_send_onewire_pillar_command_with_response);
register_PillarOneWire_send_onewire_pillar_error_listener(&enqueue_PillarOneWire_send_onewire_pillar_error);

// Init the ID, state variables and properties for external connector timer0

// Network Initialization

timer0_instance.listener_id = add_instance(&timer0_instance);

timer0_setup();

// End Network Initialization

// Init the ID, state variables and properties for instance pillar
pillar_var.active = true;
pillar_var.id_clock = add_instance( (void*) &pillar_var);
pillar_var.id_onewire = add_instance( (void*) &pillar_var);
pillar_var.PillarOneWire_PillarOneWireSC_State = PILLARONEWIRE_PILLARONEWIRESC_IDLE_STATE;
pillar_var.PillarOneWire_rxbuffer_var = array_pillar_PillarOneWire_rxbuffer_var;
pillar_var.PillarOneWire_rxbuffer_var_size = 6;

PillarOneWire_PillarOneWireSC_OnEntry(PILLARONEWIRE_PILLARONEWIRESC_STATE, &pillar_var);
// Init the ID, state variables and properties for instance logger
logger_var.active = true;
logger_var.id_onewire = add_instance( (void*) &logger_var);
logger_var.PillarOneWireLogger_PillarOneWireLoggerSC_State = PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_LOGGING_STATE;

PillarOneWireLogger_PillarOneWireLoggerSC_OnEntry(PILLARONEWIRELOGGER_PILLARONEWIRELOGGERSC_STATE, &logger_var);
}




void setup() {
initialize_configuration_PillarOneWireTest();

}

void loop() {

// Network Listener
timer0_read();
// End Network Listener


    processMessageQueue();
}
