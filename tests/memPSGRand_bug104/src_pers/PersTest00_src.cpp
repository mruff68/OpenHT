#include "Ht.h"
#include "PersTest00.h"

void CPersTest00::PersTest00() {
	if (PR1_htValid) {
		switch (PR1_htInst) {
		case TEST00_ENTRY: {
			break;
		}
		case TEST00_WR0: {
			break;
		}
		case TEST00_ST0: {
			break;
		}
		case TEST00_LD0: {
			break;
		}
		case TEST00_CHK0: {
			S_test00_0_dst_s0_data.read_addr(1);
			break;
		}
		case TEST00_RTN: {
			break;
		}
		default:
			assert(0);
		}
	}
	if (PR2_htValid) {
		switch (PR2_htInst) {
		case TEST00_ENTRY: {
			HtContinue(TEST00_WR0);
			break;
		}
		case TEST00_WR0: {
			GW2_test00_0_src_v0_data[3].write_addr(5, 5);
			GW2_test00_0_src_v0_data[3] = ((int16_t)0x0018a41147f6c400LL);
			HtContinue(TEST00_ST0);
			break;
		}
		case TEST00_ST0: {
			if (WriteMemBusy()) {
				HtRetry();
				break;
			}
			WriteMem_test00_0_src_v0_data(PR2_memAddr + 0, 3);
			WriteMemPause(TEST00_LD0);
			break;
		}
		case TEST00_LD0: {
			if (ReadMemBusy()) {
				HtRetry();
				break;
			}
			ReadMem_test00_0_dst_v0_data(PR2_memAddr + 0, 1, 0);
			ReadMemPause(TEST00_CHK0);
			break;
		}
		case TEST00_CHK0: {
			if (SR_test00_0_dst_s0_data.read_mem().test00_0_dst_v0_data[0] != ((int16_t)0x0018a41147f6c400LL)) {
				HtAssert(0, 0);
			}
			HtContinue(TEST00_RTN);
			break;
		}
		case TEST00_RTN: {
			if (SendReturnBusy_test00()) {
				HtRetry();
				break;
			}
			SendReturn_test00();
			break;
		}
		default:
			assert(0);
		}
	}
}
