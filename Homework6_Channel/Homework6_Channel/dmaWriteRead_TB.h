#include "dmaWriteRead.h"
#include "memory.h"

SC_MODULE (dmaWriteRead_TB) {
	sc_signal_rv<16> address_s;
	sc_signal_rv<8> data_s, data_s2, data_s3, data_s4, data_s5;
	sc_signal_resolved rw_s;
	sc_signal_resolved gnt1, gnt2, gnt3, gnt4, gnt5;
	sc_signal_resolved req1;
	sc_signal_resolved req2, req3, req4, req5;
	const int trans1= 1;
	
	dma* DMA1;
	transmitter* TRS1;
	transmitter* TRS2;
	transmitter* TRS3;
	transmitter* TRS4;
	transmitter* TRS5;
	receiver* RCV1;
	memory* MEM1;

	SC_CTOR(dmaWriteRead_TB) {
		DMA1 = new dma("DMA_Channel");
			DMA1->address_p(address_s);
			//NEW
			DMA1->data_p(data_s);
			//DMA1->data_p2(data_s2);
			//DMA1->data_p3(data_s3);
			//DMA1->data_p4(data_s4);
		//	DMA1->data_p5(data_s5);
			DMA1->gnt1(gnt1);
			DMA1->gnt2(gnt2);
			DMA1->gnt3(gnt3);
			DMA1->gnt4(gnt4);
			DMA1->gnt5(gnt5);
			DMA1->req1(req1);
			DMA1->req2(req2);
			DMA1->req3(req3);
			DMA1->req4(req4);
			DMA1->req5(req5);
			//END NEW
			DMA1->rw_p(rw_s);
		TRS1 = new transmitter("T1",1,4);
			TRS1->out(*DMA1);
			TRS1->req(*DMA1);
			TRS1->gnt(gnt1);
			TRS1->request(req1);

		TRS2 = new transmitter("T2",2,2);
			TRS2->out(*DMA1);
			TRS2->req(*DMA1);
			TRS2->gnt(gnt2);
			TRS2->request(req2);

		TRS3 = new transmitter("T3",3,1);
			TRS3->out(*DMA1);
			TRS3->req(*DMA1);
			TRS3->gnt(gnt3);
			TRS3->request(req3);

		TRS4 = new transmitter("T4",4,6);
			TRS4->out(*DMA1);
			TRS4->req(*DMA1);
			TRS4->gnt(gnt4);
			TRS4->request(req4);
			
		TRS5 = new transmitter("T5",5,8);
			TRS5->out(*DMA1);
			TRS5->req(*DMA1);
			TRS5->gnt(gnt5);
			TRS5->request(req5);

	//	RCV1 = new receiver("Receiver");
	//		RCV1->in(*DMA1);
		MEM1 = new memory("Memory");
			MEM1->address_p(address_s);
			MEM1->data_p(data_s);
			MEM1->rw_p(rw_s);


			
	}
	//void monitor 
};

