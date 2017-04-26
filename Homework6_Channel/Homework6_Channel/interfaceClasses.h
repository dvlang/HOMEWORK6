#include <systemc.h>

class dma_write_if: virtual public sc_interface
	{
		public:
			virtual void burstWrite(int dstAddr, int count, sc_lv<8> *data ) = 0;
};

class dma_read_if: virtual public sc_interface
	{
		public:
			virtual void burstRead(int srcAddr, int count, sc_lv<8>* data) = 0;
};

class dma_arb_if : virtual public sc_interface
{
public:
	//virtual void arbiter(const char * name, int count) = 0;
	virtual void arbiter(int name, int count) = 0;

};
