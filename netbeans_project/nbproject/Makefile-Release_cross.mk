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
CND_CONF=Release_cross
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1519963337/utils.o \
	${OBJECTDIR}/_ext/1390850504/display.o \
	${OBJECTDIR}/_ext/1521210933/gettime.o \
	${OBJECTDIR}/_ext/68783691/utf8char.o \
	${OBJECTDIR}/_ext/576727235/glresourcefactory.o \
	${OBJECTDIR}/_ext/62598791/object.o \
	${OBJECTDIR}/_ext/1531546205/iconv.o \
	${OBJECTDIR}/_ext/1019042359/osal.o \
	${OBJECTDIR}/_ext/7752610/vfs.o \
	${OBJECTDIR}/_ext/1521210933/timer.o \
	${OBJECTDIR}/_ext/1534683872/event.o \
	${OBJECTDIR}/_ext/173017642/windowslist.o \
	${OBJECTDIR}/_ext/86326340/thread.o \
	${OBJECTDIR}/_ext/173017642/window_events.o \
	${OBJECTDIR}/_ext/897345942/string.o \
	${OBJECTDIR}/_ext/1521210933/settimer.o \
	${OBJECTDIR}/_ext/173017642/window.o \
	${OBJECTDIR}/_ext/1667457878/exception.o \
	${OBJECTDIR}/_ext/1527311355/mutex.o \
	${OBJECTDIR}/_ext/659870665/fsentrypoint.o \
	${OBJECTDIR}/_ext/1153801517/glresource.o \
	${OBJECTDIR}/_ext/49809687/opengl.o \
	${OBJECTDIR}/_ext/659861322/log.o \
	${OBJECTDIR}/_ext/662815568/glcontext.o \
	${OBJECTDIR}/_ext/1029917654/main.o \
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
LDLIBSOPTIONS=-lgdi32 -lwinmm -lopengl32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans_project ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1519963337/utils.o: ../src/utils/utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1519963337/utils.o ../src/utils/utils.cpp

${OBJECTDIR}/_ext/1390850504/display.o: ../src/display/display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1390850504
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1390850504/display.o ../src/display/display.cpp

${OBJECTDIR}/_ext/1521210933/gettime.o: ../src/timer/gettime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1521210933
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1521210933/gettime.o ../src/timer/gettime.cpp

${OBJECTDIR}/_ext/68783691/utf8char.o: ../src/string/utf8char.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/68783691
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/68783691/utf8char.o ../src/string/utf8char.cpp

${OBJECTDIR}/_ext/576727235/glresourcefactory.o: ../src/glresourcefactory/glresourcefactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/576727235
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/576727235/glresourcefactory.o ../src/glresourcefactory/glresourcefactory.cpp

${OBJECTDIR}/_ext/62598791/object.o: ../src/object/object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/62598791
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/62598791/object.o ../src/object/object.cpp

${OBJECTDIR}/_ext/1531546205/iconv.o: ../src/iconv/iconv.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1531546205
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1531546205/iconv.o ../src/iconv/iconv.cpp

${OBJECTDIR}/_ext/1019042359/osal.o: ../src/osal/osal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019042359
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1019042359/osal.o ../src/osal/osal.cpp

${OBJECTDIR}/_ext/7752610/vfs.o: /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/7752610
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/7752610/vfs.o /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp

${OBJECTDIR}/_ext/1521210933/timer.o: ../src/timer/timer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1521210933
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1521210933/timer.o ../src/timer/timer.cpp

${OBJECTDIR}/_ext/1534683872/event.o: ../src/event/event.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1534683872
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1534683872/event.o ../src/event/event.cpp

${OBJECTDIR}/_ext/173017642/windowslist.o: ../src/window/windowslist.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/173017642
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/173017642/windowslist.o ../src/window/windowslist.cpp

${OBJECTDIR}/_ext/86326340/thread.o: ../src/thread/thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/86326340
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/86326340/thread.o ../src/thread/thread.cpp

${OBJECTDIR}/_ext/173017642/window_events.o: ../src/window/window_events.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/173017642
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/173017642/window_events.o ../src/window/window_events.cpp

${OBJECTDIR}/_ext/897345942/string.o: /home/artem/devel/opengl/celestial-battle/src/string/string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/897345942
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/897345942/string.o /home/artem/devel/opengl/celestial-battle/src/string/string.cpp

${OBJECTDIR}/_ext/1521210933/settimer.o: ../src/timer/settimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1521210933
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1521210933/settimer.o ../src/timer/settimer.cpp

${OBJECTDIR}/_ext/173017642/window.o: ../src/window/window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/173017642
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/173017642/window.o ../src/window/window.cpp

${OBJECTDIR}/_ext/1667457878/exception.o: /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1667457878
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1667457878/exception.o /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp

${OBJECTDIR}/_ext/1527311355/mutex.o: ../src/mutex/mutex.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1527311355
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1527311355/mutex.o ../src/mutex/mutex.cpp

${OBJECTDIR}/_ext/659870665/fsentrypoint.o: ../src/vfs/fsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659870665
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659870665/fsentrypoint.o ../src/vfs/fsentrypoint.cpp

${OBJECTDIR}/_ext/1153801517/glresource.o: ../src/glresource/glresource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1153801517
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1153801517/glresource.o ../src/glresource/glresource.cpp

${OBJECTDIR}/_ext/49809687/opengl.o: ../src/opengl/opengl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/49809687
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/49809687/opengl.o ../src/opengl/opengl.cpp

${OBJECTDIR}/_ext/659861322/log.o: ../src/log/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659861322
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659861322/log.o ../src/log/log.cpp

${OBJECTDIR}/_ext/662815568/glcontext.o: ../src/glcontext/glcontext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/662815568
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/662815568/glcontext.o ../src/glcontext/glcontext.cpp

${OBJECTDIR}/_ext/1029917654/main.o: /home/artem/devel/opengl/celestial-battle/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1029917654
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1029917654/main.o /home/artem/devel/opengl/celestial-battle/src/main.cpp

${OBJECTDIR}/_ext/1531217328/input.o: ../src/input/input.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1531217328
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1531217328/input.o ../src/input/input.cpp

${OBJECTDIR}/_ext/659870665/localfsentrypoint.o: ../src/vfs/localfsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659870665
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659870665/localfsentrypoint.o ../src/vfs/localfsentrypoint.cpp

${OBJECTDIR}/_ext/337505763/entity.o: ../src/entity/entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/337505763
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/337505763/entity.o ../src/entity/entity.cpp

${OBJECTDIR}/_ext/394022532/config.o: ../src/config/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/394022532
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/394022532/config.o ../src/config/config.cpp

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
