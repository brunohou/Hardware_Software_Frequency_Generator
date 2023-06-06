# Hardware Software Frequency Generator

This project is part of the Hardware Software course at Faculté Polytechnique de Mons, Belgium.
This course is given by Pr. Valderrama.

Made by COLLET Antoine & HOUGARDY Bruno
2022-2023 school year

## Introduction
The project aims to develop a hardware driver for an FPGA and an application program for a frequency generator. The development was carried out on the DE0-Nano-SoC kit, which includes a SoC FPGA, an ARM Hard Processor System, USB and power cables. The Intel Altera SoC Qsys was utilized for the synthesis and simulation of the FPGA and platform design.
The free and open-source terminal emulator Putty will be used to create a serial console and transfer files (with ethernet or USB).

The goal of the project is to generate a signal on one of this Output port of the board. This signal will be a pulse oscillating at a certain frequency. The frequencies will have to vary from 1 kHz to 1 Mhz
How does it work ?
To generate a signal with a certain frequency, we will play with the output level of a port. Either the output is 0 (no voltage) or 1 (voltage). Alternating between these two states will generate a square signal. 
So the FPGA receives an input value from the software part ranging from 0 to 255 (8-bit vector). The frequency range from 1 khz to 1 mh is divided into 255 equal part. The period of a square-wave signal being the duration of a high state and a low state. To generate the high state, it is necessary to remain in this state for a certain number of clock revolutions. The same principle applies to the low state.
Since we're generating from 1 kHZ to 1 MHz, the minimum period will be 100 µs. 
To calculate the other period values, we need to do 100 µs + X * (1ms-100µs)/255  
X being a positive integer to run through the values. 
Since our clock runs at 50 MHz (20 ns), we can count the number of clock revolutions needed to reach the required period. 



## Steps to follow 
### 1) Launching (Quartus)
Open the project archive with Quartus ("FPGA.qpf"). You have now the full project in front of you. 
You can use the Plateform Designer tool to have a view of the key components on the board and their interconnections such as the HPS processor, Jtag/Uart, buttons, LEDs, and switches.
### 2) Top level file 
First of all, wa have our "FPGA_TOP.v" file. This code is an hardware description in verilog for our FPGA design. 
The module describes the connections and interfaces between various components of the FPGA.
### 3) Hardware driver 
This file ("FreqOUT.vhd") is the actual implementation of the frequency generator.
It contains the specifications for the logical circuit responsible for generating a frequency from a 50MHz clock. The circuit will be implemented in the FPGA and has four inputs and one output. The file is composed of the entity and the architecture. 
### 4) Test bench for our hardware driver
The purpose of the test bench ("FreqOUT_TBvhd") is to verify the functionality and correctness of our design being implemented the VHDL code. The test bench will create a simulation environment that allows you to apply test inputs to the design, observe the outputs, and compare them against expected results.
### 5) Wrapper 
The wrapper ("Wrapper.vhd") is the module that encapsulates and integrates the different elements of the design. It provides an interface between the different design blocks or entities, allowing them to communicata and interact with each other effectively.
### 6) Simulation in Quartus environment & loading
After compiling our VHDL codes, we can launch the simulation. We set the wrapper as the top level entity and run the simulation. 
The results gives the state (voltage) of our ports (inputs & outputs) in function of time. 
When we will have to load the design on our board, we will have to set the "FPGA_TOP.v" as the top level entity.
### 7) Software
For the user interface, we will use a C file to interact and ask for the desired frequency. Theses tasks are done by the specified files in the software branch of the github. As a reminder, the user enters a frequency value between 1 kHz and 1MHz, which must then be converted to an 8-bit vector. This vector is then sent to the FPGA. 
### 8) Loading 
The files have to be loaded on the board. First step is to transfer the hardware driver on the board (USB) for the FPGA.
For the software comms, we establish an network connection with Putty. We store the C files on the board, we run them and now we have established a communication between our computer and the board. The user can enter his desired frequency and the microcontroller will generate the accurate output signal. 

Comment : in this version of the project, the board generates automatically the 1 kHz signal when there is no input data. 


### Video showing the differents parts of the project (in french) : 
https://youtu.be/cjkrS4RvQGY


