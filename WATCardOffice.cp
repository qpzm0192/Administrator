#include "WATCardOffice.h"
#include "Printer.h"
#include "WATCard.h"
#include "Bank.h"
#include <vector>

using namespace std;

_Task WATCardOffice::Courier {

};

void WATCardOffice::main() {
	Courier *courArray[numCouriers];
	for(int i=0; i < numCouriers; i++) {
		courArray[i] = new Courier;
	}

	for(;;) {
		_Accept(create) {

		} or _Accept(transfer) {

		} or _When(jobVec.size() > 0) _Accept(requestWork) {

		}
		
	}

}

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers) 
	:prt(prt), bank(bank), numCouriers(numCouriers) {}


WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
	Args arg;
	arg.sid = sid;
	arg.amount = amount;

	Job j(arg);

	jobVec.push_back(j);

	return j.result;
}


WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
	Args arg;
	arg.sid = sid;
	arg.amount = amount;

	Job j(arg);
	j.result = card;

	jobVec.push_back(j);

	return j.result;
}


Job *WATCardOffice::requestWork() {
	return jobVec.pop_front();
}