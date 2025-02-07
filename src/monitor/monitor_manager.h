
#ifndef MONITOR_MANAGER_H_
#define MONITOR_MANAGER_H_

#include <proto/cpp/chain.pb.h>
#include <common/network.h>
#include <monitor/system_manager.h>

namespace bubi {
	class MonitorManager :public utils::Singleton<MonitorManager>,
		public StatusModule,
		public TimerNotify,
		public Network,
		public utils::Runnable {
		friend class utils::Singleton<bubi::MonitorManager>;
	public:
		MonitorManager();
		~MonitorManager();

		
		//virtual bool Send(const ZMQTaskType type, const std::string& buf);

		bool Initialize();
		bool Exit();

		virtual void OnTimer(int64_t current_time) override;
		virtual void OnSlowTimer(int64_t current_time) override;
		virtual void GetModuleStatus(Json::Value &data);

		bool SendMonitor(int64_t type, const std::string &data);
		
	protected:
		virtual void Run(utils::Thread *thread) override;

	private:
		virtual void OnDisconnect(Connection *conn);
		virtual bubi::Connection *CreateConnectObject(bubi::server *server_h, bubi::client *client_,
			bubi::tls_server *tls_server_h, bubi::tls_client *tls_client_h,
			bubi::connection_hdl con, const std::string &uri, int64_t id);

		// Handlers
		bool OnMonitorHello(protocol::WsMessage &message, int64_t conn_id);
		bool OnMonitorRegister(protocol::WsMessage &message, int64_t conn_id);
		bool OnBubiStatus(protocol::WsMessage &message, int64_t conn_id);
		bool OnLedgerStatus(protocol::WsMessage &message, int64_t conn_id);
		bool OnSystemStatus(protocol::WsMessage &message, int64_t conn_id);

		bool GetBubiStatus(monitor::BubiStatus &bubi_status);
		Connection * GetClientConnection();

	private:
		utils::Thread *thread_ptr_;

		std::string monitor_id_;

		uint64_t last_connect_time_;
		uint64_t connect_interval_;

		uint64_t check_alert_interval_;
		uint64_t last_alert_time_;

		uint64_t percent_interval_;
		uint64_t last_percent_time_;

		SystemManager system_manager_;
	};
}

#endif
