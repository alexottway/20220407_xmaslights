const char homepage_content[] PROGMEM = R"=====(

<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<meta content="width=device-width, initial-scale=1.0" name="viewport" />
<title>Christmas Lights Control</title>

 <link rel="preload" href="/tree64.png" as="image">
 <link rel="preload" href="/tree64BW.png" as="image">
 <link rel="preload" href="/clock64.png" as="image">
 <link rel="preload" href="/clock64bw.png" as="image">
<script type="text/javascript">

var xmlHttp=createXmlHttpObject();
function createXmlHttpObject(){
 if(window.XMLHttpRequest){
    xmlHttp=new XMLHttpRequest();
 } else {
    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');
 }
 return xmlHttp;
}

function process(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xml',true);
   xmlHttp.onreadystatechange=handleServerResponse; // no brackets?????
   xmlHttp.send(null);
 }
 setTimeout('process()',1000);
}


function process2(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xml',true);
   xmlHttp.onreadystatechange=handleServerResponse2; // no brackets?????
   xmlHttp.send(null);
 }
 setTimeout('process2()',18000);
}

function handleServerResponse2(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   xmlResponse=xmlHttp.responseXML;

  xmldoc = xmlResponse.getElementsByTagName('colour0');
   colour0message = xmldoc[0].firstChild.nodeValue;
  document.getElementById("colour0").value = colour0message;

  xmldoc = xmlResponse.getElementsByTagName('colour1');
   colour1message = xmldoc[0].firstChild.nodeValue;
  document.getElementById("colour1").value = colour1message;

  xmldoc = xmlResponse.getElementsByTagName('colour2');
   colour2message = xmldoc[0].firstChild.nodeValue;
  document.getElementById("colour2").value = colour2message;


 }
 }


function handleServerResponse(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){

   xmlResponse=xmlHttp.responseXML;

   xmldoc = xmlResponse.getElementsByTagName('schedulerChange');
   message = xmldoc[0].firstChild.nodeValue;
    if (message == "1"){
 showAllElementsFunction();
    }
   

   xmldoc = xmlResponse.getElementsByTagName('response1');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('readystatus').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('response2');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('readystatus2').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('response3');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('readystatus3').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('response4');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('readystatus4').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('response5');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('readystatus5').innerHTML=message;
   
   xmldoc = xmlResponse.getElementsByTagName('howbright');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('howbright').innerHTML=message;
   document.getElementById("pwmSlider").value = message;

   xmldoc = xmlResponse.getElementsByTagName('howslow');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('howslow').innerHTML=message;
   document.getElementById("pwmSlider2").value = message;

   xmldoc = xmlResponse.getElementsByTagName('lightState');
   message = xmldoc[0].firstChild.nodeValue;

var statuspic = document.getElementById('statuspic');
var statuspic2 = document.getElementById('statuspic2');
   
   if (message=="on"){
    document.getElementById('offbutton1').disabled = false; 
statuspic.style.backgroundImage = 'url("/tree64.png")';

   } else {
    document.getElementById('offbutton1').disabled = true;
statuspic.style.backgroundImage = 'url("/tree64BW.png")';
   }

    if (message=="off"){
    document.getElementById('offbutton1').disabled = true; 
    statuspic.style.backgroundImage = 'url("/tree64BW.png")';
   } else {
    document.getElementById('offbutton1').disabled = false; 
    statuspic.style.backgroundImage = 'url("/tree64.png")'; 
   }



   xmldoc = xmlResponse.getElementsByTagName('scheduler');
   message = xmldoc[0].firstChild.nodeValue;
   if (message=="1"){
statuspic2.style.backgroundImage = 'url("/clock64.png")';
   } else {
statuspic2.style.backgroundImage = 'url("/clock64bw.png")';
   }


    if (message=="0"){
    statuspic2.style.backgroundImage = 'url("/clock64bw.png")';    
   } else {
    statuspic2.style.backgroundImage = 'url("/clock64.png")';    
   }

statuspic.style.backgroundRepeat = 'no-repeat';
statuspic2.style.backgroundRepeat = 'no-repeat';

   xmldoc = xmlResponse.getElementsByTagName('lightFunction');
   message = xmldoc[0].firstChild.nodeValue;
   
   if(message=="singleColourChange"){
   document.getElementById('rainbowSelection').style.display = "none";
   document.getElementById('samecolouronbutton1').disabled = true;
   document.getElementById('colourSelection').style.display = "none";
   }    

   if(message=="comets"){
   document.getElementById('rainbowSelection').style.display = "none";
   document.getElementById('cometsbutton1').disabled = true;
   document.getElementById('colourSelection').style.display = "none";
   }


   if(message=="juggle"){
   document.getElementById('rainbowSelection').style.display = "none";
   document.getElementById('jugglebutton1').disabled = true;
   }
   
   if(message=="bunting"){
   document.getElementById('rainbowSelection').style.display = "none";
   document.getElementById('buntingbutton1').disabled = true;
   }

   if(message=="theatrechase"){   
   document.getElementById('colour2').style.display = "none";
   document.getElementById('theatrechasebutton1').disabled = true;
   document.getElementById('rainbowSelection').style.display = "none";
   } 
  
   if(message=="None selected"){
   document.getElementById('rainbowSelection').style.display = "block";
   document.getElementById('rainbowsonbutton1').disabled = false; 
   document.getElementById('samecolouronbutton1').disabled = false; 
   }


   if(message=="multiRainbow"){
   document.getElementById('rainbowsonbutton1').disabled = true;
   document.getElementById('colourSelection').style.display = "none";
    }

   if(message=="confetti"){
   document.getElementById('confettibutton1').disabled = true;    
   document.getElementById('rainbowSelection').style.display = "none";
   } 

   if(message=="stripFill"){
   document.getElementById('stripfillbutton1').disabled = true; 
   document.getElementById('rainbowSelection').style.display = "none"; 
   document.getElementById('colourSelection').style.display = "none";
   }

   xmldoc = xmlResponse.getElementsByTagName('glitter');
   glittermessage = xmldoc[0].firstChild.nodeValue;
   
   if(glittermessage=="on"){
     document.getElementById('glitteron1').disabled = true;
     document.getElementById('glitteroff1').disabled = false;   
   } else {
     document.getElementById('glitteron1').disabled = false; 
     document.getElementById('glitteroff1').disabled = true;      
   }
   
    if(glittermessage=="off"){
     document.getElementById('glitteroff1').disabled = true;   
     document.getElementById('glitteron1').disabled = false;
     } else {
     document.getElementById('glitteroff1').disabled = false;       
     document.getElementById('glitteron1').disabled = true;
     }


/*
   xmldoc = xmlResponse.getElementsByTagName('topperglitter');
   topperglittermessage = xmldoc[0].firstChild.nodeValue;
   
   if(topperglittermessage=="on"){
     document.getElementById('topperglitteron1').disabled = true;
     document.getElementById('topperglitteroff1').disabled = false;   
   } else {
     document.getElementById('topperglitteron1').disabled = false; 
     document.getElementById('topperglitteroff1').disabled = true;      
   }
   
    if(topperglittermessage=="off"){
     document.getElementById('topperglitteroff1').disabled = true;   
     document.getElementById('topperglitteron1').disabled = false;
     } else {
     document.getElementById('topperglitteroff1').disabled = false;       
     document.getElementById('topperglitteron1').disabled = true;
     }

   xmldoc = xmlResponse.getElementsByTagName('topper');
   toppermessage = xmldoc[0].firstChild.nodeValue;
   
   if(toppermessage=="on"){
     document.getElementById('topperon1').disabled = true;
     document.getElementById('topperoff1').disabled = false;   
   } else {
     document.getElementById('topperon1').disabled = false; 
     document.getElementById('topperoff1').disabled = true;      
   }
   
    if(toppermessage=="off"){
     document.getElementById('topperoff1').disabled = true;   
     document.getElementById('topperon1').disabled = false;
     } else {
     document.getElementById('topperoff1').disabled = false;       
     document.getElementById('topperon1').disabled = true;
     }


*/

   xmldoc = xmlResponse.getElementsByTagName('numberRainbows');
   qty = xmldoc[0].firstChild.nodeValue;
   document.getElementById('numberRainbows' + qty).disabled = true;

 }
}

function updateSliderPWM(element) {
  var sliderValue = document.getElementById("pwmSlider").value;
  console.log(sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value="+sliderValue, true);
  xhr.send();
}
function updateSliderPWM2(element) {
  var slider2Value = document.getElementById("pwmSlider2").value;
  console.log(slider2Value);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider2?value="+slider2Value, true);
  xhr.send();
}

</script>


</head>

<body onload='process();process2();'>

<table style="width:90%; height:64px; margin:auto;">
<tr>
<td id="statuspic" style="width: 64px; height: 64px;">
</td>
<td>
<h1 align="center">Christmas Lights Control</h1>
</td>
 <td id="statuspic2" style="width: 64px; height: 64px;">
 </td>
 </tr>
 </table>
<hr>



<table style="width: 90%; align:center; margin: auto;">
<tr>
<th colspan="2" style="text-align:left">Turn Off Lights</th>
</tr>
 <tr>
    <td>
      <form id="offbutton" action="select.htm" method="post" target="dummyframe">
      <input id="lightFunction" name="lightFunction" style="display: inline-block" type="hidden" value="Off" />
      <input type="hidden" name="withGlitter" value="off">
      <input class="larger" id="offbutton1" style="display: inline-block; background-color: #ff0000" type="submit" value="ALL LIGHTS OFF" />
    </form>
 </td>


 </tr>
 </table>


<table style="width: 90%; align:center; margin: auto;">
<tr>
<th style="text-align:left" colspan="2">
Select Function:
</th>
</tr>
<tr>
<td align="center">
      <form id="rainbowsonbutton" action="select.htm" method="post" target="dummyframe">
      <input name="lightFunction" style="display: inline-block" type="hidden" value="multiRainbow"/>
      <input name="lightState" style="display: inline-block" type="hidden" value="ON" />
      <input class="larger" id="rainbowsonbutton1" style="display: inline-block; background-color: cyan" type="submit" value="RAINBOWS" />      
    </form>
 </td>

<td align="center">
      <form id="samecolouronbutton" action="select.htm" method="post" target="dummyframe">
      <input name="lightFunction" style="display: inline-block" type="hidden" value="singleColourChange"/>
      <input name="lightState" style="display: inline-block" type="hidden" value="ON" />
      <input class="larger" id="samecolouronbutton1" style="display: inline-block; background-color: cyan" type="submit" value="COLOUR SHIFT" />      
    </form>
 </td>

<td align="center">
      <form id="stripfillbutton" action="select.htm" method="post" target="dummyframe">
      <input name="lightFunction" style="display: inline-block" type="hidden" value="stripFill"/>
      <input name="lightState" style="display: inline-block" type="hidden" value="ON" />
      <input class="larger" id="stripfillbutton1" style="display: inline-block; background-color: cyan" type="submit" value="STRIP FILL" />      
    </form>
 </td>



<td align="center">
      <form id="confettibutton" action="select.htm" method="post" target="dummyframe">
      <input name="lightFunction" style="display: inline-block" type="hidden" value="confetti"/>
      <input name="lightState" style="display: inline-block" type="hidden" value="ON" />
      <input class="larger" id="confettibutton1" style="display: inline-block; background-color: cyan" type="submit" value="CONFETTI" />      
    </form>
 </td>

</tr>
<tr>

<td align="center">
      <form id="buntingbutton" action="select.htm" method="post" target="dummyframe">
      <input name="lightFunction" style="display: inline-block" type="hidden" value="bunting"/>
      <input name="lightState" style="display: inline-block" type="hidden" value="ON" />
      <input class="larger" id="buntingbutton1" style="display: inline-block; background-color: cyan" type="submit" value="BUNTING" />      
    </form>
 </td>

<td align="center">
      <form id="theatrechasebutton" action="select.htm" method="post" target="dummyframe">
      <input name="lightFunction" style="display: inline-block" type="hidden" value="theatrechase"/>
      <input name="lightState" style="display: inline-block" type="hidden" value="ON" />
      <input class="larger" id="theatrechasebutton1" style="display: inline-block; background-color: cyan" type="submit" value="THEATRE CHASE" />      
    </form>
 </td>


<td align="center">
      <form id="cometsbutton" action="select.htm" method="post" target="dummyframe">
      <input name="lightFunction" style="display: inline-block" type="hidden" value="comets"/>
      <input name="lightState" style="display: inline-block" type="hidden" value="ON" />
      <input class="larger" id="cometsbutton1" style="display: inline-block; background-color: cyan" type="submit" value="COMETS" />      
    </form>
 </td>


<td align="center">
      <form id="jugglebutton" action="select.htm" method="post" target="dummyframe">
      <input name="lightFunction" style="display: inline-block" type="hidden" value="juggle"/>
      <input name="lightState" style="display: inline-block" type="hidden" value="ON" />
      <input class="larger" id="jugglebutton1" style="display: inline-block; background-color: cyan" type="submit" value="JUGGLE" />      
    </form>
 </td> 

 </tr>

</table>


    
<hr>
<h3>Additional Options</h3>
<!--
/*
<table style="width:100%" id="toppertable">
<tr>
<div id="topperSelection" style="display: inline">
<th colspan="4">Separate Top Lighting</th>
</tr>
<tr>
<form id="topperON" action="select.htm" method="post" target="dummyframe">
<td>
<input type="hidden" name="withtopper" value="on">
<input id="topperon1" type="submit" name="submittopper" value="Topper ON" />
</form>
</td>


<form id="topperOFF" action="select.htm" method="post" target="dummyframe">
<td>
<input type="hidden" name="withtopper" value="off">
<input id="topperoff1" type="submit" name="submittopper" value="Topper OFF" />
</form>
</td>


<form id="topperLength" action="select.htm" method="post" target="dummyframe">
<td>
<input type="number" name="topperLength" min="1" max="100" placeholder="5">
</td>
<td>
<input name="topperLength_select" id="topperLengthselectbutton" type="submit" value="Set Topper Length" />
</form>
</td>

</tr><tr>

<form id="topperglitterON" action="select.htm" method="post" target="dummyframe">
<td> 
<input type="hidden" name="topperwithGlitter" value="on">
<input id="topperglitteron1" type="submit" name="submittopperGlitter" value="Topper Glitter ON" />
</form>
</td>


<form id="topperglitterOFF" action="select.htm" method="post" target="dummyframe">
<td>
<input type="hidden" name="topperwithGlitter" value="off">
<input id="topperglitteroff1" type="submit" name="topper" value="Topper Glitter OFF" />
</form>
</td>

<form id="topperPatternSelect" action="select.htm" method="post" target="dummyframe">
<td>
<label for="topperPattern">Topper Pattern:</label>
<select id="topperPattern" name ="topperPattern">
<option value="TopperRed">Red</option>
<option value="TopperGold">Gold</option>
<option value="TopperBlue">Blue</option>
<option value="TopperGreen">Green</option>
<option value="TopperPurple">Purple</option>
<option value="TopperWhite">White</option>
<option value="TopperColourShift">Colour Shift</option>
</select>
<input type="submit" value="Set">
</form>
</td>


</div>

</tr>
</table>
*/
-->
<p></p>

<div class="slidecontainer">
<span class="sliderHeading">Brightness: </span><span id="howbright"></span>
<br/>
<input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="5" max="255" step="5" class="slider">
</div>


<p></p>

<div class="slidecontainer">
<span class="sliderHeading">Speed (Higher is faster): </span><span id="howslow"></span>
<br/>
<input type="range" onchange="updateSliderPWM2(this)" id="pwmSlider2" min="1" max="1000" class="slider">
</div>

<p></p>

<table style="width: 90%; align:center; margin: auto;">
<tr><td>

<div id="glitterSelect">
<table style="width: 90%; align:center;">
  <tr>
    <th colspan="2">Add glitter?</th>
    <th>&nbsp;</th>
  </tr>
  <tr>
    <td align="right">
      <form id="glitterON" action="select.htm" method="post" target="dummyframe">
        <input type="hidden" name="withGlitter" value="on">
        <input id="glitteron1" type="submit" name="submitGlitter" value="Glitter ON" />
      </form>
    </td>

    <td align="left">
      <form id="glitterOFF" action="select.htm" method="post" target="dummyframe">
        <input type="hidden" name="withGlitter" value="off">
        <input id="glitteroff1" type="submit" name="submitGlitter" value="Glitter OFF" />
      </form>
    </td>

    <td>&nbsp;</td>

  </tr>
</table>
</div>
</td><td>

<br>
<div id="colourSelection" style="display: inline">
<table style="width: 90%; align:center;">
  <tr>
    <th colspan="3">Custom Pattern Colours</th>
  </tr>
  <tr>
    <td align="right">
      <form id="colours" action="select.htm" method="post" target="dummyframe">
        <input id="colour0" name="colour0" type="color" disabled />
      </td>
      <td align="center">
        <input id="colour1" name="colour1" type="color" />
      </td>
      <td align="left">
        <input id="colour2" name="colour2" type="color" />
      </td>
    </tr>
    <tr>
      <td colspan="3" align="center">
        <input name="colours_select" id="colourselectbutton" type="submit" value="Set System Colours" />
      </form>
    </td>
  </tr>
</table>
</div>
</td><td>


<div id="rainbowSelection" style="display: inline">
<table align="center">
<tr>
<th style="text-align:left" colspan="7">
How many rainbows per strip?
</th>
</tr>

<tr>
<td>

<form id="numRainbows1" action="select.htm" method="post" target="dummyframe">
<input type="hidden" name="numberRainbows" value="1">
<input id="numberRainbows1" type="submit" name="submitRainbows" value="1" />
</form>

</td><td>

<form id="numRainbows2" action="select.htm" method="post" target="dummyframe">
<input type="hidden" name="numberRainbows" value="2">
<input id="numberRainbows2" type="submit" name="submitRainbows" value="2" />
</form>

</td><td>

<form id="numRainbows3" action="select.htm" method="post" target="dummyframe">
<input type="hidden" name="numberRainbows" value="3">
<input id="numberRainbows3" type="submit" name="submitRainbows" value="3" />
</form>

</td><td>

<form id="numRainbows4" action="select.htm" method="post" target="dummyframe">
<input type="hidden" name="numberRainbows" value="4">
<input id="numberRainbows4" type="submit" name="submitRainbows" value="4" />
</form>

</td><td>

<form id="numRainbows6" action="select.htm" method="post" target="dummyframe">
<input type="hidden" name="numberRainbows" value="6">
<input id="numberRainbows6" type="submit" name="submitRainbows" value="6" />
</form>

</td><td>

<form id="numRainbows8" action="select.htm" method="post" target="dummyframe">
<input type="hidden" name="numberRainbows" value="8">
<input id="numberRainbows8" type="submit" name="submitRainbows" value="8" />
</form>

</td><td>

<form id="numRainbows10" action="select.htm" method="post" target="dummyframe">
<input type="hidden" name="numberRainbows" value="10">
<input id="numberRainbows10" type="submit" name="submitRainbows" value="10" />
</form>

</td>
</tr>
</table>
</div>

</td></tr></table>

<hr>


<br />
<iframe id="dummyframe" border="0" height="0" name="dummyframe" style="display: none" width="0">
</iframe>


<script>
document.getElementById("numberRainbows1").addEventListener("click", showAllRainbowQtyFunction);
document.getElementById("numberRainbows2").addEventListener("click", showAllRainbowQtyFunction);
document.getElementById("numberRainbows3").addEventListener("click", showAllRainbowQtyFunction);
document.getElementById("numberRainbows4").addEventListener("click", showAllRainbowQtyFunction);
document.getElementById("numberRainbows6").addEventListener("click", showAllRainbowQtyFunction);
document.getElementById("numberRainbows8").addEventListener("click", showAllRainbowQtyFunction);
document.getElementById("numberRainbows10").addEventListener("click", showAllRainbowQtyFunction);

function showAllRainbowQtyFunction() {
document.getElementById('numberRainbows1').disabled = false;
document.getElementById('numberRainbows2').disabled = false;
document.getElementById('numberRainbows3').disabled = false;
document.getElementById('numberRainbows4').disabled = false;
document.getElementById('numberRainbows6').disabled = false;
document.getElementById('numberRainbows8').disabled = false;
document.getElementById('numberRainbows10').disabled = false;
}



document.getElementById("offbutton1").addEventListener("click", showAllElementsFunction);
document.getElementById("rainbowsonbutton1").addEventListener("click", showAllElementsFunction);
document.getElementById("samecolouronbutton1").addEventListener("click", showAllElementsFunction);
document.getElementById("stripfillbutton1").addEventListener("click", showAllElementsFunction);
document.getElementById("confettibutton1").addEventListener("click", showAllElementsFunction);
document.getElementById("buntingbutton1").addEventListener("click", showAllElementsFunction);
document.getElementById("theatrechasebutton1").addEventListener("click", showAllElementsFunction);
document.getElementById("cometsbutton1").addEventListener("click", showAllElementsFunction);
document.getElementById("jugglebutton1").addEventListener("click", showAllElementsFunction);


function showAllElementsFunction() {
  console.log("The ShowAllElementsFunction() function was called!");
document.getElementById('offbutton1').disabled = false;
document.getElementById('rainbowsonbutton1').disabled = false;
document.getElementById('samecolouronbutton1').disabled = false;
document.getElementById('stripfillbutton1').disabled = false;
document.getElementById('confettibutton1').disabled = false;
document.getElementById('buntingbutton1').disabled = false;
document.getElementById('theatrechasebutton1').disabled = false;
document.getElementById('cometsbutton1').disabled = false;
document.getElementById('jugglebutton1').disabled = false;
document.getElementById('colourselectbutton').disabled = false;
document.getElementById('glitteron1').disabled = false;
document.getElementById('glitteroff1').disabled = false;
document.getElementById('colour0').style.display = "block";
document.getElementById('colour1').style.display = "block";
document.getElementById('colour2').style.display = "block";
document.getElementById('rainbowSelection').style.display = "block";
document.getElementById('glitterSelect').style.display = "block";
document.getElementById('colourSelection').style.display = "block";
/*
document.getElementById('topperon1').disabled = false;
document.getElementById('topperoff1').disabled = false;
document.getElementById('topperglitteron1').disabled = false;
document.getElementById('topperglitteroff1').disabled = false;
*/

}
</script>



)=====";
