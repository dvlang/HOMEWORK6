#include "dmaChannel.h"

void dma::burstWrite( int dstAddr, int count, sc_lv<8> *data ) {
	sc_lv<8> *ite = data;
	cout << "pump them bytes!" << endl;
	cout << "At " << sc_time_stamp() << "count is " << count << endl;

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
	}
}

void dma::burstRead(int srcAddr, int count, sc_lv<8>* data) {

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
   }
}

void dma::arbiter(const char * name, int count) {
	
	int i = 0;
	int countarray[5] = {0,0,0,0,0};


	//while (true) {
	//while (i<1){
/*
		// read cycle
		if (req1->read() == SC_LOGIC_1) {
			//data_p->write(*(mem_arr + (sc_uint<16>(address_p->read()))));
			cout << "ARB: Got a request!" << endl;
			gnt1->write(SC_LOGIC_1);
			// write cycle
		}
		else if (req1->read() == SC_LOGIC_0) {
			//*(mem_arr + (sc_uint<16>(address_p->read()))) = data_p->read();			
			cout << "ARB: No a request!" << endl;
			gnt1->write(SC_LOGIC_0);
		}
		wait();
	*/
		cout << "ARB: " << req1->read()<< " " << req2->read() << " " << req3->read() << " " << req4->read() << " " << req5->read() << endl;

		if (req1->read() == SC_LOGIC_1) {
			cout << "ARB: Request 1 :" << count << endl;
			countarray[0] = count;
		}
		if (req2->read() == SC_LOGIC_1) {
			cout << "ARB: Request 2 :" << count << endl;
			countarray[1] = count;
		}
		if (req3->read() == SC_LOGIC_1) {
			cout << "ARB: Request 3 :" << count << endl;
			countarray[2] = count;
		}
		if (req4->read() == SC_LOGIC_1) {
			cout << "ARB: Request 4 :" << count << endl;
			countarray[3] = count;
		}
		if (req5->read() == SC_LOGIC_1) {
			cout << "ARB: Request 5 :" << count << endl;
			countarray[4] = 2;	//forced set for test
		}
		//gnt1->write(SC_LOGIC_1);
		
		for (int y = 0; y < 5; y++) {
			cout << "Array location " << y << " is " << countarray[y] << endl;
		}

		//find smallest value in array
		int smallest = countarray[0];
		int location = 0;
		for (int i = 1; i < sizeof(countarray) / sizeof(countarray[0]); ++i) {
			if (countarray[i] < smallest) {
				smallest = countarray[i];
				location = i+1;
			}
		}
		cout << "smallest value " << smallest << " at location " << location-1 << " is req # " << location << endl;

		switch (location) {
		case 1:
			gnt1->write(SC_LOGIC_1);
			gnt2->write(SC_LOGIC_0);
			gnt3->write(SC_LOGIC_0);
			gnt4->write(SC_LOGIC_0);
			gnt5->write(SC_LOGIC_0);
			cout << "GNT " << location << " asserted" << endl;
			break;
		case 2:
			gnt1->write(SC_LOGIC_0);
			gnt2->write(SC_LOGIC_1);
			gnt3->write(SC_LOGIC_0);
			gnt4->write(SC_LOGIC_0);
			gnt5->write(SC_LOGIC_0);
			cout << "GNT " << location << " asserted" << endl;
			break;
		case 3:
			gnt1->write(SC_LOGIC_0);
			gnt2->write(SC_LOGIC_0);
			gnt3->write(SC_LOGIC_1);
			gnt4->write(SC_LOGIC_0);
			gnt5->write(SC_LOGIC_0); 
			cout << "GNT " << location << " asserted" << endl;
			break;
		case 4:
			gnt1->write(SC_LOGIC_0);
			gnt2->write(SC_LOGIC_0);
			gnt3->write(SC_LOGIC_0);
			gnt4->write(SC_LOGIC_1);
			gnt5->write(SC_LOGIC_0);
			cout << "GNT " << location << " asserted" << endl;
			break;
		case 5:
			gnt1->write(SC_LOGIC_0);
			gnt2->write(SC_LOGIC_0);
			gnt3->write(SC_LOGIC_0);
			gnt4->write(SC_LOGIC_0);
			gnt5->write(SC_LOGIC_1);
			cout << "GNT " << location << " asserted" << endl;
			break;
		default:
			cout << "req selection error" << endl;
			break;
		}
		

		//i++;
	//	}
		
	

}
