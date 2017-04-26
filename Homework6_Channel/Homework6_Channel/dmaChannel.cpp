#include "dmaChannel.h"

void dma::burstWrite( int dstAddr, int count, sc_lv<8> *data ) {
	sc_lv<8> *ite = data;
	cout << "pump them bytes!" << endl;
	cout << "At " << sc_time_stamp() << "count is " << count << endl;
	cout << "Count" << sc_time_stamp() << "count is " << count << endl;
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
		cout << "burstwrite i: "<<i << endl;
	}
	cout << "finished burst" << endl;

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

//void dma::arbiter(const char * name, int count) {
void dma::arbiter(int name, int count) {
	//int i = 0;
	//int countarray[5] = {128,128,128,128,128};
//	int grant[5] = { 0,0,0,0,0 };
	

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
		cout << "ARB_req_ary: " << req1->read()<< " " << req2->read() << " " << req3->read() << " " << req4->read() << " " << req5->read() << endl;
		cout << "ARB_cur_gnt: " << grant << endl;

		//clear the previous transmitter's grant permission
		if ((req1->read() == SC_LOGIC_0)&&(grant==1)) {
			grant = 0;
			reqarray[0] = 0;
			cout << "clear grant 1" << endl;
			//while (true) {};
		}
		else if ((req2->read() == SC_LOGIC_0) && (grant == 2)) {
			grant = 0;
			reqarray[1] = 0;
			cout << "clear grant 2" << endl;
		}
		else if ((req3->read() == SC_LOGIC_0) && (grant == 3)) {
			grant = 0;
			reqarray[2] = 0;
			cout << "clear grant 3" << endl;
		}
		else if ((req4->read() == SC_LOGIC_0) && (grant == 4)) {
			grant = 0;
			reqarray[3] = 0;
			cout << "clear grant 4" << endl;
		}
		else if ((req5->read() == SC_LOGIC_0) && (grant == 5)) {
			grant = 0;
			reqarray[4] = 0;
			cout << "clear grant 5" << endl;
		}
		else {
			grant = grant;
		}
		
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
			cout << "req selection error" << endl;
			break;

		}


		
		for (int y = 0; y < 5; y++) {
			cout << "Array location " << y << " is " << countarray[y] << endl;
		}

		//find smallest value in array
		int smallest = countarray[0];
		int location = 0;
		for (int i = 1; i < sizeof(countarray) / sizeof(countarray[0]); ++i) {
			if ((countarray[i] < smallest)&&(reqarray[i]==1)) {
				smallest = countarray[i];
				location = i;
			}
		}
		cout << "smallest value " << smallest << " at location " << location << " is req # " << location+1 << endl;

		if (grant==0) {
			switch (location) {
			case 0:
				gnt1->write(SC_LOGIC_1);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_0);
				cout << "GNT " << location + 1 << " asserted" << endl;
				grant = 1;
				break;
			case 1:
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_1);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_0);
				cout << "GNT " << location + 1 << " asserted" << endl;
				grant = 2;
				break;
			case 2:
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_1);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_0);
				cout << "GNT " << location + 1 << " asserted" << endl;
				grant = 3;
				break;
			case 3:
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_1);
				gnt5->write(SC_LOGIC_0);
				cout << "GNT " << location + 1 << " asserted" << endl;
				grant = 4;
				break;
			case 4:
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_1);
				cout << "GNT " << location + 1 << " asserted" << endl;
				grant = 5;
				break;
			default:
				gnt1->write(SC_LOGIC_0);
				gnt2->write(SC_LOGIC_0);
				gnt3->write(SC_LOGIC_0);
				gnt4->write(SC_LOGIC_0);
				gnt5->write(SC_LOGIC_0);
				//grant = 0;
				break;
			}
		}
		

		//i++;
		//}
		
	

}
