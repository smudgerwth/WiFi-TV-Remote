#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4 (D2)
ESP8266WebServer server(80);
#define C_ms  500
const char* ssid = "SSID";
const char* password = "password";


const int led = LED_BUILTIN;
const int led1 = 2;

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML><html style="width: 100s%;height:100%">
<title>Wi-Fi TV Remote</title>
<meta http-equiv="Content-Type" content="text/html, charset=utf-8, width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
<style>
.button {
  display: inline-block;
  position: relative;
  padding: 0 15px;
  font-size: 400%;
  width: 70%;
  color: white;
  text-decoration: none;
  text-shadow: 0 -1px rgba(0, 0, 0, 0.3);
  border: 2% solid;
  border-radius: 30px;
  outline: 0;
  -webkit-box-shadow: 0 2px 1px rgba(0, 0, 0, 0.25);
  box-shadow: 0 2px 1px rgba(0, 0, 0, 0.25);
}
.button:before, .button:after {
  content: '';
  position: absolute;
}
.button:before {
  top: -5px;
  bottom: -5px;
  left: -5px;
  right: -5px;
  z-index: -1;
  border-radius: 9px;
}
.button:after {
  top: 0;
  bottom: 0;
  right: 0;
  left: 0;
  border: 2px solid rgba(255, 255, 255, 0.1);
  border-bottom: 0;
  border-radius: 7px;
}
.button.alt {
  -webkit-box-shadow: 0 1px 3px rgba(0, 0, 0, 0.25);
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.25);
}
.button.alt:before {
  display: none;
}
.button.gray {
  background: #999999;
  border-color: #787878 #757575 #666666;
  background-image: -webkit-linear-gradient(top, #adadad 0%, #a6a6a6 50%, #999999 50%, #8e7b7c 100%);
  background-image: -moz-linear-gradient(top, #adadad 0%, #a6a6a6 50%, #999999 50%, #8e7b7c 100%);
  background-image: -o-linear-gradient(top, #adadad 0%, #a6a6a6 50%, #999999 50%, #8e7b7c 100%);
  background-image: linear-gradient(to bottom, #adadad 0%, #a6a6a6 50%, #999999 50%, #8e7b7c 100%);
}
.button.gray:before {
  background: #b6afaf;
  background-image: -webkit-linear-gradient(top, #8b8484, #c2b7b7);
  background-image: -moz-linear-gradient(top, #8b8484, #c2b7b7);
  background-image: -o-linear-gradient(top, #8b8484, #c2b7b7);
  background-image: linear-gradient(to bottom, #8b8484, #c2b7b7);
}
.button.gray:active {
  background: #a6a6a6;
  background-image: -webkit-linear-gradient(top, #8a7577 0%, #a1a1a1 60%, #a6a6a6 100%);
  background-image: -moz-linear-gradient(top, #8a7577 0%, #a1a1a1 60%, #a6a6a6 100%);
  background-image: -o-linear-gradient(top, #8a7577 0%, #a1a1a1 60%, #a6a6a6 100%);
  background-image: linear-gradient(to bottom, #8a7577 0%, #a1a1a1 60%, #a6a6a6 100%);
}
.button.gray:active:after {
  border-color: #a6a6a6;
}
</style>
<body style="width: 100%;height:100%;">
<table style="margin-left: auto; margin-right: auto;width: 100%; height: 100%;">
<tbody>
<tr>
<td style="text-align: center;"><a href="\b1" class="button gray alt"></a></td>
<td style="text-align: center;"><a href="\b2" class="button gray alt">&#x975C;&#x97F3</a></td>
</tr>
<tr>
<td style="text-align: center;"><a href="\b3" class="button gray alt">&#x7FE1;&#x7FE0;&#x53F0</a></td>
<td style="text-align: center;"><a href="\b4" class="button gray alt">J2&#x53F0</a></td>
</tr>
<tr>
<td style="text-align: center;"><a href="\b5" class="button gray alt">&#x65B0;&#x805E;&#x53F0</a></td>
<td style="text-align: center;"><a href="\b6" class="button gray alt">&#x660E;&#x73E0;&#x53F0</a></td>
</tr>
<tr>
<td style="text-align: center;"><a href="\b7" class="button gray alt">&#x8CA1;&#x7D93;&#x53F0</a></td>
<td style="text-align: center;"><a href="\b8" class="button gray alt">&#x6E2F;&#x53F0;31</a></td>
</tr>
<tr>
<td style="text-align: center;"><a href="\b9" class="button gray alt">&#x6E2F;&#x53F0;32</a></td>
<td style="text-align: center;"><a href="\b10" class="button gray alt">&#x6E2F;&#x53F0;33</a></td>
</tr>
<tr>
<td style="text-align: center;"><a href="\b11" class="button gray alt">76&#x53F0</a></td>
<td style="text-align: center;"><a href="\b12" class="button gray alt">77&#x53F0</a></td>
</tr>
<tr>
<td style="text-align: center;"><a href="\b13" class="button gray alt">96&#x53F0</a></td>
<td style="text-align: center;"><a href="\b14" class="button gray alt">99&#x53F0</a></td>
</tr>
<tr>
<td style="text-align: center;"><a href="\b15" class="button gray alt">&#x97F3;&#x91CF;-</a></td>
<td style="text-align: center;"><a href="\b16" class="button gray alt">&#x97F3;&#x91CF;+</a></td>
</tr>
<tr>
<td style="text-align: center;"><a href="\b17" class="button gray alt">&#x983B;&#x9053;-</a></td>
<td style="text-align: center;"><a href="\b18" class="button gray alt">&#x983B;&#x9053;+</a></td>
</tr>
</tbody>
</table>
</body>
</html>
)=====";
uint64_t btn_vol_plus = 0xFFD827;
uint64_t btn_vol_minus = 0xFF5AA5;
uint64_t btn_ch_plus = 0xFF609F;
uint64_t btn_ch_minus = 0xFF6897;
uint64_t btn_ok = 0xFF58A7;
uint64_t btn_1 = 0xFF4AB5;
uint64_t btn_2 = 0xFF0AF5;
uint64_t btn_3 = 0xFF08F7;
uint64_t btn_4 = 0xFF6A95;
uint64_t btn_5 = 0xFF2AD5;
uint64_t btn_6 = 0xFF28D7;
uint64_t btn_7 = 0xFF728D;
uint64_t btn_8 = 0xFF32CD;
uint64_t btn_9 = 0xFF30CF;
uint64_t btn_0 = 0xFFF00F;
uint64_t btn_mute = 0xFF9867;
uint64_t btn_stby = 0xFF9A65;
void leds_on() {
  digitalWrite(led, 0);
  digitalWrite(led1, 0);
}
void leds_off() {
  digitalWrite(led, 1);
  digitalWrite(led1, 1);
}
void b1() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b1");
//  irsend.sendNEC(btn_stby, 32);
  delay(C_ms);
  leds_off();
}
void b2() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b2");
  irsend.sendNEC(btn_mute, 32);
  delay(C_ms);
  leds_off();
}
void b3() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b3");
  irsend.sendNEC(btn_8, 32);
  delay(C_ms);
  irsend.sendNEC(btn_1, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b4() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b4");
  irsend.sendNEC(btn_8, 32);
  delay(C_ms);
  irsend.sendNEC(btn_2, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b5() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b5");
  irsend.sendNEC(btn_8, 32);
  delay(C_ms);
  irsend.sendNEC(btn_3, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b6() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b6");
  irsend.sendNEC(btn_8, 32);
  delay(C_ms);
  irsend.sendNEC(btn_4, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b7() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b7");
  irsend.sendNEC(btn_8, 32);
  delay(C_ms);
  irsend.sendNEC(btn_5, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b8() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b8");
  irsend.sendNEC(btn_3, 32);
  delay(C_ms);
  irsend.sendNEC(btn_1, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b9() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b9");
  irsend.sendNEC(btn_3, 32);
  delay(C_ms);
  irsend.sendNEC(btn_2, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b10() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b10");
  irsend.sendNEC(btn_3, 32);
  delay(C_ms);
  irsend.sendNEC(btn_3, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b11() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b11");
  irsend.sendNEC(btn_7, 32);
  delay(C_ms);
  irsend.sendNEC(btn_6, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b12() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b12");
  irsend.sendNEC(btn_7, 32);
  delay(C_ms);
  irsend.sendNEC(btn_7, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b13() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b13");
  irsend.sendNEC(btn_9, 32);
  delay(C_ms);
  irsend.sendNEC(btn_6, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b14() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b14");
  irsend.sendNEC(btn_9, 32);
  delay(C_ms);
  irsend.sendNEC(btn_9, 32);
  delay(C_ms);
  irsend.sendNEC(btn_ok, 32);
  delay(C_ms);
  leds_off();
}
void b15() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b15");
  irsend.sendNEC(btn_vol_minus, 32);
  delay(C_ms);
  irsend.sendNEC(btn_vol_minus, 32);
  delay(C_ms);
  leds_off();
}
void b16() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b16");
  irsend.sendNEC(btn_vol_plus, 32);
  delay(C_ms);
  irsend.sendNEC(btn_vol_plus, 32);
  delay(C_ms);
  leds_off();
}
void b17() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b17");
  irsend.sendNEC(btn_ch_minus, 32);
  delay(C_ms);
  leds_off();
}
void b18() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  Serial.println("b18");
  irsend.sendNEC(btn_ch_plus, 32);
  delay(C_ms);
  leds_off();
}
void handleRoot() {
  leds_on();
  server.send(200, "text/html", MAIN_page);
  leds_off();
}

void handleNotFound(){
  leds_on();
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  leds_off();
}

void setup(void){
  irsend.begin();
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  leds_off();
  Serial.begin(115200);
  WiFi.config(IPAddress(192,168,1,77),IPAddress(192,168,1,1),IPAddress(255,255,255,0),IPAddress(192,168,1,1));

  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (MDNS.begin("wifi-tv-remote")) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);
  server.on("/b1", b1);
  server.on("/b2", b2);
  server.on("/b3", b3);
  server.on("/b4", b4);
  server.on("/b5", b5);
  server.on("/b6", b6);
  server.on("/b7", b7);
  server.on("/b8", b8);
  server.on("/b9", b9);
  server.on("/b10", b10);
  server.on("/b11", b11);
  server.on("/b12", b12);
  server.on("/b13", b13);
  server.on("/b14", b14);
  server.on("/b15", b15);
  server.on("/b16", b16);
  server.on("/b17", b17);
  server.on("/b18", b18);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
