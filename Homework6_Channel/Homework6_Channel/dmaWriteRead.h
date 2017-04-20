#include "dmaChannel.h"

SC_MODULE (transmitter) {
	sc_port<dma_write_if> out; // with if out is a pointer

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

