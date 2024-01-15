# Doom-Like
Multiplayer 3D shooter game, very simple, just spawn people in a map and let them shoot each other to death  
An exercise in graphics, networking, and C++  

## first things first:
- [ ] set up all the libraries and build (target native windows)
- [ ] add a player entity (make it a simple 3d cube to begin with)
- [ ] add networking
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
./main.exe 8080 8081
```
terminal two:  
```bash
./main.exe 8081 8080
```