# Cryogen
Multiplayer 3D shooter game, very simple, just spawn people in a map and let them shoot each other to death  
An exercise in graphics, networking, and C++  

## first things first:
- [x] set up all the libraries and build (target native windows)
- [x] add a player entity (make it a simple 3d cube to begin with)
- [x] add networking
- [ ] decentralize with docker and github CI/CD
- [ ] write documentation 
- [ ] build out the map and mechanics  

## usage
```bash
make build
```
as of development, here is the current way to start a game:  
terminal one:  
```bash
./main.exe insert_port1 insert_port2 insert_your_lan_ipv4
```
terminal two:  
```bash
./main.exe insert_port2 insert_port1 insert_your_lan_ipv4
```
an example of a working boot:  
```bash
./main.exe 8080 8081 127.0.0.1
```
(note: currently lan support is still a work in progress, but it does run on local)
