#include "memory.h"

memory::memory(sc_module_name name, int mem_size): sc_module(name) {
	mem_arr = new sc_lv<8>[899];
	for (int i=0; i< mem_size; i++) {
		mem_arr[i] = sc_lv<8>(0);
	}
	SC_THREAD(run);
		sensitive << rw_p;
}
void memory::run() {
	while(true) {
		// read cycle
		if (rw_p->read() == SC_LOGIC_1) {
			data_p->write( *( mem_arr+(sc_uint<16>(address_p->read())) ) );
			// write cycle
		}
		else if (rw_p->read() == SC_LOGIC_0) {
			*(mem_arr + (sc_uint<16>(address_p->read()))) = data_p->read();
		}
		wait();
	}
}
