Serial myPort1; // The first serial port
Serial myPort2; // The second serial port

int xPos1 = 1;  // Horizontal position for the first graph
int xPos2 = 1;  // Horizontal position for the second graph
boolean newData = false;
float inByte1 = 0;  // Data for the first graph
float inByte2 = 0;  // Data for the second graph
int lastxPos=1;
int lastheight=0;

// Variables for the additional windows
PWindow graphWindow1;
PWindow graphWindow2;

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

  // Initialize the additional windows
  graphWindow1 = new PWindow(color(127, 34, 255));
  graphWindow2 = new PWindow(color(255, 34, 127));
}

void draw() {
  // Draw the line for the main graph:
  stroke(255);
  line(xPos1, height, xPos1, height - inByte1);
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

// Define the secondary window as a subclass of PApplet
class PWindow extends PApplet {
  // Color for the graph lines in the additional windows
  int lineColor;

  // Constructor for the secondary window
  PWindow(int lineColor) {
    super(); // Call the constructor of the superclass (PApplet)
    this.lineColor = lineColor;
    PApplet.runSketch(new String[] {this.getClass().getSimpleName()}, this);
  }

  // Set up the secondary window size and background
  void settings() {
    size(800, 100);
  }

  // Initial setup for the secondary window
  void setup() {
    background(0); // Set background color to black
  }

  // Drawing loop for the secondary window
  void draw() {
    stroke(lineColor);
    line(lastxPos, height - lastheight, xPos1, height - inByte1);
    lastxPos = xPos1;
    lastheight = int(inByte1);
  }
}
