# SDL Simulator for UOSM Dashboard

See the UOSM-Dashboard's repo for details about the dashboard application.

## Usage

### Get the project

Clone the PC project and the related sub modules:

```
git clone --recursive git@github.com:UOSupermileage/UOSM-Dashboard-SDL.git
```

### If Using Windows
You will need `WSL2` to run this project on Windows.
https://learn.microsoft.com/en-us/windows/wsl/basic-commands

Once WSL is installed, you can follow allong with the linux instructions.

You will need to add WSL in your CLion toolchains.

### Install SDL
You can download SDL from https://www.libsdl.org/

```bash
# Linux
sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev

# MacOS
brew install sdl2
```
