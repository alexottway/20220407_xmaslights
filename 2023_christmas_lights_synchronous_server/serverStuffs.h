void handle_favicon() {
  // server.send(SPIFFS, "/favicon.ico", "Christmas-Tree256.ico");
  server.serveStatic("/favicon.ico", SPIFFS, "/Christmas-Tree256.ico");
}

//*********************************************************************XML FOR WEB READY
void buildXML() {
  XML = "<?xml version='1.0' encoding='UTF-8'?>";
  XML += "<values>\r\n";

  XML += "<response1>";
  XML += busyReady;
  XML += "</response1>\r\n";

  XML += "<response2>";
  XML += busyReady2;
  XML += "</response2>\r\n";

  XML += "<response3>";
  XML += busyReady3;
  XML += "</response3>\r\n";

  XML += "<response4>";
  XML += busyReady4;
  XML += "</response4>\r\n";

  XML += "<response5>";
  XML += busyReady5;
  XML += "</response5>\r\n";

  XML += "<lightFunction>";
  XML += lightFunction;
  XML += "</lightFunction>\r\n";

  XML += "<glitter>";
  XML += applyGlitter;
  XML += "</glitter>\r\n";

  XML += "<topperglitter>";
  XML += applyTopperGlitter;
  XML += "</topperglitter>\r\n";

  XML += "<topper>";
  XML += applyTopper;
  XML += "</topper>\r\n";

  XML += "<howbright>";
  XML += bright;
  XML += "</howbright>\r\n";

  XML += "<howslow>";
  XML += (bright2);
  XML += "</howslow>\r\n";

  XML += "<lightState>";
  if (lightFunction != "Off") {
    XML += "on";
  }
  if (lightFunction == "Off") {
    XML += "off";
  }
  XML += "</lightState>\r\n";

  XML += "<colour0>";
  XML += colour0;
  XML += "</colour0>\r\n";
  XML += "<colour1>";
  XML += colour1;
  XML += "</colour1>\r\n";
  XML += "<colour2>";
  XML += colour2;
  XML += "</colour2>\r\n";

  XML += "<numberRainbows>";
  XML += numberRainbows;
  XML += "</numberRainbows>\r\n";

  XML += "<scheduler>";
  XML += scheduleEnabled;
  XML += "</scheduler>\r\n";

  XML += "<schedulerChange>";
  XML += allowSchedulerChanges;
  XML += "</schedulerChange>\r\n";

  XML += "</values>";
  //Serial.println("XML GENERATED");
}
//******************************************************

void add_status_and_summary() {
  //Wrap the bottom 2 tables in their own table:

  webpage += "\n<table style=\"width: 90%; align:center; margin: auto;\">\n<tr><td>\n";

  //Generate the status table

  webpage += "<div id=\"statusMessage\" style=\"display: inline\">\n";
  webpage += "\n<table style=\"width: 90%; align:center;\">\n";
  webpage += "\n  <tr>\n";
  webpage += "\n    <td class=\"statustext\"><b>\n";
  webpage += "\n    <span id=\"readystatus\"></span>&nbsp;\n";
  webpage += "\n    <span id=\"readystatus2\"></span><br/><br>\n";
  webpage += "\n    <span id=\"readystatus3\"></span><br/><br>\n";
  webpage += "\n    <span id=\"readystatus4\"></span><br/><br>\n";
  webpage += "\n    <span id=\"readystatus5\"></span> </b>\n";
  webpage += "\n    </td>\n";
  webpage += "\n  </tr>\n";
  webpage += "\n</table>\n";
  webpage += "</div>\n";

  webpage += "</td><td>";

  //Generate schedule summary
  webpage += "<table style=\"width: 90%; align:center;\">\n"
             "<tr bgcolor = 'white'><td colspan = '6'><br></td></tr>\n"
             "<tr bgcolor = 'teal'><td colspan = '6' align = 'center'><b>Today's scheduled activity</b></td></tr>\n";
  for (int j = 0; j < 24; j++) {
    for (int q = 0; q < 4; q++) {
      if (schedule[current_weekday_int][j][q] == 1) {
        webpage += "<tr bgcolor='green'><td colspan='6' align='center'>Lights ON at ";
        if (j < 10) {
          webpage += "0";
        }
        webpage += j;
        webpage += ":";
        if (q == 0) {
          webpage += "0";
        }
        webpage += (q * 15);
        webpage += "hrs.</td></tr>\n";
      }
      if (schedule[current_weekday_int][j][q] == 2) {
        webpage += "<tr bgcolor='red'><td colspan='6' align='center'>Lights OFF at ";
        if (j < 10) {
          webpage += "0";
        }
        webpage += j;
        webpage += ":";
        if (q == 0) {
          webpage += "0";
        }
        webpage += (q * 15);
        webpage += "hrs.</td></tr>\n";
      }
    }  //end q
  }    //end j
  webpage += "</table><br>";
  //Summary ends

  webpage += "</td></tr></table>\n";
}

//******************************************************************************
void append_HTML_footer() {

  IPAddress myip = WiFi.localIP();
  String ipstring = String(myip[0]) + "." + myip[1] + "." + myip[2] + "." + myip[3];

  webpage += "<hr><footer><table width='90%'><tr><td align='center' width='25%'>\r\n";
  webpage += "<a href="
             "/"
             "><input type='button' class='larger rounded settingsbutton' value='Home'></a></td><td width='25%'>";
  webpage += "<a href="
             "/topper.htm"
             "><input type='button' class='larger rounded settingsbutton' value='Tree Topper Settings'></a></td><td width='25%'>";
  webpage += "<a href="
             "/schedulechooser.htm"
             "><input type='button' class='larger rounded settingsbutton' value='Scheduler'></a>";

  webpage += "<td style=\"width: 25%;\">";
  webpage += "<form id=\"rebootForm\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">";
  webpage += "<input name=\"lightFunction\" type=\"hidden\" value=\"reboot\" />";
  webpage += "<input style=\"background-color: red; font-weight: bold; color: white;\" type=\"submit\" value=\"REBOOT\" />";
  webpage += "</form>";
  webpage += "</td>";

  webpage += "</center></td></tr></table>";

  String Uptime = (String(millis() / 1000 / 60 / 60)) + ": ";
  Uptime += (((millis() / 1000 / 60 % 60) < 10) ? "0" + String(millis() / 1000 / 60 % 60) : String(millis() / 1000 / 60 % 60)) + ": ";
  Uptime += ((millis() / 1000 % 60) < 10) ? "0" + String(millis() / 1000 % 60) : String(millis() / 1000 % 60);
  webpage += "<table align=\"center\"><tr><td>";
  //  webpage += "<form action='settings.htm'><button type='submit' class = 'gentlyrounded settingsbutton'>Device Settings</button></form></td>\r\n";
  webpage += "<td>System Uptime: " + Uptime + " - ";
  webpage += "&copy; Alex Ottway - " + ipstring + "</td></tr></table>\r\n";

  webpage += "</footer>\r\n</body>\r\n</html> ";
}
//******************************************************************************

//*******************************************************************
void handle_schedulechooser() {
  webpage = " <!DOCTYPE html>\r\n";  //THis will become the editing page for scheduler.
  webpage += "<html>";
  webpage += "<head>";
  webpage += "<title>" + sitetitle + "</title><br>";
  webpage += "<link rel=\"preload\" href=\"/tree64.png\" as=\"image\">\r\n";
  webpage += "<link rel=\"preload\" href=\"/tree64BW.png\" as=\"image\">\r\n";
  webpage += "<link rel=\"preload\" href=\"/clock64.png\" as=\"image\">\r\n";
  webpage += "<link rel=\"preload\" href=\"/clock64bw.png\" as=\"image\">\r\n";

  webpage += webStyle;
  webpage += "<script type="
             "text/javascript"
             ">";
  webpage += "";
  webpage += "var xmlHttp=createXmlHttpObject();";
  webpage += "function createXmlHttpObject(){";
  webpage += " if(window.XMLHttpRequest){";
  webpage += "    xmlHttp=new XMLHttpRequest();";
  webpage += " } else {\r\n";
  webpage += "    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\r\n";
  webpage += " }\r\n";
  webpage += " return xmlHttp;\r\n";
  webpage += "}\r\n";
  webpage += "\r\n";
  webpage += "function process(){\r\n";
  webpage += " if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\r\n";
  webpage += "   xmlHttp.open('PUT','xml',true);\r\n";
  webpage += "   xmlHttp.onreadystatechange=handleServerResponse; // no brackets?????\r\n";
  webpage += "   xmlHttp.send(null);\r\n";
  webpage += " }\r\n";
  webpage += " setTimeout('process()',1000);\r\n";
  webpage += "}\r\n";
  webpage += "\r\n";
  webpage += "\r\n";
  webpage += "function handleServerResponse(){\r\n";
  webpage += " if(xmlHttp.readyState==4 && xmlHttp.status==200){\r\n";
  webpage += "\r\n";
  webpage += "   xmlResponse=xmlHttp.responseXML;\r\n";
  webpage += "\r\n";


  webpage += "   xmldoc = xmlResponse.getElementsByTagName('scheduler');\r\n";
  webpage += "   schedulermessage = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "   \r\n";
  webpage += "   if(schedulermessage==\"1\"){\r\n";
  webpage += "     document.getElementById('scheduleron1').disabled = true;\r\n";
  webpage += "     document.getElementById('scheduleroff1').disabled = false;\r\n";
  webpage += "   } else {\r\n";
  webpage += "     document.getElementById('scheduleron1').disabled = false;\r\n";
  webpage += "     document.getElementById('scheduleroff1').disabled = true;\r\n";
  webpage += "   }\r\n";
  webpage += "   \r\n";
  webpage += "    if(schedulermessage==\"0\"){\r\n";
  webpage += "     document.getElementById('scheduleroff1').disabled = true;\r\n";
  webpage += "     document.getElementById('scheduleron1').disabled = false;\r\n";
  webpage += "     } else {\r\n";
  webpage += "     document.getElementById('scheduleroff1').disabled = false;\r\n";
  webpage += "     document.getElementById('scheduleron1').disabled = true;\r\n";
  webpage += "     }\r\n";
  webpage += "";



  webpage += "\n";
  webpage += "xmldoc = xmlResponse.getElementsByTagName('lightState');\n";
  webpage += "message = xmldoc[0].firstChild.nodeValue;\n";
  webpage += "\n";
  webpage += "var statuspic = document.getElementById(\"statuspic\");\n";
  webpage += "var statuspic2 = document.getElementById(\"statuspic2\");\n";
  webpage += "\n";
  webpage += "if (message==\"on\"){\n";
  webpage += "    statuspic.style.backgroundImage = \"url('/tree64.png')\";\n";
  webpage += "} else {\n";
  webpage += "    statuspic.style.backgroundImage = \"url('/tree64BW.png')\";\n";
  webpage += "}\n";
  webpage += "\n";
  webpage += "if (message==\"off\"){\n";
  webpage += "    statuspic.style.backgroundImage = \"url('/tree64BW.png')\";\n";
  webpage += "} else {\n";
  webpage += "    statuspic.style.backgroundImage = \"url('/tree64.png')\";\n";
  webpage += "}\n";
  webpage += "\n";
  webpage += "xmldoc = xmlResponse.getElementsByTagName('scheduler');\n";
  webpage += "message = xmldoc[0].firstChild.nodeValue;\n";
  webpage += "if (message==\"1\"){\n";
  webpage += "    statuspic2.style.backgroundImage = \"url('/clock64.png')\";\n";
  webpage += "} else {\n";
  webpage += "    statuspic2.style.backgroundImage = \"url('/clock64bw.png')\";\n";
  webpage += "}\n";
  webpage += "\n";
  webpage += "if (message==\"0\"){\n";
  webpage += "    statuspic2.style.backgroundImage = \"url('/clock64bw.png')\";\n";
  webpage += "} else {\n";
  webpage += "    statuspic2.style.backgroundImage = \"url('/clock64.png')\";\n";
  webpage += "}\n";
  webpage += "\n";
  webpage += "statuspic.style.backgroundRepeat = \"no-repeat\";\n";
  webpage += "statuspic2.style.backgroundRepeat = \"no-repeat\";\n";



  webpage += "   xmldoc = xmlResponse.getElementsByTagName('response1');\r\n";
  webpage += "   message = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "   document.getElementById('readystatus').innerHTML=message;\r\n";
  webpage += "\r\n";
  webpage += "   xmldoc = xmlResponse.getElementsByTagName('response2');\r\n";
  webpage += "   message = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "   document.getElementById('readystatus2').innerHTML=message;\r\n";
  webpage += "\r\n";
  webpage += "   xmldoc = xmlResponse.getElementsByTagName('response3');\r\n";
  webpage += "   message = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "   document.getElementById('readystatus3').innerHTML=message;\r\n";
  webpage += "\r\n";
  webpage += "   xmldoc = xmlResponse.getElementsByTagName('response4');\r\n";
  webpage += "   message = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "   document.getElementById('readystatus4').innerHTML=message;\r\n";
  webpage += "\r\n";
  webpage += "   xmldoc = xmlResponse.getElementsByTagName('response5');\r\n";
  webpage += "   message = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "   document.getElementById('readystatus5').innerHTML=message;\r\n";




  webpage += " }\r\n";
  webpage += "}\r\n";
  webpage += "\r\n";
  webpage += "</script>\r\n";
  webpage += "";
  //webpage += "<link href=""data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAQAABILAAASCwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA1MUAHJTtzeRBIucA1MT82NTJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABtAlWEITNTyNTFAAgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAVnRdMGowdPg6yDo8Weki3CYJ1/A+wD6IKwAmjFZwXSzI9PAgAAAAAAAAAAAAAAAAAAAAAAAAAACF3JxsjcCk1DrQOvQDoAP4A5QD9AOoA/wDqAP8A6wD/AOwA/wfLBuoTpRSdHn8jHgAAAAAAAAAAAAAAAAAAAAAWnBlKAOUA/ADsAP8A7AD/AOsA/wDrAP8A6wD/AOsA/wDKMP4A7AD/AOwA/xGtEm0AAAAAAAAAAAAAAAAAAAAALFE2DhCtEsEA7AD/AFfv/QDrAP8A4gn/AOAL/wDrAP8ASv/9AOgA/w26DaMvRzkIAAAAAAAAAAAAAAAAAAAAAC9HOgsIyQjMAOwA/wDrAP8A6wD/AKdq/gCFof4A6wD/AOsA/wDnAP8RqxOKAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMUA8EQ+xENkA6wD/AOsA/wDrAP8A6wD/AOsA/wDqAP8LwAuzJWgtFgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADI/PQ0HzgbWAOsA/wCFo/4Arl/+ANsU/gBc5v0A4wD+DrQPrgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJ2EwEgrDCrgAzir+ANUe/wDrAP8A6gD/AeIA+xOmFWcAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADYwQwQOtg/aAOoA/wDpAP8AVfL+AOsA/xWeGaI2MEMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFZ8YWwDkAP4A6wD/AMBC/gDrAP8Muw2vNjBDAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABqOHzIKxArfAIub/gCyW/4KxArgL0g6EgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAkbSwZBdMF4ADEPf4A0ib/A9wB9CRsLCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB6CJC8C4AD4A9wC8RqPHzsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAELETjRKrFXYAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/B8AAP4/AADwBwAAwAMAAMADAADAAwAAwAcAAOAHAADgDwAA8A8AAPAPAAD4DwAA+B8AAPgfAAD8PwAA/n8AAA=="" rel=""icon"" type=""image/x-icon""/>\r\n";
  webpage += "";
  webpage += "</head><body onload=\"process()\">";


  webpage += "<table style=\"width:90%; height:64px;\"><tr>";
  webpage += "<td id=\"statuspic\" style=\"width: 64px; height: 64px;\"></td>";
  webpage += "<td><h1 align=\"center\">Christmas Lights Control</h1></td>";
  webpage += "<td id=\"statuspic2\" style=\"width: 64px; height: 64px;\"> </td> </tr> </table>";
  webpage += "<hr>";

  webpage += "<h2>Scheduler Selection.</h2>";

  webpage += "<table width='90%'align='center' border='0'><tr>\r\n";


  webpage += "<td align=\"right\">\r\n";
  webpage += "<form id=\"schedulerON\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">\r\n";
  webpage += "<input type=\"hidden\" name=\"withscheduler\" value=\"on\">\r\n";
  webpage += "<input id=\"scheduleron1\" class=\"larger\" type=\"submit\" name=\"submitscheduler\" value=\"Turn Scheduler ON\" />\r\n";
  webpage += "</form>\r\n";
  webpage += "</td>\r\n";
  webpage += "\r\n";
  webpage += "<td align=\"left\">\r\n";
  webpage += "<form id=\"schedulerOFF\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">\r\n";
  webpage += "<input type=\"hidden\" name=\"withscheduler\" value=\"off\">\r\n";
  webpage += "<input id=\"scheduleroff1\" class=\"larger\" type=\"submit\" name=\"submitscheduler\" value=\"Turn Scheduler OFF\" />\r\n";
  webpage += "</form>\r\n";
  webpage += "</td><tr><tr></table>\r\n";

  webpage += "<table width='90%'align='center' border='0'><tr>\r\n";
  webpage += "<td colspan='7'><b><h3>Choose a day or block of days.</h3></b></td></tr><tr>\r\n";

  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=0"
             "><input type='button'";
  if (current_weekday.toInt() == 0) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Sunday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=1"
             "><input type='button'";
  if (current_weekday.toInt() == 1) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Monday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=2"
             "><input type='button'";
  if (current_weekday.toInt() == 2) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Tuesday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=3"
             "><input type='button'";
  if (current_weekday.toInt() == 3) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Wednesday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=4"
             "><input type='button'";
  if (current_weekday.toInt() == 4) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Thursday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=5"
             "><input type='button'";
  if (current_weekday.toInt() == 5) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Friday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=6"
             "><input type='button'";
  if (current_weekday.toInt() == 6) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Saturday'></a></td>\r\n";
  //*********************
  webpage += "</tr><tr>\r\n";
  //
  webpage += "<td colspan='2' align='center'><a href="
             "scheduleedit.htm?daychoice=7"
             "><input type='button'";
  if (current_weekday.toInt() == 7) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='All 7 Days'></a></td>\r\n";



  webpage += "<td colspan='3' align='center'><a href="
             "scheduleedit.htm?daychoice=8"
             "><input type='button'";
  if (current_weekday.toInt() == 8) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Mon to Fri'></a></td>\r\n";
  //
  webpage += "<td colspan='2' align='center'><a href="
             "scheduleedit.htm?daychoice=9"
             "><input type='button'";
  if (current_weekday.toInt() == 9) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Sat & Sun'></a></td>\r\n";

  webpage += "</tr></table> ";

  webpage += "<p></p>\n";
  webpage += "<table width='90%' align='center'><tr><td><form id=\"wipescheduleForm\" action=\"wipeschedule.htm\" method=\"post\" >\r\n";
  webpage += "<input name=\"wipeSchedule\" type=\"hidden\" value=\"wipe\" />\r\n";
  webpage += "<input style=\"background-color: blue; font-weight: bold; color: white;\" type=\"submit\" value=\"WIPE SCHEDULE DATA\" />\r\n";
  webpage += "</form></td></tr></table>\r\n";

  add_status_and_summary();

  webpage += "<iframe id=\"dummyframe\" border=\"0\" height=\"0\" name=\"dummyframe\" style=\"display: none\" width=\"0\"></iframe>";


  append_HTML_footer();

  server.send(200, "text/html", webpage);
}
//*******************************************************************

//******************************************************************************
void handle_topper() {
  webpage = " <!DOCTYPE html>\r\n";  //THis will become the editing page for scheduler.
  webpage += "<html>";
  webpage += "<head>";
  webpage += "<title>" + sitetitle + "</title><br>";
  webpage += webStyle;
  webpage += "<script type="
             "text/javascript"
             ">";
  webpage += "";
  webpage += "var xmlHttp=createXmlHttpObject();";
  webpage += "function createXmlHttpObject(){";
  webpage += " if(window.XMLHttpRequest){";
  webpage += "    xmlHttp=new XMLHttpRequest();";
  webpage += " } else {\r\n";
  webpage += "    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\r\n";
  webpage += " }\r\n";
  webpage += " return xmlHttp;\r\n";
  webpage += "}\r\n";
  webpage += "\r\n";
  webpage += "function process(){\r\n";
  webpage += " if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\r\n";
  webpage += "   xmlHttp.open('PUT','xml',true);\r\n";
  webpage += "   xmlHttp.onreadystatechange=handleServerResponse; // no brackets?????\r\n";
  webpage += "   xmlHttp.send(null);\r\n";
  webpage += " }\r\n";
  webpage += " setTimeout('process()',1000);\r\n";
  webpage += "}\r\n";
  webpage += "\r\n";
  webpage += "\r\n";
  webpage += "function handleServerResponse(){\r\n";
  webpage += " if(xmlHttp.readyState==4 && xmlHttp.status==200){\r\n";
  webpage += "\r\n";
  webpage += "   xmlResponse=xmlHttp.responseXML;\r\n";
  webpage += "\r\n";
  webpage += "   xmldoc = xmlResponse.getElementsByTagName('topperglitter');\r\n";
  webpage += "   topperglittermessage = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "   \r\n";
  webpage += "   if(topperglittermessage==\"on\"){\r\n";
  webpage += "     document.getElementById('topperglitteron1').disabled = true;\r\n";
  webpage += "     document.getElementById('topperglitteroff1').disabled = false;   \r\n";
  webpage += "   } else {\r\n";
  webpage += "     document.getElementById('topperglitteron1').disabled = false; \r\n";
  webpage += "     document.getElementById('topperglitteroff1').disabled = true;      \r\n";
  webpage += "   }\r\n";
  webpage += "   \r\n";
  webpage += "    if(topperglittermessage==\"off\"){\r\n";
  webpage += "     document.getElementById('topperglitteroff1').disabled = true;   \r\n";
  webpage += "     document.getElementById('topperglitteron1').disabled = false;\r\n";
  webpage += "     } else {\r\n";
  webpage += "     document.getElementById('topperglitteroff1').disabled = false;       \r\n";
  webpage += "     document.getElementById('topperglitteron1').disabled = true;\r\n";
  webpage += "     }\r\n";
  webpage += "\r\n";
  webpage += "   xmldoc = xmlResponse.getElementsByTagName('topper');\r\n";
  webpage += "   toppermessage = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "   \r\n";
  webpage += "   if(toppermessage==\"on\"){\r\n";
  webpage += "     document.getElementById('topperon1').disabled = true;\r\n";
  webpage += "     document.getElementById('topperoff1').disabled = false;   \r\n";
  webpage += "   } else {\r\n";
  webpage += "     document.getElementById('topperon1').disabled = false; \r\n";
  webpage += "     document.getElementById('topperoff1').disabled = true;      \r\n";
  webpage += "   }\r\n";
  webpage += "   \r\n";
  webpage += "    if(toppermessage==\"off\"){\r\n";
  webpage += "     document.getElementById('topperoff1').disabled = true;   \r\n";
  webpage += "     document.getElementById('topperon1').disabled = false;\r\n";
  webpage += "     } else {\r\n";
  webpage += "     document.getElementById('topperoff1').disabled = false;       \r\n";
  webpage += "     document.getElementById('topperon1').disabled = true;\r\n";
  webpage += "     }\r\n";


  webpage += "   xmldoc = xmlResponse.getElementsByTagName('lightState');\r\n";
  webpage += "   message = xmldoc[0].firstChild.nodeValue;\r\n";
  webpage += "var statuspic = document.getElementById('statuspic');\r\n";
  webpage += "var statuspic2 = document.getElementById('statuspic2');\r\n";
  webpage += "   if (message==\"on\"){\r\n";
  //webpage += "    document.getElementById('offbutton1').disabled = false;\r\n";
  webpage += "statuspic.style.backgroundImage = 'url(\"/tree64.png\")';\r\n";
  webpage += "statuspic2.style.backgroundImage = 'url(\"/tree64.png\")';\r\n";
  webpage += "   } else {\r\n";
  //webpage += "    document.getElementById('offbutton1').disabled = true;\r\n";
  webpage += "statuspic.style.backgroundImage = 'url(\"/tree64BW.png\")';\r\n";
  webpage += "statuspic2.style.backgroundImage = 'url(\"/tree64BW.png\")';\r\n";
  webpage += "   }\r\n";

  webpage += "statuspic.style.backgroundRepeat = 'no-repeat';";
  webpage += "statuspic2.style.backgroundRepeat = 'no-repeat';";


  webpage += " }\r\n";
  webpage += "}\r\n";
  webpage += "\r\n";
  webpage += "</script>\r\n";
  webpage += "";
  webpage += "<link href="
             "data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAQAABILAAASCwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA1MUAHJTtzeRBIucA1MT82NTJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABtAlWEITNTyNTFAAgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAVnRdMGowdPg6yDo8Weki3CYJ1/A+wD6IKwAmjFZwXSzI9PAgAAAAAAAAAAAAAAAAAAAAAAAAAACF3JxsjcCk1DrQOvQDoAP4A5QD9AOoA/wDqAP8A6wD/AOwA/wfLBuoTpRSdHn8jHgAAAAAAAAAAAAAAAAAAAAAWnBlKAOUA/ADsAP8A7AD/AOsA/wDrAP8A6wD/AOsA/wDKMP4A7AD/AOwA/xGtEm0AAAAAAAAAAAAAAAAAAAAALFE2DhCtEsEA7AD/AFfv/QDrAP8A4gn/AOAL/wDrAP8ASv/9AOgA/w26DaMvRzkIAAAAAAAAAAAAAAAAAAAAAC9HOgsIyQjMAOwA/wDrAP8A6wD/AKdq/gCFof4A6wD/AOsA/wDnAP8RqxOKAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMUA8EQ+xENkA6wD/AOsA/wDrAP8A6wD/AOsA/wDqAP8LwAuzJWgtFgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADI/PQ0HzgbWAOsA/wCFo/4Arl/+ANsU/gBc5v0A4wD+DrQPrgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJ2EwEgrDCrgAzir+ANUe/wDrAP8A6gD/AeIA+xOmFWcAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADYwQwQOtg/aAOoA/wDpAP8AVfL+AOsA/xWeGaI2MEMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFZ8YWwDkAP4A6wD/AMBC/gDrAP8Muw2vNjBDAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABqOHzIKxArfAIub/gCyW/4KxArgL0g6EgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAkbSwZBdMF4ADEPf4A0ib/A9wB9CRsLCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB6CJC8C4AD4A9wC8RqPHzsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAELETjRKrFXYAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/B8AAP4/AADwBwAAwAMAAMADAADAAwAAwAcAAOAHAADgDwAA8A8AAPAPAAD4DwAA+B8AAPgfAAD8PwAA/n8AAA=="
             " rel="
             "icon"
             " type="
             "image/x-icon"
             "/>\r\n";
  webpage += "";
  webpage += "</head><body onload=\"process()\">";


  webpage += "<table style=\"width:90%; height:64px;\"><tr>";
  webpage += "<td id=\"statuspic\" style=\"width: 64px; height: 64px;\"></td>";
  webpage += "<td><h1 align=\"center\">Christmas Lights Control</h1></td>";
  webpage += "<td id=\"statuspic2\" style=\"width: 64px; height: 64px;\"> </td> </tr> </table>";
  webpage += "<hr>";


  webpage += "<table style=\"width:100%\" id=\"toppertable\">";
  webpage += "<tr><div id=\"topperSelection\" style=\"display: inline\"><th colspan=\"4\">Separate Top Lighting<br><br></th></tr>";
  webpage += "<tr><form id=\"topperON\" action=\"select.htm\" method=\"post\" target=\"dummyframe\"><td align=\"right\">";
  webpage += "<input type=\"hidden\" name=\"withtopper\" value=\"on\">";
  webpage += "<input id=\"topperon1\" type=\"submit\" name=\"submittopper\" value=\"Topper ON\" /></form></td>";
  webpage += "";
  webpage += "";
  webpage += "<form id=\"topperOFF\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">";
  webpage += "<td><input type=\"hidden\" name=\"withtopper\" value=\"off\">";
  webpage += "<input id=\"topperoff1\" type=\"submit\" name=\"submittopper\" value=\"Topper OFF\" /></form><br></td>";
  webpage += "";
  webpage += "";
  webpage += "<form id=\"topperLength\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">";
  webpage += "</tr><tr><td align=\"right\"><input type=\"number\" name=\"topperLength\" min=\"1\" max=\"100\" placeholder=\"5\"></td>";
  webpage += "<td align=\"left\"><input name=\"topperLength_select\" id=\"topperLengthselectbutton\" type=\"submit\" value=\"Set Topper Length\" />";
  webpage += "</form><br></td></tr><tr>";
  webpage += "";
  webpage += "<form id=\"topperglitterON\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">";
  webpage += "<td align=\"right\"><input type=\"hidden\" name=\"topperwithGlitter\" value=\"on\">";
  webpage += "<input id=\"topperglitteron1\" type=\"submit\" name=\"submittopperGlitter\" value=\"Topper Glitter ON\" /></form></td>";
  webpage += "";
  webpage += "";
  webpage += "<form id=\"topperglitterOFF\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">";
  webpage += "<td><input type=\"hidden\" name=\"topperwithGlitter\" value=\"off\">";
  webpage += "<input id=\"topperglitteroff1\" type=\"submit\" name=\"topper\" value=\"Topper Glitter OFF\" /></form></td>";
  webpage += "";
  webpage += "<form id=\"topperPatternSelect\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">";
  webpage += "<td></tr><tr><td  align=\"right\"><br>";
  webpage += "<label for=\"topperPattern\">Topper Pattern:</label></td><td><br>";
  webpage += "<select id=\"topperPattern\" name =\"topperPattern\">";
  webpage += "<option value=\"TopperRed\">Red</option>";
  webpage += "<option value=\"TopperGold\">Gold</option>";
  webpage += "<option value=\"TopperBlue\">Blue</option>";
  webpage += "<option value=\"TopperGreen\">Green</option>";
  webpage += "<option value=\"TopperPurple\">Purple</option>";
  webpage += "<option value=\"TopperWhite\">White</option>";
  webpage += "<option value=\"TopperColourShift\">Colour Shift</option>";
  webpage += "</select>";
  webpage += "<input type=\"submit\" value=\"Set\">";
  webpage += "</form><br></td></tr><tr><td><br></td></div></tr></table><br>";
  webpage += "<iframe id=\"dummyframe\" border=\"0\" height=\"0\" name=\"dummyframe\" style=\"display: none\" width=\"0\"></iframe>";
  append_HTML_footer();

  server.send(200, "text/html", webpage);
}
//*******************************************************************

//***************************************************************************HOMEPAGE
void handle_OnConnect() {
  webpage = " <!DOCTYPE html>\r\n";  //THis will become the editing page for scheduler.
  webpage += "<html>";
  webpage += "<head>";
  webpage += "<title>" + sitetitle + "</title><br>";
  webpage += webStyle;
  webpage += homepage_content;  //generate webpage

  add_status_and_summary();

  append_HTML_footer();

  server.send(200, "text/html", webpage);
}
//***************************************************************************HOMEPAGE ENDS

//**************************************Schedule Editor********************************
void handle_scheduleedit() {
  if (server.args() > 0) {
    for (uint8_t i = 0; i < server.args(); i++) {
      Serial.println("\nExecuting handlescheduleedit");
      Serial.println(server.argName(i));
      Serial.println(server.arg(i));

      if (server.argName(i) == "daychoice") {
        daychoice = server.arg(i);
        r = daychoice.toInt();
        //        Serial.println("\nAssigning R");
      }
    }
  }
  webpage = "";
  webpage += "<!DOCTYPE html><html><head>";
  webpage += "<meta http-equiv='refresh' content='600'>";  // 5-min refresh time, test needed to prevent auto updates repeating some commands
  webpage += "<title>" + sitetitle + "</title><br>";
  webpage += webStyle;

  webpage += "</head><body style='margin: 0px; padding: 0px'>";


  webpage += "<table width='90%' align='center' border='0'><tr>\r\n";
  webpage += "<td colspan='3'><b><h2>Daily Schedule Editor</h2></b></td></tr><tr>\r\n";

  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=0"
             "><input type='button'";
  if (daychoice.toInt() == 0) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Sunday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=1"
             "><input type='button'";
  if (daychoice.toInt() == 1) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Monday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=2"
             "><input type='button'";
  if (daychoice.toInt() == 2) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Tuesday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=3"
             "><input type='button'";
  if (daychoice.toInt() == 3) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Wednesday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=4"
             "><input type='button'";
  if (daychoice.toInt() == 4) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Thursday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=5"
             "><input type='button'";
  if (daychoice.toInt() == 5) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Friday'></a></td>\r\n";
  //
  webpage += "<td><a href="
             "scheduleedit.htm?daychoice=6"
             "><input type='button'";
  if (daychoice.toInt() == 6) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Saturday'></a></td>\r\n";
  //*********************
  webpage += "</tr><tr>";
  //
  webpage += "<td colspan='2' align='right'><a href="
             "scheduleedit.htm?daychoice=7"
             "><input type='button'";
  if (daychoice.toInt() == 7) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='All 7 Days'></a></td>\r\n";



  webpage += "<td colspan='3' align='center'><a href="
             "scheduleedit.htm?daychoice=8"
             "><input type='button'";
  if (daychoice.toInt() == 8) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Mon to Fri'></a></td>\r\n";
  //
  webpage += "<td colspan='2' align='left'><a href="
             "scheduleedit.htm?daychoice=9"
             "><input type='button'";
  if (daychoice.toInt() == 9) {
    webpage += " class='gentlyrounded weekdaybuttonselected'";
  } else {
    webpage += " class='gentlyrounded weekdaybutton'";
  }
  webpage += " value='Sat & Sun'></a></td>\r\n";

  webpage += "</tr></table> ";

  // END OF SCHEDULE DAYPICKER GRID

  webpage += "<p><span class='scheduleheading'>";
  if (r <= 6) {
    webpage += days[r];
    scheduleButtonText = days[r];
    scheduleDaysPicker = r;
  }
  if (r == 7) {
    webpage += "All 7 days";
    scheduleButtonText = "All 7 days";
    scheduleDaysPicker = 0;  //Need to give the multi-day scheduler some context to work with so pick an arbitrary day from existing scheduler
  }
  if (r == 8) {
    webpage += "Monday to Friday";
    scheduleButtonText = "Monday to Friday";
    scheduleDaysPicker = 1;
  }
  if (r == 9) {
    webpage += "Saturday and Sunday";
    scheduleButtonText = "Saturday and Sunday";
    scheduleDaysPicker = 6;
  }
  webpage += " Schedule Editor</span></p>\r\n";


  webpage += "<p><form action = 'submit.htm' method = 'post'>";
  webpage += "<input type = 'hidden' name = 'daychoice' value = '";
  webpage += r;
  webpage += "'>";
  webpage += " <table id=\"schedule-grid\" width='90%' align='center' border ='1' cellpadding='0' cellspacing='0'>\r\n";
  webpage += "<tr bgcolor = 'grey'><th>Time </th><th>On </th><th>NC </th><th>Off </th><th> _ </th><th>Time </th><th>On </th><th>NC </th><th>Off </th><th> _ </th>\r\n";
  webpage += "<th>Time </th><th>On </th><th>NC </th><th>Off </th><th> _ </th><th>Time </th><th>On </th><th>NC </th><th>Off </th></tr>\r\n";
  for (h = 0; h < 24; h++) {
    delay(5);
    webpage += "<tr>";
    for (quarter = 0; quarter < 4; quarter++) {

      webpage += "<td class=\"timecell\" align='center' bgcolor = 'cyan'>";

      if (h < 10) {
        webpage += "0";
      }
      webpage += h;
      webpage += ":";

      webpage += quarter * 15;
      if (quarter == 0) {
        webpage += "0";
      }
      webpage += " </td>\r\n";
      webpage += "<td class=\"oncell\" align='center'";
      //colour in on off cells

      if ((schedule[scheduleDaysPicker][h][quarter]) == 1) {
        webpage += " bgcolor = 'green'";
      }

      webpage += ">\r\n";
      webpage += "<input type = 'radio' name = '";
      webpage += h;
      webpage += "_";
      webpage += quarter;
      webpage += "' value = '1'";
      if ((schedule[scheduleDaysPicker][h][quarter]) == 1) {
        webpage += " checked";
      }
      webpage += ">ON </td>\r\n";
      webpage += "<td class=\"nccell\" align='center'";
      if (((schedule[scheduleDaysPicker][h][quarter]) == 0) || ((schedule[scheduleDaysPicker][h][quarter]) > 2)) {
        webpage += " bgcolor = 'yellow'";
      }
      webpage += ">\r\n";
      webpage += "<input type = 'radio' name = '";
      webpage += h;
      webpage += "_";
      webpage += quarter;
      webpage += "' value = '0'";

      if (((schedule[scheduleDaysPicker][h][quarter]) == 0) || ((schedule[scheduleDaysPicker][h][quarter]) > 2)) {
        webpage += " checked";
      }
      webpage += ">  </td>\r\n";
      webpage += "<td class=\"oncell\" align='center'";

      if ((schedule[scheduleDaysPicker][h][quarter]) == 2) {
        webpage += " bgcolor = 'red'";
      }

      webpage += ">";
      webpage += "<input type = 'radio' name = '";
      webpage += h;
      webpage += "_";
      webpage += quarter;
      webpage += "' value = '2'";
      if ((schedule[scheduleDaysPicker][h][quarter]) == 2) {
        webpage += " checked";
      }
      webpage += ">OFF </td>\r\n";
      if (quarter < 3) {
        webpage += "<td bgcolor = 'grey'> </td>\r\n";
      }
    }  //end q
    webpage += " </tr> ";
  }  //end h
  webpage += " </table><br>\r\n";
  webpage += "<table width='90%' align='center'><tr><td align='right'><input type = 'submit' value='Save ";
  webpage += scheduleButtonText;
  webpage += " Schedule' class='larger rounded modebuttonred'></td></tr></table>\r\n";
  webpage += " </form><br>";
  append_HTML_footer();

  server.send(200, "text / html", webpage);
}
//*****************Editor ends*****************************************************************
//******-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o***********
void handle_lightsfunction_select() {

  if (server.args() > 0) {
    for (uint8_t i = 0; i < server.args(); i++) {
      Serial.println("\nExecuting handle function select");
      Serial.println(server.argName(i));
      Serial.println(server.arg(i));

      if (server.argName(i) == "colour0") {
        parseColour0(server.arg(i));
        Serial.println("ParseCol 0");
        colour0 = server.arg(i);
        Serial.println(colour0);
      }
      if (server.argName(i) == "colour1") {
        parseColour1(server.arg(i));
        Serial.println("ParseCol 1");
        colour1 = server.arg(i);
      }
      if (server.argName(i) == "colour2") {
        parseColour2(server.arg(i));
        Serial.println("ParseCol 2");
        colour2 = server.arg(i);
      }


      if (server.argName(i) == "schedulewipeyes") {
      //If schedule wipe selected:
      Serial.println("WIPE SCHEDULE PLEASE");
      memset(schedule, 0, sizeof(schedule));
      Serial.println("Schedule wiped by MEMSET");
      preferences.begin("settings", false);  // open preferences as READ WRITE
      preferences.putBytes("schedule", schedule, sizeof(schedule));
      preferences.end();  //close preferences
      Serial.println("Zero schedule written to Preferences");
      }


      //Deal with Topper pattern selection and stuff
      if (server.argName(i) == "topperPattern") {
        topperPattern = server.arg(i);
      }


      if (server.argName(i) == "topperLength") {
        topperLength = server.arg(i).toInt();
      }


      //Ends dealing with Topper
      if (server.argName(i) == "lightFunction") {
        lightFunction = server.arg(i);
        //****************************************************************


        if (lightFunction == "stripFill") {
          currentColour = 0;
          currentPosition = 0;
        }  //For stripFill, reset colour index and position index to 0 and work with them in the loop


        if (lightFunction == "confetti") {
          fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  //set all to black
          //FastLED.show();
        }  //If confetti selected, black out strip

        if (lightFunction == "comets") {
          fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  //set all to black
          currentPosition = 0;
          //FastLED.show();
        }  //If comets selected, black out strip
      }
      //********************************************SELECT LIGHTS FUNCTION END


      //********************************************SELECT BRIGHTNESS
      if (server.argName(i) == "bright") {
        bright = server.arg(i).toInt();
      }
      //********************************************SELECT BRIGHTNESS ENDS

      //********************************************Scheduler Enable
      if (server.argName(i) == "withscheduler") {
        String str = server.arg(i);
        if (str == "on") {
          scheduleEnabled = true;
        } else if (str == "off") {
          scheduleEnabled = false;
        }
      }
      //********************************************Scheduler Enable ENDS


      //********************************************SELECT GLITTER
      if (server.argName(i) == "withGlitter") {
        applyGlitter = server.arg(i);
      }
      //********************************************SELECT GLITTER ENDS


      //********************************************SELECT TOPPER GLITTER
      if (server.argName(i) == "topperwithGlitter") {
        applyTopperGlitter = server.arg(i);
      }
      //********************************************SELECT TOPPER GLITTER ENDS


      //********************************************SELECT TOPPER
      if (server.argName(i) == "withtopper") {
        applyTopper = server.arg(i);
      }

      //********************************************SELECT TOPPER ENDS

      //********************************************SELECT RAINBOWS QUANTITY
      if (server.argName(i) == "numberRainbows") {
        numberRainbows = server.arg(i).toInt();
      }
      //********************************************SELECT RAINBOWS QTY ENDS
    }
  }

  //*****************************************************************************Save settings in preferences
  preferences.begin("settings", false);  // open preferences as READ WRITE
  preferences.putString("colour0", colour0);
  preferences.putString("colour1", colour1);
  preferences.putString("colour2", colour2);
  preferences.putString("topperPattern", topperPattern);
  preferences.putInt("topperLength", topperLength);
  preferences.putInt("bright", bright);
  preferences.putString("applyGlitter", applyGlitter);
  preferences.putString("applyTopperGlitter", applyTopperGlitter);
  preferences.putString("applyTopper", applyTopper);
  preferences.putInt("numberRainbows", numberRainbows);
  preferences.putBool("scheduleEnabled", scheduleEnabled);

  if (lightFunction != "reboot") {
    preferences.putString("lightFunction", lightFunction);
  }  //Don't write "reboot as last function else it'll wake up and...reboot!

  preferences.end();  //close preferences
  //*****************************************************************************Save settings in preferences ends

  webpage = homepage_content;  //generate webpage

  add_status_and_summary();

  // append_HTML_footer();
  server.send(200, "text/html", webpage);
}  //ends handle_function_select

void handleXML() {
  buildXML();
  server.send(200, "text/xml", XML);
}
//**************************************************************************************************

//SLIDER 1
void handle_slider1() {
  Serial.println("slider web call");
  String inputMessage;
  // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
  if (server.args() > 0) {
    for (uint8_t i = 0; i < server.args(); i++) {
      inputMessage = server.arg(i);
      sliderValue = inputMessage;
      bright = sliderValue.toInt();
    }
  } else {
    inputMessage = "No message sent";
  }
  Serial.println(inputMessage);

  preferences.begin("settings", false);  // open preferences as READ WRITE
  preferences.putInt("bright", bright);
  preferences.end();  //close preferences

  server.send(200, "text / plain", "OK");
}

//CODE FOR 2ND SLIDER BELOW..

void handle_slider2() {
  Serial.println("slider 2 web call");
  String inputMessage;
  // GET input2 value on <ESP_IP>/slider?value=<inputMessage>
  if (server.args() > 0) {
    inputMessage = server.arg(0);
    slider2Value = inputMessage;
    bright2 = slider2Value.toInt();
  } else {
    inputMessage = "No message sent";
  }
  Serial.println(inputMessage);

  preferences.begin("settings", false);  // open preferences as READ WRITE
  preferences.putInt("bright2", bright2);
  preferences.end();  //close preferences
  server.send(200, "text / plain", "OK");
}


//***************************************** SUBMIT ********************************************
void handle_submit()  //for schedule changes
{
  String webpage = "";
  //Inputs are sequarteruential. 1st is daychoice then 0 hour quarter0 1 2 3.. 1 hour quarter0 1 2 3 etc.
  //Now sequarteruentially write inputs to schedule array.
  //D is daychoice
  //Set up a 24,4 loop with counter.
  //1st iteration,Day D, h 0 quarter 0 gets server arg 2
  //Server arg counter increments, go round loop again quarteruarters.
  //Daychoice 7 = ALL 7 days (0-6)
  //Daychoice 8 = Mon-Fri (1-5)
  //Daychoice 9 = Sat,Sun (0 & 6)
  if (server.args() > 0) {
    for (uint8_t i = 0; i < server.args(); i++) {

      if (server.argName(i) == "daychoice") {
        daychoice = server.arg(i);

      }  //end if arg daychoice
    }
  }
  Serial.print("Daychoice is argument number: ");
  Serial.println(daychoice);
  webpage += " <!DOCTYPE html>\r\n";  //THis will become the editing page for scheduler.
  webpage += "<html>";
  webpage += "<head>";
  webpage += "<meta http-equiv=\"refresh\" content=\"1; url=scheduleedit.htm?daychoice=";
  webpage += daychoice;
  webpage += "\">";
  webpage += "</head><body>";
  int argcount = 1;
  int activeDays = (daychoice).toInt();
  int dayCount;

  Serial.print("ActiveDays is argument number: ");
  Serial.println(activeDays);
  //*****************************************************
  if (activeDays <= 6) {
    Serial.print("Editing active day: ");
    Serial.println(activeDays);
    argcount = 1;
    for (h = 0; h < 24; h++) {
      for (quarter = 0; quarter < 4; quarter++) {
        schedule[activeDays][h][quarter] = (server.arg(argcount)).toInt();
        argcount = argcount + 1;
      }  //end quarter
    }    //end h
  }
  //******************************************************
  //*****************************************************
  if (activeDays == 7) {
    for (dayCount = 0; dayCount < 7; dayCount++)  // Days 0 to 6 inc
    {
      Serial.print("Editing active day: ");
      Serial.println(dayCount);
      argcount = 1;
      for (h = 0; h < 24; h++) {
        for (quarter = 0; quarter < 4; quarter++) {
          schedule[dayCount][h][quarter] = (server.arg(argcount)).toInt();
          argcount = argcount + 1;
        }  //end quarter
      }    //end h
    }      //end dayCount
  }        //end if activedays 7
  //******************************************************
  //*****************************************************
  if (activeDays == 8) {
    for (dayCount = 1; dayCount < 6; dayCount++)  //days 1 to 5 inc
    {
      Serial.print("Editing active day: ");
      Serial.println(dayCount);
      argcount = 1;
      {
        for (h = 0; h < 24; h++) {
          for (quarter = 0; quarter < 4; quarter++) {
            schedule[dayCount][h][quarter] = (server.arg(argcount)).toInt();
            argcount = argcount + 1;
          }  //end quarter
        }    //end h
      }      //end dayCount
    }
  }  //end if activedays 8
  //******************************************************
  //*****************************************************
  if (activeDays == 9) {
    for (dayCount = 0; dayCount < 7; dayCount = dayCount + 6)  //days 0 and 6
    {
      Serial.print("Editing active day: ");
      Serial.println(dayCount);
      argcount = 1;
      {
        for (h = 0; h < 24; h++) {
          for (quarter = 0; quarter < 4; quarter++) {
            schedule[dayCount][h][quarter] = (server.arg(argcount)).toInt();
            argcount = argcount + 1;
          }  //end quarter
        }    //end h
      }      //end dayCount
    }
  }  //end if activedays 8
  //******************************************************

  webpage += "Done. Click <a href='scheduleedit.htm?daychoice=";
  webpage += daychoice;
  webpage += "'>Click here to return</a><br><br>";

  address = 0;

  const int arrayLength = 4;
  const int arrayWidth = 24;
  const int arrayHeight = 7;
  Serial.println("Writing schedule to preferences begins");
  preferences.begin("settings", false);  // open preferences as READ WRITE
  preferences.putBytes("schedule", schedule, sizeof(schedule));

  Serial.print("The size of \"schedule\" is (in bytes): ");
  Serial.println(preferences.getBytesLength("schedule"));
  Serial.println("");
  byte tempdata[672] = {};  // No magic about 20. Just making a buffer (array) big enough.
  Serial.println("Retrieving the value of preferences into tempdata.");
  Serial.println("   - Note the data type of myIntBuffer matches that of myArray");
  preferences.getBytes("schedule", tempdata, preferences.getBytesLength("schedule"));

  Serial.println("Printing myIntBuffer...");
  // In the next statement, sizeof() needs to match the data type of the elements of myArray
  for (int i = 0; i < preferences.getBytesLength("schedule") / sizeof(byte); i++) {
    Serial.print(tempdata[i], HEX);
    Serial.print(", ");
  }
  Serial.println("\r\n");
  preferences.end();  //close preferences



  append_HTML_footer();
  server.send(200, "text/html", webpage);
}
//*************************SUBMIT ENDS**************************************************************

void handle_wipe_schedule() {

  webpage = " <!DOCTYPE html>\r\n";  //THis will become the editing page for scheduler.
  webpage += "<html>";
  webpage += "<head>";
  webpage += webStyle;
  webpage += "<title>" + sitetitle + "</title><br>";
  webpage += "</head><body><hr>";
  webpage += "Really wipe schedule?";


  webpage += "<table><tr><td align=\"right\">\r\n";
  webpage += "<form id=\"wipe\" action=\"select.htm\" method=\"post\" target=\"dummyframe\">\r\n";
  webpage += "<input type=\"hidden\" name=\"schedulewipeyes\" value=\"on\">\r\n";
  webpage += "<input id=\"schedulewipe\" class=\"larger\" type=\"submit\" name=\"submitschedulewipe\" value=\"YES - Wipe all schedule data\" onclick=\"redirectToHomePage()\" />\r\n";
  webpage += "</form>\r\n";
  webpage += "</td>\r\n";
  webpage += "\r\n";
  webpage += "<td align=\"left\">\r\n";
  webpage += "<a href=\"/\"><button class = \"larger\" >NO - go home!</button></a>\r\n";
  webpage += "</td><tr><tr></table>\r\n";

  webpage += "<iframe id=\"dummyframe\" border=\"0\" height=\"0\" name=\"dummyframe\" style=\"display: none\" width=\"0\"></iframe>";
  
  append_HTML_footer();

  webpage += "<script>";
  webpage += "function redirectToHomePage() {";
  webpage += "  window.location.href = \"/\";";
  webpage += "}";
  webpage +="</script>";

  server.send(200, "text / html", webpage);
}
