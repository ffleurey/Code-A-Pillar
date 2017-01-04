# Flash A Pillar

This sketch implements the code a pillar protocol to communicate with the Code-a-Pillar tail.

Connections: Data bus to arduino pin 2 and "enable" on arduino pin 3.

The sketch periodically resets the bus and discovers the tail in the order of the blocks. It then flashes the blocks and blink them.

The order of the blocks is written on the serial port.