#include <ESP8266WiFi.h>
WiFiClient client;

const char* SSID = "SSID"; //SSID NETWORK
const char* PASSWORD = "PASSWORD"; // PASSWORD NETWORK

// THINGSPEAK
String API_KEY = "API_KEY_WRITE";
const char* SERVER = "api.thingspeak.com";

String data; // VARIÁVEL PARA ARMEZENAR OS DADOS A SEREM ENVIADOS
void setup() {

  Serial.begin(9600);

  WiFi.begin(SSID, PASSWORD);

  // CONECTANDO NA REDE...
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  // INFORMAÇÕES DE REDE
  Serial.println("");
  Serial.print("Conectado na rede ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  data = random(100); // GERA NÚMEROS RANDÓMICOS

  // TENTA SE CONECTAR AO THINGSPEAK
  if (client.connect(SERVER, 80)) {

    // MONTA O VALOR A SER ENVIADO AO THINGSPEAK
    String PACOTE = "field1=" + data;

    //
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + API_KEY + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(PACOTE.length());
    client.print("\n\n");
    client.print(PACOTE);

    // DEBUG SERIAL
    Serial.print("Value: ");
    Serial.println(PACOTE);

  }
  client.stop();
  delay(20000);
}
