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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1827138917/mt19937-64.o \
	${OBJECTDIR}/RW.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rw.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rw.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rw ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1827138917/mt19937-64.o: /C/cppprojects/Computational\ Physics/RW/mt19937-64.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1827138917
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/cppprojects/Computational\ Physics/RW -I/C/cppprojects/MC\ techniques/MC_problem1 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1827138917/mt19937-64.o /C/cppprojects/Computational\ Physics/RW/mt19937-64.cpp

${OBJECTDIR}/RW.o: RW.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/cppprojects/Computational\ Physics/RW -I/C/cppprojects/MC\ techniques/MC_problem1 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RW.o RW.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rw.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
