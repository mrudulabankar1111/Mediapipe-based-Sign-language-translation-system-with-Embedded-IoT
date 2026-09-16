// Core Libraries (Built-in with ESP32)
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>  // Install: WebSockets by Markus Sattler
#include <Wire.h>
#include <Adafruit_SSD1306.h>   // Install: Adafruit SSD1306
#include <Adafruit_GFX.h>       // Install: Adafruit GFX Library

// Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define BUZZER_PIN 4

// Initialize OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// WebSocket and WebServer
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// WiFi AP Credentials
const char* ssid = "Mrudula";
const char* password = "Mr7451010";

String currentPhrase = "None";

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 Starting...");
    
    // Initialize I2C
    Wire.begin(21, 22);  // SDA=21, SCL=22
    
    // Initialize OLED
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED allocation failed");
    } else {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("Sign Language IoT");
        display.display();
        Serial.println("OLED initialized");
    }
    
    // Initialize Buzzer - NEW ESP32 3.x COMPATIBLE METHOD
    // ledcAttach(pin, frequency, resolution) - combines setup + attach
    ledcAttach(BUZZER_PIN, 2000, 8);  // 2000Hz frequency, 8-bit resolution
    ledcWriteTone(BUZZER_PIN, 0);      // Start with no sound
    
    // Setup WiFi Access Point
    WiFi.softAP(ssid, password);
    Serial.println("Access Point Started");
    Serial.print("IP Address:192.168.4.1 ");
    Serial.println(WiFi.softAPIP());
    
    // Setup web server routes
    server.on("/", HTTP_GET, []() {
        String html = "<!DOCTYPE html><html><head>";
        html += "<meta http-equiv='refresh' content='2'>";
        html += "<style>body{font-family:Arial;text-align:center;margin-top:50px;}</style>";
        html += "</head><body>";
        html += "<h1>Sign Language Detection</h1>";
        html += "<h2>Current Phrase: " + currentPhrase + "</h2>";
        html += "<p>Connect to WiFi: " + String(ssid) + "</p>";
        html += "</body></html>";
        server.send(200, "text/html", html);
    });
    
    server.begin();
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    
    // Test buzzer on startup
    beep(1000, 200);
    
    Serial.println("ESP32 Ready!");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_TEXT:
            currentPhrase = String((char*)payload);
            Serial.println("Received: " + currentPhrase);
            
            // Update OLED display
            updateOLED(currentPhrase);
            
            // Buzzer feedback - using new API
            beep(1000, 200);
            
            // Broadcast to all connected web clients
            webSocket.broadcastTXT(currentPhrase);
            break;
    }
}

void updateOLED(String text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Detected:");
    display.setTextSize(2);
    display.setCursor(0, 20);
    
    // Handle long text
    if(text.length() > 10) {
        display.setTextSize(1);
        display.println(text);
    } else {
        display.println(text);
    }
    
    display.display();
}

// Buzzer function - uses new ESP32 3.x API
void beep(int frequency, int duration) {
    ledcWriteTone(BUZZER_PIN, frequency);  // Start tone on the pin
    delay(duration);
    ledcWriteTone(BUZZER_PIN, 0);          // Stop tone
}

void loop() {
    server.handleClient();
    webSocket.loop();
}
