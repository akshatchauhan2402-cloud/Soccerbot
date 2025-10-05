# **Steps for connecting components**

## Step 1: Adjust output of Buck converter to 5V using a multimeter

## Step 2: Now take a thick wire or a multipin node(here 10-pin node) which will be the common ground of the circuit

## Step 2: Connecting buck module
* ### Connect battery+ to LM2596 VIN+
* ### Connect LM2596 VOUT+ to ESP32 5V(or VIN)
* ### Connect battery-, LM2596 VIN- and VOUT-, ESP32 GND to the common ground

## Step 3: Connecting motor drivers
* ### For each MD1OC
  * #### Connect battery+ to MD10C V+ pin
  * #### Connect MD10C V- pin to the common ground
* 
