
#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include "storage.h"

namespace bubi {
	class Argument {
	public:
		Argument();
		~Argument();

		bool help_modle_;
		bool drop_db_;

		bool peer_addr_;
		bool clear_peer_addresses_;
		bool clear_consensus_status_;
		bool create_hardfork_;

		bool Parse(int argc, char *argv[]);
		void Usage();
		void ShowHardwareAddress();
		void ShowNodeId(int argc, char *argv[]);
		void RequestCert(int argc, char *argv[]);
		void ShowRequest(int argc, char *argv[]);
	};

	extern bool g_enable_;

	void InstallSignal();
}
#endif
