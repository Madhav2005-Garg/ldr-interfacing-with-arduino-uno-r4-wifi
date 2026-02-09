#include <Arduino.h>
int ldr_Pin=A0;
void setup() {
// write your initialization code here
    pinMode(ldr_Pin, INPUT);
    Serial.begin(9600);
}

void loop() {
// write your code here
    int ldrValue=analogRead(ldr_Pin);
    int ldrPercent=map(ldrValue, 0, 1023, 0, 100);
    Serial.print("LDR Value: ");
    Serial.print(ldrValue);
    Serial.print(" - LDR Percent: ");
    Serial.print(ldrPercent);
    Serial.println("%");
    delay(1000); // Delay for 1 second before the next reading


}