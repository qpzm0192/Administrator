#include "Printer.h"
#include <iostream>
#include <vector>

using namespace std;

void Printer::flush() {
	//parent
	objectState &parent = osv[0];
	if(parent.valid) {
		char state = parent.state;
		cout << state;
		if(state == 'D') {
			cout << parent.lid << ',' << parent.value1;
		}
		parent.valid = false;
	}
	cout << '\t';
	
	//groupoff
	objectState &groupoff = osv[1];
	if(groupoff.valid) {
		char state = groupoff.state;
		cout << state;
		if(state == 'D') {
			cout << groupoff.value1;
		}
		groupoff.valid = false;
	}
	cout << '\t';
	

	//WATCard office
	objectState &watoff = osv[2];
	if(watoff.valid) {
		char state = watoff.state;
		cout << state;
		if(state == 'C' || state == 'S') {
			cout << watoff.lid << ',' << watoff.value1;
		}
		watoff.valid = false;
	}
	cout << '\t';
	

	//name server
	objectState &names = osv[3];
	if(names.valid) {
		char state = names.state;
		cout << state;
		if(state == 'R') {
			cout << names.lid;
		} else if(state == 'N') {
			cout << names.lid << ',' << names.value1;
		}
		names.valid = false;
	}
	cout << '\t';


	//truck
	objectState &truck = osv[4];
	if(truck.valid) {
		char state = truck.state;
		cout << state;
		if(state == 'P') {
			cout << truck.value1;
		} else if(state == 'd' || state == 'U' || state == 'D') {
			cout << truck.lid << ',' << truck.value1;
		}
		truck.valid = false;
	}
	cout << '\t';


	//plant
	objectState &plant = osv[5];
	if(plant.valid) {
		char state = names.state;
		cout << state;
		if(state == 'G') {
			cout << plant.value1;
		}
		plant.valid = false;
	}
	cout << '\t';

	//student
	for(unsigned int i = 6; i < 6 + numStudents; i++) {
		objectState &os = osv[i];
		if(os.valid) {
			char state = os.state;
			cout << state;
			if(state == 'S') {
				cout << os.value1 << ',' <<os.value2;
			} else if(state == 'V') {
				cout << os.lid;
			} else if(state == 'G' || state == 'B') {
				cout << os.value1;
			}
			os.valid = false;
		}
		cout << '\t';
	}

	//vending machine
	for(unsigned int i = 6 + numStudents; i < 6 + numStudents + numVendingMachines; i++) {
		objectState &os = osv[i];
		if(os.valid) {
			char state = os.state;
			cout << state;
			if(state == 'S') {
				cout << os.lid ;
			} else if(state == 'B') {
				cout << os.value1 << ',' << os.value2;
			}
			os.valid = false;
		}
		cout << '\t';
	}

	//vending courier
	for(unsigned int i = 6 + numStudents + numVendingMachines; i < total; i++) {
		objectState &os = osv[i];
		if(os.valid) {
			char state = os.state;
			cout << state;
			if(state == 't' || state == 'T') {
				cout << os.lid << ',' << os.value1;
			}
			os.valid = false;
		}
		cout << '\t';
	}
	cout << endl;
}

void Printer::finish(Printer::Kind kind) {
	objectState os = osv[kind];
	if(os.valid) {
		flush();
	}

	for(unsigned int i = 0; i < total; i++) {
		if(i == kind) {
			cout << "F\t";
		} else {
			cout << "...\t";
		}
	}
	cout << endl;
}

void Printer::finish(Printer::Kind kind, unsigned int lid) {
	unsigned int index;
	switch(kind) {
		case Printer::Student:
			index = 6 + lid;
			break;
		case Printer::Vending:
			index = 6 + numStudents + lid;
			break;
		case Printer::Courier:
			index = 6 + numVendingMachines + lid;
			break;
		default:
			index = kind;
			break;
	}

	objectState os = osv[index];
	if(os.valid) {
		flush();
	}

	for(unsigned int i = 0; i < total; i++) {
		if(i == index) {
			cout << "F\t";
		} else {
			cout << "...\t";
		}
	}
	cout << endl;

	
}

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers)
	: numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {

	total = 6 + numStudents + numVendingMachines + numCouriers;

	for(unsigned int i=0; i < total; i++) {
		objectState os;
		os.valid = false;
		osv.push_back(os);
	}

	cout << "Parent\t";
	cout << "Gropoff\t";	
	cout << "WAToff\t";	
	cout << "Names\t";	
	cout << "Truck\t";	
	cout << "Plant\t";

	for(unsigned int i=0; i < numStudents; i++) {
		cout << "Stud" << i << '\t';
	}

	for(unsigned int i=0; i < numVendingMachines; i++) {
		cout << "Mach" << i << '\t';
	}

	for(unsigned int i=0; i < numCouriers; i++) {
		cout << "Cour" << i << '\t';
	}
	cout << endl;

	for(unsigned int i=0; i < total; i++) {
		cout << "*******\t";
	}
	cout << endl;
}


objectState& Printer::getRef(Printer::Kind kind, unsigned int lid) {
	switch(kind) {
		case Printer::Student:
			return osv[6 + lid];
		case Printer::Vending:
			return osv[6 + numStudents + lid];
		case Printer::Courier:
			return osv[6 + numVendingMachines + lid];
		default:
			return osv[kind];
	}
}

void Printer::print(Printer::Kind kind, char state) {
	if(state == 'F') {
		finish(kind);
	} else {
		objectState &osRef = osv[kind];

		if(osRef.valid) {
			flush();
		}
		osRef.state = state;
		osRef.valid = true;		
	}
}

void Printer::print(Printer::Kind kind, char state, int value1) {
	if(state == 'F') {
		finish(kind);
	} else {
		objectState &osRef = osv[kind];

		if(osRef.valid) {
			flush();
		}
		osRef.state = state;
		osRef.value1 = value1;
		osRef.valid = true;
	}
}

void Printer::print(Printer::Kind kind, char state, int value1, int value2) {
	if(state == 'F') {
		finish(kind);
	} else {
		objectState &osRef = osv[kind];

		if(osRef.valid) {
			flush();
		}
		osRef.state = state;
		osRef.value1 = value1;
		osRef.value2 = value2;
		osRef.valid = true;
	}
}

void Printer::print(Printer::Kind kind, unsigned int lid, char state) {
	if(state == 'F') {
		finish(kind, lid);
	} else {
		objectState &osRef = getRef(kind, lid);

		if(osRef.valid) {
			flush();
		}
		osRef.lid = lid;
		osRef.state = state;
		osRef.valid = true;
	}	
}

void Printer::print(Printer::Kind kind, unsigned int lid, char state, int value1) {
	if(state == 'F') {
		finish(kind, lid);
	} else {
		objectState &osRef = getRef(kind, lid);

		if(osRef.valid) {
			flush();
		}
		osRef.lid = lid;
		osRef.state = state;
		osRef.value1 = value1;
		osRef.valid = true;
	}
}

void Printer::print(Printer::Kind kind, unsigned int lid, char state, int value1, int value2) {
	if(state == 'F') {
		finish(kind, lid);
	} else {
		objectState &osRef = getRef(kind, lid);

		if(osRef.valid) {
			flush();
		}
		osRef.lid = lid;
		osRef.state = state;
		osRef.value1 = value1;
		osRef.value2 = value2;
		osRef.valid = true;
	}
}



