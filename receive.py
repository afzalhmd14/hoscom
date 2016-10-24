from time import sleep
import serial
import sys


file_name="output/"+str(sys.argv[1])
ser = serial.Serial('/dev/ttyACM0', 115200,timeout=5) # Establish the connection on a specific port
f=open(file_name,'w')
i=ser.read(1)
while True:
	try:
		if i!=None:
			f.write(i)
		i=ser.read(1)
	except serial.SerialException:
		continue