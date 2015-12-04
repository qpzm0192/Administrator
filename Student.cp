#include "Student.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "Groupoff.h"
#include "WATCard.h"
#include "VendingMachine.h"
#include "MPRNG.h"
#include "uFuture.h"

extern MPRNG rng;

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
				unsigned int id, unsigned int maxPurchases)
				: prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), 
				maxPurchases(maxPurchases) {
}

void Student::main() {
	unsigned int purchases = rng(1, maxPurchases);
	unsigned int flavour = rng(0,3);
	prt.print(Printer::Student, id, 'S', flavour, purchases);

	unsigned int sodaCost;

	WATCard::FWATCard fCard = cardOffice.create(id, 5);
	WATCard *card = NULL;
	
	WATCard::FWATCard fGift = groupoff.giftCard();

	VendingMachine *vending = nameServer.getMachine(id);
	prt.print(Printer::Student, id, 'V', vending->getId());

	sodaCost = vending->cost();

	for(;;) {
		if(purchases == 0) break; // exit outter for
		yield(rng(1,10));

		// make to purchase 
		try {
			for(;;) { // re-attempt puchase without yielding
				try {
					if(fGift.available()) { // use giftcard
						vending->buy(flavour, fGift);
						prt.print(Printer::Student, id, 'G', fGift.getBlance());

						fGift.reset();
					} else if(fCard.available()) { // use watcard
						vending->buy(flavour, fCard);
						prt.print(Printer::Student, id, 'B', fCard.getBlance());
					}
					break; // exit inner for			
				} _Catch(WATCardOffice::Lost) {
					prt.print(Printer::Student, id, 'L');
					fCard = cardOffice.create(id, 5);
				} // inner try
			} // inner for
			purchases--;
		} _Catch(VendingMachine::Funds) {
			cardOffice.transfer(id, 5 + sodaCost, fCard);
		} _Catch(VendingMachine::Stock) {
			vending = nameServer.getMachine(id);
		} // outter try
	} // outter for

	prt.print(Printer::Student, id, 'F');
}