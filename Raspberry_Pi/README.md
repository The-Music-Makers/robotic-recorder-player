The Raspberry Pi 4B has been configured such that it can run headless over WiFi. Furthermore, forwarding has been configured such that any network connected to the <code>eth0</code> port will forward to the <code>wlan</code> port (i.e: Connecting the ethernet port to the University network will allow internet access over the broadcasted WiFi).

### Connecting to the Raspberry Pi

The Raspberry Pi automatically broadcasts on the SSID: <code>jukebox</code> when it boots up, the password to connect to the wireless hotspot is <code>password</code>.

The Raspberry Pi is enabled to support SSH (Secure Shell) and VNC (Virtual Network Computing).

### SSH

To launch a secure shell connection, open a new terminal and use the command:
<br></br>
<code>ssh pi@jukebox.wlan</code> or <code>ssh pi@10.20.1.1</code>
<br></br>
The Raspberry Pi uses <code>port 22</code> (default) for SSH. You will then be prompted to enter the Raspberry Pi's local password, which is <code>password</code>. 

### VNC

To connect to the GUI, you can use the <a href="https://www.realvnc.com/en/connect/download/viewer/">REALVNC Viewer</a>. Once installed, simply enter the ip address of the Raspberry Pi (<code>10.20.1.1</code>) and then the local system username (<code>pi</code>) and password (<code>password</code>) when prompted.

