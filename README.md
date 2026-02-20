<div align="center">

# 🐟 Real-time Monitoring System for Aquaculture using IoT

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Blynk](https://img.shields.io/badge/Blynk-23CE6B?style=for-the-badge&logo=blynk&logoColor=white)](https://blynk.io/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](LICENSE)
[![IoT](https://img.shields.io/badge/IoT-Enabled-blue?style=for-the-badge)]()

*An Arduino-based IoT system that monitors water quality parameters in real-time for aquaculture farms, streaming live data to a mobile dashboard with automated alerts.*

</div>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [System Architecture](#-system-architecture)
- [Features](#-features)
- [Hardware Requirements](#-hardware-requirements)
- [Software Dependencies](#-software-dependencies)
- [Circuit Wiring](#-circuit-wiring)
- [Installation & Setup](#-installation--setup)
- [Usage](#-usage)
- [Project Report](#-project-report)
- [Contributing](#-contributing)
- [License](#-license)

---

## 🔍 About the Project

Aquaculture contributes ~1.07% of India's GDP, with fish demand projected at 16 million tonnes by 2025. Commercial aquaculture faces significant losses due to sudden climatic fluctuations that alter water quality. Traditional manual testing is time-consuming and inaccurate — by the time readings are taken, conditions may have already changed.

This project solves that problem by building a **real-time, IoT-enabled water quality monitoring system** that:
- Continuously reads multiple water parameters via sensors
- Streams data to the **Blynk** cloud platform over serial communication
- Provides a **live mobile dashboard** with gauges and status indicators
- Sends **instant push notifications** when parameters exceed safe thresholds
- Allows **remote control** of equipment (pumps, aerators) via relay switches

> *Built as a final-year engineering project to demonstrate the application of embedded systems and IoT in precision aquaculture.*

---

## 🏗️ System Architecture

<div align="center">

![System Architecture](images/architecture.png)

</div>

**Data Flow:**

```
Sensors ─→ Arduino Uno ─→ Serial/WiFi ─→ Blynk Cloud ─→ Mobile App
                │
                └─→ Relay Module ─→ Pumps / Aerators
```

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🌡️ **Temperature Monitoring** | LM35 sensor reads water temperature in °C with high-temp alerts |
| 💧 **pH Monitoring** | Dedicated pH sensor module for acidity/alkalinity tracking |
| 🌊 **Turbidity Detection** | Analog turbidity sensor measures water clarity |
| ⚡ **Conductivity Check** | Digital conductivity sensor for dissolved solids indication |
| 📏 **Water Level** | Digital sensor detects tank full/empty status |
| 📱 **Live Dashboard** | Blynk mobile app with real-time gauges and status widgets |
| 🔔 **Push Notifications** | Instant alerts for high temperature and low water level |
| 🔌 **Remote Relay Control** | Control 2 relay channels (pumps/aerators) from the app |

---

## 🔧 Hardware Requirements

| Component | Quantity | Purpose |
|-----------|:--------:|---------|
| Arduino Uno / Mega | 1 | Main microcontroller |
| LM35 Temperature Sensor | 1 | Water temperature measurement |
| pH Sensor Module (with serial output) | 1 | pH level measurement |
| Turbidity Sensor (analog) | 1 | Water clarity measurement |
| Conductivity Sensor (digital) | 1 | Dissolved solids indication |
| Water Level Sensor (digital) | 1 | Tank level detection |
| 2-Channel Relay Module | 1 | Equipment control |
| ESP8266 / USB-Serial Adapter | 1 | Blynk connectivity |
| Jumper Wires, Breadboard | — | Wiring |
| 5V Power Supply | 1 | System power |

---

## 💻 Software Dependencies

| Software | Version | Purpose |
|----------|---------|---------|
| [Arduino IDE](https://www.arduino.cc/en/software) | 1.8+ | Code upload and compilation |
| [Blynk Library](https://github.com/blynkkk/blynk-library) | 0.6.x | IoT cloud connectivity |
| [SimpleTimer](https://github.com/jfturcot/SimpleTimer) | — | Non-blocking timer functions |
| [Blynk App](https://blynk.io/) | — | Mobile dashboard (iOS/Android) |

**Install libraries via Arduino Library Manager:**
```
Sketch → Include Library → Manage Libraries → Search "Blynk" → Install
```

---

## 🔌 Circuit Wiring

| Arduino Pin | Direction | Connected To | Signal Type |
|:-----------:|:---------:|--------------|:-----------:|
| A0 | INPUT | Turbidity Sensor | Analog |
| A1 | INPUT | LM35 Temperature Sensor | Analog |
| A4 | RX | pH Sensor Module TX | Serial |
| A5 | TX | pH Sensor Module RX | Serial |
| D2 | RX | Debug Serial (USB-TTL) | Serial |
| D3 | TX | Debug Serial (USB-TTL) | Serial |
| D6 | OUTPUT | Relay Module CH1 | Digital |
| D7 | OUTPUT | Relay Module CH2 | Digital |
| D8 | INPUT | Conductivity Sensor | Digital |
| D13 | INPUT | Water Level Sensor | Digital |

> 📖 For a more detailed wiring reference, see [`docs/circuit_diagram.md`](docs/circuit_diagram.md).

---

## 🚀 Installation & Setup

### 1. Clone the Repository

```bash
git clone https://github.com/raghu-007/Real-time-monitoring-system-for-aquaculture-using-IOT.git
cd Real-time-monitoring-system-for-aquaculture-using-IOT
```

### 2. Install Arduino Libraries

Open Arduino IDE and install via **Library Manager** (`Sketch → Include Library → Manage Libraries`):
- `Blynk` by Volodymyr Shymanskyy
- `SimpleTimer`

### 3. Configure Auth Token

1. Open the Blynk app on your phone
2. Create a new project and note the **Auth Token**
3. Open `src/aquaculture_monitor/aquaculture_monitor.ino`
4. Replace the placeholder:
   ```cpp
   char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
   ```

### 4. Set Up Blynk Dashboard

Add these widgets in the Blynk app:

| Widget | Virtual Pin | Data Type |
|--------|:-----------:|-----------|
| Button | V0 | Relay 1 ON/OFF |
| Button | V1 | Relay 2 ON/OFF |
| Gauge | V2 | Temperature (°C) |
| Gauge | V6 | Turbidity (V) |
| Value Display | V7 | Water Level |
| Value Display | V8 | Conductivity |
| Value Display | V9 | pH Value |

### 5. Upload & Run

1. Connect Arduino via USB
2. Select board and port in Arduino IDE
3. Upload `src/aquaculture_monitor/aquaculture_monitor.ino`
4. Open the Blynk app — your dashboard should go online!

---

## 📊 Usage

Once the system is running:

- **Monitor**: Open the Blynk app to view real-time sensor readings
- **Alerts**: Receive push notifications when:
  - Temperature exceeds 30°C
  - Water level drops (tank empty)
- **Control**: Toggle relay switches from the app to control connected equipment

---

## 📄 Project Report

The full engineering project report is available at [`docs/project_report.pdf`](docs/project_report.pdf).

---

## 🤝 Contributing

Contributions are welcome! Please read the [Contributing Guidelines](CONTRIBUTING.md) before submitting a pull request.

---

## 📝 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

<div align="center">

**Built with ❤️ as a Final Year Engineering Project**

*If this project helped you, consider giving it a ⭐!*

</div>
