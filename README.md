# DLP_UV_Radiometer

This is a very simple, low cost, bare bones DLP UV Radiometer that measures the UV output of a DLP projector in mW/cm^2.  It is a useful tool for any DLP UV resin printer as it helps by measuring the UV output and by knowing your UV output and the Critical Energy required to properly cure a UV resin, the end user can calculate how many seconds exposure he or she will need.

I developed this with the initial intent to use it to characterize [MakerJuice UV Resins](http://www.makerjuice.com/) and decided it might be prudent to allow others to build this too and expand on it.

Many UV resin manufacturers supply the Critical Energy required to properly cure their resins at a given layer height.  This number is typically supplied in mJ/cm^2.  If the end user knows their DLP UV output in mW/cm^2, they can simply apply the following forumla to find out how many seconds exposure they will need for their particular setup:

Seconds Exposure = (mJ/cm^2) / (mW/cm^2)

Then simply set your layer height and exposure time and the end user should be in the ballpark (or closer) for their exposure time.

As written, the sensor is wired up to an Arduino Nano, which is in turn plugged into either a computer or a smartphone with a USB-OTG cable.  To use it, simply place the sensor at the appropriate distance from the DLP light source and either use the Ardino IDI serial terminal to obtain the output reading or plug it into your smartphone using a USB-OTG cable and run something like DroidTerm to view your results.

# Hookup Guide

![Wiring](/Arduino/ML8511_UV_Hookup.png?raw=true "Sparkfun Redboard and ML8511 Sensor")

# Development Links

http://makerhive.proboards.com/thread/641/low-cost-uv-radiometer

https://learn.sparkfun.com/tutorials/ml8511-uv-sensor-hookup-guide

http://makerhive.proboards.com/thread/1045/help-circuit-schematic

https://goo.gl/photos/gHvPpna38RmeMD9JA

https://goo.gl/photos/hdz6ypwXF4V1uDZu9

https://goo.gl/photos/mLwZ4yQtefcNKiSG6


# License

CC-SA (see cc-sa-license.txt)