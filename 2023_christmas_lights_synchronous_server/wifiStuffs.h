const char* ssid       = "Alex_BT";
const char* password   = "1865Nottinghamffc";

#ifdef DEBUG
IPAddress local_IP(192, 168, 0, 81);
#else
IPAddress local_IP(192, 168, 0, 80);
#endif


IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress secondaryDNS(1, 1, 1, 1); //optional
IPAddress primaryDNS(192, 168, 0, 1); //optional
String sitetitle      = "Window_Lights";               // Appears on the tabe of a Web Browser

void connectWifi()
{
  WiFi.disconnect();
  delay(1000);
  Serial.println("\nAttempting to establish wifi connection...");
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
//  WiFi.config(local_IP, gateway, subnet);
  //  WiFi.begin(ssid, password);
  WiFi.begin(ssid, password);
  //  WiFi.config(ip, gateway, subnet);

  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 10))
  {
    retries++;
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED_WIFI_OK, HIGH);
  Serial.println(" CONNECTED");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.printf("Connected to %s ", ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  IPAddress myip = WiFi.localIP();
  if (myip != NULL) {
    ipstring = String(myip[0]) + "." + myip[1] + "." + myip[2 ] + "." + myip[3];
  } else {
    ipstring = "IP temporary error";
  }


  
}
