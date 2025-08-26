Uses geant4 10.07.00, ROOT 6.24.02, gcc 9.3

Source the .sh script to start your environment. Modules will be loaded and nptool is already compiled aginst them.

To execute a simulation for CUBE, call npsimulation -D CUBE.detector -E eventGenerator.file -B geantmacro.mac -O outputName

The outputName will be stored in $NPTOOL/Outputs/Simulation

If you want a basic skeleton example of how to analyze the simulation, type 'npp CUBE'
This will take you to an nptool project directory that has an example macro, among other things



