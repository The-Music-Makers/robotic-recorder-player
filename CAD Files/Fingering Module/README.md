# Music Makers

## Fingering Module


<p float="left">
  <img src="../../Documents/placeholder_image.png" height="300" />
</p>

You will need the following prepared parts (some may require printing) in order to build the Fingering module.

1) Recorder base frame stand [top](recorder_base_frame_stand_top_slider.stl) and [bottom](recorder_base_frame_stand_bottom.stl). This consists of two separate components which will need printing individually.

2) A 350mm x 250mm x 20mm piece of wood (plywood is ideal) used to mount the fingering module components and act as a base frame for the recorder robot. This will be placed in the recorder base frame stand.

Most printers should be able to print the parts, with all parts being able to fit on a 150mmx140mm build plate.

On an Ultimaker 2+, we achieved good results with the following settings:

- layer height: 0.2mm
- wall thickness: 1.5mm
- infill density: 20%
- infill pattern: grid
- print speed 80 mm/s
- supports where required for the recorder base frame.

Parts have been printed using PLA and TPU (TPU for the fingerpads) all with good results. The print was not affected very much by the print settings. However, printing slower and with smaller layer height will improve the print quality. Tree supports where found to be easier to remove from prints in post processing although normal supports can be used instead. 


## Bill of materials
The robot recorder player relies on readily available hobby electronics components. The components can be changed for other makes or types but changing the components will have an effect on how each module operates, for some types of woodwind instruments changes may be needed to allow the modules to operate as desired. Links have been provided for UK suppliers for the components used to create the module, these suppliers are not the only source of the components and they can be bought from other suppliers or locations. 

You will need the following components:

### General

- 1 off Arduino mega was used for this project although any Arduino can be used [UK](https://www.amazon.co.uk/ELEGOO-Controller-ATmega2560-ATMEGA16U2-Compatible/dp/B06XKMZ3T9/ref=sr_1_1_sspa?dchild=1&keywords=Arduino+mega&qid=1614255721&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzM1FEMENJVzdIVEk4JmVuY3J5cHRlZElkPUEwNTU1OTQ0MjQ4N0QxTTZZNFdDUCZlbmNyeXB0ZWRBZElkPUEwMzI4MTAzMTlYOUw0TUpKUThYMiZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=)

- 12V battery is needed to power the modules [UK](https://www.amazon.co.uk/SUNPADOW-Battery-Airplane-Quadcopter-Helicopter/dp/B08Q79M7QB/ref=sr_1_2?dchild=1&keywords=12V+LIPO&qid=1614255912&sr=8-2)

- 10 off JF-0530B solenoids [UK](https://www.amazon.co.uk/Rtengtunn-JF-0530B-Push-Pull-Gangbei-0530B-Electromagnet/dp/B08291L2XL/ref=sr_1_7?dchild=1&keywords=JF-0530B&qid=1614263171&sr=8-7)

- 1 off 3-D printed six solenoid container body (for finger tune hole solenoids)

- 1 off 3-D printed single solenoid container body (for thumb tune hole solenoid)

- 1 off 3D printed four solenoid container body (for two double tune hole solenoids)

- 10 off M3 nut and bolt, 1 for each solenoid to add tension and keep secured in position [UK](https://www.amazon.co.uk/Screw-Bolts-Stainless-Steel-340pcs/dp/B08RRW6B3H/ref=sr_1_12?dchild=1&keywords=M3+nut+and+bolt&qid=1614263398&sr=8-12)


The following are needed per double tune hole solenoid use (two double tune holes in total):

- 1 off 3D printed medium fingerpad (for larger hole in the double tune hole)

- 1 off 3D printed small fingerpad (for smaller hole in the double tune hole)

- 1 off 3D printed extension arm (one for each solenoid fingerpad)


The following are needed per-solenoids used:
- 3-D printed solenoid fingerpads

- TIP120 Darlington Transistor [UK](https://www.amazon.co.uk/BOJACK-Epitaxial-Transistor-Darlington-Transistors/dp/B08D8SJPCG/ref=sr_1_4?dchild=1&keywords=TIP120+Darlington+Transistor&qid=1614263478&sr=8-4)

- 1K Ohm Resistor [UK](https://www.amazon.co.uk/sourcing-map-Metal-Resistors-Tolerances/dp/B07LGM23Y4/ref=sr_1_10?dchild=1&keywords=1K+Ohm+Resistor&qid=1614263525&sr=8-10)

- 1N4001 Diode [UK](https://www.amazon.co.uk/ExcLent-100Pcs-1N4001-50V-Diode/dp/B07J3ZT55G/ref=sr_1_8?dchild=1&keywords=1N4001+Diode&qid=1614263550&sr=8-8)


### Build instructions

#### Fingering Module
<p float="left">
  <img src="../../Documents/singleSolenoidWiringDiagram.PNG" height="300" />
</p>

1. Print out the recorder base frame, six solenoid container, body single solenoid container body and two mounting vee-frames
supports and remove any other stray parts from the printing process
2. Insert a M3 nut into the internal side wall of the 3D-printed six solenoid container body, repeat this for each
location where a solenoid is required for tune hole fingering. 
3. Push the solenoid wires through the holes at the rear of the container body and insert a solenoid into each seating position (one for each tune hole across the recorder), making sure that the solenoid plunger can freely move up and down. 
4. Insert a M3 bolt through solenoid container and through the M3 nut to tighten the solenoids into position. Only a light finger tight is required. If the plunger does not move freely and gets stuck carefully un-tighten the bolt and move the solenoid until the plunger moves freely.
5. Repeat the above for each solenoid location in the six seater container body, the single container body and four seater container body
6. connected solenoid circuit following the wiring diagram 
 -   connect one solenoid contact to the common power rail.
 -   connect the other solenoid contacts to the middle pin (pin C) of the darlington transistor.
 -   connect the diode between the two solenoid contacts, make sure that the
white stripe on the diode is on the negative side of the connection. The
diode acts as a power snubber preventing power spikes from the solenoid
damaging the other electrical components.
-   connect the resistor to pin B of the transistor then to one of the digital
ports of the arduino, the port depends on the tune hole the solenoid seals
down on, currently the thumb tune hole is to port 1 on the arduino.
-   connect pin E of the transistor to the common ground rail.
7. To attach the six solenoid container body to the recorder base frame insert a M3 nut in to the slot on either
side of the six solenoid container body, then align the container body to the frame and insert
the M3 bolt through the available holes. Finger tighten the bolt. Feel free to add padding between these contact points to reduce any vibration that may be seen during play. 


### Acknowledgements
The page has been 'forked' from <b>Andrew Henry's</b>, GitLab whose <b><a href="https://gitlab.com/Andrew_Henry/automated-guitar">automated guitar player</a></b> was the inspiration for this project. 


