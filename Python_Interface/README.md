# Python Interface

## Getting Started

### Prerequisites
Some additional libraries are required to allow the program to run these are:

- [python 3.7](https://www.python.org/downloads/release/python-370/) is required to run the Python API
- The [pyserial](https://pyserial.readthedocs.io/en/latest/pyserial.html) library is used to provide the backends support to connect to the Aurdino.
- The [time](https://docs.python.org/3/library/time.html#module-time) library is used to provide the timing and delays in the python script.
- [MIDO](https://mido.readthedocs.io/en/latest/#) is required for working with MIDI messages and ports

### Building
To build the code download the python Python API and run through ether the command prompt or an IDE such as Spyder.

## Using the `jukebox_testing.py` utility

A small, hacky, but helpful utility to aid in testing by making it easier to send MIDI data to the Arduino and read any messages it sends back. To use:
1. Set `Raspberry_Pi/` as the current directory.
2. Ensure the Serial port is correct in `jukebox_testing.py`. Your serial port can be found by `Arduino -> Tools -> Port` or in the bottom right of your Arduino sketch console. 
3. Enter an interactive python session (by executing `python3` in your command line).
4. Run `from jukebox_testing import *`.
5. Use as described by the prompts given.

### Functions Description  
There are two primary functions provided by the utility. One to send a single MIDI message and one to play a MIDI file. Their usage is explained in the utility and below:

- Msg(msg) where msg is a mido message object e.g msg = mido.Message('note_on', note=60, velocity=64). The use the command first create your message then use sendMsg(msg) to send the newly created note to the recorder and also print anything the arduino sends to the command line.
- To play a MIDI file use the playFile(filename) command. The working directory must  be the music_makers repo root and the MIDI file must be saved in  midi_examples. Specify filename as a string and the function will print anything the arduino sends to the command line.

Help at anytime can be found by using the command showHelp().

## Creating `.mid` Files

The [examples](midi_examples) folder contains some example MIDI files. You can create your own too.

The MIDI files were created using Aria Maestosa, an open-source (GPL) MIDI sequencer/editor (https://ariamaestosa.github.io/ariamaestosa/docs/index.html). The system uses the MIDI numbering whereby MIDI note 60 corresponds to Middle C, also known as C4 which has a fundametnal frequency = 261.63 hz (https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies). To compose a simple tune for the system, download a MIDI sequencer/editor (Aria Maestosa runs on Mac OS X, Windows and Linux/Unix), select the tempo for the composition, add the notes to the sequencer, and export the track as a MIDI file. 

## The Raspberry Pi
### Connecting to the Raspberry Pi

The Raspberry Pi 4B, nicknamed <code>jukebox</code>, has been configured such that it can run headless over WiFi. Furthermore, forwarding has been configured such that any network connected to the <code>eth0</code> port will forward to the <code>wlan</code> port (i.e: Connecting the ethernet port to the University network will allow internet access over the broadcasted WiFi).

The Raspberry Pi automatically broadcasts on the SSID: <code>jukebox</code> when it boots up, the password to connect to the wireless hotspot is <code>password</code>.

The Raspberry Pi is enabled to support SSH (Secure Shell) and VNC (Virtual Network Computing).

### SSH

To launch a secure shell connection, open a new terminal and use the command:
<br></br>
<code>ssh pi@jukebox.wlan</code> or <code>ssh pi@10.20.1.1</code>
<br></br>
The Raspberry Pi uses <code>port 22</code> (default) for SSH. You will then be prompted to enter the Raspberry Pi's local password, which is <code>password</code>. 

### VNC

To connect to the GUI, you can use the <a href="https://www.realvnc.com/en/connect/download/viewer/">REALVNC Viewer</a>. Once installed, simply enter the IP address of the Raspberry Pi (<code>10.20.1.1</code>) and then the local system username (<code>pi</code>) and password (<code>password</code>) when prompted.

