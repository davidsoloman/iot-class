
#include <ESP8266WiFi.h>

const char* ssid     = "NYCR24";
const char* password = "clubmate";

char* host = "www.timeapi.org";

void httpGet(String url, char* host) {
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // This will send the request to the server
  client.println(String("GET ") + url + " HTTP/1.1");
  client.print("Host: ");
  client.println("www.timeapi.org");
  client.println("User-Agent: curl/7.43.0");
  client.println();
  delay(800);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
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


void loop() {
  delay(5000);

  httpGet("/est/now", host);
}
