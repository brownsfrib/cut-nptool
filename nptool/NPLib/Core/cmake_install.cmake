# Install script for directory: /mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core

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
   "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPCore.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPVAnalysis.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPAnalysisFactory.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPRandom.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPCalibrationManager.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPOptionManager.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/RootInput.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/RootOutput.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/RootHistogramsCalib.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/TAsciiFile.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPDetectorManager.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPVTreeReader.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPVDetector.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPGlobalSystemOfUnits.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPPhysicalConstants.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPSystemOfUnits.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPVSpectra.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPDetectorFactory.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPSpectraServer.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPInputParser.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPImage.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPElog.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPDeltaSpectra.h;/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include/NPXmlParser.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/include" TYPE FILE MESSAGE_LAZY FILES
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPCore.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPVAnalysis.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPAnalysisFactory.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPRandom.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPCalibrationManager.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPOptionManager.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/RootInput.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/RootOutput.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/RootHistogramsCalib.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/TAsciiFile.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPDetectorManager.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPVTreeReader.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPVDetector.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPGlobalSystemOfUnits.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPPhysicalConstants.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPSystemOfUnits.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPVSpectra.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPDetectorFactory.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPSpectraServer.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPInputParser.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPImage.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPElog.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPDeltaSpectra.h"
    "/mnt/simulations/hira/Sam/ForJoe/nptool/NPLib/Core/NPXmlParser.h"
    )
endif()

