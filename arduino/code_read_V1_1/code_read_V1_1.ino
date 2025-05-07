#include <Servo.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>

// Configuration DHT22
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Configuration NeoPixel
#define PIN 4
#define NUMPIXELS 10
#define DELAYVAL 250
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Configuration Servo
Servo monServo;
const int pinServo = 9;
const String commandPrefix = "[arduino]:";
const String infoPrefix = "[arduino]:[info]:";

void setup() {
  Serial.begin(9600);
  
  // Initialisation DHT22
  Serial.println("Test du capteur DHT22...");
  dht.begin();
  
  // Initialisation NeoPixel
  pixels.begin();
  pixels.setBrightness(75);
  
  // Initialisation Servo
  monServo.attach(pinServo);
  monServo.write(90);
  Serial.println(infoPrefix + "{status:'System ready'}");
  Serial.println(infoPrefix + "{help:'Send " + commandPrefix + "{angle:value} (0-180)'}");
}

void loop() {
  // Partie DHT22 et NeoPixel (inchangée)
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

    // Contrôle NeoPixel
    if(t < 40 && h < 50) {
      pixels.clear();
      pixels.show(); 
      delay(DELAYVAL);
      for(int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 150, 0));
      }
      pixels.show();
      delay(DELAYVAL);
    } else if(h > 50) {
      pixels.clear();
      pixels.show(); 
      delay(DELAYVAL);
      for(int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 150, 255));
      }
      pixels.show();
      delay(DELAYVAL);
    } else if(t > 35) {
      pixels.clear();
      pixels.show(); 
      delay(DELAYVAL);
      for(int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
      pixels.show();
      delay(DELAYVAL);
    }
  }

  // Partie Servo (nouvelle)
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim();
    
    if (message.startsWith(commandPrefix + "{angle:")) {
      int start = message.indexOf(':') + 1;
      int end = message.indexOf('}');
      
      if (start > 0 && end > start) {
        String angleStr = message.substring(start, end);
        int angle = angleStr.toInt();
        
        if (angle >= 0 && angle <= 180) {
          monServo.write(angle);
          Serial.println(infoPrefix + "{status:'OK', angle:" + String(angle) + "}");
        } else {
          Serial.println(infoPrefix + "{error:'Invalid angle', range:'0-180'}");
        }
      } else {
        Serial.println(infoPrefix + "{error:'Invalid format', expected:'" + commandPrefix + "{angle:value}'}");
      }
    }
  }

  delay(1000);
}
