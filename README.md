# Ultrasonic-sensor-
Well I'm making a radar sensor as its supposed to be pretty easy and is my first ever project. My goal rn is to build a rover connect it an ai model .
The radar I'm planning to make will be later mounted on the rove and if things go well I might add a camera as well .
Now how will the radar work ?
The arduino will turn the servo motor (2 degrees at a time) and as the ultrasonic sensor is mounted on the the servo motor it acts as an head .
One of the silver cylinders on the sensor is a speaker. It blasts a high-frequency sound wave (too high for human ears to hear) outward.
If that sound wave hits an object, it bounces backward.
The other silver cylinder is a microphone. It waits to hear the echo of that bounce.
The Arduino acts as a stopwatch. It measures exactly how many microseconds it took for the sound to leave the speaker and return to the microphone. Because we know the speed of sound in air, the code uses a simple math formula (distance = (time × speed)/2) to calculate exactly how far away the object is.
​Now the Arduino knows two things:
​Where it was looking (the angle of the servo).
​How far away an object is in that direction (from the sensor's math).
It instantly updates the tiny OLED screen with those numbers, and simultaneously blasts those numbers over the HC-05 Bluetooth module to my phone.
Then the Arduino Bluetooth Controller app reads those numbers and draws a green dot on the screen, creating the classic "radar" visual! Then, the servo turns another 2 degrees, and the whole loop starts over.
