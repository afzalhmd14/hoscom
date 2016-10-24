f = open("2", "rb")
try:
    byte = f.read(1)
    while byte != "":
        # Do stuff with byte.
        print byte
        byte = f.read(1)
finally:
    f.close()