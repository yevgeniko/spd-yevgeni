import os
import subprocess

def build(directory):
    os.chdir(directory)
    subprocess.run(['qmake'])
    subprocess.run(['make', 'clean'])
    subprocess.run(['make', '-j8'])

def open_terminal_in_directory(directory):
    os.chdir(directory)
    subprocess.Popen(['gnome-terminal', '--working-directory=' + directory])

def clean(directory):
    os.chdir(directory)
    subprocess.run(['make', 'clean'])


def main():
    root_dir = os.getcwd()
    dirs = [
        'tests/server', 
        'tests/sensors',
        'tests/sensors2',
        'tests/sensors3',
        'tests/sensors4',
        'tests/client'
    ]

    for directory in dirs:
        full_dir = os.path.join(root_dir, directory)
        build(full_dir)

    for directory in dirs:
        full_dir = os.path.join(root_dir, directory)
        open_terminal_in_directory(full_dir)

    input("Press Enter after you've executed and closed all terminal sessions...")

    for directory in dirs:
        full_dir = os.path.join(root_dir, directory)
        clean(full_dir)

if __name__ == "__main__":
    main()
