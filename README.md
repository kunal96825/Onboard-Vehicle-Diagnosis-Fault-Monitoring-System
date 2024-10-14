# Onboard-Vehicle-Diagnosis-Fault-Monitoring-System

Code and explanation for your onboard vehicle diagnosis fault monitoring system project using the mentioned components. I'll focus on the Arduino (Atmega328P microcontroller), and ESP8266 for Wi-Fi communication, and include basic data processing for each sensor:

Overview of the System:
Arduino (Atmega328P microcontroller): Main controller for sensor data acquisition and processing.
LCD Display: To display sensor data and fault messages.
Ultrasonic Sensor: Measures distance to detect obstacles.
Temperature Sensor (LM35): Monitors engine temperature.
Accelerometer: Detects sudden movement or impact.
Vibration Sensor: Detects unusual vibrations indicating mechanical issues.
ESP8266 WiFi Module: Sends data to a server for remote monitoring.
Light Sensor (LDR): Detects ambient light levels, possibly for night mode in vehicles.

Explanation:
LCD Display: The LCD is initialized with the LiquidCrystal library to display temperature, distance, and fault warnings.
Ultrasonic Sensor: Measures the distance to obstacles. If the distance falls below a threshold, a warning is shown on the LCD.
Temperature Sensor (LM35): Reads analog values and converts them into Celsius. A temperature above 100°C triggers an overheat warning.
Vibration Sensor: Detects vibrations and sends an alert if unusual movement is detected.
Accelerometer: Reads acceleration values, which can be used to detect impacts or accidents.
LDR: Measures ambient light to monitor environmental conditions, which can be used to adjust display brightness or trigger night mode.
ESP8266 WiFi: Connects to a Wi-Fi network and sends data to a remote server whenever a fault is detected.




To send messages to Telegram from your onboard vehicle diagnosis fault monitoring system, you can use the Telegram Bot API. Below are the steps to create a Telegram bot and modify your Arduino code to send messages through Telegram.

Step 1: Create a Telegram Bot
Open Telegram and search for the user @BotFather.
Start a chat with BotFather and send the command /newbot.
Follow the instructions to create your bot. You will receive a bot token. Keep this token safe as you will need it to send messages.
Step 2: Get Your Chat ID
Start a chat with your new bot by searching for its username in Telegram.
Send a message to your bot (e.g., "Hello").
Open your web browser and enter the following URL, replacing YOUR_BOT_TOKEN with the token you received from BotFather:

https://api.telegram.org/botYOUR_BOT_TOKEN/getUpdates

Look for the "chat" object in the JSON response. You will find your chat ID there (it usually looks like a series of digits).

Code Explanation:
Telegram Configuration: Replace YOUR_BOT_TOKEN and YOUR_CHAT_ID with your actual bot token and chat ID.
sendToTelegram Function: This function constructs a URL for sending messages to your Telegram bot using the Bot API and makes a GET request.
Sending Alerts: Whenever a fault is detected (overheating, vibration, or obstacle detection), the relevant message is sent to your Telegram account.
Note:
Make sure your ESP8266 module has internet access to send messages to Telegram.
If you encounter any issues with the connection or sending messages, check your Wi-Fi credentials and ensure the Telegram bot token and chat ID are correct.
