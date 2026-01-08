#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>

typedef struct {
  const char* timestamp;
  const char* meter_datetime;
  float total_m3;
  const char* status;
} DataPoint;

typedef struct {
  const char* media;
  const char* meter;
  const char* deviceId;
  const char* unit;
  DataPoint data;
} DeviceReading;

typedef struct {
  const char* gatewayId;
  const char* date;
  const char* deviceType;
  int interval_minutes;
  int total_readings;
  DeviceReading device;
} GatewayData;

int serialize_to_json(
  const GatewayData* input,
  char* output_buffer,
  size_t buffer_size
);

#endif
