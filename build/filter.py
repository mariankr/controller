import subprocess
import sys
if __name__ == "__main__":
    proc = subprocess.Popen(sys.argv[1:], stdout=subprocess.PIPE, shell=True)
    while proc.poll() is None:
        output = proc.stdout.readline().decode('Windows-1250')
        if output:
            print(output.replace("../", "").strip())
