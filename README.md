# Mediapipe-based-Sign-language-translation-system-with-Embedded-IoT
 This system allows users to define their very own vocabulary of up to 16 custom gestures. After that it translates them into either spoken words or text displayed on an OLED or LCD unit that uses an ESP32 chip .The whole process, or pipeline, happens in three phases using just a web browser – no cloud needed, which is quit efficient.
###MediaPipe-Based Hand Gesture Recognition System for Sign Language Translation with Embedded IoT Display Interface

### Real-Time Hand Gesture Recognition with ESP32

SignBridge is a low-cost system that recognizes hand gestures using a webcam, MediaPipe Hands, and TensorFlow.js. The recognized gesture is sent to an ESP32 through Wi-Fi and displayed on an OLED/LCD with buzzer feedback.

The system supports up to 16 custom gestures and runs directly in the browser.

## Features

* Real-time gesture recognition
* Webcam-based hand tracking
* MediaPipe Hands with 21 landmarks
* TensorFlow.js machine-learning model
* Supports up to 16 gestures
* Browser-based training and prediction
* ESP32 Wi-Fi communication
* OLED/LCD display output
* Buzzer feedback
* Local processing without cloud services

## How It Works

```text
Webcam
  ↓
MediaPipe Hands
  ↓
Feature Extraction
  ↓
TensorFlow.js Model
  ↓
Gesture Prediction
  ↓
ESP32
  ↓
OLED/LCD + Buzzer
```

## Technologies

* HTML / JavaScript
* MediaPipe Hands
* TensorFlow.js
* WebGL
* ESP32
* Wi-Fi
* OLED/LCD
* I2C
* Buzzer

## Supported Gestures

The system supports 16 gestures, including:

* Hello
* Yes
* No
* Okay
* Stop
* Thank You
* I Need Help
* Call the Doctor
* I Love You

## Hardware Connections

### OLED/LCD

| Pin | ESP32     |
| --- | --------- |
| VCC | 3.3V / 5V |
| GND | GND       |
| SDA | GPIO 21   |
| SCL | GPIO 22   |

### Buzzer

| Pin      | ESP32  |
| -------- | ------ |
| Positive | GPIO 4 |
| Negative | GND    |

## How to Run

### 1. Clone the Repository

```bash
git clone <YOUR-REPOSITORY-URL>
cd SignBridge
```

### 2. Start the Web App

```bash
python -m http.server 8000
```

Open:

```text
http://localhost:8000
```

### 3. Set Up the ESP32

1. Connect the OLED/LCD and buzzer.
2. Upload the ESP32 code.
3. Connect the ESP32 to Wi-Fi.
4. Enter the ESP32 IP address in the web app.

### 4. Collect and Train

1. Open the **Collect** section.
2. Record samples for each gesture.
3. Open the **Train** section.
4. Train the model in the browser.
5. Use the **Recognize** section to test gestures.

## Results

| Metric              |          Result |
| ------------------- | --------------: |
| Gesture Classes     |              16 |
| Test Accuracy       |           94.2% |
| Validation Accuracy |           95.2% |
| Training Time       |     3–6 minutes |
| Latency             | 1.2–1.8 seconds |
| Hardware Cost       |      Below ₹500 |

## Applications

* Assistive communication
* Gesture-based interfaces
* IoT projects
* Educational demonstrations
* Accessibility systems

Academic prototype using browser-based machine learning and ESP32 IoT hardware.
