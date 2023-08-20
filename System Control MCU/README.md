# 🚗 Simple Garage System

Welcome to the Simple Garage System repository. This project showcases an innovative solution designed to revolutionize vehicle access management within a garage setting. Built with the Agile Scrum methodology using Jira software, the system ensures smooth operations, user convenience, and efficient administration.

![Screenshot 2023-08-21 085608](https://github.com/t0ti20/Simple_Garage_System/assets/61616031/65c69817-eb35-4e97-ada3-ef4bf8f21eb3)


## 🌟 Overview

The Simple Garage System operates with a clear workflow:

Users who wish to enter the garage present their ID through an RFID system. This ID is captured by the **Entrance Gate ECU** using the USART module. The Entrance ECU then communicates with the **System Control ECU** via the SPI protocol to verify the validity of the presented ID.

Upon successful ID validation:
- The garage gate opens.
- A green LED indicator illuminates, signaling authorized access.
- The system waits for a signal from the motion sensor, confirming the vehicle's passage.
- Once the vehicle has passed, the gate automatically closes.
- During this process, the admin dashboard receives an update on the recent activity.

Should the ID be deemed invalid:
- A buzzer sounds an alarm.
- The system displays an "ID not valid" message.
- A red LED lights up to indicate unauthorized access.
- The admin dashboard is immediately updated with this failed access attempt.

For both scenarios, a seven-segment display provides a real-time count of available slots in the garage.

Exiting the garage follows a similar pattern. The client presents their ID via RFID to the **Exit Gate ECU**. The ID is then verified with the System Control ECU. If the ID is valid, the exit gate opens, allowing the vehicle to leave. If not, the admin is notified without the gate opening.

Furthermore, administrators have access to a dedicated dashboard. Using a keypad and LCD interface, they can add new IDs, granting authorized access to new users.

## 🛠 Development

The system was developed in adherence to the Agile Scrum methodology and managed using Jira software. Over two releases, the solution has been refined to its current state:

- **First Release (2 Sprints)**
    1. Design and implement the MCAL (Microcontroller Abstraction Layer) for the three microcontrollers.
    2. Implementation of the HAL (Hardware Abstraction Layer) and the application layer.

- **Second Release**
    The refinement of various system functionalities and the finalization of the application layer.

This Agile approach ensured iterative improvement and effective incorporation of feedback, leading to a reliable and efficient garage management system.

## ⚙️ Features

- **RFID Integration:** Fast and efficient ID scanning for vehicle access.
- **SPI Communication:** Seamless and swift communication between ECUs using the SPI protocol in a single-master multiple-slave configuration.
- **Admin Dashboard:** Enables administrative oversight and control, from monitoring access attempts to adding new authorized IDs.
- **Seven Segment Display:** Offers real-time updates on garage occupancy.

## 🎥 User Story Exploration Video

Delve deeper into our garage management system by exploring a user story in action. Click on the thumbnail below to view the video.

https://github.com/t0ti20/Simple_Garage_System/assets/61616031/373c13ae-4bc4-4b18-9ada-e79a058e9a08

This video provides a comprehensive walk-through of a typical user story, showcasing the ease of use and functionalities of our system. From scanning an RFID at the entrance to seamless communication between ECUs, witness firsthand how our system transforms garage operations.

## 🚀 Future Improvements

- Integration of a centralized database for more extensive ID storage.
- Advanced analytics on the admin dashboard for tracking peak garage usage times.
- Enhanced security features including encryption for ID data.

## Authors
- [@Khaled El_Sayed](https://github.com/t0ti20)
Thank you for exploring the Simple Garage System. Your feedback and contributions are always welcome!
