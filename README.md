# Physics Based Sphere Movement [C++] [Unreal Version: 5.0.1]
An approach to pure physics based sphere movement using C++ in Unreal Engine.
## Key Features:
### Movement
Pure physics movement by WASD keys in direction where player is looking. Ball can Jump by Space Bar and dash by Left Shift Key
### Magnetism
Level Ball Bearings are attracted to Goals by tolerated distance.
### Debugging HUD
Using UE_LOG or GEngine->AddOnScreenDebugMessage for Debugging purposes can be real pain. So this project has DebugHUD which lets you see all the values specified in BallBearingHUD (derived from DebugHUD) in realtime on your screen without the worrying about print keys and scrolling in console!
### Main Properties exposed to Blueprints
Properties like Move Force, Jump Force, Dash force, Magnetism are exposed to Level Designers through Blueprints! You can directly edit them by deriving Blueprints from BallBearingGoal, BallBearing and PlayerBallBearing respectively.

This code base was used to achieve the following game:
![Screenshot (25)](https://user-images.githubusercontent.com/106145602/207292085-848d54de-2943-4dd4-a4ea-b9dbd84af88f.png)

![Screenshot (24)](https://user-images.githubusercontent.com/106145602/207291904-97a59c0d-f445-4c8b-928b-a17188ef3219.png)

![Screenshot (23)](https://user-images.githubusercontent.com/106145602/207291728-19bcd38b-a0d8-4b8b-81cb-0f58d7f78179.png)
