# SpoolScale
3D Filament Spool Scale / Meter Indicator

This is an Arduino powered scale which holds your 3D filament and calculates approximately how much filament you have remaining on your spool in meters. It's fairly accurate (+/- 1 meters when whole spool is on the scale & +/- 5 meters when the printer is pulling on the filament) Closer to the end of the spool, it will get much less accurate as the pull force of the extruder and the spring force of the tighter coiled filament becomes greater than the weight of the spool itself. 

The 3D printed things can be found here: 


How to Calibrate Your Scale

- In the setup routine change set_scale(432) to set_scale() with no parameter and upload.
- Place a known weight on the scale and using the Arduino IDE serial monitor copy the numbers which are similar to each other (i.e in the same range), I would suggest 10 to 20 values and average them togther.
- Divide the result in step 2 to your known weight. You should get about the parameter you need to pass to set_scale (i.e set_scale(432)).
- Adjust the parameter in step 3 until you get an accurate reading.
- 
For a more indepth look at how to communicate with the HX711 sheild please checkout the libraries readme file: https://github.com/bogde/HX711
