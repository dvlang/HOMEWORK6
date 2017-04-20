#include "dmaWriteRead.h"
#include "memory.h"

SC_MODULE (dmaWriteRead_TB) {
	sc_signal_rv<16> address_s;
	sc_signal_rv<8> data_s;
	sc_signal_resolved rw_s;
	
	dma* DMA1;
	transmitter* TRS1;
	receiver* RCV1;
	memory* MEM1;

	SC_CTOR(dmaWriteRead_TB) {
		DMA1 = new dma("DMA_Channel");
			DMA1->address_p(address_s);
			DMA1->data_p(data_s);
			DMA1->rw_p(rw_s);
		TRS1 = new transmitter("Transmitter");
			TRS1->out(*DMA1);
		RCV1 = new receiver("Receiver");
			RCV1->in(*DMA1);
		MEM1 = new memory("Memory");
			MEM1->address_p(address_s);
			MEM1->data_p(data_s);
			MEM1->rw_p(rw_s);

			cout << "hi dan" << endl;
			
	}
	//void monitor 
};

