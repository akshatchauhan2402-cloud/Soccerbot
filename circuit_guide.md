## **Steps for connecting components**

### **Step 1:** Adjust output of Buck converter to 5V using a multimeter

### **Step 2:** Now take a thick wire or a multipin node(here 10-pin node) which will be the common ground of the circuit

### **Step 3:** Connecting buck module
* #### Connect battery+ to LM2596 VIN+
* #### Connect LM2596 VOUT+ to ESP32 5V(or VIN)
* #### Connect battery-, LM2596 VIN- and VOUT-, ESP32 GND to the common ground

### **Step 4:** Connecting motor drivers
* #### From each MD1OC → battery
  * ##### Connect battery+ to MD10C V+ pin
  * ##### Connect MD10C V- pin to the common ground
* #### From each MD10C → each Motor
  * ##### Connect Motor A+ to MD10C OUT+
  * ##### Connect Motor A- to MD10C OUT-

 ### **Step 5:** Control Wiring 
 * #### Connect MD10C DIR pins to ESP32_D14,D27,D26,D25
 * #### Connect MD10C PWM pins to ESP32_D32,D33,D12,D13

