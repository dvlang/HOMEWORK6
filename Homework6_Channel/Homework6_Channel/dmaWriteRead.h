#include "dmaChannel.h"

SC_MODULE (transmitter) {
	sc_port<dma_write_if> out; // with if out is a pointer
	sc_in_resolved gnt;
	sc_port<dma_arb_if> req;
	//sc_out_resolved req;

	SC_CTOR (transmitter)
	{
		SC_THREAD(writeBlocks);
	}
	void writeBlocks();
};

SC_MODULE (receiver) {
	sc_port<dma_read_if> in;

	SC_CTOR (receiver)
	{
		SC_THREAD(readBlocks);
	}
	void readBlocks();
};

