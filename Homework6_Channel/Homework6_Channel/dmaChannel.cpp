#include "dmaChannel.h"

void dma::burstWrite( int dstAddr, int count, sc_lv<8> *data ) {
	sc_lv<8> *ite = data;

	cout << "MEM: !!!Start burst of "  << count << " bytes at " << sc_time_stamp() << endl;

	for (int i=0; i<count; i++) {
		address_p->write(dstAddr++);
		data_p->write( *(ite++) );
		wait(10, SC_NS);
		
		rw_p->write(SC_LOGIC_0); // Write pulse
		wait(50, SC_NS);
		rw_p->write(SC_LOGIC_Z);
		
		address_p->write("ZZZZZZZZZZZZZZZZ");
		data_p->write("ZZZZZZZZ");

		wait(10, SC_NS);
		//cout << "MEM: burstwrite() i: "<<i << endl;
	}
	cout << "MEM: finished burstwrite of " <<count <<" bytes at " << sc_time_stamp() << endl;

}

void dma::burstRead(int srcAddr, int count, sc_lv<8>* data) {
/*
	for (int i=0; i<count; i++) {
		address_p->write(srcAddr++);
		wait(10, SC_NS);

		rw_p->write(SC_LOGIC_1); // Read pulse
		wait(10, SC_NS);

		*(data++) = data_p->read();
		
		wait(40, SC_NS);
		rw_p->write(SC_LOGIC_Z);

		address_p->write("ZZZZZZZZZZZZZZZZ");
		data_p->write("ZZZZZZZZ");
		wait(10, SC_NS);
   }*/
}

//void dma::arbiter(const char * name, int count) {
void dma::arbiter(int name, int count) {
	bool skipgrant = false;


//	cout << "ARB: request from: " << name << endl;
//		cout << "ARB_req_ary: " << req1->read()<< " " << req2->read() << " " << req3->read() << " " << req4->read() << " " << req5->read() << endl;
		cout << "ARB: Current Device w/ grant " << grant << endl;
		
		//log the count from the transmitter into an array
		switch (name) {
		case 1:
			countarray[0] = count;
			reqarray[0] = 1;
			break;
		case 2:
			countarray[1] = count;
			reqarray[1] = 1;
			break;
		case 3:
			countarray[2] = count;
			reqarray[2] = 1;
			break;
		case 4:
			countarray[3] = count;
			reqarray[3] = 1;
			break;
		case 5:
			countarray[4] = count;
			reqarray[4] = 1;
			break;
		default:
			cout << "ARB: req selection error" << endl;
			break;
		}

		//clear the previous transmitter's grant permission
		if ((req1->read() == SC_LOGIC_0) && (grant == 1)) {
			grant = 0;
			//gnt1->write(SC_LOGIC_0);
			skipgrant = true;
			reqarray[0] = 0;
			cout << "ARB: clear grant 1 at " << sc_time_stamp() << endl;

		}
		else if ((req2->read() == SC_LOGIC_0) && (grant == 2)) {
			grant = 0;
			//gnt2->write(SC_LOGIC_0);
			skipgrant = true;
			reqarray[1] = 0;
			cout << "ARB: clear grant 2 at " << sc_time_stamp() << endl;
		}
		else if ((req3->read() == SC_LOGIC_0) && (grant == 3)) {
			grant = 0;
		//	gnt3->write(SC_LOGIC_0);
			skipgrant = true;
			reqarray[2] = 0;
			cout << "ARB: clear grant 3 at " << sc_time_stamp() << endl;
		}
		else if ((req4->read() == SC_LOGIC_0) && (grant == 4)) {
			grant = 0;
		//	gnt4->write(SC_LOGIC_0);
			skipgrant = true;
			reqarray[3] = 0;
			cout << "ARB: clear grant 4 at " << sc_time_stamp() << endl;
		}
		else if ((req5->read() == SC_LOGIC_0) && (grant == 5)) {
			grant = 0;
			//gnt5->write(SC_LOGIC_0);
			skipgrant = true;
			reqarray[4] = 0;
			cout << "ARB: clear grant 5 at " << sc_time_stamp() << endl;
		}
		else {
			grant = grant;
		}

		if (skipgrant!=true) {
			//print out the array
			cout << "ARB: Count Array ";
			for (int y = 0; y < 5; y++) {
				cout << " " << countarray[y];
			}
			cout << endl;

			//find smallest value in array

			int smallest = 129;
			int location = 0;
			for (int i = 0; i < 5; ++i) {
				if ((countarray[i] < smallest) && (reqarray[i] == 1)) {
					smallest = countarray[i];
					location = i;
//					cout << "smallest updated" << endl;
				}
			}
//			cout << "ARB: smallest value " << smallest << " at location " << location << " is req # " << location + 1 << endl;
//			cout << "ARB_gnt_before_set: " << grant << endl;

	//assert the grant to the target with lowest byte count
			if (grant == 0) {
				switch (location) {
				case 0:
					gnt1->write(SC_LOGIC_1);
					gnt2->write(SC_LOGIC_0);
					gnt3->write(SC_LOGIC_0);
					gnt4->write(SC_LOGIC_0);
					gnt5->write(SC_LOGIC_0);
					cout << "ARB: GNT " << location + 1 << " asserted at " << sc_time_stamp() << endl;
					grant = 1;
					break;
				case 1:
					gnt1->write(SC_LOGIC_0);
					gnt2->write(SC_LOGIC_1);
					gnt3->write(SC_LOGIC_0);
					gnt4->write(SC_LOGIC_0);
					gnt5->write(SC_LOGIC_0);
					cout << "ARB: GNT " << location + 1 << " asserted at " << sc_time_stamp() << endl;
					grant = 2;
					break;
				case 2:
					gnt1->write(SC_LOGIC_0);
					gnt2->write(SC_LOGIC_0);
					gnt3->write(SC_LOGIC_1);
					gnt4->write(SC_LOGIC_0);
					gnt5->write(SC_LOGIC_0);
					cout << "ARB: GNT " << location + 1 << " asserted at " << sc_time_stamp() << endl;
					grant = 3;
					break;
				case 3:
					gnt1->write(SC_LOGIC_0);
					gnt2->write(SC_LOGIC_0);
					gnt3->write(SC_LOGIC_0);
					gnt4->write(SC_LOGIC_1);
					gnt5->write(SC_LOGIC_0);
					cout << "ARB: GNT " << location + 1 << " asserted at " << sc_time_stamp() << endl;
					grant = 4;
					break;
				case 4:
					gnt1->write(SC_LOGIC_0);
					gnt2->write(SC_LOGIC_0);
					gnt3->write(SC_LOGIC_0);
					gnt4->write(SC_LOGIC_0);
					gnt5->write(SC_LOGIC_1);
					cout << "ARB: GNT " << location + 1 << " asserted at " << sc_time_stamp() << endl;
					grant = 5;
					break;
				default:
					/*gnt1->write(SC_LOGIC_0);
					gnt2->write(SC_LOGIC_0);
					gnt3->write(SC_LOGIC_0);
					gnt4->write(SC_LOGIC_0);
					gnt5->write(SC_LOGIC_0);
					grant = 0;*/
					break;
				}
			}
			else if (grant == 1) {
				gnt1->write(SC_LOGIC_1);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_0);
			}
			else if (grant == 2) {
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_1);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_0);
			}
			else if (grant == 3) {
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_1);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_0);
			}
			else if (grant == 4) {
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_1);
				gnt5->write(SC_LOGIC_0);
			}
			else if (grant == 5) {
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_1);
			}
			else {
				/*	gnt1->write(SC_LOGIC_0);
					gnt2->write(SC_LOGIC_0);
					gnt3->write(SC_LOGIC_0);
					gnt4->write(SC_LOGIC_0);
					gnt5->write(SC_LOGIC_0);*/
			}

	/*		cout << "ARB: grant 1 is " << gnt1->read() << endl;
			cout << "ARB: grant 2 is " << gnt2->read() << endl;
			cout << "ARB: grant 3 is " << gnt3->read() << endl;
			cout << "ARB: grant 4 is " << gnt4->read() << endl;
			cout << "ARB: grant 5 is " << gnt5->read() << endl;
*/
		}
		//}
		
	

}
