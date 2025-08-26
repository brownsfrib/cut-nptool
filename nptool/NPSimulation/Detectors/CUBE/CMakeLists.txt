add_library(NPSCUBE SHARED  CUBE.cc)
target_link_libraries(NPSCUBE NPSCore ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} ${NPLib_LIBRARIES} -lNPCUBE)
