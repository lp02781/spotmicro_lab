# Importing Libraries
import serial
import time
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    arduino.flush()
    time.sleep(0.3)
    data = arduino.readline().decode('utf-8').rstrip()
    arduino.flush()
    return data
while True:
    num = "0.15/0.22/0.34/0.44/0.54/0.63/0.73/0.86/0.98/0.10/0.11/0.12\n"
    value = write_read(num)
    print(value)
