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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1519963337/utils.o \
	${OBJECTDIR}/_ext/241037705/win_window.o \
	${OBJECTDIR}/_ext/1390850504/display.o \
	${OBJECTDIR}/_ext/62598791/object.o \
	${OBJECTDIR}/_ext/1019042359/osal.o \
	${OBJECTDIR}/_ext/7752610/vfs.o \
	${OBJECTDIR}/_ext/1964180579/win_input.o \
	${OBJECTDIR}/_ext/960476113/x11_display.o \
	${OBJECTDIR}/_ext/1534683872/event.o \
	${OBJECTDIR}/_ext/241038541/x11_window.o \
	${OBJECTDIR}/_ext/897345942/string.o \
	${OBJECTDIR}/_ext/173017642/window.o \
	${OBJECTDIR}/_ext/1964181415/x11_input.o \
	${OBJECTDIR}/_ext/1667457878/exception.o \
	${OBJECTDIR}/_ext/1060664647/x11_glcontext.o \
	${OBJECTDIR}/_ext/659870665/fsentrypoint.o \
	${OBJECTDIR}/_ext/1153801517/glresource.o \
	${OBJECTDIR}/_ext/49809687/opengl.o \
	${OBJECTDIR}/_ext/659861322/log.o \
	${OBJECTDIR}/_ext/662815568/glcontext.o \
	${OBJECTDIR}/_ext/1029917654/main.o \
	${OBJECTDIR}/_ext/1060663811/win_glcontext.o \
	${OBJECTDIR}/_ext/960476949/win_display.o \
	${OBJECTDIR}/_ext/1531217328/input.o \
	${OBJECTDIR}/_ext/659870665/localfsentrypoint.o \
	${OBJECTDIR}/_ext/337505763/entity.o \
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
LDLIBSOPTIONS=-lX11 -lGL

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1519963337/utils.o: ../src/utils/utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1519963337/utils.o ../src/utils/utils.cpp

${OBJECTDIR}/_ext/241037705/win_window.o: ../src/window/win/win_window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/241037705
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/241037705/win_window.o ../src/window/win/win_window.cpp

${OBJECTDIR}/_ext/1390850504/display.o: ../src/display/display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1390850504
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1390850504/display.o ../src/display/display.cpp

${OBJECTDIR}/_ext/62598791/object.o: ../src/object/object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/62598791
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/62598791/object.o ../src/object/object.cpp

${OBJECTDIR}/_ext/1019042359/osal.o: ../src/osal/osal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019042359
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1019042359/osal.o ../src/osal/osal.cpp

${OBJECTDIR}/_ext/7752610/vfs.o: /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/7752610
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/7752610/vfs.o /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp

${OBJECTDIR}/_ext/1964180579/win_input.o: ../src/input/win/win_input.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1964180579
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1964180579/win_input.o ../src/input/win/win_input.cpp

${OBJECTDIR}/_ext/960476113/x11_display.o: ../src/display/x11/x11_display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960476113
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/960476113/x11_display.o ../src/display/x11/x11_display.cpp

${OBJECTDIR}/_ext/1534683872/event.o: ../src/event/event.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1534683872
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1534683872/event.o ../src/event/event.cpp

${OBJECTDIR}/_ext/241038541/x11_window.o: ../src/window/x11/x11_window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/241038541
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/241038541/x11_window.o ../src/window/x11/x11_window.cpp

${OBJECTDIR}/_ext/897345942/string.o: /home/artem/devel/opengl/celestial-battle/src/string/string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/897345942
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/897345942/string.o /home/artem/devel/opengl/celestial-battle/src/string/string.cpp

${OBJECTDIR}/_ext/173017642/window.o: ../src/window/window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/173017642
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/173017642/window.o ../src/window/window.cpp

${OBJECTDIR}/_ext/1964181415/x11_input.o: ../src/input/x11/x11_input.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1964181415
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1964181415/x11_input.o ../src/input/x11/x11_input.cpp

${OBJECTDIR}/_ext/1667457878/exception.o: /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1667457878
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1667457878/exception.o /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp

${OBJECTDIR}/_ext/1060664647/x11_glcontext.o: ../src/glcontext/x11/x11_glcontext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1060664647
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1060664647/x11_glcontext.o ../src/glcontext/x11/x11_glcontext.cpp

${OBJECTDIR}/_ext/659870665/fsentrypoint.o: ../src/vfs/fsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659870665
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659870665/fsentrypoint.o ../src/vfs/fsentrypoint.cpp

${OBJECTDIR}/_ext/1153801517/glresource.o: ../src/glresource/glresource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1153801517
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1153801517/glresource.o ../src/glresource/glresource.cpp

${OBJECTDIR}/_ext/49809687/opengl.o: ../src/opengl/opengl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/49809687
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/49809687/opengl.o ../src/opengl/opengl.cpp

${OBJECTDIR}/_ext/659861322/log.o: ../src/log/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659861322
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659861322/log.o ../src/log/log.cpp

${OBJECTDIR}/_ext/662815568/glcontext.o: ../src/glcontext/glcontext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/662815568
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/662815568/glcontext.o ../src/glcontext/glcontext.cpp

${OBJECTDIR}/_ext/1029917654/main.o: /home/artem/devel/opengl/celestial-battle/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1029917654
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1029917654/main.o /home/artem/devel/opengl/celestial-battle/src/main.cpp

${OBJECTDIR}/_ext/1060663811/win_glcontext.o: ../src/glcontext/win/win_glcontext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1060663811
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1060663811/win_glcontext.o ../src/glcontext/win/win_glcontext.cpp

${OBJECTDIR}/_ext/960476949/win_display.o: ../src/display/win/win_display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960476949
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/960476949/win_display.o ../src/display/win/win_display.cpp

${OBJECTDIR}/_ext/1531217328/input.o: ../src/input/input.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1531217328
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1531217328/input.o ../src/input/input.cpp

${OBJECTDIR}/_ext/659870665/localfsentrypoint.o: ../src/vfs/localfsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659870665
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659870665/localfsentrypoint.o ../src/vfs/localfsentrypoint.cpp

${OBJECTDIR}/_ext/337505763/entity.o: ../src/entity/entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/337505763
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/337505763/entity.o ../src/entity/entity.cpp

${OBJECTDIR}/_ext/394022532/config.o: ../src/config/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/394022532
	${RM} $@.d
	$(COMPILE.cc) -g -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/394022532/config.o ../src/config/config.cpp

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
