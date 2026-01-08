#include <Arduino.h>
#include "json_serializer.h"

char json_buffer[512];

void setup() {
  Serial.begin(9600);

  GatewayData gateway = {
    .gatewayId = "gateway_1234",
    .date = "1970-01-01",
    .deviceType = "stromleser",
    .interval_minutes = 15,
    .total_readings = 1,
    .device = {
      .media = "water",
      .meter = "waterstarm",
      .deviceId = "stromleser_50898527",
      .unit = "m3",
      .data = {
        .timestamp = "1970-01-01 00:00",
        .meter_datetime = "1970-01-01 00:00",
        .total_m3 = 107.752,
        .status = "OK"
      }
    }
  };

  serialize_to_json(&gateway, json_buffer, sizeof(json_buffer));

  Serial.println("JSON Output:");
  Serial.println(json_buffer);
}

void loop() {}
