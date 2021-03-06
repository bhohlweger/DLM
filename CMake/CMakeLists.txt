CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project(CATS)
# SET PATHS #
SET(CATS_DESTINATION "/home/dmihaylov/Temp/CATS_TEST1")#where to install CATS. Folder must exist.
SET(ROOT_INCLUDE "/home/dmihaylov/root/include")#where are all ROOT related .h files
SET(ROOT_LIB "/home/dmihaylov/root/lib")#where are the ROOT related .a and .so files
SET(GSL_INCLUDE "/usr/include/gsl")#where are all GSL related .h files
SET(GSL_LIB "/usr/lib")#where are the GSL .a and .so files
SET(CATS_FOLDER "/home/dmihaylov/Dudek_Ubuntu/DLM_GitHub")#where is the CATS main folder located
# DO NOT CHANGE THE REST #

SET(VERSION_MAJOR 2)
SET(VERSION_MINOR 10)
SET(VERSION_PATCH 0)
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CATS_DESTINATION})

include_directories(${CATS_FOLDER}/CATS)
include_directories(${CATS_FOLDER}/DLM_CppTools)
include_directories(${GSL_INCLUDE})
include_directories(${ROOT_INCLUDE})

add_library(CATSbasic STATIC 		${CATS_FOLDER}/CATS/CATS.cpp 
					${CATS_FOLDER}/CATS/CATStools.cpp 
					${CATS_FOLDER}/DLM_CppTools/DLM_CppTools.cpp)
add_library(CATSextended STATIC 	${CATS_FOLDER}/CATS_Extentions/DLM_CkModels.cpp 
					${CATS_FOLDER}/CATS_Extentions/DLM_Potentials.cpp 
					${CATS_FOLDER}/CATS_Extentions/DLM_Source.cpp
					${CATS_FOLDER}/CATS_Extentions/DLM_StefanoPotentials.cpp)
add_library(CATSdev	STATIC		${CATS_FOLDER}/CATS_Extentions/DLM_CkDecomposition.cpp 
					${CATS_FOLDER}/CATS_Extentions/DLM_Fitters.cpp 
					${CATS_FOLDER}/CATS_Extentions/DLM_ResponseMatrix.cpp
					${CATS_FOLDER}/CATS_Extentions/DLM_WfModel.cpp)

set_target_properties( 	CATSbasic CATSextended CATSdev PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CATS_DESTINATION}/lib" LIBRARY_OUTPUT_DIRECTORY "${CATS_DESTINATION}/lib" RUNTIME_OUTPUT_DIRECTORY "${CATS_DESTINATION}/bin")

install (TARGETS CATSbasic DESTINATION ${CATS_DESTINATION}/lib)
install (TARGETS CATSextended DESTINATION ${CATS_DESTINATION}/lib)
install (TARGETS CATSdev DESTINATION ${CATS_DESTINATION}/lib)

install (FILES ${CATS_FOLDER}/CATS/CATS.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS/CATStools.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS_Extentions/DLM_CkDecomposition.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS_Extentions/DLM_CkModels.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS_Extentions/DLM_Fitters.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS_Extentions/DLM_Potentials.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS_Extentions/DLM_ResponseMatrix.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS_Extentions/DLM_Source.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS_Extentions/DLM_StefanoPotentials.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/CATS_Extentions/DLM_WfModel.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/DLM_CppTools/DLM_MergeSort.h DESTINATION ${CATS_DESTINATION}/include)
install (FILES ${CATS_FOLDER}/DLM_CppTools/DLM_CppTools.h DESTINATION ${CATS_DESTINATION}/include)
