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

struct skiResortBasicInfo {
  String name;
  String latitude;
  String longitude;
  String serverName;
};

skiResortBasicInfo vailBasicInfo = {
  "vail",
  "39.61",
  "-106.37",
  "https://api.open-meteo.com/v1/forecast?latitude=39.61&longitude=-106.37&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch",
};

skiResortBasicInfo keystoneBasicInfo = {
  "keystone",
  "39.59",
  "-105.95",
  "https://api.open-meteo.com/v1/forecast?latitude=39.59014&longitude=-105.94614&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch",
};

skiResortBasicInfo breckenridgeBasicInfo = {
  "breckenridge",
  "39.47",
  "-106.08",
  "https://api.open-meteo.com/v1/forecast?latitude=39.47&longitude=-106.08&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch",
};

skiResortBasicInfo skiCooperBasicInfo = {
  "ski cooper",
  "39.36",
  "-106.29",
  "https://api.open-meteo.com/v1/forecast?latitude=39.36&longitude=-106.29&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch",
};

skiResortBasicInfo eldoraBasicInfo = {
  "eldora",
  "39.94",
  "-105.59",
  "https://api.open-meteo.com/v1/forecast?latitude=39.94&longitude=-105.59&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch",
};

skiResortBasicInfo resortsBasicInfoArr[] = {
  vailBasicInfo,
  keystoneBasicInfo,
  breckenridgeBasicInfo,
  skiCooperBasicInfo,
  eldoraBasicInfo,
};

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
String serverName = "https://api.open-meteo.com/v1/forecast?latitude=39.61&longitude=-106.37&daily=snowfall_sum&timezone=America%2FDenver&past_days=7&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch";


String jsonBuffer;

struct skiResort {
  String name;
  String latitude;
  String longitude;
  String snowToday;
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

  Serial.println(vailBasicInfo.name);
  Serial.println(vailBasicInfo.latitude);
  Serial.println(vailBasicInfo.longitude);
  
  Serial.println(keystoneBasicInfo.name);
  Serial.println(keystoneBasicInfo.latitude);
  Serial.println(keystoneBasicInfo.longitude);

  Serial.println(resortsBasicInfoArr[3].name);




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
      // Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
      JSONVar skiResortJsonObj = myObject;

      Serial.print("JSON object = ");
      Serial.println(myObject);

      // Serial.println(myObject["latitude"]);
      // Serial.println(skiResortJsonObj);
      skiResortJsonObj["resort"] = "vail";
      // Serial.println(skiResortJsonObj);

      // Serial.println("...");

      Serial.print("resort: ");
      Serial.println(skiResortJsonObj["resort"]);
      // Serial.println("snow accum one week ago: ");
      // Serial.print("date: ");
      // Serial.println(skiResortJsonObj["daily"]["time"][0]);
      // Serial.print("amount: ");
      // Serial.print(skiResortJsonObj["daily"]["snowfall_sum"][0]);
      // Serial.println(" inches");
      
      Serial.println(">>");

      String testSkiResortName = JSON.stringify(skiResortJsonObj["resort"]);
      // Serial.println(testSkiResortName);
      
      skiResort tokyoMegaplex = {"tokyo megaplex", "123.45", "67.890", "lots of snow"};
      // Serial.println(tokyoMegaplex.name);
      skiResort vail = {
        // String name;
        JSON.stringify(skiResortJsonObj["resort"]),

        // String latitude;
        JSON.stringify(skiResortJsonObj["latitude"]),

        // String longitude;
        JSON.stringify(skiResortJsonObj["longitude"]),

        // String snowToday;
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][7]),

        // String snowAccum[14] = {};
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][0]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][1]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][2]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][3]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][4]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][5]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][6]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][7]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][8]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][9]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][10]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][11]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][12]),
        JSON.stringify(skiResortJsonObj["daily"]["snowfall_sum"][13]),

      };
      Serial.println(vail.name);
      Serial.println(vail.latitude);
      Serial.println(vail.longitude);
      Serial.print("snowToday: ");
      Serial.println(vail.snowToday);


float pastWeekSnowAccum = 0;
float nextWeekSnowAccumForecast = 0;

for (int i = -6, j = 0; i < 8; i++, j++) {

  Serial.print("Snow accumulation ");
  if (i < 0) {
    Serial.print(i * -1);
    Serial.print(" day(s) ago: ");

    // Serial.println(" ");
    // Serial.println("***");
    // Serial.print("raw snow accum: ");
    // Serial.println(vail.snowAccum[j]);
    // Serial.println(vail.snowAccum[j].toFloat());
    pastWeekSnowAccum += vail.snowAccum[j].toFloat();
    // Serial.print("pastWeekSnowAccum: ");
    // Serial.println(pastWeekSnowAccum);
  } else if (i == 0) {

    Serial.print("today: ");

    // pastWeekSnowAccum += vail.snowAccum[j].toFloat();
    // Serial.print("pastWeekSnowAccum: ");
    // Serial.println(pastWeekSnowAccum);
  } else {

    Serial.print(i);
    Serial.print(" day(s) in the future: ");

    nextWeekSnowAccumForecast += vail.snowAccum[j].toFloat();
  };

  Serial.print(vail.snowAccum[j]);
  Serial.println(" inches");

  // Serial.print("j: ");
  // Serial.println(j);
  // Serial.println(vail.snowAccum[6]);
};

Serial.println("***");
Serial.print("pastWeekSnowAccum: ");
Serial.print(pastWeekSnowAccum);
Serial.println(" inches");

Serial.print("nextWeekSnowAccumForecast: ");
Serial.print(nextWeekSnowAccumForecast);
Serial.println(" inches");
Serial.println("***");

// Serial.println("Last week");
// Serial.print("snowAccum[0]: ");
// Serial.print(vail.snowAccum[0]);
// Serial.println(" inches");

// Serial.print("snowAccum[1]: ");
// Serial.print(vail.snowAccum[1]);
// Serial.println(" inches");

// Serial.print("snowAccum[2]: ");
// Serial.print(vail.snowAccum[2]);
// Serial.println(" inches");

// Serial.print("snowAccum[3]: ");
// Serial.print(vail.snowAccum[3]);
// Serial.println(" inches");

// Serial.print("snowAccum[4]: ");
// Serial.print(vail.snowAccum[4]);
// Serial.println(" inches");

// Serial.print("snowAccum[5]: ");
// Serial.print(vail.snowAccum[5]);
// Serial.println(" inches");

// Serial.print("snowAccum[6]: ");
// Serial.print(vail.snowAccum[6]);
// Serial.println(" inches");

// Serial.println("Today");

// Serial.print("snowAccum[7]: ");
// Serial.print(vail.snowAccum[7]);
// Serial.println(" inches");

// Serial.println("Next week");

// Serial.print("snowAccum[8]: ");
// Serial.print(vail.snowAccum[8]);
// Serial.println(" inches");

// Serial.print("snowAccum[9]: ");
// Serial.print(vail.snowAccum[9]);
// Serial.println(" inches");

// Serial.print("snowAccum[10]: ");
// Serial.print(vail.snowAccum[10]);
// Serial.println(" inches");

// Serial.print("snowAccum[11]: ");
// Serial.print(vail.snowAccum[11]);
// Serial.println(" inches");

// Serial.print("snowAccum[12]: ");
// Serial.print(vail.snowAccum[12]);
// Serial.println(" inches");

// Serial.print("snowAccum[13]: ");
// Serial.print(vail.snowAccum[13]);
// Serial.println(" inches");



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
