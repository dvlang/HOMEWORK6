#include "interfaceClasses.h"

class dma : public sc_channel, public dma_write_if, public dma_read_if {

public:
	sc_out_rv<16> address_p;
	sc_inout_rv<8> data_p;
	sc_out_resolved rw_p;

//	SC_HAS_PROCESS(dma);
//		dma(sc_module_name name);
	dma (sc_module_name name): sc_channel(name){};

	virtual void burstWrite( int dstAddr, int count, sc_lv<8>* data );
	virtual void burstRead(int srcAddr, int count, sc_lv<8>* data);
};
