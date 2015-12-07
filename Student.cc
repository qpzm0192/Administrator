#include "Student.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "Groupoff.h"
#include "WATCard.h"
#include "VendingMachine.h"
#include "MPRNG.h"
#include "uFuture.h"
#include "iostream"

using namespace std;

extern MPRNG rng;

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
				unsigned int id, unsigned int maxPurchases)
				: prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), 
				maxPurchases(maxPurchases) {}

void Student::main() {
	unsigned int purchases = rng(1, maxPurchases);

	VendingMachine::Flavours flavour;
	switch(rng(0,3)) {
		case 0:
			flavour = VendingMachine::Apple;
			break;
		case 1:
			flavour = VendingMachine::Orange;
			break;
		case 2:
			flavour = VendingMachine::Grape;
			break;
		case 3:
			flavour = VendingMachine::Lemon;
			break;
	}

	prt.print(Printer::Student, id, 'S', flavour, purchases);

	unsigned int sodaCost;

	WATCard::FWATCard fCard = cardOffice.create(id, 5);
	
	WATCard::FWATCard fGift = groupoff.giftCard();

	VendingMachine *vending = nameServer.getMachine(id);
	prt.print(Printer::Student, id, 'V', vending->getId());

	sodaCost = vending->cost();

	for(;;) {
		if(purchases == 0) break; // exit outter for
		yield(rng(1,10));

		// make to purchase
		try {		
			_Select(fCard || fGift)	{
				if(fGift.available()) {
					// use gift card
					vending->buy(flavour, *(fGift()));
					prt.print(Printer::Student, id, 'G', fGift()->getBalance());
					fGift.reset();
				} else if(fCard.available()) {
					for(;;) {
						try {
							//use wat card
							vending->buy(flavour, *(fCard()));
							prt.print(Printer::Student, id, 'B', fCard()->getBalance());
							break;							
						} catch(WATCardOffice::Lost) {
							prt.print(Printer::Student, id, 'L');
							fCard = cardOffice.create(id, 5);
						}
					}
										
				}
			} // if available
			purchases--;
		} catch(VendingMachine::Funds) {
			fCard = cardOffice.transfer(id, 5 + sodaCost, fCard);
		} catch(VendingMachine::Stock) {
			vending = nameServer.getMachine(id);
			prt.print(Printer::Student, id, 'V', vending->getId());
		} // outter try			
		
	} // outter for

	prt.print(Printer::Student, id, 'F');
} // main

