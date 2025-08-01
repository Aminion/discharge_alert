# Discharge alert module
Module signaling about low (3.6) and critical(3.2) voltage level
# Hardware description:
Designed for Attiny85. Uses comparation between battery voltage (pin A1, downscaled with a voltage divider to 2.5V at 4.2V input (via a variable resistor 50kOhm) and external reference voltage (AREF pin, TL431A as source with interconnected emmiter and collector).
Note that both the reference and measured source voltage should be less than Vcc for the microcontroller itself. One beep each hour for LOW and two beeps for CRITICAL via active buzzer on pin 1 (controlled with BC547 transistor with 500 Ohm resistor in base).
# Software description:
I used a chip with a Micronucleus bootloader(flashed via Arduino Uno as SPI) plus HW-260 board. after this you can simply:

    pio run -t upload

Note: you need appropriate rights to access USB:

    extraGroups = [ "udev" ];
    # ATtiny boards with Micronucleus bootloader (Digispark, Adafruit Trinket, etc.)
    SUBSYSTEM=="usb", ATTR{idVendor}=="16d0", ATTR{idProduct}=="0753", MODE="0666"
    SUBSYSTEM=="usb", ATTR{idVendor}=="1781", ATTR{idProduct}=="0c9f", MODE="0666"
    ''; 
Then plug in the board within seconds (bootloader wait time) and it will be flashed.
