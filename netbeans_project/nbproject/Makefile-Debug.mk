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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/_DOTDOT/src/utils/utils.o \
	${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/exception/exception.o \
	${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/main.o \
	${OBJECTDIR}/_ext/_DOTDOT/src/config/config.o \
	${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/string/string.o \
	${OBJECTDIR}/_ext/_DOTDOT/src/vfs/fsentrypoint.o \
	${OBJECTDIR}/_ext/_DOTDOT/src/vfs/localfsentrypoint.o \
	${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/vfs/vfs.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/netbeans_project

dist/Debug/GNU-Linux-x86/netbeans_project: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/_DOTDOT/src/utils/utils.o: nbproject/Makefile-${CND_CONF}.mk ../src/utils/utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/src/utils
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/src/utils/utils.o ../src/utils/utils.cpp

${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/exception/exception.o: nbproject/Makefile-${CND_CONF}.mk /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/exception
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/exception/exception.o /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp

${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/main.o: nbproject/Makefile-${CND_CONF}.mk /home/artem/devel/opengl/celestial-battle/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/main.o /home/artem/devel/opengl/celestial-battle/src/main.cpp

${OBJECTDIR}/_ext/_DOTDOT/src/config/config.o: nbproject/Makefile-${CND_CONF}.mk ../src/config/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/src/config
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/src/config/config.o ../src/config/config.cpp

${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/string/string.o: nbproject/Makefile-${CND_CONF}.mk /home/artem/devel/opengl/celestial-battle/src/string/string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/string
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/string/string.o /home/artem/devel/opengl/celestial-battle/src/string/string.cpp

${OBJECTDIR}/_ext/_DOTDOT/src/vfs/fsentrypoint.o: nbproject/Makefile-${CND_CONF}.mk ../src/vfs/fsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/src/vfs
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/src/vfs/fsentrypoint.o ../src/vfs/fsentrypoint.cpp

${OBJECTDIR}/_ext/_DOTDOT/src/vfs/localfsentrypoint.o: nbproject/Makefile-${CND_CONF}.mk ../src/vfs/localfsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/src/vfs
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/src/vfs/localfsentrypoint.o ../src/vfs/localfsentrypoint.cpp

${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/vfs/vfs.o: nbproject/Makefile-${CND_CONF}.mk /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/vfs
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/artem/devel/opengl/celestial-battle/src/vfs/vfs.o /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/netbeans_project

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
