#include "interfaceClasses.h"

class dma : public sc_channel, public dma_write_if, public dma_read_if, public dma_arb_if {

public:
	sc_out_rv<16> address_p;
	sc_inout_rv<8> data_p;

	//NEW
	//sc_inout_rv<8> data_p2;
	//sc_inout_rv<8> data_p3;
	//sc_inout_rv<8> data_p4;
	//sc_inout_rv<8> data_p5;
	sc_out_resolved gnt1, gnt2, gnt3, gnt4, gnt5;
	sc_in_resolved req1;
	sc_in_resolved req2, req3, req4, req5;
	//END NEW

	sc_out_resolved rw_p;

//	SC_HAS_PROCESS(dma);
//		dma(sc_module_name name);
	dma (sc_module_name name): sc_channel(name){};

	virtual void burstWrite( int dstAddr, int count, sc_lv<8>* data );
	virtual void burstRead(int srcAddr, int count, sc_lv<8>* data);
	virtual void arbiter(const char * name, int count);
	
	
};
