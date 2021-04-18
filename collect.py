import subprocess
import random

for i in range(0, 10):
    traceFile = open("Traces/trace" + str(i) + ".txt", "w")
    process = subprocess.Popen(["/home/jessicalam/Desktop/pin-3.17-98314-g0c048d619-gcc-linux/pin",
        "-t", "PinTracer/obj-intel64/PinTracer.so",
        "-o", "./out",
        "--",
        "PinTracerWrapper/wrapper"],
        stdin=subprocess.PIPE,
        stdout=traceFile,
        stderr=subprocess.DEVNULL)
    first = random.randint(-180, 180)
    second = random.randint(-180, 180)
    process.stdin.write(str.encode(str(first) + " " + str(second)))
    process.communicate()
    process.stdin.close()
