#include <RestClient.h>
#include <ESP8266WiFi.h>
#include <SimpleDHT.h>


const char* ssid     = "dlinkFD49";
const char* password = "1234567890";

const char* host = "192.168.2.9";

RestClient client = RestClient(host);

int pinDHT11 = 2;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(115200);
  delay(10);
  client.setContentType("application/json");
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String response;
char buffer[50];
void loop(){
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }
  
  response = "";
  sprintf (buffer, "{\"temperature\": %d, \"humidity\": %d}",(int)temperature, (int)humidity);
  int statusCode = client.post("/api/sensors/", buffer , &response);
  if(statusCode == 201){;
    Serial.println(response);
  }
  delay(2000);
}

