Hexapod
=======

0b00 - Start communication in manual mode
0b01 - Start communication in auto mode
0b10 - Next bite
0b11 - End of message

Manual:
0b00|x x x x x x
0b10|L L L L L L 
0b10|L T T T T T
0b11|S S S S S P

Auto:
0b01|C C C C C C
0b11|S S S S S P

x - wchich leg is to be activated (1-6)
L - lift position
T - turn position
S - speed
P - power on(1)/power off(0)
C - command
