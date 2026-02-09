# LDR interfacing with Arduino Uno R4 WiFi

Brief project README for reading an LDR (photoresistor) with `Arduino Uno R4 WiFi`, reporting values over serial and optionally via WiFi.

## Contents
1. Project overview
2. Hardware
3. Wiring
4. Files
5. Build / Upload
6. Usage
7. How the code works
8. Calibration & troubleshooting
9. License

## 1\. Project overview
This project reads an analog LDR value, converts it to a normalized/light-level value, prints it to `Serial`, and can optionally send readings over WiFi (using the R4 WiFi stack). It is intended for `Arduino IDE` or `arduino-cli`.

## 2\. Hardware
- `Arduino Uno R4 WiFi`
- LDR (photoresistor)
- 10kΩ resistor (for voltage divider)
- Breadboard and jumper wires
- USB-C cable for programming and serial

## 3\. Wiring
1. Create a voltage divider:
   1. Connect one end of the LDR to `5V`.
   2. Connect the other end of the LDR to `A0` and to one end of the 10kΩ resistor.
   3. Connect the other end of the 10kΩ resistor to `GND`.
2. `A0` reads the divider midpoint.

Simple ASCII:
\`\`\`
5V --- LDR ---+--- A0 (analog input)
              |
            10kΩ
              |
GND ----------+
\`\`\`

## 4\. Files
- `README.md` (this file)
- `src/ldr.ino` — main Arduino sketch (reads analog, prints, optional WiFi send)
- `lib/` — optional libraries or helper files (if present)

If your repository uses a different file layout, adjust the filenames above accordingly.

## 5\. Build / Upload
Option A: Arduino IDE
1. Open `src/ldr.ino` in Arduino IDE.
2. Select board: `Arduino Uno R4 WiFi`.
3. Select correct serial port.
4. Upload.

Option B: arduino-cli
1. Install `arduino-cli`.
2. Compile:
   1. `arduino-cli compile --fqbn arduino:avr:uno src`
3. Upload:
   1. `arduino-cli upload -p COM3 --fqbn arduino:avr:uno src`

(Replace `COM3` and fully-qualified board name as appropriate for R4 WiFi in your CLI core.)

## 6\. Usage
1. Open Serial Monitor at `115200` baud.
2. Observe raw analog readings (0–1023) and normalized percentages.
3. If WiFi is enabled in the sketch, readings will also be sent to the configured server/endpoint.

## 7\. How the code works
Brief explanation followed by an example sketch. The sketch:
1. Reads `A0` with `analogRead`.
2. Maps the reading to 0–100% for readability.
3. Prints to `Serial`.
4. Optionally connects to WiFi and sends readings periodically.

Example sketch:

```cpp
// Example Arduino sketch: src/ldr.ino
// Reads LDR on A0, prints value and percentage to Serial

const int LDR_PIN = A0;
const unsigned long INTERVAL_MS = 1000;

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for Serial */ }
  pinMode(LDR_PIN, INPUT);
  Serial.println("LDR reader started");
  // Optional: initialize WiFi here if required
}

void loop() {
  unsigned long now = millis();
  if (now - lastMillis < INTERVAL_MS) return;
  lastMillis = now;

  int raw = analogRead(LDR_PIN);           // 0..1023
  float percent = (raw / 1023.0f) * 100.0f;

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("  Percent: ");
  Serial.print(percent, 1);
  Serial.println("%");

  // Optional: send over WiFi / HTTP here
}
```

## 8\. Calibration & troubleshooting
1. Readings too noisy: add small capacitor (e.g., 0.1µF) across LDR/resistor, or average multiple samples in software.
2. Always verify wiring: sensor to `5V`, resistor to `GND`, midpoint to `A0`.
3. If `Serial` shows nothing: confirm correct baud (`115200`) and board port.
4. WiFi fails: ensure correct credentials, check library support for R4 WiFi, and update cores/libraries.

## 9\. License
Use or adapt this project under an appropriate open-source license. Add `LICENSE` to the repo as needed.

End of README.
