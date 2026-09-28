# Setting Up a Raspberry Pi from Scratch and Adding a Basic 0.96-inch OLED

This guide assumes that Raspberry Pi OS has already been installed successfully and SSH access is working.

## 1. Update the System

```bash
sudo apt update
sudo apt full-upgrade -y
sudo reboot
```
Set the timezone:
```bash
sudo timedatectl set-timezone Europe/Athens
```
## 2. Install Basic Tools
```bash
sudo apt install -y git
sudo apt install -y curl
sudo apt install -y wget
sudo apt install -y vim
sudo apt install -y nano
sudo apt install -y unzip
```
## 3. Check Python
```bash
python3 --version
```
If Python, pip, and the virtual environment tools are not installed:
```bash
sudo apt install -y python3 python3-pip python3-venv python3-dev
```
## 4. Enable I²C
```bash
sudo raspi-config
```
and go to Interface Options → I2C → Enable. Then reboot. <br>
After reboot, verify that the I²C device exists:
```bash
ls -l /dev/i2c-1
```
## 5. Detect the OLED on I²C
```bash
sudo i2cdetect -y 1
```
The OLED should appear at 0x3c

## 6. Create the Project Directory
```bash
mkdir -p ~/projects/oled
cd ~/projects/oled
```

## 7. Create a Python Virtual Environment
```bash
python3 -m venv .venv
source .venv/bin/activate
```

## 8. Install Required Adafruit Libraries
```bash
pip install --no-cache-dir adafruit-lgpio

pip install --no-cache-dir --no-deps adafruit-blinka

pip install --no-cache-dir adafruit-platformdetect

pip install --no-cache-dir RPi.GPIO

pip install --no-cache-dir --no-deps adafruit-circuitpython-ssd1306

pip install --no-cache-dir --no-deps adafruit-circuitpython-busdevice

pip install --no-cache-dir --no-deps adafruit-circuitpython-typing

pip install --no-cache-dir --no-deps typing_extensions

pip install --no-cache-dir --no-deps adafruit-circuitpython-framebuf

pip install --no-cache-dir --no-deps Adafruit-PureIO
```
## 9. Install the OLED font
```bash
cd ~/projects/oled
```
## 10. Create the OLED Test Program
```bash
nano ~/projects/oled/test_oled.py
```
and copy:
```python
import board
import busio
import adafruit_ssd1306

i2c = busio.I2C(board.SCL, board.SDA)

oled = adafruit_ssd1306.SSD1306_I2C(
    128,
    64,
    i2c,
    addr=0x3C
)

oled.fill(0)
oled.text("HELLO!", 0, 0, 1)
oled.text("Adafruit OK", 0, 20, 1)
oled.show()

print("OLED DONE")
```
Run it with:
```bash
python3 test_olded.py
```
