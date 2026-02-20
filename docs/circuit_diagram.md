# Circuit Wiring & Pin Mapping

## Arduino Pin Assignments

| Arduino Pin | Direction | Connected To           | Signal Type |
|:-----------:|:---------:|------------------------|:-----------:|
| A0          | INPUT     | Turbidity Sensor       | Analog      |
| A1          | INPUT     | LM35 Temperature Sensor | Analog    |
| A4          | RX        | pH Sensor Module TX    | Serial      |
| A5          | TX        | pH Sensor Module RX    | Serial      |
| D2          | RX        | Debug Serial (FTDI/USB-TTL) | Serial |
| D3          | TX        | Debug Serial (FTDI/USB-TTL) | Serial |
| D6          | OUTPUT    | Relay Module CH1       | Digital     |
| D7          | OUTPUT    | Relay Module CH2       | Digital     |
| D8          | INPUT     | Conductivity Sensor    | Digital     |
| D13         | INPUT     | Water Level Sensor     | Digital     |

## Power Supply

- **Arduino**: Powered via USB or 9V DC barrel jack.
- **Sensors**: Powered from the Arduino 5V rail.
- **Relay module**: Powered from Arduino 5V; relay coils may need an external 5V supply if current draw exceeds the Arduino regulator capacity.

## Notes

- The **LM35** is a linear temperature sensor: output voltage = 10 mV/°C.
- The **pH sensor** communicates over a SoftwareSerial link at 9600 baud and sends ASCII-encoded pH readings prefixed with `P`.
- The **turbidity sensor** outputs an analog voltage inversely proportional to water clarity.
- The **conductivity sensor** provides a simple HIGH/LOW digital output.
- The **water level sensor** outputs HIGH when the tank is full.
