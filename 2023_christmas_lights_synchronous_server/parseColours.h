void parseColour0(String colour0) {
  colour0.remove(0, 1);
  colour0.toUpperCase();

  Serial.print("In function parsecolour0 received colour0 is: ");
  Serial.println(colour0);
  long number = (long) strtol( &colour0[0], NULL, 16);

  r0 = number >> 16;
  g0 = number >> 8 & 0xFF;
  b0 = number & 0xFF;
  vTaskDelay(1);
}

void parseColour1(String colour1) {
  colour1.remove(0, 1);
  colour1.toUpperCase();

  Serial.print("In function parsecolour1 received colour1 is: ");
  Serial.println(colour1);
  long number = (long) strtol( &colour1[0], NULL, 16);

  r1 = number >> 16;
  g1 = number >> 8 & 0xFF;
  b1 = number & 0xFF;
  vTaskDelay(1);
}


void parseColour2(String colour2) {
  colour2.remove(0, 1);
  colour2.toUpperCase();

  Serial.print("In function parsecolour2 received colour2 is: ");
  Serial.println(colour2);
  long number = (long) strtol( &colour2[0], NULL, 16);

  r2 = number >> 16;
  g2 = number >> 8 & 0xFF;
  b2 = number & 0xFF;
  vTaskDelay(1);
}
