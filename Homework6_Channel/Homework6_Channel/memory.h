#include <systemc.h>

SC_MODULE (memory) {
	sc_in_rv<16> address_p;
	sc_inout_rv<8> data_p;
	sc_in_resolved rw_p;
	sc_lv<8> *mem_arr;

	SC_HAS_PROCESS(memory);
		memory(sc_module_name nm, int mem_size=899);
	~memory() {delete []mem_arr;}

public:
	void run();
	
};