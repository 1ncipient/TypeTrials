All source, header, and build files are located in this zip archive. The executable TypeTrials was also pre-built on the Gaul server, so executing that alone should work. 

## Building on Gaul Server
TypeTrials.pro was also tested to work on Western's Gaul server. To build and run on the server, please execute the following commands:
```
qmake-qt5
make
./TypeTrials
```

## Building on MacOS
If running in a MacOS environment where Boost and Qt were both brew installed, simply adding the line `INCLUDEPATH += /usr/local/include` to TypeTrials.pro will allow you to build and run it using the following commands:
```
qmake
make
./TypeTrials
```