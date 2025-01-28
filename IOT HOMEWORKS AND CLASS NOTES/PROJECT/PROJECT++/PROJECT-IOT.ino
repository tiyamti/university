#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ArduinoJson.h>

char *rawHomePage PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Iot_Project</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f7f7f7;
            color: #333;
            margin: 0;
            padding: 0;
        }

        .container {
            width: 80%;
            margin: 0 auto;
            padding: 20px;
            background-color: white;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
        }

        .header {
            text-align: center;
            margin-bottom: 20px;
        }

        h1 {
            font-size: 36px;
            color: #2c6a3b; /* Dark Green */
        }

        .led-status {
            display: flex;
            justify-content: center;
            gap: 30px;
            margin-bottom: 20px;
        }

        .led-label {
            font-weight: bold;
            font-size: 18px;
            padding: 10px;
            border-radius: 5px;
            display: inline-block;
            color: white;
            text-align: center;
            width: 150px;
        }

        .led-on {
            background-color: #28a745; /* Green */
        }

        .led-off {
            background-color: #dc3545; /* Red */
        }

        .form-container {
            text-align: center;
            margin-bottom: 30px;
        }

        .prompt-textarea {
            width: 80%;
            min-height: 100px;
            padding: 12px;
            margin-top: 10px;
            border: 2px solid #28a745;
            border-radius: 5px;
            font-size: 16px;
            font-family: Arial, sans-serif;
            resize: none;
        }

        .prompt-textarea:focus {
            outline: none;
            border-color: #007bff;
        }

        .send-button {
            padding: 12px 20px;
            background-color: #28a745; /* Green */
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
        }

        .send-button:hover {
            background-color: #218838;
        }

        .stop-button {
            padding: 12px 20px;
            background-color: #dc3545; /* Red */
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
        }

        .stop-button:hover {
            background-color: #c82333;
        }

        .status-message {
            text-align: center;
            margin-top: 20px;
            font-size: 18px;
            font-weight: bold;
            color: #28a745;
        }

        footer {
            text-align: center;
            font-size: 12px;
            color: #777;
            margin-top: 30px;
        }

        footer p {
            margin: 5px;
        }
    </style>
    <script>
        const SERVER_URL = 'http://192.168.4.1';

        function showDialog(message) {
            const overlay = document.getElementById('dialogOverlay');
            const content = document.getElementById('dialogContent');
            try {
                const jsonResponse = JSON.parse(message);
                content.textContent = jsonResponse.message || message;
            } catch (e) {
                content.textContent = message;
            }
            overlay.style.display = 'block';
        }

        function hideDialog() {
            document.getElementById('dialogOverlay').style.display = 'none';
        }

        function updateLEDs(status) {
            document.getElementById('led1Status').textContent = `LED1: ${status.led1}`;
            document.getElementById('led2Status').textContent = `LED2: ${status.led2}`;
            document.getElementById('led1Status').className = status.led1 === 'ON' ? 'led-label led-on' : 'led-label led-off';
            document.getElementById('led2Status').className = status.led2 === 'ON' ? 'led-label led-on' : 'led-label led-off';
        }

        function sendStopCommand() {
            fetch(`${SERVER_URL}/stop`, {
                method: 'POST',
            })
            .then(response => response.text())
            .then(data => {
                showDialog(data);
                document.getElementById('stop-status').textContent = data;
            })
            .catch(error => {
                showDialog(`Error: ${error.message}`);
            });
        }

        document.addEventListener('DOMContentLoaded', function() {
            document.getElementById('sendButton').addEventListener('click', function(e) {
                e.preventDefault();
                
                const promptText = document.getElementById('prompt').value;
                
                fetch(`${SERVER_URL}/prompt`, {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        prompt: promptText
                    })
                })
                .then(response => response.text())
                .then(data => {
                    showDialog(data);
                    document.getElementById('prompt').value = '';
                })
                .catch(error => {
                    showDialog(`Error: ${error.message}`);
                });
            });

            // Fetch initial LED status
            fetch(`${SERVER_URL}/status`)
                .then(response => response.json())
                .then(data => updateLEDs(data))
                .catch(error => console.error('Error fetching LED status:', error));
        });
    </script>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>IOT Project - LED Control</h1>
        </div>

        <div class="led-status">
            <span id="led1Status" class="led-label">LED1: OFF</span>
            <span id="led2Status" class="led-label">LED2: OFF</span>
        </div>

        <div class="form-container">
            <label for="prompt">Enter your prompt:</label><br>
            <textarea id="prompt" class="prompt-textarea" placeholder="Type your prompt here..."></textarea><br>
            <button id="sendButton" class="send-button">Send</button>
        </div>

        <!-- Stop Button Section -->
        <div class="form-container">
            <button id="stopButton" class="stop-button" onclick="sendStopCommand()">Stop</button>
        </div>

        <div id="stop-status" class="status-message">System is running...</div>
    </div>

    <footer>
        <p>User: no</p>
        <p>Last Updated: 2025-01-17 21:15:24 UTC</p>
    </footer>
</body>
</html>
)rawliteral";

#define WIFI_SSID "iot"
#define WIFI_PASSWORD "123456789"
#define LED1 33
#define LED2 4
#define HOME_PATH "/"
#define STATUS_PATH "/status"
#define PROMPT_PATH "/prompt"
#define STOP_PATH "/stop"
WebServer server(80);

bool LED1_Status = false;
bool LED2_Status = false;
bool systemStopped = false;

void handleHomePage() {
    String html = String(rawHomePage);
    html.replace("SERVER_IP_ADDRESS", WiFi.localIP().toString());
    server.send(200, "text/html", html);
}

void handleStatus() {
    String res = "{\"led1\": \"LED1_STATUS\",\"led2\": \"LED2_STATUS\"}";
    res.replace("LED2_STATUS", LED2_Status ? "ON" : "OFF");
    res.replace("LED1_STATUS", LED1_Status ? "ON" : "OFF");
    server.send(200, "application/json", res);
}

void handlePrompt() {
    if (server.hasArg("plain")) {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, server.arg("plain"));
        if (error) {
            server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
            return;
        }
        if (!doc.containsKey("prompt")) {
            server.send(400, "application/json", "{\"error\":\"Missing 'prompt' field\"}");
            return;
        }
        String prompt = doc["prompt"].as<String>();
        Serial.println("Prompt received: " + prompt);

        if (prompt == "turn on led1") {
            LED1_Status = true;
        } else if (prompt == "turn off led1") {
            LED1_Status = false;
        } else if (prompt == "turn on led2") {
            LED2_Status = true;
        } else if (prompt == "turn off led2") {
            LED2_Status = false;
        } else {
            server.send(400, "application/json", "{\"error\":\"Unknown command\"}");
            return;
        }

        digitalWrite(LED1, LED1_Status ? HIGH : LOW);
        digitalWrite(LED2, LED2_Status ? HIGH : LOW);

        server.send(200, "application/json", "{\"message\":\"Prompt processed successfully\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"No data received\"}");
    }
}

void handleStop() {
    systemStopped = !systemStopped;
    if (systemStopped) {
        server.send(200, "application/json", "{\"message\":\"System stopped\"}");
    } else {
        server.send(200, "application/json", "{\"message\":\"System resumed\"}");
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);

    Serial.println("Setting up Wi-Fi...");
    WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());

    server.on(HOME_PATH, handleHomePage);
    server.on(STATUS_PATH, handleStatus);
    server.on(PROMPT_PATH, HTTP_POST, handlePrompt);
    server.on(STOP_PATH, HTTP_POST, handleStop); 

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();  
    if (Serial.available()) {
        String ans = Serial.readString();
        ans.trim(); 

        Serial.println("Received command: " + ans); 
        if (ans == "A") {
            LED1_Status = true;  
            digitalWrite(LED1, LOW);
            Serial.println("LED1 is ON");
        } else if (ans == "B") {
            LED1_Status = false; 
            digitalWrite(LED1, HIGH);
            Serial.println("LED1 is OFF");
        } else if (ans == "C") {
            LED2_Status = true;  
            digitalWrite(LED2, HIGH);
            Serial.println("LED2 is ON");
        } else if (ans == "D") {
            LED2_Status = false; 
            digitalWrite(LED2, LOW);
            Serial.println("LED2 is OFF");
        }
        else if (ans == "E") {
            LED1_Status = true; 
            LED2_Status = true;
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, HIGH);
            Serial.println("LEDS is ON");
        }
        else if (ans == "F") {
            LED1_Status = false; 
            LED2_Status = false;
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, LOW);
            Serial.println("LEDS is OFF");
        }
      }
  }

