---
layout: page
title: Programming
permalink: /programming/
---

In this section we will provide a basic overview of getting started with programming an Arduino microcontroller. We will then jump into some more complex discussion of how some of the important parts of the code work under the hood.

The sample code provided for the system is [here](https://github.com/careyi3/balance_beam_kit/blob/master/code/arduino/ball_and_beam/ball_and_beam.ino).

I have a [video on YouTube](https://www.youtube.com/watch?v=OBsXWNbOTRY) breaking down the code and going over it in some detail, it is a good companion to this guide if you want to take a look.

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

Stepper motors, as we covered in the electronics section, require more than just a simple on/off switch to control. Along with the stepper driver board, you need to write some code on your microcontroller to tell the motor driver when to send pulses. At it's most basic, you can interface with a stepper driver by pulsing a pin high and low (high for a minimum duration of 10us usually) at a particular frequency. On an Arduino, you can do this using `digitalWrite` and `delay`. This isn't the most advanced way of doing it, but it will work. Of course, the speed them of the motor is effectively controlled by the frequency of the pulses. So sending a step high low pulse with a shorter `delay` value between each pulse, you can make the motor spin faster.

While the above mechanism for pulsing a motor will work file for lots of different cases, it lacks some features that are very important for controlling a motor. One major thing missing from the above is acceleration. When working with electric motors in general you will find that one way they are specced is with torque-speed curves. These are plots of the amount of torque they have a certain speeds. A rough way to think about this is that the motor will have less torque at higher speed. So if you had a machine, like a cnc machine with a large enough mass, you can't just tell the motors to go full speed from a dead stop. The motors will stall immediately the not be able to move the machine. Instead you can start the motors spinning at a slower rate and ramp the speed up to full speed. A ramp down can then be used to slow the machine down to stop precisely at the desired location. These so called acceleration profiles are a bit more complicated to implement so it might be nice to use a library that implements this for us.

For this project I used the [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/) library which handles basic operations of a motor as well as implementing accelerations and different operating modes like running a motor at a specific speed or moving it a specific number of steps at a certain speed. Thanks to stepper motors precise open loop position control, the software can also provide accurate tracking information on the exact angle of the stepper motor, including how many revolutions it's moved through and in which direction. I have used this library in many projects and I can honestly say I think it's fantastic. I strongly recommend having a read of the documentation and getting to grips with how it works, it is highly worth while. It has lots of config that is worth understanding including the limits to the maximum speeds and accelerations.

&nbsp;

---

&nbsp;

## HC-SR04 Library

With reference to the electronics section where we presented the timing diagram for this device, we should remember that the width of the pulse returned by the device should be measured to determine the distance from the sensor and object is. To trigger the device, all we have to do is send a pulse of a certain length to the device on the trigger pin. We then need to "listen" for a response on the echo pin and record the length of it. This might sound complicated but we can achieve the trigger pulse by using `analogWrite` and `delay` and we can listen to and record the response pulse length using the `pulseln` function. There is then a tiny bit of maths that needs to be done involving the speed of sound to turn the pulse length into a distance. None of this is very difficult bu there is a nice library we are using here which wraps all of this up in a handy package. You can find the source code [here](https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib/). I recommend having a read of it and understanding what is going on.

&nbsp;

---

&nbsp;

## Kalman Filter

The above sensor library and the sensor module are pretty good at what they do especially considering the price of the modules. They have their limitations but within their operating ranges they work pretty well and should achieve enough accuracy for most hobby applications. The range of the sensors is from about 2-400cm, so if you are detecting objects at around a meter or so away and you don't need to worry about variances of 1-2cm, these sensors will work perfectly as they are. In our application, we are using the sensor in about the 2-30cm range and within that range a 1-2cm variance is going to be way to much error for the PID controller to stabilise it properly. Now, in real life, over the 2-30cm range the sensor isn't giving 1-2cm of variance, but there is still some noise in the sensor readings making them a little harder to use in the PID controller. As the PID controller changes it's input based on the error signal from the sensor, if this error signal has lots of noise, the PID controller has to compensate for this making it difficult to reach stability.

We can improve the situation a lot by using something to smooth out the noise in our sensor readings. There are many different ways to achieve this but by far one of the most effective ways is to use a Kalman filter. I am not going to go into the details of a Kalman filter here as they are a relatively complex and deep topic. For an amazing coverage of them, I highly recommend following [this tutorial on YouTube](https://www.youtube.com/playlist?list=PLX2gX-ftPVXU3oUFNATxGXY90AULiqnWT), watching the first 4-5 videos in the series will give you a really good working knowledge of the basic version used in our project here (I have always struggled with these and this videos series really cleared up lots for me). At a very high level view, the Kalman filter uses predictions of errors compared with actual measurements of values to build a model of the system under the hood. Amazingly, this model very quickly approaches an extremely accurate output of the real values of the system even if there is lots of noise present.

Regardless of if we understand the details or not, we can ignore the implementation if we use one of the great Kalman filter libraries available to us! For this project we use the excellent [SimpleKalmanFilter](https://github.com/denyssene/SimpleKalmanFilter) library as it works well for a single variable and doesn't over complicate the system. I suggest reading their docs about setting up the library but really we are only required to pass in some tuning parameters to initalise the state of the filter. These can also be tuned with trial and error to get it working the way you want.

&nbsp;

---

&nbsp;

## Coding a PID Controller

The main logic of the code for the system essentially follows a pattern of; read sensor -> process data -> command motors. This continues in a loop forever attempting to balance the ball at a set point. The part in the middle, "process data", is where the magic really happens in converting the sensor data into the correct motor commands to make the machine do what it needs to do. In specific it does this by implementing a PID controller. In the next section of this guide I will dive into control theory and the basic intuition around how a PID controller works and what it is doing. In terms of the software, we are using a library in the example code, but coding your own PID controller isn't very hard once you understand the concept. If you already know a bit about this subject but haven't seen how to do it from scratch I recommend you take a look at this [YouTube video](https://youtu.be/RZW1PsfgVEI) that walks through a basic from scratch implementation of a PID controller on an Arduino. If you don't know anything about PID controllers I recommend going to the [control theory](./control_theory) section and reading up and coming back to this video later.
