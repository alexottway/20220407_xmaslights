/*
  Things still to do
  Topper Pattern Selection ----------DONE
  Get time and see if system works -----DONE
  Scheduler
  Remember settings via EEPROM
  OTA Web update
*/

#define DEBUG

//If you have #define as an ACTUAL line, the device will configure in test mode with IP address 81
//If you don't, it'll be the LIVE version with IP 80
//DEBUG also sets num_leds to 150 for testing with single strip

#include <Preferences.h>  //The successor to EEPROM
#include <WiFi.h>
#include <WiFiClient.h>
#include "time.h"
#include <ArduinoOTA.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <FastLED.h>
#include <SPIFFS.h>
#include "style_file.h"

Preferences preferences;

//TIME STUFF

const char* ntpServer = "pool.ntp.org";
String time_str;
int failCount = 0;
String current_hour;
String current_minute;
String current_second;
String current_weekday;
int current_hour_int;
int current_minute_int;
int current_second_int;
int current_weekday_int;
int scheduleDaysPicker;
String scheduleButtonText;
bool allowSchedulerChanges = false;

String daychoice;
const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
byte schedule[7][24][4] = {};
int address = 0;
int d;
int h;
int quarter;
int r;
bool scheduleEnabled = false;
bool scheduledLightsOn = false;

String ipstring = "";
String webpage;
String homepage;
String applyGlitter = "off";
String applyTopper = "off";
String applyTopperGlitter = "off";

uint8_t gHue = 0;
uint8_t cometColour;
uint8_t localHue = 0;

int bright = 60;
int r0 = 0x00;
int g0 = 0x00;
int b0 = 0xFF;
int r1 = 0xFF;
int g1 = 0xFF;
int b1 = 0xFF;
int r2 = 0xff;
int g2 = 0x00;
int b2 = 0x00;
int r3 = 0xFF;
int g3 = 0xFF;
int b3 = 0x00;

String colour0 = "#0000ff";
String colour1 = "#ffffff";
String colour2 = "#ff0000";

//bright2 becomes lethargy
int bright2 = 250;

int changeRate;
int numberRainbows = 4;
String XML;
String busyReady = "";
String busyReady2 = "";
String busyReady3 = "";
String busyReady4 = "";
String busyReady5 = "";
String lightFunction = "Off";  //Sets initial lights status to OFF. Will be overridden by EEPROM settings later
String previouslightFunction = "Off";
String topperPattern = "TopperRed";

int currentColour;
int currentPosition;
int lastPosition;
byte numberOfColours;
byte numberOfTopperColours;
byte previousColour;
bool colourUpdated = false;

int topperColour = 0;
int topperLength = 5;

// Define variables used by the confetti sequences.
uint8_t thisfade = 2;   // How quickly does it fade? Lower = slower fade rate.
int thishue = 50;       // Starting hue.
uint8_t thisinc = 1;    // Incremental value for rotating hues
uint8_t thissat = 200;  // The saturation, where 255 = brilliant colours.
uint8_t thisbri = 255;  // Brightness of a sequence. Remember, max_bright is the overall limiter.
int huediff = 256;      // Range of random #'s to use for hue
//*****

const char* PARAM_INPUT = "value";  //for slider
String sliderValue = "30";
String slider2Value = "250";

#define LED_WIFI_OK 27
#define DATA_PIN 14

#ifdef DEBUG
#define NUM_LEDS 300  //Single Strip length = 150
const char* hostnamestring = "debug";
#else
#define NUM_LEDS 600
const char* hostnamestring = "ChristmasLights";
#endif

CRGB leds[NUM_LEDS];
uint32_t colour[] = { CRGB::Blue, CRGB::Orange, CRGB::Red, CRGB::Green, CRGB::Gold, CRGB::Cyan, CRGB::Magenta, CRGB::White };  //Colour array for autosequence
//uint32_t buntingcolour[] = {CRGB::Red, CRGB::White, CRGB::Blue}; //Colour array for bunting
uint32_t toppercolour[] = { CRGB::Blue, CRGB::Red, CRGB::Green, CRGB::Silver, CRGB::Gold, CRGB::Cyan, CRGB::Magenta, CRGB::White, CRGB::Orange };  //Colour array for autosequence

CRGB topperpixelcolour;

#include "timestuffs.h"
#include "wifiStuffs.h"
#include "homepage.h"  //imports homepage_content
#include "addGlitter.h"
#include "parseColours.h"

WebServer server(80);  //Set up web server

#include "serverStuffs.h"

//Server Config ends
//************************************************************************VOID SETUP BEGINS
void setup() {
  Serial.begin(2000000);
  Serial.println("Void Setup started");

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }


  //spiffs dump

  Serial.println("SPIFFS File list: ");
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.print("FILE: ");
    Serial.println(file.name());


    //SET UP SERVER TO SERVE ALL FILES IN ROOT
    String fileName = file.name();
    if (fileName.endsWith(".jpg") || fileName.endsWith(".jpeg") || fileName.endsWith(".png") || fileName.endsWith(".gif")) {
      String mimeType = "image/jpeg";
      if (fileName.endsWith(".png")) {
        mimeType = "image/png";
      } else if (fileName.endsWith(".gif")) {
        mimeType = "image/gif";
      }
      Serial.println("server.on(\"" + fileName + "\", [" + fileName + ", " + mimeType + "]...");
      //      server.on("/" + fileName, []() {
      server.on(fileName, [fileName, mimeType]() {
        File file = SPIFFS.open(fileName, "r");
        server.streamFile(file, mimeType);
        file.close();
      });
    }

    //END FILE SERVE SETUP
    //  server.on("/Christmas-Tree256.ico", [](){
    //    File file = SPIFFS.open("/Christmas-Tree256.ico", "r");
    //    server.streamFile(file, "image/ico");
    //    file.close();
    //  }); //and that's how you code for an image in SPIFFS


    file = root.openNextFile();
  }
  Serial.println(" Done.");
  //spiffs dump ends
  preferences.begin("settings", true);  // open preferences as READ ONLY
  lightFunction = preferences.getString("lightFunction", "Off");

  colour0 = preferences.getString("colour0", colour0);
  colour1 = preferences.getString("colour1", colour1);
  colour2 = preferences.getString("colour2", colour2);
  //Colour hex values need parsing into R G B values, so send them to the parser...
  parseColour0(colour0);
  parseColour1(colour1);
  parseColour2(colour2);

  byte tempdata[672] = {};  // Create a temp array to grab schedule data.
  //    Serial.println("Retrieving the value of preferences into tempdata.");
  //    Serial.println("   - Note the data type of myIntBuffer matches that of myArray");
  preferences.getBytes("schedule", tempdata, preferences.getBytesLength("schedule"));
  //Now reformat the data into the scheduler 3-d array
  int tempindex = 0;
  for (d = 0; d < 7; d++) {
    for (h = 0; h < 24; h++) {
      for (quarter = 0; quarter < 4; quarter++) {
        schedule[d][h][quarter] = tempdata[tempindex];  //Iterate through schedule
        tempindex++;
      }
    }
  }
  tempindex = 0;

  Serial.println("Schedule Data read from Preferences");

  topperPattern = preferences.getString("topperPattern", topperPattern);
  topperLength = preferences.getInt("topperLength", topperLength);
  bright = preferences.getInt("bright", bright);
  applyGlitter = preferences.getString("applyGlitter", applyGlitter);
  applyTopperGlitter = preferences.getString("applyTopperGlitter", applyTopperGlitter);
  applyTopper = preferences.getString("applyTopper", applyTopper);
  numberRainbows = preferences.getInt("numberRainbows", numberRainbows);
  bright = preferences.getInt("bright", bright);
  bright2 = preferences.getInt("bright2", bright2);
  scheduleEnabled = preferences.getBool("scheduleEnabled", false);

  Serial.println("Previous Settings read from Preferences");
  preferences.end();  //close preferences

  //****************************************LEDS REBOOT CONFIGURATION
  //////Serial.println("Setting up LEDs");
  LEDS.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  leds[0].setHSV(60, 100, 50);
  //FastLED.show();
  delay(1000);
  FastLED.setBrightness(bright);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  //set all to black
  FastLED.setBrightness(20);
  leds[0] = 0x160000;
  FastLED.show();  //Show dim red LED until wifi is set up
  //****************************************LEDS REBOOT CONFIGURATION ENDS


  pinMode(LED_WIFI_OK, OUTPUT);
  connectWifi();

  //****Once wifi connected, get time

  //init and get the time
  configTime(0, 0, ntpServer);
  setenv("TZ", "GMT0BST,M3.5.0/1,M10.5.0/2", 1);
  Serial.println("Setting up time");
  printLocalTime();

  // Setup OTA
#ifdef DEBUG
  ArduinoOTA.setHostname("WindowLightsTest");
#else
  ArduinoOTA.setHostname("WindowLightsLive");
#endif
  ArduinoOTA.setHostname((const char*)sitetitle.c_str());
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else  // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      //////Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      //////Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      //////Serial.printf("Progress: % u % % \r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR)
        Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR)
        Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR)
        Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR)
        Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  vTaskDelay(10);
  busyReady = " Ready";

  numberOfColours = (sizeof(colour) / sizeof(colour[0]));
  numberOfTopperColours = (sizeof(toppercolour) / sizeof(toppercolour[0]));

  if (!MDNS.begin(hostnamestring)) {
    Serial.println("Error starting mDNS");
    return;
  }

  //**************************************************
  server.on("/", handle_OnConnect);                        //done
  server.on("/xml", handleXML);                            //done
  server.on("/select.htm", handle_lightsfunction_select);  //done
  server.on("/slider", handle_slider1);                    //done
  server.on("/slider2", handle_slider2);                   //done
  server.on("/scheduleedit.htm", handle_scheduleedit);     //done
  server.on("/submit.htm", handle_submit);
  server.on("/topper.htm", handle_topper);
  server.on("/schedulechooser.htm", handle_schedulechooser);
  server.on("/wipeschedule.htm", handle_wipe_schedule);
  server.serveStatic("/favicon.ico", SPIFFS, "/favicon/tree32.png");  //That's how favicon works

  //**************************************************
  server.begin();
  Serial.println("HTTP server started");
}
//*************************************************SETUP ENDS



//**********************************************LOOP BEGIN
void loop() {
  server.handleClient();  //Poll the webserver
  ArduinoOTA.handle();    //...and the OTA handler every time loop loops

  printLocalTime();  //step 1 - get hold of the time

  current_hour_int = current_hour.toInt();
  current_minute_int = current_minute.toInt();
  current_second_int = current_second.toInt();
  current_weekday_int = current_weekday.toInt();  //Parse the

  //*********************Schedule Checker

  if ((current_minute_int == 0) && (current_second_int < 5))  //At the top of the minute.....iterate 4 times for 4 quarter-hours
  {
    if ((schedule[current_weekday_int][current_hour_int][0]) == 1) {
      scheduledLightsOn = true;
      allowSchedulerChanges = true;
    }
  }

  if ((current_minute_int == 0) && (current_second_int < 5)) {
    if ((schedule[current_weekday_int][current_hour_int][0]) == 2) {
      scheduledLightsOn = false;
      allowSchedulerChanges = true;
    }
  }

  //**********************^0 v15
  if ((current_minute_int == 15) && (current_second_int < 5))  //iterate 4 times for 4 quarter-hours
  {
    if ((schedule[current_weekday_int][current_hour_int][1]) == 1) {
      scheduledLightsOn = true;
      allowSchedulerChanges = true;
    }
  }

  if ((current_minute_int == 15) && (current_second_int < 5)) {
    if ((schedule[current_weekday_int][current_hour_int][1]) == 2) {
      scheduledLightsOn = false;
      allowSchedulerChanges = true;
    }
  }
  //********************^15 v30
  if ((current_minute_int == 30) && (current_second_int < 5))  //iterate 4 times for 4 quarter-hours
  {
    if ((schedule[current_weekday_int][current_hour_int][2]) == 1) {
      scheduledLightsOn = true;
      allowSchedulerChanges = true;
    }
  }

  if ((current_minute_int == 30) && (current_second_int < 5)) {
    if ((schedule[current_weekday_int][current_hour_int][2]) == 2) {
      scheduledLightsOn = false;
      allowSchedulerChanges = true;
    }
  }
  //********************
  if ((current_minute_int == 45) && (current_second_int < 5))  //iterate 4 times for 4 quarter-hours
  {
    if (schedule[current_weekday_int][current_hour_int][3] == 1) {
      scheduledLightsOn = true;
      allowSchedulerChanges = true;
    }
  }

  if ((current_minute_int == 45) && (current_second_int < 5)) {
    if (schedule[current_weekday_int][current_hour_int][3] == 2) {
      scheduledLightsOn = false;
      allowSchedulerChanges = true;
    }
  }
  //*****************************Schedule Checker ends



  //Deal with status message at foot of web interface

  busyReady = "Main Lights: ";
  busyReady += lightFunction;

  if (lightFunction == "multiRainbow") {
    busyReady += " (";
    busyReady += numberRainbows;
    busyReady += " rainbows along a strip)";
  }
  busyReady += ". ";
  busyReady += "Glitter: ";
  busyReady += applyGlitter;
  busyReady += ".";
  //busyReady (no number) is pattern/on-off/glitter (main)
  //busyReady2 is speed & brightness

  busyReady2 = "Brightness: ";
  busyReady2 += bright;
  busyReady2 += ". Display update rate: ";
  busyReady2 += bright2;

  busyReady3 = "Separate Top Lighting: ";
  busyReady3 += applyTopper;
  busyReady3 += ". Length: ";
  busyReady3 += topperLength;
  busyReady3 += ". Top Glitter: ";
  busyReady3 += applyTopperGlitter;
  busyReady3 += ". Top Pattern: ";
  busyReady3 += topperPattern;

  busyReady4 = "System date and time: ";
  busyReady4 += time_str;
  busyReady4 += ". Scheduler is ";
  if (scheduleEnabled) {
    busyReady4 += "ENABLED.";
  }
  if (!scheduleEnabled) {
    busyReady4 += "DISABLED.";
  }

  busyReady5 = "Page address: http://";
  busyReady5 += hostnamestring;
  busyReady5 += ".local or ";
  busyReady5 += ipstring;
  busyReady5 += " ";


  //*****************************************Housekeeping and master hue increment control

  EVERY_N_MILLIS_I(thisTimer, 1) {
    thisTimer.setPeriod((1001 - bright2) / 2);
    gHue++;
    localHue++;         //Master base colour change rate
    currentPosition++;  //increment linear position with non blocking delay
    // if (currentPosition == NUM_LEDS) {
    //   currentPosition = 0;
    // }
    if (applyTopper == "off") {
      currentPosition = currentPosition % NUM_LEDS;
    }
    if (applyTopper == "on") {
      currentPosition = currentPosition % (NUM_LEDS - topperLength);
    }
  }


  //*************************************************Deal with lights off selected

  if (lightFunction == "Off") {
    applyTopper = "off";
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  //set all to black
    leds[0] = 0x001600;                         //Light a green LED (very dim) for system ready
    //FastLED.show();
    //    vTaskDelay(1);
  }
  //*******************************************************lights off ends

  //**********************************************************************THEATRE CHASE

  if (lightFunction == "theatrechase") {
    int chaseLength = 5;
    if (bright2 < 200) {
      (bright2) = 200;  //need to slow down the cycle
    }



    FastLED.setBrightness(bright);
    if ((currentPosition % 2) == 0) {
      for (int i = 0; i < NUM_LEDS; i = i + chaseLength * 2) {

        for (int j = 0; j < chaseLength; j++) {
          leds[i + j].r = r1;
          leds[i + j + chaseLength].r = r0;
          leds[i + j].g = g1;
          leds[i + j + chaseLength].g = g0;
          leds[i + j].b = b1;
          leds[i + j + chaseLength].b = b0;
        }
      }
    }

    if ((currentPosition % 2) == 1) {
      for (int i = 0; i < NUM_LEDS; i = i + chaseLength * 2) {

        for (int j = 0; j < chaseLength; j++) {
          leds[i + j].r = r0;
          leds[i + j + chaseLength].r = r1;
          leds[i + j].g = g0;
          leds[i + j + chaseLength].g = g1;
          leds[i + j].b = b0;
          leds[i + j + chaseLength].b = b1;
        }
      }
    }

    if (applyGlitter == "on") {
      addGlitter(32);
    }

    //FastLED.show();
  }

  //**********************************************************************THEATRE CHASE ENDS

  //********************************************************CONFETTI
  if (lightFunction == "confetti") {

    if (bright2 < 100) {
      bright2 = 100;
    }  //Confetti doesn't work well with excess speed

    if (currentPosition != lastPosition)  //Only execute this loop based on "lethargy" setting
    {
      FastLED.setBrightness(bright);
      uint8_t secondHand = (millis() / bright2) % 2;  // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
      static uint8_t lastSecond = 99;                 // Static variable, means it's only defined once. This is our 'debounce' variable.
      if (lastSecond != secondHand) {                 // Debounce to make sure we're not repeating an assignment.
        lastSecond = secondHand;
        switch (secondHand) {
          case 1:
            currentColour++;
            currentColour = currentColour % numberOfColours;
            break;
        }
      }

      fadeToBlackBy(leds, NUM_LEDS, 2);  // Low values = slower fade.
      int pos = random16(NUM_LEDS);      // Pick an LED at random.
      leds[pos] = colour[currentColour];
      lastPosition = currentPosition;  //sequence the loop based on the master "Lethargy" slider
      //FastLED.show();
    }  //if currentpos different
  }
  //********************************************************CONFETTI ENDS





  //***********************************************************multiRainbow
  if (lightFunction == "multiRainbow") {
    FastLED.setBrightness(bright);
    fill_rainbow(leds, NUM_LEDS, gHue, numberRainbows);
    if (applyGlitter == "on") {
      addGlitter(32);
    }
    //FastLED.show();
    //    vTaskDelay(10);

  }  //ends if multirainbow

  //*********************************************************multiRainbow ends

  //*********************************************************singleColourChange

  if (lightFunction == "singleColourChange") {
    if (bright < 120) {
      bright = 120;
    }  //Solid colour rainbow doesn't work well with brightness below 120
    FastLED.setBrightness(bright);
    fill_solid(leds, NUM_LEDS, CHSV(localHue, 255, bright));  // CHSV (hue, saturation, value);
    if (applyGlitter == "on") {
      addGlitter(32);
    }
    //FastLED.show();
    //    vTaskDelay(10);
  }  //ends if singlecolourchange
  //*********************************************************singleColourChange ends

  //*********************************************************Strip Fill

  if (lightFunction == "stripFill") {
    FastLED.setBrightness(bright);

    // if (applyTopper == "off") {
    //   currentPosition = currentPosition % NUM_LEDS;
    // }
    // if (applyTopper == "on") {
    //   currentPosition == currentPosition % (NUM_LEDS - topperLength);
    // }

    //Loop comes round quickly enough to cause multiple colour updates as currentPosition=0 for several loop iterations
    //Use boolean to stop multiple changes.

    if (currentPosition == 0) {  //numleds

      if (colourUpdated == false) {
        currentColour++;
        colourUpdated = true;
        currentColour = currentColour % numberOfColours;
      }
    }  //ends if current position = 0

    if (currentPosition > 0) {
      colourUpdated = false;  //reset catcher when position non-zero
    }

    if (currentColour == 0) {
      previousColour = numberOfColours - 1;
      //eg numcols=4 ..currentcol=0, prevcol=3 = largest array index
    } else {

      previousColour = currentColour - 1;
    }

    // Serial.print("Current Colour: ");
    // Serial.print(currentColour);
    // Serial.print(" Previous Colour:  ");
    // Serial.println(previousColour);

    for (int x = 0; x <= currentPosition; x++) {
      leds[x] = colour[currentColour];
    }


    for (int x = currentPosition + 1; x < NUM_LEDS; x++) {
      leds[x] = colour[previousColour];  //Doing it like this writes whole strip and allows glitter
    }
    if (applyGlitter == "on") {
      addGlitter(48);
    }
    //FastLED.show();
    //    vTaskDelay(10);
  }

  //*********************************************************Strip Fill ends



  //************************************************************Handle reboot
  if (lightFunction == "reboot") {
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  //Set all to black
    //FastLED.show();
    delay(10);
    ESP.restart();
  }
  //***********************************************************Handle reboot ends


  //************************************************************************BUNTING
  //Bunting = 3 areas, 10px each, colour, colour, moving along the strip.


  //Total length of 1 bunting element = 30
  //  19 complete sets, then deal with the start and end of strip

  if (lightFunction == "bunting") {
    FastLED.setBrightness(bright);
    int offset = currentPosition % 30;

    // 3 colours, 10 pixels per colour bar, 600px total = 20 itertations.

    for (byte iteration = 0; iteration < 20; iteration++) {

      for (byte currentColour = 0; currentColour < 3; currentColour++) {

        for (byte pixel = 0; pixel < 10; pixel++) {
          if (currentColour == 0) {
            //leds[(sets * 30) + (x * 10) + px + offset] = buntingcolour[x];
            leds[((iteration * 30) + (currentColour * 10) + pixel + offset) % NUM_LEDS] = CRGB(r0, g0, b0);
          }
          if (currentColour == 1) {
            //leds[(sets * 30) + (x * 10) + px + offset] = buntingcolour[x];
            leds[((iteration * 30) + (currentColour * 10) + pixel + offset) % NUM_LEDS] = CRGB(r1, g1, b1);
          }
          if (currentColour == 2) {
            //leds[(sets * 30) + (x * 10) + px + offset] = buntingcolour[x];
            leds[((iteration * 30) + (currentColour * 10) + pixel + offset) % NUM_LEDS] = CRGB(r2, g2, b2);
          }


        }  //ends pixel

      }  //ends currentcolour

    }  //end iterations



    if (applyGlitter == "on") {
      addGlitter(48);
    }
    //FastLED.show();
    vTaskDelay(2);
    yield();
  }  //ends "if lightfunction=bunting"

  //******************************************************BUNTING ENDS

  //*************************************************COMETS
  if (lightFunction == "comets") {

    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = map(bright2, 1, 1000, 2, 200);
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 32, 255);
    for (int i = 0; i < NUM_LEDS; i++) {  //9948
      leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
    if (applyGlitter == "on") {
      addGlitter(48);
    }
    //FastLED.show();
  }

  //*************************************************COMETS ENDS


  //**************************************************JUGGLE
  if (lightFunction == "juggle") {

    if (bright2 < 850) {
      (bright2) = 850;  //need to speed up the cycle
    }

    if (bright < 200) {
      (bright) = 200;  //need to brighten
    }


    if (currentPosition != lastPosition)  //Allow speed change
    {
      // eight colored dots, weaving in and out of sync with each other
      fadeToBlackBy(leds, NUM_LEDS, 20);
      uint8_t dothue = 0;
      for (int i = 0; i < 10; i++) {                                           //8
        leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, bright);  //7
        dothue += 25;
      }
      lastPosition = currentPosition;
      //FastLED.show();
    }
  }

  //**************************************************JUGGLE ENDS



  //*************************************************************TOPPER

  if (applyTopper == "on") {

    EVERY_N_SECONDS(10) {
      topperColour++;
      topperColour = topperColour % numberOfTopperColours;
    }

    //*********************************************************Topper Pattern Select

    //Colour Shift - not the same as main chain - this cycles slowly around the topper colour array

    if (topperPattern == "TopperColourShift") {

      EVERY_N_MILLISECONDS(100) {
        topperpixelcolour = blend(topperpixelcolour, (toppercolour[topperColour + 1 % numberOfTopperColours]), 6);
      }
      for (int i = (NUM_LEDS - topperLength); i < NUM_LEDS; i++) {
        leds[i] = topperpixelcolour;
      }
    }
    //Colour Shift Ends

    //Solid Colours
    if (topperPattern == "TopperRed") {
      for (int i = (NUM_LEDS - topperLength); i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
      }
    }

    if (topperPattern == "TopperGold") {
      for (int i = (NUM_LEDS - topperLength); i < NUM_LEDS; i++) {
        leds[i] = CRGB::Gold;
      }
    }

    if (topperPattern == "TopperBlue") {
      for (int i = (NUM_LEDS - topperLength); i < NUM_LEDS; i++) {
        leds[i] = CRGB::Blue;
      }
    }

    if (topperPattern == "TopperGreen") {
      for (int i = (NUM_LEDS - topperLength); i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
      }
    }

    if (topperPattern == "TopperPurple") {
      for (int i = (NUM_LEDS - topperLength); i < NUM_LEDS; i++) {
        leds[i] = CRGB::Magenta;
      }
    }

    if (topperPattern == "TopperWhite") {
      for (int i = (NUM_LEDS - topperLength); i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
      }
    }
    //Solid Colours Ends


    //*********************************************************TOPPER GLITTER
    if (applyTopperGlitter == "on") {

      //Glitter value for topper needs to be in proportion to its length

      if (random8() < topperLength / 1.5) {     //defines how MUCH glitter...
        int localpos = random16(topperLength);  //defines WHERE a white px appears
        leds[localpos + (NUM_LEDS - topperLength)] += CRGB::White;
      }
    }

    //*********************************************************TOPPER GLITTER ENDS
  }

  //*************************************************************TOPPER ENDS

  vTaskDelay(2);
  yield();

  //*********Deal with schedule on/off.
  // Scheduled on/off is only checked at the quarters of hours
  // If scheduler enabled then store current lightFunction as previouslightFunction
  // If scheduler enabled and scheduledLightsOn is FALSE (lights off by scheduler) then
  //  current lightFunction = "Off" - overwrite whatever
  // If scheduler enabled and scheduledLightsOn = TRUE (lights ON by scheduler) then
  //  current lightFunction == previouslightFunction
  // Store CURRENT lightFunction as previouslightFunction WHEN lightFunction is not "Off" or "reboot" so we retain
  // knowledge of selected function (eg user turns lights off before scheduled "off"
  // If user turns lights ON with schedule set to off, lights will stay ON until next "off"
  // Need a flag to monitor "have I dealt with the schedule command?"



  if (lightFunction != "reboot" && lightFunction != "Off") {
    previouslightFunction = lightFunction;
  }  //Previous active light function is stored

  if (allowSchedulerChanges == true) {
    //During the 5 seconds each quarter when the schedule command gets checked...
    if (scheduledLightsOn) {
      lightFunction = previouslightFunction;
    }

    if (!scheduledLightsOn) {
      lightFunction = "Off";
    }

    if (current_second_int > 5){
    allowSchedulerChanges = false;} //Hold this variable for 5 secs to allow JS to update buttons

  }  

  FastLED.show();  //One 'show' command so that auxilliary sections can be easily coded

}  //ends Void Loop
//**********************************************LOOP ENDS




void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(250);
  }
}
