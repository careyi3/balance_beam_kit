---
layout: page
title: Electronics
permalink: /electronics/
---

In this section we are going to break down our discussion into four main topics for discussion. stepper motors and drivers, the Arduino microcontroller, the acoustic position sensor and finally the PCB. The most advanced topic of the discussion is the PCB and in this section we will also discuss the details of the design of the power switching circuit on the board.

In a final part to this section, we will also provide a basic circuit diagram for getting the board working on a breadboard or protoboard.

&nbsp;

---

&nbsp;

## Arduino

![arduino nano](../images/electronics/arduino_nano.jpg)

An Arduino is a low cost, flexible, simple and robust microcontroller. In the wild, microcontrollers are the smart electronics that control electronic devices. Microcontrollers are tiny programmable computers that exist on a single chip. In terms of electronics, they occupy the space somewhere between things that are simple on-off devices with analog components and fully fledged computers. That is to say, a microcontroller can typically interface with simple low level electronics but can bring some intelligence to them while not having the power of a full computer. Even tho these devices don't have the computing power of full computers, modern microcontroller are incredibly powerful and capable of doing amazing things. Microcontroller shine in their ability to do relatively complex tasks at a low level very fast while consuming very little power. Consider that a modern computer has to be able to do lots of different things all at once, typically a microcontroller only has to do one or a small hand full of things at a time; in this way, they can be highly optimised for the task at hand.

While there are loads of different kind of microcontroller available these days, Arduino's provide a great platform to learn embedded software development and electronics. Arduino's are cheap and very robust, they are hard to blow up compared to other kinds of microcontroller, and when they are blown up, they are easily replaceable. Arduino's also come with a companion software development environment and a whole host of nice libraries and hardware abstractions which means you can get up and running really quickly. There is also a huge online community ready and willing to provide support.

For all of the above reasons and more, I choose to base the kit around an Arduino. I also have a lot of experience personally working with these devices so it was quick for me to prototype the system using one.

To learn more about Arduino I suggest visiting their [website](https://www.arduino.cc/) where you can find loads of information on them. Aside from the basic background presented here, we will dive into more detail about working with an Arduino in the [programming](../programming) section of this guide.

For this project, we will use an Arduino Nano. You can use any Arduino for this, but if you wish to use the PCB for the project, it has a socket which will accept an Arduino Nano. Also note, if you are sourcing an Arduino for the first time, you can buy them from the Arduino website, however these days you can buy many many clones of them online. They are all largely the same, some might have slight differences. Largely these are fine to use but buy them at your own risk as some can be faulty. With that said, they are usually available at a fraction of the price of the branded versions.

&nbsp;

---

&nbsp;

## Stepper Motors & Drivers

![stepper](../images/electronics/stepper.jpg)

Stepper motors are a special kind of brushless DC motor that are capable of accurate positioning with no external sensors under normal operation. This means that you can command the motor to spin a certain amount of degrees and hold it's position. The motor will move to the commanded position and stay there with very little error. This effect is achieved pulsing coils in the motor in a certain pattern, the magnetic field created with these coils then interacts with a specially shaped toothed rotor in the motor snapping the motor between so called "steps".

In this way, each rotation of the motor is actually made up of lots of small "steps" hence the motors name. In effect stepper motors are sort of like a poorly designed DC motor in that each state the motor gets into it doesn't really want to leave. This also means that at each step the motor has a very powerful holding torque and doesn't want to slip. These traits can be leveraged in many applications to make stepper motors extremely useful.

![stepper internals](../images/electronics/stepper_internals.png)

In terms of machine control, you can work out how many steps correspond to a certain about of movement of an axis of a machine. Once this is known, you can tell the machine how far to move the axis byt sending the correct number of steps to the motor. Due to the way the motors moves in steps and doesn't want to slip from it's holding position, this is extremely accurate and does not require sensors to detect the actual position.

One common modern usage of stepper motors is in low cost desktop 3D printers. The prevalence of these devices has made the NEMA 17 form factor of stepper motor widely mass produced and easily purchased the world over for very low cost. However, they do come with certain disadvantages including extra complicity in their operation. Compared to a regular DC motor, stepper motors require a driver and controller to function. Typically you would use a stepper driver board to interface directly with the motor and a microcontroller to tell the driver when to step the motor. Thanks to the 3D printer market, stepper drivers are also widely available and cheap such as the DRV8825 and in general microcontrollers are also cheap these days, so the expense might not be huge but there is a step up in complicity with compared to flicking a switch for a DC motor.

![DRV8825](../images/electronics/drv88245.jpg)

Considering all of the pros above, a stepper is a decent choice for this project. However it may not be the best choice for all control type projects. The nature of this machine means that the motor doesn't need to move very fast. While moving fast is something stepper motors can do, there are limitations to how fast an Arduino can drive a stepper and so if you require very high speeds this might not be the best solution.

Without going into hugh detail, it's worth knowing that the maximum speed your stepper can attain with be related to how fast your driver can send pulses to the motor (along with how fast your motor can respond to the pulses). The driver in theory will send a pulse to the motor every time it receives a pulse from the microcontroller. Typically the driver will have a "step" pin, by pulsing it high and low from the microcontroller, it will then send a "step" pulse to the motor. There is a minimum pulse width required by the driver and also a theoretical max frequency of the pulses set by the clock speed of your microcontroller. For an Arduino using the widely used [AccelStepper library](https://www.airspayce.com/mikem/arduino/AccelStepper/) this more or less ends up maxing out the pulses per second to 4000 on an Arduino with a 16Mhz clock.

&nbsp;

---

&nbsp;

## Acoustic Position Sensors

Sensor stuff here

&nbsp;

---

&nbsp;

## PCB

PCB stuff here

&nbsp;

---

&nbsp;

### Power Circuit

Power circuit stuff here

&nbsp;

---

&nbsp;

## Breadboard/Protoboard Circuit

Breadboard circuit here