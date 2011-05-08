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
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1519963337/utils.o \
	${OBJECTDIR}/_ext/7752610/vfs.o \
	${OBJECTDIR}/_ext/897345942/string.o \
	${OBJECTDIR}/_ext/1667457878/exception.o \
	${OBJECTDIR}/_ext/659870665/fsentrypoint.o \
	${OBJECTDIR}/_ext/1029917654/main.o \
	${OBJECTDIR}/_ext/659870665/localfsentrypoint.o \
	${OBJECTDIR}/_ext/394022532/config.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1519963337/utils.o: ../src/utils/utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1519963337/utils.o ../src/utils/utils.cpp

${OBJECTDIR}/_ext/7752610/vfs.o: /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/7752610
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/7752610/vfs.o /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp

${OBJECTDIR}/_ext/897345942/string.o: /home/artem/devel/opengl/celestial-battle/src/string/string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/897345942
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/897345942/string.o /home/artem/devel/opengl/celestial-battle/src/string/string.cpp

${OBJECTDIR}/_ext/1667457878/exception.o: /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1667457878
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1667457878/exception.o /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp

${OBJECTDIR}/_ext/659870665/fsentrypoint.o: ../src/vfs/fsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659870665
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659870665/fsentrypoint.o ../src/vfs/fsentrypoint.cpp

${OBJECTDIR}/_ext/1029917654/main.o: /home/artem/devel/opengl/celestial-battle/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1029917654
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1029917654/main.o /home/artem/devel/opengl/celestial-battle/src/main.cpp

${OBJECTDIR}/_ext/659870665/localfsentrypoint.o: ../src/vfs/localfsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659870665
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659870665/localfsentrypoint.o ../src/vfs/localfsentrypoint.cpp

${OBJECTDIR}/_ext/394022532/config.o: ../src/config/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/394022532
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/394022532/config.o ../src/config/config.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
