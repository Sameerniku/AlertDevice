# **Woman Safety Device with SIM800L and Email Alert**

This project provides a woman safety device that uses an **ESP32** microcontroller, a **GPS module**, and a **SIM800L GSM module**. In case of an emergency, the device sends the user's location via both **SMS** and **Email** to predefined contacts. The device can be activated by pressing a button, triggering the alert system.

## **Key Features**
- **SMS Alert**: Sends an emergency SMS with the user's GPS coordinates using the **SIM800L GSM module**.
- **Email Alert**: Sends an email with the user's GPS location using **Wi-Fi** and **ESP Mail Client**.
- **GPS Location Tracking**: Uses a **GPS module** (e.g., NEO-6M) to get real-time latitude and longitude.
- **Emergency Button**: Pressing the button triggers the device to send alerts.
- **ESP32 Microcontroller**: Controls both SMS and email functionality.

## **Hardware Required**
- **ESP32 Development Board**
- **SIM800L GSM Module**
- **GPS Module** (e.g., NEO-6M)
- **Push Button**
- **Jumper Wires**

## **Libraries Used**
- **TinyGPS++**: For GPS location tracking.
- **ESP Mail Client**: For sending emails via SMTP.
- **SoftwareSerial**: For communication with the SIM800L GSM module.

## **How It Works**
1. **Button Press**: When the user presses the emergency button, the device activates.
2. **GPS Location**: The device retrieves the current GPS coordinates (latitude and longitude).
3. **SMS Alert**: The **SIM800L GSM module** sends an SMS with the user's location to an emergency contact.
4. **Email Alert**: The **ESP32** sends an email with the same location details to a predefined recipient using Wi-Fi.

## **Setup Instructions**
### **1. Wiring the Components**
- **ESP32**:
  - **TX (ESP32)** → **RX (SIM800L)** (GPIO17)
  - **RX (ESP32)** → **TX (SIM800L)** (GPIO16)
  - **VCC** → **5V**
  - **GND** → **GND**
- **GPS Module**:
  - **TX (GPS)** → **RX (ESP32)** (GPIO4)
  - **RX (GPS)** → **TX (ESP32)** (GPIO5)
  - **VCC** → **3.3V**
  - **GND** → **GND**
- **Button**:
  - One side of the button goes to **GND**, and the other side goes to a digital pin (e.g., GPIO13).

### **2. Modify the Code**
- **Wi-Fi Credentials**: Replace the `ssid` and `password` with your Wi-Fi network credentials.
- **Email Credentials**: Replace the email-related fields (`EMAIL_SENDER`, `EMAIL_PASSWORD`, `EMAIL_RECIPIENT`) with your Gmail details and the recipient's email.
- **SIM800L Phone Number**: Replace the `phoneNumber` variable with the emergency contact's phone number.

### **3. Upload the Code**
- Open the project in **Arduino IDE** or **PlatformIO**.
- Select the correct board (**ESP32**) and upload the code to the ESP32.

### **4. Test the Device**
- Once the device is powered on, it will connect to the Wi-Fi network.
- Press the emergency button to trigger the alert system.
- Check the **Serial Monitor** for status messages and confirmation of sent SMS and email.

## **Troubleshooting**
- **No GPS Signal**: Ensure the GPS module has a clear view of the sky for accurate location tracking.
- **SIM800L Not Sending SMS**: Verify the SIM card has sufficient balance and supports SMS.
- **Email Not Sending**: Ensure that you have enabled "Less secure apps" or used **App Passwords** for Gmail accounts.

## **Contributing**
Feel free to fork this repository, submit issues, or contribute improvements. If you have suggestions for additional features or improvements, please open a pull request.

## **License**
This project is open-source and available under the **MIT License**.
