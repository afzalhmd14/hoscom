import time
import serial
import os
import sys

file="input/"+str(sys.argv[1])
ser = serial.Serial('/dev/ttyACM1', 115200,timeout=5) # Establish the connection on a specific port
time.sleep(0.1)
f = open(file, "r")
b=os.path.getsize(file)
abc='b'
start=time.time()
u=0
byte = f.read(1)
k=0
while byte!="":
	i=0
	if byte!=None:
		while(i==0):
			
			
			if k>=0 and k<2:
				i=ser.write(abc)
				time.sleep(1)
				k=k+1
			else:
				time.sleep(0.01)
				i=ser.write(byte)
				byte = f.read(1)
		if(u%(1024)==0):
			done_percent=100*float(u)/b
			diff=time.time()-start
			if diff is not 0:
				print int(done_percent)," %_ done. (",(u/1024),"KB), Time elapsed: ",diff," seconds @ ",(float(u/(1024*(diff))))," KB/s"
				
	u+=1

end=time.time()
print "Time taken to transfer ",(b/1024)," KB is",(end-start), "secs @ ",(b/(1024*(end-start))), " KB/s."
f.close()
ser.close()