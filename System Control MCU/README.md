# 🚧 Main ECU Functionality - Garage Management System

![2](https://github.com/t0ti20/Simple_Garage_System/assets/61616031/01a92b2e-0142-4962-9be4-b20293aacd09)

Embedded with the powerful STM32F103C6 microcontroller, the Main ECU stands as the heart and administrative core of our Garage Management System. Its capabilities span across providing an intricate admin dashboard, ID management, and supervising the complete vehicle ingress and egress workflow.

## 📖 Detailed Overview

### Step 1: Admin Dashboard Authentication
Accessing the specialized administrative dashboard on the Main ECU requires validation through a secure password. The STM32F103C6 ensures this access mechanism remains impenetrable, allowing only authorized personnel.

### Step 2: ID Management 
Upon successful authentication, the admin can seamlessly navigate the system using the keypad, enabling the addition of new, authorized IDs. The LCD, empowered by the STM32F103C6, offers an interactive experience, promptly displaying feedback and confirmation of ID inclusions.

### Step 3: Inter-ECU Communication
As vehicles aim to traverse the garage boundaries, the associated ECUs (Entrance or Exit) engage the Main ECU to validate the presented ID. The SPI communication, an integral feature of the STM32F103C6, facilitates this interaction:

- **Valid ID Scenario**:
  - Post verification, the Main ECU affirms the ID's legitimacy and transmits a "valid" flag to the inquiring ECU. This acknowledgment induces the desired reaction at the respective boundary – primarily, the initiation of the gate mechanism.

- **Invalid ID Scenario**:
  - In case of ID discrepancies, the Main ECU promptly relays an "invalid" signal to the querying ECU. Such instances ensure the gate's sustained closure and activation of associated alert systems, such as buzzers or LEDs, indicating an unauthorized endeavor.

Every ID verification, be it valid or otherwise, is diligently recorded and available for review from the admin dashboard, embodying a layer of transparency and control.

## 🛠 Technologies & Hardware

- **Keypad**: An interface designed for the streamlined addition of authenticated IDs and admin credentials.
- **LCD Screen**: Working in harmony with the STM32F103C6, it ensures administrators experience a lucid and dynamic interaction.
- **SPI Protocol**: This facilitates robust communication between the Main ECU and peripheral ECUs (Entrance/Exit).
