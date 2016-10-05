#include <Adafruit_NeoPixel.h>
#include "Utility.h"
#include "ALA.h"
#include "ALALed.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "xxxxx";
const char* password = "xxxx";

ESP8266WebServer server(80);

#define PIN      2
//#define N_LEDS 6
#define N_LEDS 106
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

bool keepAnimation = false;
int currentAnimation =0;
AlaColor gcol1 = AlaColor(255, 255, 255);
AlaColor gcol2 = AlaColor(0,0,0);  
int gdelay = 50;
int rainbowLoops = 5;
int whiteLoops = 5;
AlaPalette gpallete = alaPalRgb;

void handleRoot() {
  String message = "";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "<br>";
  }
  String header ="HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin:*\r\nAccess-Control-Allow- Methods:GET, PUT \r\n";
  header += "Access-Control-Allow-Headers *AUTHORISED*\r\nContent-type: text/html\r\nServer: ESP8266-1\r\n\n";
  
  int cmd = server.arg("cmd").toInt();
  if(server.arg("delay") != NULL) {
    gdelay = server.arg("delay").toInt();
  }
  if(server.arg("c1") != NULL) {
   // getRGB("0"+ server.arg("c1"), gcol1);
   gcol1 = AlaColor(hexStrTolong("0"+ server.arg("c1"))); 
  }
  if(server.arg("c2") != NULL) {
    gcol2 = AlaColor(hexStrTolong("0"+ server.arg("c2"))); 
  }
  if(server.arg("rl") != NULL) {
    rainbowLoops = server.arg("rl").toInt();
  }
  if(server.arg("wl") != NULL) {
    whiteLoops = server.arg("wl").toInt();
  }
  if(server.arg("p") != NULL) {
    int pnum = server.arg("p").toInt();
    switch(pnum) {
      case 1: gpallete = alaPalRgb; break;
      case 2: gpallete = alaPalRainbow; break;
      case 3: gpallete = alaPalRainbowStripe; break;
      case 4: gpallete = alaPalParty; break;
      case 5: gpallete = alaPalHeat; break;
      case 6: gpallete = alaPalFire; break;
      default: gpallete = alaPalRgb;
      
    }
  }

  server.sendContent(header+message+"<br>");  
  handleStates(cmd);
  
}

void handleStates(int cmd) {
  currentAnimation =cmd;
  if(cmd ==0) {
    keepAnimation = false;
    allOn(strip, 0);
  }
  if(cmd ==1) {
     keepAnimation = false;
    allOn(strip, strip.Color(gcol1.r, gcol1.g, gcol1.b));
  }
  if(cmd >= 2) {
    keepAnimation = true;
  }

}

long long hexStrTolong(String c) {
  return strtoul( &c[1], NULL, 16);
}

void handleNotFound(){
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
}

void setup(void){
  strip.begin();

/*for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i  ,  strip.Color(250, 245, 80));
          strip.show();

  }*/

/*strip.setPixelColor(0  ,  strip.Color(255, 0, 0));
strip.setPixelColor(1  ,  strip.Color(0, 255, 0));
strip.setPixelColor(2  ,  strip.Color(0, 0, 255));
strip.show();  */
  
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }


/*  Serial.begin(115200);
  Serial.println(WiFi.localIP());
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }*/

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  
  /*delay(100);
  for(int i=0; i<strip.numPixels(); i++) {
     if((i % 2) == 0) {
        strip.setPixelColor(i  ,  strip.Color(250, 246, 196));
     }
  }
  strip.show();*/
}
void loop(void){
  server.handleClient();

  if(keepAnimation) {
    if(currentAnimation ==2) { chase(strip, strip.Color(gcol1.r, gcol1.g, gcol1.b), strip.Color(gcol2.r, gcol2.g, gcol2.b), gdelay) ;}
    if(currentAnimation ==3) {blink(strip, strip.Color(gcol1.r, gcol1.g, gcol1.b), strip.Color(gcol2.r, gcol2.g, gcol2.b), gdelay);}
    if(currentAnimation ==4) {blinkalt(strip, strip.Color(gcol1.r, gcol1.g, gcol1.b), strip.Color(gcol2.r, gcol2.g, gcol2.b), gdelay);}
    if(currentAnimation ==5) {
      int r0 =  random(0, 255);
      int g0 =  random(0, 255);
      int b0 =  random(0, 255);
     chase(strip, strip.Color(r0, g0, b0), 0, gdelay);
    }
    if(currentAnimation ==6) {rainbowFade2White(strip, 3, 2, 1);}//low low delay
    if(currentAnimation ==7) {whiteOverRainbow(strip, gdelay, rainbowLoops, whiteLoops);}
    if(currentAnimation ==8) {rainbow(strip, gdelay);}
    if(currentAnimation ==9) {theaterChaseRainbow(strip, gdelay);}//low low delay // DONT USE MAY BE 
    if(currentAnimation ==10) {theaterChase(strip, strip.Color(gcol1.r, gcol1.g, gcol1.b), gdelay);}//low low delay
    if(currentAnimation ==11) {sparkle(strip, gpallete, gdelay);} // HIGH delays for better effect
    if(currentAnimation ==12) {sparkle2(strip, gpallete, gdelay);}
    if(currentAnimation ==13) {strobo(strip, gcol1, gdelay);}
    if(currentAnimation ==14) {pixelShiftRight(strip, gpallete,gdelay);} // HIGH delays for better effect > 1000 
    if(currentAnimation ==15) {pixelShiftLeft(strip, gpallete,gdelay);}// HIGH delays for better effect > 1000
    if(currentAnimation ==16) {pixelShiftRight(strip, gpallete,gdelay);pixelShiftLeft(strip, gpallete,gdelay);}
    if(currentAnimation ==17) {pixelBounce(strip, gpallete,gdelay);}
    if(currentAnimation ==18) {pixelBounce(strip, gpallete,gdelay);} // DISCARD
    if(currentAnimation ==19) {pixelSmoothShiftRight(strip, gpallete,gdelay);}
    if(currentAnimation ==20) {pixelSmoothShiftLeft(strip, gpallete,gdelay);}
    if(currentAnimation ==21) {pixelSmoothShiftLeft(strip, gpallete,gdelay);pixelSmoothShiftRight(strip, gpallete,gdelay);}
    if(currentAnimation ==22) {comet(strip, gpallete,gdelay); }
    if(currentAnimation ==23) {cometCol(strip, gpallete,gdelay);}
    if(currentAnimation ==24) {pixelSmoothBounce(strip, gpallete,gdelay);}
    if(currentAnimation ==25) {larsonScanner(strip, gpallete,gdelay);}
    if(currentAnimation ==26) {larsonScanner2(strip, gpallete,gdelay);}
    if(currentAnimation ==27) {fadeIn(strip, gcol1,gdelay);}
    if(currentAnimation ==28) {fadeOut(strip, gcol1,gdelay);}
    if(currentAnimation ==29) {fadeInOut(strip, gcol1,gdelay);}
    if(currentAnimation ==30) {glow(strip, gcol1,gdelay);}
    if(currentAnimation ==31) { fadeColors(strip, gpallete,gdelay);}
    if(currentAnimation ==32) { pixelsFadeColors(strip, gpallete,gdelay);}
    if(currentAnimation ==33) { fadeColorsLoop(strip, gpallete,gdelay);}
    if(currentAnimation ==34) { cycleColors(strip, gpallete,gdelay);}
    if(currentAnimation ==35) { movingBars(strip, gpallete,gdelay);}
    if(currentAnimation ==36) { movingGradient(strip, gpallete,gdelay);}
    if(currentAnimation ==37) { fire(strip, gpallete);}
    if(currentAnimation ==38) {//low low delay
      int r0 =  random(0, 255);
      int g0 =  random(0, 255);
      int b0 =  random(0, 255);
      int r1 =  random(0, 255);
      int g1 =  random(0, 255);
      int b1 =  random(0, 255);
     chase(strip, strip.Color(r0, g0, b0), strip.Color(r1, g1, b1), gdelay);
    }
    if(currentAnimation ==39) {//low low delay
       chase2(strip, gdelay);
    }
    if(currentAnimation ==40) {fillPixel(strip, gcol1,gdelay);}
    if(currentAnimation ==41) {fillPixelPalette(strip, gcol1,gpallete,gdelay);}
    if(currentAnimation ==42) {fillPixelRandom(strip, gdelay);}
  }
}

void sendInfo() {
  String info = "{\"name\":\"amit\",\"ip\":\"amit\",\"pixels\":12}";  
}

