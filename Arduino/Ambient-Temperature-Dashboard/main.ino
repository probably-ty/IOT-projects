//Libraries
#include "DHT.h"
#include "WiFiS3.h"
#include "webpage.h"

//WIFI SETUP
#define SECRET_SSID "Click for Virus"
#define SECRET_PASS "D@LanQiul3rs"

// #define SECRET_SSID "gist-7614"
// #define SECRET_PASS "Gist20237614"


int status = WL_IDLE_STATUS;
WiFiServer server(80);

//Global Variables
#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;
float fahrenheit;

int BlueLight = 11;
int GreenLight = 12;
int RedLight = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(BlueLight, OUTPUT);
  pinMode(GreenLight, OUTPUT);
  pinMode(RedLight, OUTPUT);

  Serial.begin(9600);
  dht.begin();

  while(status != WL_CONNECTED){
    Serial.println("Connecting to WiFi....");
    status = WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(5000);
  }

  Serial.println("Connected!");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  fahrenheit = temperature * 9 / 5 + 32;

  if (isnan(humidity) || isnan(temperature)){
    Serial.println("Error reading data!");
    return;
  }

  
  WiFiClient client = server.available();

  if (client){

    String request = client.readStringUntil('\r');

    Serial.println(request);

    //Sensor request
    if(request.indexOf("GET /sensor") >= 0){

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Connection: close");
      client.println();


      //Json formatting and sending of the data
      client.print("{");

      client.print("\"temperature\":");
      client.print(temperature);

      client.print(",");

      client.print("\"humidity\":");
      client.print(humidity);

      client.print(",");

      client.print("\"fahrenheit\":");
      client.print(fahrenheit);

      client.print("}");
    }

    //normal webpage request
    else{

      String page = webpage;

      page.replace("%TemperatureC%", String(temperature));
      page.replace("%Humidity%", String(humidity));
      page.replace("%TemperatureF%", String(temperature));

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();

      client.println(page);


    }

    client.stop();


    // Serial.println("Client connected");

    // while (client.connected()){

    //   if (client.available()){

    //     //Clear browser request
    //     client.readString();

    //     //Copy webpage
    //     String page = webpage; 

    //     //Replace information on page with real readings
    //     page.replace("%TemperatureC%", String(temperature));
    //     page.replace("%Humidity%", String(humidity));

    //     //Send webpage

    //     client.println("HTTP/1.1 200 OK");
    //     client.println("Content-Type: text/html");
    //     client.println("Connection: close");
    //     client.println();

    //     client.println(page);

    //     break;

    //   }
    // }
    Serial.println("Client Disconnected");

  }


  if(temperature <=23){
    digitalWrite(BlueLight, HIGH);
    digitalWrite(GreenLight, LOW);
    digitalWrite(RedLight, LOW);
  }
  else if (temperature > 23 && temperature < 30){
    digitalWrite(BlueLight, LOW);
    digitalWrite(RedLight, LOW);
    digitalWrite(GreenLight, HIGH);
  }
  else{
    digitalWrite(BlueLight, LOW);
    digitalWrite(GreenLight, LOW);
    digitalWrite(RedLight, HIGH);
  }

  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.println();
  delay(2000);

  
}
