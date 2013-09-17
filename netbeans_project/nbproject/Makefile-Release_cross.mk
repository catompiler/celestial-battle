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
CND_DLIB_EXT=so
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
	${OBJECTDIR}/_ext/767039133/tokenparser.o \
	${OBJECTDIR}/_ext/1019114841/mesh.o \
	${OBJECTDIR}/_ext/49809687/functions.o \
	${OBJECTDIR}/_ext/1358156373/reader.o \
	${OBJECTDIR}/_ext/2106539989/notfoundexception.o \
	${OBJECTDIR}/_ext/1390850504/display.o \
	${OBJECTDIR}/_ext/1521210933/gettime.o \
	${OBJECTDIR}/_ext/767039133/parseexception.o \
	${OBJECTDIR}/_ext/1262803996/gltexture.o \
	${OBJECTDIR}/_ext/68783691/utf8char.o \
	${OBJECTDIR}/_ext/767039133/tokenssequence.o \
	${OBJECTDIR}/_ext/659868756/tga.o \
	${OBJECTDIR}/_ext/62598791/object.o \
	${OBJECTDIR}/_ext/1019042359/osal.o \
	${OBJECTDIR}/_ext/1531546205/iconv.o \
	${OBJECTDIR}/_ext/7752610/vfs.o \
	${OBJECTDIR}/_ext/767039133/tokenizer.o \
	${OBJECTDIR}/_ext/1521210933/timer.o \
	${OBJECTDIR}/_ext/1923734139/glprogram.o \
	${OBJECTDIR}/_ext/799496470/shaderreader.o \
	${OBJECTDIR}/_ext/774992765/componentfactory.o \
	${OBJECTDIR}/_ext/1522320622/scene.o \
	${OBJECTDIR}/_ext/180677857/material.o \
	${OBJECTDIR}/_ext/173017642/windowslist.o \
	${OBJECTDIR}/_ext/86326340/thread.o \
	${OBJECTDIR}/_ext/173017642/window_events.o \
	${OBJECTDIR}/_ext/2106539989/badindexexception.o \
	${OBJECTDIR}/_ext/2106539989/badtypeexception.o \
	${OBJECTDIR}/_ext/1014552289/glbuffer.o \
	${OBJECTDIR}/_ext/1677581042/transform.o \
	${OBJECTDIR}/_ext/1521210933/settimer.o \
	${OBJECTDIR}/_ext/666085778/glframebuffer.o \
	${OBJECTDIR}/_ext/173017642/window.o \
	${OBJECTDIR}/_ext/1667457878/exception.o \
	${OBJECTDIR}/_ext/767039133/tokenposition.o \
	${OBJECTDIR}/_ext/767039133/tokens.o \
	${OBJECTDIR}/_ext/767039133/tokenparsers.o \
	${OBJECTDIR}/_ext/1527311355/mutex.o \
	${OBJECTDIR}/_ext/799496470/tgareader.o \
	${OBJECTDIR}/_ext/659870665/fsentrypoint.o \
	${OBJECTDIR}/_ext/774992765/locatedcomponent.o \
	${OBJECTDIR}/_ext/1153801517/glresource.o \
	${OBJECTDIR}/_ext/907685599/transformstree.o \
	${OBJECTDIR}/_ext/49809687/opengl.o \
	${OBJECTDIR}/_ext/662815568/glcontext.o \
	${OBJECTDIR}/_ext/158927991/glpatch.o \
	${OBJECTDIR}/_ext/659861322/log.o \
	${OBJECTDIR}/_ext/1521210933/nanosleep.o \
	${OBJECTDIR}/_ext/1029917654/main.o \
	${OBJECTDIR}/_ext/1358156373/resources.o \
	${OBJECTDIR}/_ext/250496777/glsampler.o \
	${OBJECTDIR}/_ext/767039133/token.o \
	${OBJECTDIR}/_ext/774992765/component.o \
	${OBJECTDIR}/_ext/540013372/glshader.o \
	${OBJECTDIR}/_ext/1578303221/glrenderbuffer.o \
	${OBJECTDIR}/_ext/659868756/texture.o \
	${OBJECTDIR}/_ext/1531217328/input.o \
	${OBJECTDIR}/_ext/26177488/render.o \
	${OBJECTDIR}/_ext/799496470/mesh3dreader.o \
	${OBJECTDIR}/_ext/394022532/configexception.o \
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

${OBJECTDIR}/_ext/767039133/tokenparser.o: ../src/tokenizer/tokenparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/767039133
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/767039133/tokenparser.o ../src/tokenizer/tokenparser.cpp

${OBJECTDIR}/_ext/1019114841/mesh.o: ../src/mesh/mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019114841
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1019114841/mesh.o ../src/mesh/mesh.cpp

${OBJECTDIR}/_ext/49809687/functions.o: ../src/opengl/functions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/49809687
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/49809687/functions.o ../src/opengl/functions.cpp

${OBJECTDIR}/_ext/1358156373/reader.o: ../src/resources/reader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1358156373
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1358156373/reader.o ../src/resources/reader.cpp

${OBJECTDIR}/_ext/2106539989/notfoundexception.o: ../src/exception/notfoundexception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2106539989
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2106539989/notfoundexception.o ../src/exception/notfoundexception.cpp

${OBJECTDIR}/_ext/1390850504/display.o: ../src/display/display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1390850504
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1390850504/display.o ../src/display/display.cpp

${OBJECTDIR}/_ext/1521210933/gettime.o: ../src/timer/gettime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1521210933
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1521210933/gettime.o ../src/timer/gettime.cpp

${OBJECTDIR}/_ext/767039133/parseexception.o: ../src/tokenizer/parseexception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/767039133
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/767039133/parseexception.o ../src/tokenizer/parseexception.cpp

${OBJECTDIR}/_ext/1262803996/gltexture.o: ../src/gltexture/gltexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1262803996
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1262803996/gltexture.o ../src/gltexture/gltexture.cpp

${OBJECTDIR}/_ext/68783691/utf8char.o: ../src/string/utf8char.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/68783691
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/68783691/utf8char.o ../src/string/utf8char.cpp

${OBJECTDIR}/_ext/767039133/tokenssequence.o: ../src/tokenizer/tokenssequence.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/767039133
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/767039133/tokenssequence.o ../src/tokenizer/tokenssequence.cpp

${OBJECTDIR}/_ext/659868756/tga.o: ../src/tga/tga.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659868756
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659868756/tga.o ../src/tga/tga.cpp

${OBJECTDIR}/_ext/62598791/object.o: ../src/object/object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/62598791
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/62598791/object.o ../src/object/object.cpp

${OBJECTDIR}/_ext/1019042359/osal.o: ../src/osal/osal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019042359
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1019042359/osal.o ../src/osal/osal.cpp

${OBJECTDIR}/_ext/1531546205/iconv.o: ../src/iconv/iconv.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1531546205
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1531546205/iconv.o ../src/iconv/iconv.cpp

${OBJECTDIR}/_ext/7752610/vfs.o: /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/7752610
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/7752610/vfs.o /home/artem/devel/opengl/celestial-battle/src/vfs/vfs.cpp

${OBJECTDIR}/_ext/767039133/tokenizer.o: ../src/tokenizer/tokenizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/767039133
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/767039133/tokenizer.o ../src/tokenizer/tokenizer.cpp

${OBJECTDIR}/_ext/1521210933/timer.o: ../src/timer/timer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1521210933
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1521210933/timer.o ../src/timer/timer.cpp

${OBJECTDIR}/_ext/1923734139/glprogram.o: ../src/glprogram/glprogram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923734139
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923734139/glprogram.o ../src/glprogram/glprogram.cpp

${OBJECTDIR}/_ext/799496470/shaderreader.o: ../src/readers/shaderreader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/799496470
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/799496470/shaderreader.o ../src/readers/shaderreader.cpp

${OBJECTDIR}/_ext/774992765/componentfactory.o: ../src/component/componentfactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/774992765
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/774992765/componentfactory.o ../src/component/componentfactory.cpp

${OBJECTDIR}/_ext/1522320622/scene.o: ../src/scene/scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522320622
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1522320622/scene.o ../src/scene/scene.cpp

${OBJECTDIR}/_ext/180677857/material.o: ../src/material/material.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/180677857
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/180677857/material.o ../src/material/material.cpp

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

${OBJECTDIR}/_ext/2106539989/badindexexception.o: ../src/exception/badindexexception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2106539989
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2106539989/badindexexception.o ../src/exception/badindexexception.cpp

${OBJECTDIR}/_ext/2106539989/badtypeexception.o: ../src/exception/badtypeexception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2106539989
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2106539989/badtypeexception.o ../src/exception/badtypeexception.cpp

${OBJECTDIR}/_ext/1014552289/glbuffer.o: ../src/glbuffer/glbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1014552289
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1014552289/glbuffer.o ../src/glbuffer/glbuffer.cpp

${OBJECTDIR}/_ext/1677581042/transform.o: ../src/transform/transform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1677581042
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1677581042/transform.o ../src/transform/transform.cpp

${OBJECTDIR}/_ext/1521210933/settimer.o: ../src/timer/settimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1521210933
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1521210933/settimer.o ../src/timer/settimer.cpp

${OBJECTDIR}/_ext/666085778/glframebuffer.o: ../src/glframebuffer/glframebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/666085778
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/666085778/glframebuffer.o ../src/glframebuffer/glframebuffer.cpp

${OBJECTDIR}/_ext/173017642/window.o: ../src/window/window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/173017642
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/173017642/window.o ../src/window/window.cpp

${OBJECTDIR}/_ext/1667457878/exception.o: /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1667457878
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1667457878/exception.o /home/artem/devel/opengl/celestial-battle/src/exception/exception.cpp

${OBJECTDIR}/_ext/767039133/tokenposition.o: ../src/tokenizer/tokenposition.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/767039133
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/767039133/tokenposition.o ../src/tokenizer/tokenposition.cpp

${OBJECTDIR}/_ext/767039133/tokens.o: ../src/tokenizer/tokens.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/767039133
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/767039133/tokens.o ../src/tokenizer/tokens.cpp

${OBJECTDIR}/_ext/767039133/tokenparsers.o: ../src/tokenizer/tokenparsers.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/767039133
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/767039133/tokenparsers.o ../src/tokenizer/tokenparsers.cpp

${OBJECTDIR}/_ext/1527311355/mutex.o: ../src/mutex/mutex.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1527311355
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1527311355/mutex.o ../src/mutex/mutex.cpp

${OBJECTDIR}/_ext/799496470/tgareader.o: ../src/readers/tgareader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/799496470
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/799496470/tgareader.o ../src/readers/tgareader.cpp

${OBJECTDIR}/_ext/659870665/fsentrypoint.o: ../src/vfs/fsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659870665
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659870665/fsentrypoint.o ../src/vfs/fsentrypoint.cpp

${OBJECTDIR}/_ext/774992765/locatedcomponent.o: ../src/component/locatedcomponent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/774992765
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/774992765/locatedcomponent.o ../src/component/locatedcomponent.cpp

${OBJECTDIR}/_ext/1153801517/glresource.o: ../src/glresource/glresource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1153801517
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1153801517/glresource.o ../src/glresource/glresource.cpp

${OBJECTDIR}/_ext/907685599/transformstree.o: ../src/transformstree/transformstree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/907685599
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/907685599/transformstree.o ../src/transformstree/transformstree.cpp

${OBJECTDIR}/_ext/49809687/opengl.o: ../src/opengl/opengl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/49809687
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/49809687/opengl.o ../src/opengl/opengl.cpp

${OBJECTDIR}/_ext/662815568/glcontext.o: ../src/glcontext/glcontext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/662815568
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/662815568/glcontext.o ../src/glcontext/glcontext.cpp

${OBJECTDIR}/_ext/158927991/glpatch.o: ../src/glpatch/glpatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/158927991
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/158927991/glpatch.o ../src/glpatch/glpatch.cpp

${OBJECTDIR}/_ext/659861322/log.o: ../src/log/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659861322
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659861322/log.o ../src/log/log.cpp

${OBJECTDIR}/_ext/1521210933/nanosleep.o: ../src/timer/nanosleep.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1521210933
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1521210933/nanosleep.o ../src/timer/nanosleep.cpp

${OBJECTDIR}/_ext/1029917654/main.o: /home/artem/devel/opengl/celestial-battle/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1029917654
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1029917654/main.o /home/artem/devel/opengl/celestial-battle/src/main.cpp

${OBJECTDIR}/_ext/1358156373/resources.o: ../src/resources/resources.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1358156373
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1358156373/resources.o ../src/resources/resources.cpp

${OBJECTDIR}/_ext/250496777/glsampler.o: ../src/glsampler/glsampler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/250496777
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/250496777/glsampler.o ../src/glsampler/glsampler.cpp

${OBJECTDIR}/_ext/767039133/token.o: ../src/tokenizer/token.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/767039133
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/767039133/token.o ../src/tokenizer/token.cpp

${OBJECTDIR}/_ext/774992765/component.o: ../src/component/component.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/774992765
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/774992765/component.o ../src/component/component.cpp

${OBJECTDIR}/_ext/540013372/glshader.o: ../src/glshader/glshader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/540013372
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/540013372/glshader.o ../src/glshader/glshader.cpp

${OBJECTDIR}/_ext/1578303221/glrenderbuffer.o: ../src/glrenderbuffer/glrenderbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1578303221
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1578303221/glrenderbuffer.o ../src/glrenderbuffer/glrenderbuffer.cpp

${OBJECTDIR}/_ext/659868756/texture.o: ../src/tga/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659868756
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659868756/texture.o ../src/tga/texture.cpp

${OBJECTDIR}/_ext/1531217328/input.o: ../src/input/input.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1531217328
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1531217328/input.o ../src/input/input.cpp

${OBJECTDIR}/_ext/26177488/render.o: ../src/render/render.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/26177488
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/26177488/render.o ../src/render/render.cpp

${OBJECTDIR}/_ext/799496470/mesh3dreader.o: ../src/readers/mesh3dreader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/799496470
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/799496470/mesh3dreader.o ../src/readers/mesh3dreader.cpp

${OBJECTDIR}/_ext/394022532/configexception.o: ../src/config/configexception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/394022532
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/394022532/configexception.o ../src/config/configexception.cpp

${OBJECTDIR}/_ext/659870665/localfsentrypoint.o: ../src/vfs/localfsentrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/659870665
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../src/ -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/659870665/localfsentrypoint.o ../src/vfs/localfsentrypoint.cpp

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
