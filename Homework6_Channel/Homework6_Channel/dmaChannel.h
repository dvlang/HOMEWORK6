#include "interfaceClasses.h"

class dma : public sc_channel, public dma_write_if, public dma_read_if, public dma_arb_if {

public:
	sc_out_rv<16> address_p;
	sc_inout_rv<8> data_p;
	sc_out_resolved gnt1, gnt2, gnt3, gnt4, gnt5;
	sc_in_resolved req1;
	sc_in_resolved req2, req3, req4, req5;
	sc_out_resolved rw_p;


	dma (sc_module_name name): sc_channel(name){};

	virtual void burstWrite( int dstAddr, int count, sc_lv<8>* data );
	virtual void burstRead(int srcAddr, int count, sc_lv<8>* data);

	virtual void arbiter(int name, int count);
	int countarray[5] = { 0,0,0,0,0 };
	int reqarray[5] = { 0,0,0,0,0 };
	int grant = 0;

	
};
