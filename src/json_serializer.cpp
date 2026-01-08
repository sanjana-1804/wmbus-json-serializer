#include "json_serializer.h"
#include <Arduino.h>
#include <stdio.h>

int serialize_to_json(
  const GatewayData* g,
  char* out,
  size_t size
) {
  if (!g || !out || size == 0) return -1;

  char total_m3_str[16];
  dtostrf(g->device.data.total_m3, 0, 3, total_m3_str);

  int len = snprintf(out, size,
    "[{"
    "\"gatewayId\":\"%s\","
    "\"date\":\"%s\","
    "\"deviceType\":\"%s\","
    "\"interval_minutes\":%d,"
    "\"total_readings\":%d,"
    "\"values\":{"
      "\"device_count\":1,"
      "\"readings\":["
        "{"
          "\"media\":\"%s\","
          "\"meter\":\"%s\","
          "\"deviceId\":\"%s\","
          "\"unit\":\"%s\","
          "\"data\":["
            "{"
              "\"timestamp\":\"%s\","
              "\"meter_datetime\":\"%s\","
              "\"total_m3\":%s,"
              "\"status\":\"%s\""
            "}"
          "]"
        "}"
      "]"
    "}"
    "}]",
    g->gatewayId,
    g->date,
    g->deviceType,
    g->interval_minutes,
    g->total_readings,
    g->device.media,
    g->device.meter,
    g->device.deviceId,
    g->device.unit,
    g->device.data.timestamp,
    g->device.data.meter_datetime,
    total_m3_str,
    g->device.data.status
  );

  if (len >= size) return -2;
  return len;
}
