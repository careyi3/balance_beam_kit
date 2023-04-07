---
layout: page
title: Programming
permalink: /programming/
---

In this section we will provide a basic overview of getting started with programming an Arduino microcontroller. We will then jump into some more complex discussion of how some of the important parts of the code work under the hood.

The sample code provided for the system is [here](https://github.com/careyi3/balance_beam_kit/blob/master/code/arduino/ball_and_beam/ball_and_beam.ino).

&nbsp;

---

&nbsp;

## The Basics

The Arduino platform is an extremely powerful and easy to use platform for getting up and running with embedded software development projects and requires very little prior knowledge to get started. The basic flow of how the system work goes like this; your microcontroller (usually an Atmel chip for Arduino) is soldered onto the Arduino board, you connect your Arduino board to your computer via USB. Using Arduino's software tools, you write your code in C/C++. Once written, the Arduino software interfaces with the microcontroller on the board and uploads your code to it. Once powered up, the microcontroller on the Arduino board then executes your code continuously. This flow is a little different to how production grade chips would usually work. Typically, microcontrollers require a special programmer to program or flash them with the required machine code. With Arduino, this is avoided by the microcontroller coming with a "bootloader" pre installed. This bootloader allows a very high level software interface to program the chip over USB.

I am not going to go into the details of setting up your first project with an Arduino, there are countless resources online for this the best of which is the basic Arduino getting started guide. If this is your first time working with this platform I highly recommend you take a look and follow the [getting started guide](https://docs.arduino.cc/learn/starting-guide/getting-started-arduino).

The rest of this section is going to go into the details and usage of specific libraries used in the example code for the system. It assumes that you have the code downloaded and can follow along with it. You can grab the code [here](https://github.com/careyi3/balance_beam_kit/blob/master/code/arduino/ball_and_beam/ball_and_beam.ino).

&nbsp;

---

&nbsp;

## AccelStepper Library

Stepper lib

&nbsp;

---

&nbsp;

## HC-SR04 Library

Sensory Lib stuff

&nbsp;

---

&nbsp;
## Kalman Filter

Talk a little bit about a kalman filter

&nbsp;

---

&nbsp;

## Coding a PID Controller

The main logic of the code for the system essentially follows a pattern of; read sensor -> process data -> command motors. This continues in a loop forever attempting to balance the ball at a set point. The part in the middle, "process data", is where the magic really happens in converting the sensor data into the correct motor commands to make the machine do what it needs to do. In specific it does this by implementing a PID controller. In the next section of this guide I will dive into control theory and the basic intuition around how a PID controller works and what it is doing. In terms of the software, we are using a library in the example code, but coding your own PID controller isn't very hard once you understand the concept. If you already know a bit about this subject but haven't seen how to do it from scratch I recommend you take a look at this [YouTube video](https://youtu.be/RZW1PsfgVEI) that walks through a basic from scratch implementation of a PID controller on an Arduino. If you don't know anything about PID controllers I recommend going to the [control theory](./control_theory) section and reading up and coming back to this video later.
