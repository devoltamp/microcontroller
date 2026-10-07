const int SCR1_PIN = 8;
const int SCR2_PIN = 9;

void setup() {
    pinMode(SCR1_PIN, OUTPUT);
    pinMode(SCR2_PIN, OUTPUT);

    digitalWrite(SCR1_PIN, LOW);
    digitalWrite(SCR2_PIN, LOW);
}

void loop() {
    /* 3 - sec */
    digitalWrite(SCR1_PIN, HIGH);
    digitalWrite(SCR2_PIN, HIGH);
    delay(3000);

    /* 2 - sec */
    digitalWrite(SCR1_PIN, LOW);
    digitalWrite(SCR2_PIN, LOW);
    delay(2000);
}

/* notes;
 *
 * IO8 -> Optocoupler U4 -> SCR U2
 * & IO9 -> Optocoupler U5 -> SCR U3
 */
