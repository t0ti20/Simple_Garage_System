# 🚧 Exit Gate ECU Functionality - Garage Management System

![3](https://github.com/t0ti20/Simple_Garage_System/assets/61616031/e71c6094-6e22-4316-86a8-40a7fe4514b7)

Developed utilizing the robust ATmega32 microcontroller, the Exit Gate ECU is a vital component of our Garage Management System. It supervises and authenticates the exiting vehicles through a seamless interaction of RFID, USART, and SPI communication mechanisms.

## 📖 Detailed Overview

### Step 1: Vehicle Prepares to Exit
As a vehicle is poised to exit the garage, the user must present their ID to the RFID scanner at the exit gate. This identification process is expertly handled by the USART module integrated within the ATmega32.

### Step 2: Exit ECU Communicates with Main ECU
Upon ID capture, the Exit ECU initiates a query process with the Main ECU. This communication is executed over the SPI protocol, embedded in the ATmega32, ensuring rapid and error-free data exchanges.

### Step 3: ID Validation and Exit Execution

- **Valid ID Scenario**:
  - Recognizing an authenticated ID, the gate automatically swings open, authorizing the vehicle to exit.
  - During this time, a notification or alert is dispatched to the admin dashboard, ensuring real-time monitoring and awareness.

- **Invalid ID Scenario**:
  - Should the ID prove inauthentic, the gate remains firmly shut.
  - While the vehicle is not granted permission to exit, an urgent notification is routed to the admin dashboard, highlighting the unauthorized exit attempt.
  
Regardless of the ID's validity, the ATmega32 ensures that every exit attempt is duly recorded and the admin dashboard is updated promptly.

## 🛠 Technologies & Hardware

- **RFID**: Offers efficient, contactless ID scanning for exiting vehicles.
- **USART Module**: Embedded in the ATmega32, it ensures the seamless capture of ID from the RFID scanner.
- **SPI Protocol**: Leveraging ATmega32's capabilities, it governs the communication between the Exit ECU and Main ECU.
