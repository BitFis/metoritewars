#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW_1-Windows
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/scene.o \
	${OBJECTDIR}/src/ship.o \
	${OBJECTDIR}/src/time-helper.o \
	${OBJECTDIR}/src/world.o \
	${OBJECTDIR}/src/Object.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lopengl32 -lfreeglut -lglu32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meteoritewars.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meteoritewars.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -L"C:/MinGW/freeglut/lib" -L"C:/MinGW/SDL-1.2.15/lib/64x" -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meteoritewars ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I/C/MinGW/freeglut -I/C/MinGW/SDL-1.2.15/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/scene.o: src/scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I/C/MinGW/freeglut -I/C/MinGW/SDL-1.2.15/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/scene.o src/scene.cpp

${OBJECTDIR}/src/ship.o: src/ship.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I/C/MinGW/freeglut -I/C/MinGW/SDL-1.2.15/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ship.o src/ship.cpp

${OBJECTDIR}/src/time-helper.o: src/time-helper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I/C/MinGW/freeglut -I/C/MinGW/SDL-1.2.15/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/time-helper.o src/time-helper.cpp

${OBJECTDIR}/src/world.o: src/world.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I/C/MinGW/freeglut -I/C/MinGW/SDL-1.2.15/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/world.o src/world.cpp

${OBJECTDIR}/src/Object.o: src/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -I/C/MinGW/freeglut -I/C/MinGW/SDL-1.2.15/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Object.o src/Object.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meteoritewars.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
