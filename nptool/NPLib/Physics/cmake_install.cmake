# Install script for directory: /mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/GEF.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPInelasticBreakup.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPFissionDecay.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPDecay.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPBeam.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPEnergyLoss.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPFunction.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPParticle.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPNucleus.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPReaction.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPPhaseSpace.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPQFS.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPTimeStamp.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TInitialConditions.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TTrackInfo.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TInteractionCoordinates.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TReactionConditions.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TFissionConditions.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPBreitWigner.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include" TYPE FILE MESSAGE_LAZY FILES
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/GEF.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPInelasticBreakup.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPFissionDecay.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPDecay.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPBeam.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPEnergyLoss.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPFunction.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPParticle.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPNucleus.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPReaction.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPPhaseSpace.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPQFS.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPTimeStamp.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TInitialConditions.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TTrackInfo.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TInteractionCoordinates.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TReactionConditions.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TFissionConditions.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPBreitWigner.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/GEF.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPInelasticBreakup.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPFissionDecay.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPDecay.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPBeam.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPEnergyLoss.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPFunction.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPParticle.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPNucleus.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPReaction.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPPhaseSpace.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPQFS.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPTimeStamp.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TInitialConditions.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TTrackInfo.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TInteractionCoordinates.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TReactionConditions.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TFissionConditions.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPBreitWigner.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include" TYPE FILE MESSAGE_LAZY FILES
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/GEF.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPInelasticBreakup.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPFissionDecay.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPDecay.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPBeam.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPEnergyLoss.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPFunction.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPParticle.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPNucleus.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPReaction.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPPhaseSpace.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPQFS.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPTimeStamp.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TInitialConditions.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TTrackInfo.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TInteractionCoordinates.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TReactionConditions.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/TFissionConditions.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Physics/NPBreitWigner.h"
    )
endif()

