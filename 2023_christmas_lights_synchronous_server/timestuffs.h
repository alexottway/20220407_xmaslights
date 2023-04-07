//************TIME FUNCTION***********

String printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    failCount++;
    if (failCount == 6)
    {
      ESP.restart();
    }
    printLocalTime();
    //    return"Bugger";
  }

  char output1[80];
  strftime(output1, 80, "%H", &timeinfo);
  current_hour = String(output1);

  char output2[80];
  strftime(output2, 80, "%M", &timeinfo);
  current_minute = String(output2);

  char output3[80];
  strftime(output3, 80, "%S", &timeinfo);
  current_second = String(output3);

  char output4[80];
  strftime(output4, 80, "%w", &timeinfo);
  current_weekday = String(output4);

  char output[80];
  strftime(output, 80, "%A, %B %d, %Y \n %H:%M:%S", &timeinfo);
  time_str = String(output);
  return time_str;
}
//***********TIME FUNCTION ends*******
