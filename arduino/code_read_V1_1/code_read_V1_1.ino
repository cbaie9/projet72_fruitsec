#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#define DHTPIN 2      // Vérifie la bonne broche !
#define DHTTYPE DHT22
#define PIN        4
#define NUMPIXELS 10
#define DELAYVAL 250
DHT dht(DHTPIN, DHTTYPE);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(9600);
    Serial.println("Test du capteur DHT22...");
    dht.begin();
    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.setBrightness(75);
}

void loop() {
  // capteur DHT32
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
        Serial.println("Échec de lecture du capteur !");
    } else {
        Serial.print("{temp: ");
        Serial.print(t);
        Serial.print("},");

        Serial.print("{humid: ");
        Serial.print(h);
        Serial.println("}");
    
    //led 
     // Si des données sont disponibles
    if(t<40 && h<50){
        // début led normal
    pixels.clear();
    pixels.show(); 
    delay(DELAYVAL);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
      }
      pixels.show();
    delay(DELAYVAL);
    /// fin led normal
    } else if(h>50){
      // début led normal
    pixels.clear();
    pixels.show(); 
    delay(DELAYVAL);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 150, 255));
    }
    pixels.show();
    delay(DELAYVAL);
    } else if(t>35){
      // début led normal
    pixels.clear();
    pixels.show(); 
    delay(DELAYVAL);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(255, 0,0));
    }
    pixels.show();
    delay(DELAYVAL);
    } 
 delay(1000); 
    }
}
