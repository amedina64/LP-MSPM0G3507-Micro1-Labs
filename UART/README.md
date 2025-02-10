## Demo Codes for UART

### Add Explanation to calculate values for certain registers

## MAC and Linux Serial Communication
To see serial communication, open up a terminal. We'll be using the cu command to see serial data. Give it the serial port you will be accessing the MSPM0 and the desired baud rate

sudo cu --line /dev/"type serialPort" -- speed 115200

To select the correct COM port to use, on a terminal change into the dev directory
cd /dev/
then type ls. Then identify the com port for the MSPM0

For my Mac, the XDS110 debugger is shown as tty.usbmodemMG3500011 and tty.usbmodemMG3500014

The name might be different on your machine. Run below command (assuming you already cd into /dev/) 

sudo cu --line tty.usbmodemMG3500011 --speed 115200

For more info "https://commandmasters.com/commands/cu-linux/" or type "man cu" into the terminal