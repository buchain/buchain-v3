﻿
#ifndef PEER_MANAGER_H_
#define PEER_MANAGER_H_

#include <utils/singleton.h>
#include <utils/net.h>
#include <common/general.h>
#include <common/private_key.h>
#include "peer_network.h"

namespace bubi {

	class PeerManager : public utils::Singleton<PeerManager>,
		public StatusModule,
		public TimerNotify,
		public utils::Runnable {
		friend class utils::Singleton<PeerManager>;
	public:
		PeerManager();
		~PeerManager();

		bool Initialize(char *serial_num = NULL, bool cert_enabled = false);
		bool Exit();

		virtual void OnTimer(int64_t current_time) override {};
		virtual void OnSlowTimer(int64_t current_time);

		virtual void Run(utils::Thread *thread) override;

		void Broadcast(int64_t type, const std::string &data);
		//bool SendMessage(int64_t peer_id, protocol::WsMessage &message);
		bool SendRequest(int64_t peer_id, int64_t type, const std::string &data);

		inline PeerNetwork& ConsensusNetwork() {
			return *consensus_network_;
		}

		inline std::string& GetSerialNumber() {
			return serial_num_;
		}
		std::string GetPeerNodeAddress() {
			return priv_key_.GetBase16Address();
		}

		virtual void GetModuleStatus(Json::Value &data);

	private:
		//high way to deliver urgent message asap
		PeerNetwork *consensus_network_;

		utils::Thread *thread_ptr_;
		PrivateKey priv_key_;
		std::string peer_node_address_;

		bool cert_enabled_;
		std::string serial_num_;
		utils::Mutex ca_list_mutex_;
	};
}

#endif

