#include <Keypad.h>

char password[] = "3690"; // Define the password
int passwordLength = 4; // Length of the password
int position = 0; // Position in the entered password

const byte ROWS = 4; // Number of rows in the keypad
const byte COLS = 4; // Number of columns in the keypad

// Define the keypad layout
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define the pin connections for rows and columns
byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

// Initialize the keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int Lock = 5; // Pin connected to the relay module controlling the lock

void setup() {
  pinMode(Lock, OUTPUT); // Set lock pin as output
  LockedPosition(true); // Lock the system initially
}

void loop() {
  char key = keypad.getKey(); // Get the pressed key
  
  if (key != NO_KEY) { // If a key is pressed
    if (key == '*' || key == 'A') { // Check if the lock key is pressed
      position = 0; // Reset the position
      LockedPosition(true); // Lock the system
    } else if (key == password[position]) { // Check if entered key matches password
      position++; // Move to the next position in the password
    }
    
    if (position == passwordLength) { // If entire password is entered correctly
      LockedPosition(false); // Unlock the system
      position = 0; // Reset the position for next use
    }
  }
  
  delay(100); // Delay for stability
}

void LockedPosition(bool locked) {
  if (locked) {
    digitalWrite(Lock, LOW); // Lock the system
  } else {
    digitalWrite(Lock, HIGH); // Unlock the system
  }
}
