#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>

// Define pins for SIM800L and GPS
#define RXD2 16  // RX for SIM800L
#define TXD2 17  // TX for SIM800L
#define GPS_BAUD 9600
#define SIM_BAUD 9600

// Initialize GPS and SoftwareSerial for SIM800L
TinyGPSPlus gps;
SoftwareSerial ss(RXD2, TXD2);  // RX, TX for SIM800L

// Emergency contact number
const char* phoneNumber = "+91XXXXXXXXXX";  // Replace with the recipient's phone number

// Wi-Fi credentials
const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

// Email credentials
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define EMAIL_SENDER "your_email@gmail.com"
#define EMAIL_PASSWORD "your_email_password"
#define EMAIL_RECIPIENT "recipient_email@example.com"

// Set up the email message
SMTPData smtpData;

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
  ss.begin(SIM_BAUD);

  // Start Wi-Fi
  connectToWiFi();

  // Start GPS communication
  Serial.println("Initializing GPS...");
  
  // Wait for GPS fix
  while (gps.location.isUpdated() == false) {
    delay(1000);
    Serial.println("Waiting for GPS fix...");
  }

  Serial.println("GPS initialized.");
}

void loop() {
  // Read data from the GPS module
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  // Check if we have a valid GPS fix
  if (gps.location.isUpdated()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();

    // Print the location to the serial monitor
    Serial.print("Latitude= "); 
    Serial.print(latitude, 6);
    Serial.print(" Longitude= ");
    Serial.println(longitude, 6);

    // Send the emergency message via SIM800L
    sendSMS(latitude, longitude);

    // Send the emergency email via Wi-Fi
    sendEmail(latitude, longitude);
  }

  delay(1000);  // Delay for 1 second before checking again
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void sendSMS(float latitude, float longitude) {
  // Start the SMS process
  Serial.println("Sending SMS...");
  
  // AT commands to initialize the SIM800L module
  ss.println("AT");
  delay(1000);
  ss.println("AT+CMGF=1");  // Set SMS format to text mode
  delay(1000);
  ss.println("AT+CSCS=\"GSM\"");  // Set character set to GSM
  delay(1000);
  
  // Compose the message
  String message = "Emergency! My location is: \n";
  message += "Latitude: " + String(latitude, 6) + "\n";
  message += "Longitude: " + String(longitude, 6) + "\n";
  
  // Send the SMS
  ss.print("AT+CMGS=\"");
  ss.print(phoneNumber);  // Recipient's phone number
  ss.println("\"");
  delay(1000);
  ss.println(message);  // The message content
  delay(1000);
  ss.write(26);  // Send Ctrl+Z to indicate end of message
  delay(1000);

  Serial.println("Message Sent!");
}

void sendEmail(float latitude, float longitude) {
  // Set up email message
  String subject = "Emergency Alert";
  String body = "Emergency! My location is: \n";
  body += "Latitude: " + String(latitude, 6) + "\n";
  body += "Longitude: " + String(longitude, 6) + "\n";
  
  smtpData.setLogin(EMAIL_SENDER, EMAIL_PASSWORD);
  smtpData.setSender("ESP32", EMAIL_SENDER);
  smtpData.setSubject(subject);
  smtpData.setMessage(body, true);
  smtpData.addRecipient(EMAIL_RECIPIENT);

  // Send email
  if (MailClient.sendMail(smtpData)) {
    Serial.println("Email sent successfully.");
  } else {
    Serial.println("Error sending email: " + MailClient.smtpErrorReason());
  }
}

