# 🚧 Gate ECU Functionality - Garage Management System

![1](https://github.com/t0ti20/Simple_Garage_System/assets/61616031/34ac202e-645e-4062-8391-cab5f3027ad1)

Developed on the robust ATmega32 microcontroller platform, the Gate ECU lies at the heart of our Garage Management System, governing vehicle access through a blend of RFID, USART, and SPI communication protocols.

## 📖 Detailed Overview

### Step 1: User Approach and ID Scanning
When a user seeks to access the garage, they present their ID to the RFID scanner. This ID scanning action is driven by the USART module integrated with the ATmega32. 

### Step 2: Entrance ECU to Main ECU Communication
On capturing the ID, the Entrance ECU starts communicating with the Main ECU. This communication relies on the SPI protocol, facilitated by the ATmega32, to ensure a swift and error-free data transmission.

### Step 3: ID Validation and Action Execution

- **Valid ID Scenario**:
  - The gate automatically opens, granting vehicle access.
  - A green LED, connected to the ATmega32, illuminates to indicate successful validation.
  - The system enters a standby mode, with the ATmega32 continuously reading the motion sensor.
  - As the motion sensor detects the vehicle's movement, the gate begins its closing sequence.
  
- **Invalid ID Scenario**:
  - A buzzer, interfaced with the ATmega32, gets triggered, notifying the user of an access denial.
  - The LCD screen, driven by the ATmega32, promptly flashes an "ID not valid" message.
  - Concurrently, a red LED fires up, signalling the failed access attempt.
  
In both scenarios — valid and invalid — the ATmega32 ensures that the admin dashboard gets timely notifications for real-time system monitoring.

## 🛠 Technologies & Hardware

- **RFID**: Enables efficient, contactless ID scanning.
- **USART Module**: Integrated with ATmega32 for seamless RFID-ECU interactions.
- **SPI Protocol**: Facilitated by ATmega32 for inter-ECU communication.
- **Motion Sensor**: Connected to ATmega32 for real-time vehicle detection.

Leveraging the power of ATmega32, the Gate ECU ensures a streamlined, secure, and intuitive garage access mechanism.