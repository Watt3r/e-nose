// Setup Gas sensor
#include "Adafruit_SGP40.h"
Adafruit_SGP40 sgp;

// Humidity and Temp sensor
#include "DHT.h"
#define DHTPIN 2               
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float h,t;

// OLED ASCII Display
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#define I2C_ADDRESS 0x3C // For some reason my OLED is 0x3C, not 0x3D like others. If the OLED doesn't work, try 0x3D
SSD1306AsciiWire oled;
// Display width of oled, used to right align text
const int oledDisplayWidth = 128;

// VOC qualitative Scale
const char scale[6][6] = {"Great", "Good ", "Meh  ", "Bad  ", "Awful", "Foul "};

// VOC last 5 point average
float rollingNumerators[5] = {0,0,0,0,0};
int index = 0;


void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  // Setup sensors
  dht.begin();
  sgp.begin();
  
  // Setup display
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.clear();
  oled.setFont(Adafruit5x7);

  t = dht.readTemperature();
  h = dht.readHumidity();
  Serial.print(t);
  // Show splash screen on startup
  // oled.set2X();
  oled.println("Initializing E-Nose");

  // Wait until sgp is reading actual data
  // sgp40 reads 0 until properly setup
  for (int i = 0;!sgp.measureVocIndex(t, h);i++) {
    Serial.print(".");
    t = dht.readTemperature();
    h = dht.readHumidity();

    // Display temperature and humidity while initializing
    // because why not?
    displayTempHumid(t,h,6);

    // Takes an avg of 45 seconds to startup, countdown progress bar
    oled.setCursor(0,2);
    oled.print(i); oled.println("/45");
    for (int j = 0; j < ((oledDisplayWidth / 7)*i)/45; j++) {
      oled.print("=");
    }
    
    // Wait 1 second before checking sensor again
    delay(1000);
  }
  
  // Clear progress bar and other initialization text
  oled.clear();
}

void loop() {
  int32_t voc_index;
  
  t = dht.readTemperature();
  h = dht.readHumidity();

  voc_index = sgp.measureVocIndex(t, h);

  oled.setCursor(0,0);
  oled.print("Current: ");
  // clear previous voc index and replace
  oled.clearToEOL();
  oled.println(voc_index);

  char qualitative[8];
  toQualitative(voc_index, qualitative); // converts quantitative voc to more qualitative
  
  // Since all qualitative strings are same length (padded with spaces) no need to clear
  // This reduces flash on every refresh
  // oled.clearToEOL();
  oled.println(qualitative);
  
  
  // Calculate rolling average 
  rollingNumerators[index % 5] = voc_index;
  index++;
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += rollingNumerators[i];
  }
  
  oled.setCursor(0,3);
  oled.println("Trend:");
  oled.clearToEOL();
  oled.print(abs(sum/5 - voc_index) > 10 ? "significantly " : ""); oled.print(sum/5 >= voc_index ? "better" : "worse ");

  // Display temp and humidity, we have the space, so why not use it?
  displayTempHumid(t,h,6);
  
  delay(1000);
}

void toQualitative(int voc, char* outStr) {
  // Convert 0-500 VOC range to 0-5 qualitative range
  // NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
  int newVal = ((voc * 5) / 500);
  Serial.println(newVal);
  Serial.println(scale[newVal]);
  strncpy(outStr, scale[newVal], sizeof(scale[newVal]));
  Serial.println(outStr);
}

void displayTempHumid(float t, float h, int row) {
  // Show Temp and Humidity
  oled.setCursor(0,row);
  oled.print("Temp "); oled.print(t); oled.print("C");
  // 49 = 7 (font char width) * 7 chars
  oled.setCursor(oledDisplayWidth-49,row);
  oled.print("H "); oled.print(h); oled.print("%");
}
