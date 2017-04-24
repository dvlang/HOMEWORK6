#include "dmaChannel.h"

void dma::burstWrite( int dstAddr, int count, sc_lv<8> *data ) {
	sc_lv<8> *ite = data;

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
	cout << "ARB running" <<endl;
	int i = 0;

	//while (true) {
	while (i<1){
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
		cout << "ARB: Request from: "<< name <<" passed count is " << count << endl;
		gnt1->write(SC_LOGIC_1);
		i++;
	}

}
