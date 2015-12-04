CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = main.o Config.o Printer.o 
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXEC}					# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

main.o: main.cc
	${CXX} ${CXXFLAGS} main.cc -c

Config.o: Config.cp
	${CXX} ${CXXFLAGS} Config.cp -c

Printer.o: Printer.cp
	${CXX} ${CXXFLAGS} Printer.cp -c		

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}

