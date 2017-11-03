# BME280
**This project is still under development**

This is a sub project in which we will try to get the temperature, pressure and humidity using a BME280 implemented in the Weather Click from MikroE. 

It's part of the big project which consist of getting these outputs and send them over using a MQTT protocol and then have a feedback.

## 1. Development Environment
Os : Ubuntu MATE 16.04  
IDE : System Workbench for STM32  

## 2. Hardware used
-STM32F407G-DISC1 with a MikroE Shield (Shield not indispensable)

-MikroE Weather Click that integrate a BME280 sensor (Sensor alone works too)

-A USB cable to power the board and load our program

## 3. Implement the code to a new project
You will need the System Workbench for STM32 available on Windows and Mac too.

This operation is unskipable since it will create all the headers, drivers and HAL files we need.

Go onto File => New Project => C project.

Name your project and press Next.

Check Debug and Release then press Next.

Choose STM32F4 for Series then STM32F4DISCOVERY for Boards and press Next.

Choose Hardware Abstraction Layer(Cube HAL), wait for the end of the download if first time and press Finish.

Now Sys Workbench have created all the necessary drivers and more importantly the two folders Src & Inc.

You can finally copy the Src and Inc files onto your two fresh directories.

Plug the sensor onto the STM 32F4 and then connect the board to your computer via USB.

Press Build (Hammer Icon) then Run (Play Icon).

## 4. Hardware setup
I use the first port on the STM32 shield that's the reason why I configure the PORTA, GPIO wise.

Since I've chosen the I2C protocol to communicate (SPC supported too) I need to setup SP7 for SDA and SP8 for SCL on the weather click. 

Click Schematic and BME280 datasheet available.
