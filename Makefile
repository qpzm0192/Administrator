CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = main.o Config.o Printer.o Bank.o WATCard.o WATCardOffice.o \
		Parent.o Groupoff.o BottlingPlant.o NameServer.o Truck.o VendingMachine.o \
		Student.o
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXEC}					# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

main.o: main.cc
	${CXX} ${CXXFLAGS} main.cc -c

Config.o: Config.cc
	${CXX} ${CXXFLAGS} Config.cc -c

Printer.o: Printer.cc
	${CXX} ${CXXFLAGS} Printer.cc -c

Bank.o: Bank.cc
	${CXX} ${CXXFLAGS} Bank.cc -c

WATCard.o: WATCard.cc
	${CXX} ${CXXFLAGS} WATCard.cc -c

WATCardOffice.o: WATCardOffice.cc
	${CXX} ${CXXFLAGS} WATCardOffice.cc -c

Parent.o: Parent.cc
	${CXX} ${CXXFLAGS} Parent.cc -c

Student.o: Student.cc
	${CXX} ${CXXFLAGS} Student.cc -c				

Groupoff.o: Groupoff.cc
	${CXX} ${CXXFLAGS} Groupoff.cc -c

BottlingPlant.o: BottlingPlant.cc
	${CXX} ${CXXFLAGS} BottlingPlant.cc -c

NameServer.o: NameServer.cc
	${CXX} ${CXXFLAGS} NameServer.cc -c

Truck.o: Truck.cc
	${CXX} ${CXXFLAGS} Truck.cc -c

VendingMachine.o: VendingMachine.cc
	${CXX} ${CXXFLAGS} VendingMachine.cc -c				
#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}

