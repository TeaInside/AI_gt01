
NAME = ai_gt01
DEBUG_MODE = 1
PHP_VERSION = 7.2
INI_DIR = /etc/php/${PHP_VERSION}/mods-available
ROOT_DIR = $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
INCLUDE_DIR = ${ROOT_DIR}/include
EXTENSION_DIR = $(shell php-config${PHP_VERSION} --extension-dir)
PRIORITY = 20
EXTENSION = ${NAME}.so
INI = ${NAME}.ini
COMPILER = g++
LINKER = g++
LINKER_FLAGS = -shared
LINKER_DEPENDENCIES = -lphpcpp

ifneq (${DEBUG_MODE},0)
	COMPILER_FLAGS += -Wall -I${INCLUDE_DIR} -c -std=c++11 -fpic -ggdb -g3 -D ESTEH_DEBUG
else
	COMPILER_FLAGS += -Wall -I${INCLUDE_DIR} -c -std=c++11 -fpic -O2 -s
endif

COMPILER_FLAGS += -o

RM = rm -vf
CP = cp -vf
LN = ln -vsf
MKDIR = mkdir -vp
SOURCES = $(shell find ${ROOT_DIR}/src/ -name '*.cpp')
OBJECTS = $(SOURCES:%.cpp=%.o)

all: ${OBJECTS} ${EXTENSION}

${EXTENSION}: ${OBJECTS}
	${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
	${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

install:		
	${CP} ${EXTENSION} ${EXTENSION_DIR}
	${CP} ${ROOT_DIR}/${INI} ${INI_DIR}/${PRIORITY}-${INI}
	${LN} ${INI_DIR}/${PRIORITY}-${INI} /etc/php/${PHP_VERSION}/cli/conf.d

clean:
	${RM} ${OBJECTS} ${EXTENSION}
