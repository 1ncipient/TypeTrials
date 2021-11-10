# CS 3307 Group Project

All source, header, and build files are located in this zip archive. The executable TypeTrails was also pre-built on the Gaul server, so executing that alone should work. 

## Building on Gaul Server
TypeTrails.pro was also tested to work on Western's Gaul server. To build and run on the server, please execute the following commands:
```
qmake-qt5
make
./TypeTrails
```

## Building on MacOS
If running in a MacOS environment where Boost and Qt were both brew installed, simply adding the line `INCLUDEPATH += /usr/local/include` to TypeTrials.pro will allow you to build and run it using the following commands:
```
qmake
make
./TypeTrails
```