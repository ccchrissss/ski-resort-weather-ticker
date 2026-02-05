/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-https-request
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

// vail
// latitude = 39.61425;
// longitude = -106.365917;

// keystone
// latitude = 39.59014;
// longitude = -105.94614;
// String serverName = "https://api.open-meteo.com/v1/forecast?latitude=39.59014&longitude=-105.94614&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch";

// breckenridge
// latitude = 39.47356;
// longitude = -106.07825;

// ski cooper
// latitude = 39.35553;
// longitude = -106.28522;

// eldora
// latitude = 39.93842;
// longitude = -105.59283;

const char WIFI_SSID[] = "SETUP-D9CC";
const char WIFI_PASSWORD[] = "aisle5961corral";

// const char WIFI_SSID[] = "SpectrumSetup-512A";
// const char WIFI_PASSWORD[] = "fairsignal60";

// const char WIFI_SSID[] = "SETUP-D025-2.4ghz";
// const char WIFI_PASSWORD[] = "charge6626drain";

// String HOST_NAME   = "https://YOUR_DOMAIN.com"; // CHANGE IT
// String PATH_NAME   = "/products/arduino";      // CHANGE IT
// //String PATH_NAME   = "/products/arduino.php";      // CHANGE IT
// String queryString = "temperature=26&humidity=70";

// 
String SCHEME_AND_DOMAIN_NAME = "https://api.open-meteo.com";
String PATH_NAME = "/v1/forecast";
String queryString = "?latitude=39.61425&longitude=-106.365917";
String PARAMETERS = "&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch";
String serverName = "https://api.open-meteo.com/v1/forecast?latitude=39.61425&longitude=-106.365917&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch";

String jsonBuffer;

struct skiResort {
  String name;
  String latitude;
  String longitude;
  String snowDay0;
  String snowAccum[14] = {};
};

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  HTTPClient http;

  http.begin(serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      // Serial.println(payload);
      // Serial.printf("httpCode: ");
      // Serial.println(httpCode);

      jsonBuffer = payload;
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
      JSONVar skiResortJsonObj = myObject;

      Serial.print("JSON object = ");
      Serial.println(myObject);

      Serial.println(myObject["latitude"]);
      Serial.println(skiResortJsonObj);
      skiResortJsonObj["resort"] = "vail";
      Serial.println(skiResortJsonObj);
      Serial.println("...");
      Serial.print("resort: ");
      Serial.println(skiResortJsonObj["resort"]);
      Serial.println("snow accum one week ago: ");
      Serial.print("date: ");
      Serial.println(skiResortJsonObj["daily"]["time"][0]);
      Serial.print("amount: ");
      Serial.print(skiResortJsonObj["daily"]["snowfall_sum"][0]);
      Serial.println(" inches");
      
      Serial.println(">>");

      String testSkiResortName = JSON.stringify(skiResortJsonObj["resort"]);
      // Serial.println(testSkiResortName);
      
      skiResort tokyoMegaplex = {"tokyo megaplex", "123.45", "67.890", "lots of snow"};
      // Serial.println(tokyoMegaplex.name);
      skiResort vail = {
        JSON.stringify(skiResortJsonObj["resort"]),
        JSON.stringify(skiResortJsonObj["latitude"]),
        JSON.stringify(skiResortJsonObj["longitude"]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][0]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][0]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][1]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][13])
      };
      Serial.println(vail.name);
      Serial.println(vail.latitude);
      Serial.println(vail.longitude);
      Serial.println(vail.snowDay0);
      Serial.println(vail.snowAccum[0]);
      Serial.println(vail.snowAccum[1]);
      Serial.println(vail.snowAccum[2]);
      Serial.println(vail.snowAccum[13]);
      // Serial.println(vail.l)

      // struct skiResort {
      //   String name;
      //   String latitude;
      //   String longitude;
      //   String snowAccumulation;
      // };


    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() {
}
