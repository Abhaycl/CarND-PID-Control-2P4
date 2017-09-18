# PID Controller Project Starter Code

A PID (Proportional, Integral, Derivative) controller is a control loop feedback controller which is widely used in different control systems.

<!--more-->

[//]: # (Image References)

[image1]: /build/result.jpg "Sample final score"
[image2]: /build/result1.jpg "Sample final score"

#### How to run the program

```sh
1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./PID
6. and run the simulator and select Project 4: PID Controller
```

The summary of the files and folders int repo is provided in the table below:

| File/Folder               | Definition                                                                                  |
| :------------------------ | :------------------------------------------------------------------------------------------ |
| src/json.hpp              | Various definitions.                                                                        |
| src/PID.cpp               | Initializes variables, updates errors, error totalizer.                                     |
| src/PID.h                 | Definition of the package of pid.                                                           |
| src/main.cpp              | Has several functions within main(), communicates with the Term 2 Simulator receiving data  |
|                           | measurements, calls a function to run the PID (Proportional, Integral, Derivative), these   |
|                           | all handle the uWebsocketIO communication between the simulator and it's self.              |
|                           |                                                                                             |
| src                       | Folder where are all the source files of the project.                                       |
| build                     | Folder where the project executable has been compiled.                                      |
|                           |                                                                                             |


---

# How it was tuned

Generally speaking, it requires to set Kd and Ki to 0 and gradually increase Kp before the car runs with stable and consistent oscillations. This value of Kp and the oscillation period can be used to calculate optimal pid controller parameters by the method. Parameters was able to drive car around the track but with a lot of wobbling, that is why parameters were further tuned manually after several rounds of trial and error.

The same process was applied for different speed, so different PID parameters were found for different speed. The results were linearized in order to make the parameters automatically tune with the car speed variation.

![Final score][image1]

---

#### Discussion

Parameterization of the tuning could be improved to obtain better results.
