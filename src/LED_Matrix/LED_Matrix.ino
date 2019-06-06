#include"matrix.h"

Matrix<int> m(3, 5);
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    m.set_size(10, 10);
    m.set_value(90, 9, 9);
    Serial.println(m.get_value(9, 9));
    m.set_size(5, 5);
    m.get_value(4, 4) = 10;
    Serial.println(m.get_value(4, 4));
    delay(100);
}
