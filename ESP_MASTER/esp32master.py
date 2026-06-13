from machine import I2C, Pin
import ssd1306
import time

i2c = I2C(0, scl=Pin(22), sda=Pin(21))
oled = ssd1306.SSD1306_I2C(128, 32, i2c)

buf = bytearray(12)

while True:
    try:
        time.sleep(0.1)
        i2c.readfrom_into(8, buf)
        raw = buf.decode().strip()

        # parse
        if raw.startswith("DIST:"):
            val = raw.split(":")[1]
        else:
            val = "ERR"

    except:
        raw = "ERROR"
        val = "ERR"

    # ---------- SHELL OUTPUT ----------
    print("----------------------")
    print("ULTRASONIC NODE DATA")
    print("Raw   :", raw)
    print("Value :", val, "cm")
    print("----------------------\n")

    # ---------- OLED DISPLAY ----------
    oled.fill(0)
    oled.text("Distance", 0, 0)
    oled.text(val + " cm", 0, 12)
    oled.show()

    time.sleep(2)