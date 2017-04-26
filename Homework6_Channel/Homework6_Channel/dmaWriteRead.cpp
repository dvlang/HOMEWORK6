#include "dmaWriteRead.h"
#include <stdlib.h>
#include <time.h>

void transmitter::writeBlocks()
{
	const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
	int i, j = 0;
	int start, count;
	bool done = false;
	sc_lv<8> data[128];

	srand(device*(unsigned)time(NULL));

	//for(i=0; i<=1; i++) {	//this loop looks like it will control how many times this will run set i (orig 3)
		while(true){
		cout << "Device: " << device << " at " << sc_time_stamp() << " is idle ...\n";
		cout << "Device: " << device << " delay " << delay << endl;
		wait(delay * 30, SC_NS);
		cout << "Device: " << device << " at " << sc_time_stamp() << " has requested ...\n";
		//fills buffer with rando data
		//start=100*(i+1);
		start = 100;
		//count=12+i*2;
		srand(device*(unsigned)time(NULL));
		count = 1+(rand() % 128);
		cout << "count is " << count << endl;
		for(j=0; j<count; j++) {
			data[j]=start*100+j;
		}
//		cout << "trans_wb: my name is " << name << endl;
		srand(device*(unsigned)time(NULL));
		//rand()%
		wait(rand()%10, SC_NS);

		
		request->write(SC_LOGIC_1);
		wait(1, SC_NS);
		req->arbiter(name, count);// = SC_LOGIC_1;
		cout << "trans_wb: " << name << " Sent a request at " << sc_time_stamp() << endl;
		wait(1, SC_NS);
		
		//while (gnt != SC_LOGIC_1) { cout << "trans_wb: " << name << " Watitng " << sc_time_stamp() << " " << endl; };
		//while (gnt->read() != SC_LOGIC_1) { cout << name << " here" << endl; };
		if (gnt->read() == SC_LOGIC_1) {
			cout << "trans_wb: " << name << " Got a GRANT!" << endl;
			out->burstWrite(start, count, data);
			cout << "return from BURSTWRITE" << endl;
			cout << "TRANS: At " << sc_time_stamp() << " write start at: "
				<< start << " count " << count << ", first data: "
				<< data[0] << '\n';
		
			wait(13, SC_NS);
			done = true;
			request->write(SC_LOGIC_0);
			wait(1, SC_NS);
		}

	}
}

void receiver::readBlocks()
{
	int i, j = 0;
	int start, count;
	sc_lv<8> data[128];
	for(i=0; i<=1; i++) {	//this loop looks like it will control how many times this will run set i (orig 3)
		start=100*(i+1);
		count=12+i*2;
		wait(count*10+11, SC_NS);
		in->burstRead(start, count, data);
		cout << "RCV: At " << sc_time_stamp() << " read start at: " 
			 << start << " count " << count << ", first data: " 
			 << data[0] << '\n';
		wait(13, SC_NS);
	}
}

