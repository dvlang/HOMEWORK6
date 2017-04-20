#include "dmaChannel.h"

void dma::burstWrite( int dstAddr, int count, sc_lv<8> *data ) {
	sc_lv<8> *ite = data;

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

