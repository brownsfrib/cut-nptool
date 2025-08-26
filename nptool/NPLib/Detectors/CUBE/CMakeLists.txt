add_custom_command(OUTPUT TCUBEPhysicsDict.cxx COMMAND ../../scripts/build_dict.sh TCUBEPhysics.h TCUBEPhysicsDict.cxx TCUBEPhysics.rootmap libNPCUBE.dylib DEPENDS TCUBEPhysics.h)
add_custom_command(OUTPUT TCUBEDataDict.cxx COMMAND ../../scripts/build_dict.sh TCUBEData.h TCUBEDataDict.cxx TCUBEData.rootmap libNPCUBE.dylib DEPENDS TCUBEData.h)
add_library(NPCUBE SHARED TCUBESpectra.cxx TCUBEData.cxx TCUBEPhysics.cxx TCUBEDataDict.cxx TCUBEPhysicsDict.cxx )
target_link_libraries(NPCUBE ${ROOT_LIBRARIES} NPCore) 
install(FILES TCUBEData.h TCUBEPhysics.h TCUBESpectra.h DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

