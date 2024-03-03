# How to develop using Cryogen!

## Dependencies
#### Ubuntu 20.04:
```bash
sudo apt install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev libglfw3 libglfw3-dev make 
```
#### Note for Windows:  
Cryogen primarily runs on Linux, but Windows users can use WSL to run Cryogen, this will require a few extra steps for setup.  
##### Requirements:  
- Install [XLaunch](https://sourceforge.net/projects/vcxsrv/)  
- In XLaunch Settings have the following:  
    - Multi-Window, Display=0  
    - Start No Client  
    - Clipboard=True, Primary Selection=True, Native OpenGL=False, Disable Access Control=True  
    - Then in WSL: 
```bash
export DISPLAY=$(awk '/nameserver / {print $2; exit}' /etc/resolv.conf 2>/dev/null):0
export LIBGL_ALWAYS_INDIRECT=0
```

## Usage
- todo, documentation on how to use the resource managers and other features that will later be implemented