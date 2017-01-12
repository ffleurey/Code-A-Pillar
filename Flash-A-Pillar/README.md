# Flash-A-Pillar

This sketch implements protocol to communicate with the Code-a-Pillar tail. The head/body of the code a pillar is replaced by an Arduino which can discover the tail and send commands to the different modules.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=aNHJMacFLYw" target="_blank"><img src="http://img.youtube.com/vi/aNHJMacFLYw/0.jpg" 
alt="youtube video" width="320" height="240" border="10" /></a>

## Protocol

When first connected, the tail blocks are waiting for a reset to happen on the bus in order to initialize. Upon reset, the modules are initialized in the order they are connected on the bus and get their address on the bus. Addresses start at 1 for the first block which is connected to the head (or Arduino is our case). The order in which blocks are initialized is enforced by the "enable" signals. Upon reset all blocks set their enable signals high. The head keeps it low. After the reset, only one block has a low "enable": the one connected to the head. After it is initialized, it sets its "enable" line low in order to allow the second block to initialize. It works the same for the rest of the tail.

During the initialisation, the head send "discover" initialization messages starting with address 1 and increments the address as long as it gets replies from the tail. In the reply to the initialization messages, the tail blocks indicate their types and implicitly acknowledge their address. After the initialization, the master thus has fully discovered the order and types of the blocks that makes up the tail.

Once the blocks are initialized, there are 5 main commands the head can send to individual blocks (there are also a few broadcast commands but they are not yet implemented in the sketch):
 
 * **DISCOVER**: That is the commend used for the initialization. In normal use, the head is periodically sending discover messages with the first non allocated address (address of the last block + 1) in order to detect if any new blocks are connected to the tail.
 * **PING**: Ping the address of one block. The block acknowledges the packet to indicate that it is still present and running. In the normal use of the code-a-pillar, the head is constantly pinging the tail blocks in order to detect if and block have been disconnected.
 * **LED_ON**: Turn the LED of the block ON.
 * **LED_OFF**: Turn the LED of the block OFF.
 * **LED_BLINK**: Blink the LED of the block.

All commands are acknowledged by the blocks.

## Hardware

* Arduino Uno (or any other arduino flavour)
* A USB female connector (For example from a USB extension cable)

Code-a-pillar data bus is connected to arduino pin 2 and "enable" on arduino pin 3 (or connected to ground).

## Software

The sketch periodically resets the bus and discovers the tail in the order of the blocks. It then flashes the blocks and blink them.

The order of the blocks is written on the serial port.
