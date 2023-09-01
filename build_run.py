import os
import subprocess
import time

def build(directory):
    os.chdir(directory)
    subprocess.run(['qmake'])
    subprocess.run(['make', 'clean'])
    subprocess.run(['make', '-j8'])

def run(directory):
    os.chdir(directory)
    return subprocess.Popen(['./qmake'])

def clean(directory):
    os.chdir(directory)
    subprocess.run(['make', 'clean'])

def kill_qmake_processes():
    subprocess.run(['pkill', 'qmake'])

def main():
    root_dir = os.getcwd()
    # The order of directories
    dirs = [
        'tests/server',  # Start with server
        'tests/sensors',  # Then sensors
        'tests/client'   # Finally, client
    ]

    for directory in dirs:
        full_dir = os.path.join(root_dir, directory)
        build(full_dir)

    server_process = run(os.path.join(root_dir, dirs[0]))
    time.sleep(2)
    sensor_process = run(os.path.join(root_dir, dirs[1]))  # Now sensors are started after the server
    time.sleep(2)
    client_process = run(os.path.join(root_dir, dirs[2]))  # Client is started last

    # Wait for the client to finish before killing other processes
    client_process.wait()
    kill_qmake_processes()

    for directory in dirs:
        full_dir = os.path.join(root_dir, directory)
        clean(full_dir)

if __name__ == "__main__":
    main()