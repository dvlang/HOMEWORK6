#include "dmaWriteRead.h"

void transmitter::writeBlocks()
{
	int i, j = 0;
	int start, count;
	sc_lv<8> data[25];
	for(i=0; i<=3; i++) {
		start=100*(i+1);
		count=12+i*2;
		for(j=0; j<count; j++) {
			data[j]=start*100+j;
		}
		out->burstWrite(start, count, data);
		cout << "At " << sc_time_stamp() << " write start at: " 
			 << start << " count " << count << ", first data: " 
			 << data[0] << '\n';
		wait(13, SC_NS);
	}
}

void receiver::readBlocks()
{
	int i, j = 0;
	int start, count;
	sc_lv<8> data[25];
	for(i=0; i<=3; i++) {
		start=100*(i+1);
		count=12+i*2;
		wait(count*10+11, SC_NS);
		in->burstRead(start, count, data);
		cout << "At " << sc_time_stamp() << " read start at: " 
			 << start << " count " << count << ", first data: " 
			 << data[0] << '\n';
		wait(13, SC_NS);
	}
}

