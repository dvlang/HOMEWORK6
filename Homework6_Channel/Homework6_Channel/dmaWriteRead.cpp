#include "dmaWriteRead.h"
#include <stdlib.h>
#include <time.h>

void transmitter::writeBlocks()
{
//	const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
	int i, j = 0;
	int start, count;
	bool done = true;
	sc_lv<8> data[128];

	srand(device*(unsigned)time(NULL));

	cout << "Initiator transmitter " << device << " online... idle at " << sc_time_stamp() << endl;
		while(true){

		srand(device*(unsigned)time(NULL));
		wait((rand()% delay) * 30, SC_NS);

		//		cout << "TRS: Device " << device<< endl;


		//fills buffer with rando data
		//start=100*(i+1);
		start = 100;
		//count=12+i*2;
		if (done) {
			done = false;
			srand(device*(unsigned)time(NULL));
			count = 1 + (rand() % 128);
			//cout << "trans: count updatelp; Device " << device << " count is " << count << endl;
			for (j = 0; j < count; j++) {
				data[j] = start * 100 + j;
			}
			//		cout << "trans_wb: my name is " << name << endl;
			srand(device*(unsigned)time(NULL));
			//rand()%
			wait(rand() % 10, SC_NS);


		//	request->write(SC_LOGIC_1);
			
			//wait(1, SC_NS);
			
		}
			//arbiter needs to be 
		request->write(SC_LOGIC_1);
		cout << "TRS: " << device << " Sent request to send " << count << " bytes at " << sc_time_stamp() << endl;
		req->arbiter(device, count);
		wait(10, SC_NS);
			
			//wait(1, SC_NS);

		
		if (gnt->read() == SC_LOGIC_1) {
			cout << "TRS: " << device << " Got a GRANT! at " << sc_time_stamp() << endl;
			out->burstWrite(start, count, data);

			cout << "TRS: " << device << " return from BURSTWRITE() at " << sc_time_stamp() << endl;


		
			wait(1, SC_NS);
			done = true;
			request->write(SC_LOGIC_0);
			wait(1, SC_NS);
 			req->arbiter(device, count);	//sending count shouldnt matter, just need to kick the arb
			wait(10, SC_NS);

		}

	}
}

void receiver::readBlocks()
{
/*	int i, j = 0;
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
	}*/
}

