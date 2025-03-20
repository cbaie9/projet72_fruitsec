#include <DHT.h>

#define DHTPIN 3      // Vérifie la bonne broche !
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    Serial.println("Test du capteur DHT22...");
    dht.begin();
}

void loop() {
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
    }
    delay(2000);
}
