const char webStyle[] PROGMEM = R"=====(

<style>


body {
  background-color: azure;
}

p, h2, h3 {
font-family: arial;
color:Green;
}

h1 {
font-family: arial;
color:Red;
}


input[type=submit], select {
  border: 2px solid green;
  border-radius: 4px;
  color:Dark Grey;
  font-weight:bold;
  outline: 1px solid black;
  margin-right: 5px;
  cursor:pointer;
}

input[type=number] {
  border: 2px solid red;
  border-radius: 4px;
  color:Dark Grey;
  font-weight:bold;
  outline: 1px solid black;
  margin-right: 5px;
  cursor:pointer;
}

input[type=submit]:disabled {
  cursor: not-allowed;
  pointer-events: all !important;
  border: 2px solid red;
  border-radius: 4px;
  color: DarkRed;
  
}

input[type=color] {
  border: 2px solid red;
  border-radius: 4px;
  outline: 1px solid black;
  margin-right: 5px;
  margin-bottom: 5px;
  cursor:pointer;
}

.auto-style8 {
  border-collapse: collapse;
  border-style: solid;
  border-width: 2px;
  background-color: Blue;
  color:white;
  border-radius: 4px;
  
}


th {
color: black;
font-family: arial;
font-size: medium
}

.slidecontainer {
  width:90%; /* Width of the outside container */
  margin:auto;
}

/* The slider itself */
.slider {
  -webkit-appearance: none;  /* Override default CSS styles */
  appearance: none;
  width: 100%; /* Full-width */
  height: 25px; /* Specified height */
  background: #d3d3d3; /* Grey background */
  
  
  border: 1px solid blue;
  outline: Yellow solid 2px;
  margin: auto;  
  padding: 2px;
  
  
  opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */
  -webkit-transition: .2s; /* 0.2 seconds transition on hover */
  transition: opacity .2s;
}

/* Mouse-over effects */
.slider:hover {
  opacity: 1; /* Fully shown on mouse-over */
}

/* The slider handle (use -webkit- (Chrome, Opera, Safari, Edge) and -moz- (Firefox) to override default look) */
.slider::-webkit-slider-thumb {
  -webkit-appearance: none; /* Override default look */
  appearance: none;
  width: 25px; /* Set a specific slider handle width */
  height: 25px; /* Slider handle height */
  background: Blue; /* Green background */
  cursor: pointer; /* Cursor on hover */
}

.slider::-moz-range-thumb {
  width: 25px; /* Set a specific slider handle width */
  height: 25px; /* Slider handle height */
  background: #4CAF50; /* Green background */
  cursor: pointer; /* Cursor on hover */
}


#toppertable {
  border: 2px solid red;
  border-radius: 4px;
  color:Dark Grey;
  font-weight:bold;
  outline: 1px solid black;
  margin-right: 5px;
}

.rounded {
    background-color: #4CAF50;
    color: white;

    text-align: right;
    text-decoration: none;
    display: inline-block;
    font-size: 14px;
    margin: 2px 1px;
    border-radius: 12px;

}

.larger {
  
   padding: 8px 12px;
      font-size: 18px;
    font-weight: bold;
}

.bigger {
    border: none;
    color: white;

    text-align: right;
    text-decoration: none;
    display: inline-block;
    font-size: 18px;
    font-weight: bold;
    margin: 2px 1px;
    cursor: none;
}

.gentlyrounded {
    background-color: #4CAF50; 
    border: none;
    color: white;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 14px;
    margin: 2px 1px;
    border-radius: 4px;

}

.modebuttonred {
    background-color: Green;
    color: White;
    border: 2px solid #FF0000;
    font-weight: bold;
    cursor: pointer;
}
.modebuttonblue {
    background-color: cyan;
    color: black;
    border: 2px solid #CCCCCC;
    font-weight: bold;
    cursor: pointer;
}


.returntomonitoring {
    background-color: white;
    color: black;
    border: 2px solid green;
    cursor: pointer;
}

.weekdaybutton {
    background-color: LightSteelBlue;
    color: black;
    border: 1px solid Grey;
    font-weight: bold;
    cursor: pointer;
    border: 2px solid green;
    border-radius: 4px;
    color: DarkRed;
}

.weekdaybuttonselected {
    background-color: gold;
    color: black;
    border: 1px solid Grey;
    font-weight: bold;
    cursor: pointer;
    border: 2px solid green;
    border-radius: 4px;
    color: DarkRed;
}

.daychoicebutton {
    background-color: LightSteelBlue;
    color: black;
    border: 1px solid Grey;
    font-weight: bold;
    cursor: pointer;
    border: 2px solid green;
    border-radius: 4px;
    color: DarkRed;
}

.daychoicebuttonselected {
    background-color: gold;
    color: black;
    border: 1px solid Grey;
    font-weight: bold;
    cursor: not-allowed;
    border: 2px solid red;
    border-radius: 4px;
    color: DarkRed;
}

.settingsbutton {
   background-color: white;
    color: black;
    border: 2px solid green;
    cursor: pointer;
}

.linkbutton {
    background-color: LightGrey;
    color: black;
    border: 1px solid LightGrey;
    cursor: pointer;
}

.linkbuttonselected {
    background-color: Green;
    color: black;
    border: 1px solid DarkGrey;
    font-weight: bold;
    cursor: not-allowed;
}


.rebootButton {
    background-color: Red;
    color: black;
    border: 4px solid Black;
    font-weight: bold;
cursor: pointer;
}

#schedule-grid td {
  font-size: 12px;
  font-family: Arial, Helvetica, sans-serif;
}

.timecell {
  font-size: 14px;
  font-weight: bold;
}

.scheduleheading {
  display: block;
  width: 90%;
  margin: 0 auto;
  font-family: Arial, Helvetica, sans-serif;
  font-weight: Bold;
  font-size: 18px;
  text-align: center;
  color: Blue;
}

.statustext{
  display: block;
  width: 90%;
  margin: 0 auto;
  font-family: Arial, Helvetica, sans-serif;
  font-weight: Bold;
  font-size: 14px;
  text-align: center;
  color: Green;
}

.sliderHeading {
   font-family: Arial, Helvetica, sans-serif;
  font-weight: Bold;
  font-size: 14px;
  text-align: center;
  color: Green;
}
</style>

)=====";
