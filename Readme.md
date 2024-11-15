![profile1](https://github.com/user-attachments/assets/0da8725e-8b70-4d56-b087-c30ebe710fc4)

# **Lighthouse - IoT Monitoring System for Lighthouse State**

### **Overview**
The *Lighthouse* project is an IoT-based system designed to monitor and control the state of the Al Hank lighthouse in Casablanca. This system integrates a custom electronic board with sensors and communication modules to monitor parameters such as power supply status, lighting functionality, and environmental conditions. LTE cellular communication and the MQTT protocol are used to transmit real-time data to the ThingsBoard platform for remote monitoring and control. Additionally, an alarm notification system triggers alerts to designated personnel when issues are detected, ensuring timely intervention.

### **Project Details**
- **Platform**: ThingsBoard (Cloud version)
- **Communication Protocol**: MQTT (Message Queuing Telemetry Transport) for data efficiency
- **Network**: LTE (Long-Term Evolution) for reliable, wide-range connectivity
- **Alarm Notification**: The system includes an alarm feature that sends notifications via ThingsBoard when anomalies or malfunctions are detected.
  
### **Objectives**
The project aims to provide a cost-effective and reliable solution to remotely monitor and control lighthouse functionality, minimizing the need for manual intervention and ensuring maritime safety. The primary goals are to:
1. Automate the lighthouse monitoring process and reduce dependency on human intervention.
2. Develop a custom PCB with optimized impedance and reduced electromagnetic interference (crosstalk).
3. Implement a firmware solution for real-time data collection, processing, and MQTT-based communication.
4. Enable remote control functionality through ThingsBoard for seamless adjustments and troubleshooting.
5. Integrate an alarm notification system to respond promptly to malfunctions.

### **Project Components and Hardware Design**
1. **Sensor Integration**  
   - Sensors used include capacitive proximity sensors (to detect rotation frequency), light-dependent resistors (LDR) for lighting functionality, and optional environmental sensors like temperature and humidity.
  
2. **Custom PCB Design**  
   - The custom PCB is designed with multiple layers for effective power management, using components like the ATmega2560 microcontroller and SIM808 module for cellular communication. Voltage regulation and design practices, such as minimizing crosstalk and optimizing impedance, were critical to PCB stability.
  
3. **LTE and MQTT Communication**  
   - The SIM808 module facilitates LTE cellular communication. MQTT is used due to its low bandwidth and efficient publish-subscribe model, which is well-suited for IoT applications.

4. **ThingsBoard Platform**  
   - Data is sent to ThingsBoard, which acts as the central monitoring and control hub. MQTT data is formatted in JSON and transmitted under specific topics to ThingsBoard, allowing for seamless integration.
    ![data_full](https://github.com/user-attachments/assets/ca87851b-6b1f-46d3-b898-761781d36820)
5. **Alarm Notification System**  
   - The alarm system is configured within ThingsBoard to alert operators via email when critical thresholds or malfunctions are detected, ensuring rapid response.
     ![email_notice](https://github.com/user-attachments/assets/ee68ffd8-df3d-4622-bc40-52105fd2438d)


### **Project Phases**
The project is structured into distinct phases following a V-model lifecycle:
1. **Requirements & Planning**  
   - A detailed analysis was performed, and a benchmark study was conducted to determine suitable hardware and protocols.

2. **Design & Prototyping**  
   - The hardware architecture includes multiple functional blocks, such as power regulation, microcontroller, sensors, and LTE communication. The PCB was designed to ensure stability and efficiency, incorporating multilayer structures to manage impedance.

3. **Firmware Development**  
   - Firmware was developed in C, utilizing AT commands for SIM808 configuration and MQTT for data handling. Functions include sensor data acquisition, processing, and communication with ThingsBoard.

4. **Testing & Validation**  
   - The system underwent tests for communication stability, sensor accuracy, and alarm functionality, ensuring reliability and efficiency under different scenarios.

5. **Deployment**  
   - The final implementation involved deploying the PCB and connecting it to ThingsBoard, enabling live monitoring and control of the lighthouse.

### **Getting Started**
To begin with the *Lighthouse* project, you will need:
- LTE-enabled development board and sensors.
- A ThingsBoard account for monitoring and control.
- A development environment for firmware and MQTT setup.

### **Setup Instructions**
1. **Clone the Repository**:  
   ```bash
   git clone https://github.com/your-username/lighthouse](https://github.com/yassinegannoune/LIghtHouse-Monitoring.git)
   
2. **Install Dependencies**:
   - Install required libraries for sensor interfacing, LTE communication, and MQTT protocol.

3. **Configure MQTT & LTE**:
   - Set up MQTT credentials and LTE configuration for ThingsBoard.

4. **Run Tests**:
   - Test firmware functionality on the development board, ensuring accurate data transmission to ThingsBoard.

### **License**
This project is licensed under the MIT License - see the LICENSE file for details.

### **Contact**
For further inquiries, contact [yassine.gannoune@usmba.ac.ma] or open an issue on the project repository.
