Embedded JSON Serialization Library for w-M-Bus Firmware (Arduino)

Project Overview

This project implements an embedded-friendly JSON serialization library that converts structured smart-meter measurement data into a predefined JSON format.

The library is designed for gateway-level firmware where meter readings are collected, stored in internal data structures, and later forwarded to backend systems. The focus of this implementation is on clean architecture, deterministic behavior, and controlled memory usage, which are essential for embedded systems.
Out-of-scope components such as w-M-Bus radio communication, OMS decoding, encryption, or real meter interaction are intentionally excluded.

Chosen Platform and Programming Language

Platform: Arduino (AVR)  
Programming Language: C / C++

Justification

Arduino represents a resource-constrained embedded environment and encourages the use of
static memory and simple runtime models. It is suitable for demonstrating firmware-level
serialization logic and was explicitly allowed as an alternative platform in the assignment.

The implementation was validated using the Wokwi Arduino Simulator, which provides a
virtual Arduino board and serial monitor without requiring physical hardware.

Build and Run Instructions

Option 1: Arduino IDE (with or without hardware)

1. Install Arduino IDE
2. Open the example file:
examples/arduino_demo.ino
3. Select the board:
Tools → Board → Arduino Uno
4. Upload the sketch
5. Open the Serial Monitor (9600 baud) to view the output

Option 2: Wokwi Simulator (No Hardware Required)

1. Open https://wokwi.com
2. Create a new Arduino Uno project
3. Paste the example application code
4. Run the simulation
5. View the JSON output in the Serial Monitor

Public API Description
Serialization Function
int serialize_to_json(
const GatewayData input,
char output_buffer,
size_t buffer_size
);

API Characteristics

•	Transport-agnostic (no UART, MQTT, Serial, or radio inside the library)
•	Output is written into a caller-provided buffer
•	No dynamic memory allocation
•	Prevents buffer overflows
•	Designed for deterministic execution

Return Values

Value	        
Description
> 0	Number of bytes written
-1	Invalid input parameters
-2	Output buffer too small

Internal Data Model

The following data structures are used internally to represent gateway metadata and
measurement data:
typedef struct {
  const char timestamp;
  const char meter_datetime;
  float total_m3;
  const char status;
} DataPoint;

typedef struct {
  const char media;
  const char meter;
  const char deviceId;
  const char unit;
  DataPoint data;
} DeviceReading;

typedef struct {
  const char gatewayId;
  const char date;
  const char deviceType;
  int interval_minutes;
  int total_readings;
  DeviceReading device;
} GatewayData;
These structures were chosen to keep memory usage predictable and easy to reason about in an
embedded environment.

Example JSON Output

The library generates exactly the following JSON structure, matching the assignment
requirements:
[
  {
    "gatewayId":"gateway_1234",
    "date":"1970-01-01",
    "deviceType":"stromleser",
    "interval_minutes":15,
    "total_readings":1,
    "values":{
      "device_count":1,
      "readings":[
        {
          "media":"water",
          "meter":"waterstarm",
          "deviceId":"stromleser_50898527",
          "unit":"m3",
          "data":[
            {
              "timestamp":"1970-01-01 00:00",
              "meter_datetime":"1970-01-01 00:00",
              "total_m3":107.752,
              "status":"OK"
            }
          ]
        }
      ]
    }
  }
]

Output screenshot is attached.



Design Decisions and Assumptions

Design Decisions

•	Manual JSON construction using snprintf
•	No external JSON libraries
•	Fixed C data structures for predictable memory usage
•	Caller-controlled output buffer
•	Serialization logic separated from I/O
•	Floating-point values converted using dtostrf due to AVR limitations

Assumptions

•	Example demonstrates one device and one data point for clarity
•	Input data is assumed to be valid and pre-validated
•	Output buffer size is sufficient for the generated JSON
•	Time values are provided as formatted strings

Notes on Possible Extensions

This implementation can be extended in several ways:
•	Support for multiple devices and multiple data points
•	Configurable maximum limits
•	Streaming JSON serialization for large datasets
•	Porting to STM32 (STM32CubeIDE) or ESP32 (ESP-IDF)
•	Integration with real w-M-Bus gateway communication layers

Project Structure

wmbus-json-serializer/
├── include/
│   └── json_serializer.h
├── src/
│   └── json_serializer.cpp
├── examples/
│   └── arduino_demo.ino
├── README.md
└── LICENSE (optional)

Summary

This project demonstrates a robust and embedded-safe approach to JSON serialization for
smart-meter gateway firmware, focusing on correctness, clarity, and suitability for
resource-constrained systems.


