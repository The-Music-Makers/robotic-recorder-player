The Raspberry Pi 4 B has been configured such that it can run headless over WiFi.

### Connecting to the Raspberry Pi

The Raspberry Pi automatically broadcasts on the SSID: <code>jukebox</code> when it boots up, the password to connect to the wireless hotspot is <code>password</code>.

The Raspberry Pi is enabled to support SSH (Secure Shell) and VNC (Virtual Network Computing).

### SSH

To launch a secure shell connection, open a new terminal and use the command:
<br></br>
<code>ssh pi@jukebox.wlan</code> or <code>ssh pi@10.20.1.1</code>
<br></br>
The Raspberry Pi uses <code>port 22</code> (default) for SSH. You will then be prompted to enter the Raspberry pi's local password <code>password</code>. 



