Serial myPort1; // The first serial port
Serial myPort2; // The second serial port

int xPos1 = 1;  // Horizontal position for the first graph
int xPos2 = 1;  // Horizontal position for the second graph
boolean newData = false;
float inByte1 = 0;  // Data for the first graph
float inByte2 = 0;  // Data for the second graph
int lastxPos=1;
int lastheight=0;

void setup() {
  // Set the window size:
  size(800, 300);

  // List all the available serial ports
  // If using Processing 2.1 or later, use Serial.printArray()
  println(Serial.list());

  // Open the first serial port
  myPort1 = new Serial(this, Serial.list()[2], 9600);

  // Open the second serial port
  myPort2 = new Serial(this, Serial.list()[3], 9600);

  // Don't generate a serialEvent() unless you get a newline character:
  myPort1.bufferUntil('\n');
  myPort2.bufferUntil('\n');

  // Set the initial background:
  background(0);
}

void draw() {
  // Draw the line for the first graph:
  stroke(127, 34, 255);
  line(xPos1, height, xPos1, height - inByte1);

  // Draw the line for the second graph:
  stroke(255, 34, 127);
  line(xPos2, height, xPos2, height - inByte2);

  // Increment the horizontal positions:
  xPos1++;
  xPos2++;

  // At the edge of the screen, go back to the beginning:
  if (xPos1 >= width) {
    xPos1 = 0;
          background(0);

  }
  if (xPos2 >= width) {
    xPos2 = 0;
          background(0);

  }
}

void serialEvent(Serial myPort) {
  // Get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // Trim off any whitespace:
    inString = trim(inString);

    // Convert to a float and map to the screen height:
    float inByte = float(inString);

    // Assign the value to the appropriate variable based on the serial port:
    if (myPort == myPort1) {
      inByte1 = map(inByte, 0, 1023, 0, height);
    } else if (myPort == myPort2) {
      inByte2 = map(inByte, 0, 1023, 0, height);
    }
  }
}
