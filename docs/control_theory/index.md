---
layout: page
title: Control Theory
permalink: /control_theory/
---

The main goal of the project is to act as a resource for teaching the basics of control theory and in particular the practical implementation of a PID controller. Below is a system diagram showing the main components of the system and their connection in the common system diagram format.

![system diagram](../images/control_theory/system_diagram.png)

Before we dive into the details, there are two videos of mine which will help, this first one is dedicated to explaining the [software behind the system in general](https://www.youtube.com/watch?v=OBsXWNbOTRY) and the next one is an in depth look at [implementing your own PID controller from scratch on an Arduino](https://youtu.be/RZW1PsfgVEI) (you may want to wait until after you have read this to watch, or not, who knows!).

## What is a System?

In engineering there came a point where machines started to evolve from being purely mechanical. With the advent of electricity and electric motors, there became a need to use a common framework to control system containing both electrical and mechanical elements. However, before we could control such a system, we need a common way of modelling it. To this end, the idea of systems & control theory started to come about. There are lots of formal maths that surround this topic, however we are only going to lightly touch on that here.

Typically we can thing of a system as being anything either electrical or mechanical or both, that takes some input that we can model and produces some output that we can also model. Usually the model of a system would be some mathematical function where we write the output as a function of the input. With expressions for the input and output we can define something called the transfer function for the system. This is basically a single mathematical expression that defines the characteristic of the system we are working with. Again, not getting into the details but this function is labelled `G(s)` and is the Leplace transform of the input expression divided by the Leplace transform of the output expression. If you feel comfortable looking into the maths behind this, I suggest researching the topic on your own. I can highly recommend Modern Control System by Dorf & Bishop for this topic.

For this discussion I only want you to be aware that a highly complex system can be broken down into a single function that defines it's behaviours and in control engineer we would refer to it via it's transfer function. In terms of control theory, we often refer to the system being controlled as the "plant". We would also often present it in block diagram for like below.

![system block](../images/control_theory/system_block.png)

The above just simply represents some input to the system, being fed into the system and providing an output. It should be noted that transfer functions can be simple or complex and they can be nested. However, no matter how complex, they can always be boiled down to a single block in a control diagram. It should also be noted that you don't necessarily need to derive the transfer function for a complex system to control it. It is possible to use maths to analytically come up with the best control scheme for a system, but there are other methods, this will become clear later.

&nbsp;

---

&nbsp;

## What is Control Theory?

Considering the above diagram, we have what we would call an open loop system. This means that the input and outputs are totally independent. We feed some input to the plant, it does something, we get and output, but the system doesn't "know" anything about the out or the state surrounding the plant. A good example of a system that behaves like this is our stepper motor. The stepper doesn't know anything about it's state, we just give it an input and it goes to it's output. Due to the engineering of stepper motors we can trust that for the most part this system can be controlled in open loop. Let's consider another real world example of where open loop control might fall down. Consider a cruise control system in a car, we are on a straight flat road travelling at 100km/h. We trigger the cruise control and the system now holds the throttle (the input) at it's current level. This results in the car continuing to travel at the same speed (the output) of 100km/h. Now, lets consider what will happen when we approach a hill in the road. At the point, gravity will act against the car requiring the car to accelerate to compensate for gravity pushing it back down the hill. However, remember, our input doesn't know anything about our output. So the car will begin to slow down and the throttle position won't change at all.

The above example is missing something, we call it feedback. What the cruise control system was missing was the information that the the car has slowed down below the target speed and based on how much it had slowed, it needed to know that it should increase it's throttle to maintain speed. In control theory we would call this type of system a closed loop control system, other terms used are a feedback control loop or simply feedback loop. In these loops we usually have a set point (the desired speed of the car), and output (actual speed of the car), some form of sensor to provide feedback (the cars speedometer) and an error signal (the difference between the desired and actual speed). It should be noted that in these closed loop systems, the input to the plant becomes the error signal from the summation block in the diagram below.

![feedback loop](../images/control_theory/feedback_loop.png)

Now that we have some working model of how a feedback system works we are in a far better state that we were with the open loop case. However, we are still missing a key ingredient to make the system do what we want. We are assuming that by piping the output of the system back to the input and feeding the error back into the system that we will get the response we desire. This is a fairly large assumption and for the majority of cases this will not work. There are some system that just so happen to be naturally stable and will respond fine to this situation, but that is not the general rule. Most sufficiently complex electromechanical systems are not going to be independently stable. The last missing piece from our system is something called compensation. There are many different types of compensators but one of the most widely used ones, the PID controller, is where we will focus our attention in the next section. To add compensation to a system, we need to insert something between the error signal and the input of the system. What this will do is figure out what the best input should be to the plant to minimise the error signal as much as possible. With some clever maths, these compensators can drastically change the characteristics of a plant and are extremely powerful. So much so that the basics of these system has remained unchanged for 100 years (that's right you don't need computers for these, you can build fully analog compensators...wild!).

Before we move on, as a final note, have a look at the plot below. It is a common type of system response plot that you might see. This should help give some intuition as to how our system will respond when we are trying to get it to settle to some set point. We will start at some value, in this case 0, we will command the system to reach a value, in this case 5. As the system runs, it will begin below the set point with a large error value. This error value will be fed into the plant demanding a large response. The system will respond and end up overshooting the target by a decent margin. At this point the error will turn negative because we have overshot the target and now we need to bring it back down again, so we will change the input of the plant to compensate. This continues for a time until as we see we settle down to a steady state with little or no error. This type of second order system response is really common all over engineering and you will see it in some many different systems. Have you ever noticed in a home heating system how when you change the temperature it sometimes ends up going higher or lower than you wanted first before settling down to the value you wanted? That is because it is doing the exact same thing as I talked about above (and is probably use a PID controller to do it too!).

![system response](../images/control_theory/system_response.png)

&nbsp;

---

&nbsp;

## How Does a PID Controller Work?

Allllllll the PID theory