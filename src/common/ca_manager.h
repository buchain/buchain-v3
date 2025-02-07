
#ifndef CA_MANAGER_H_
#define CA_MANAGER_H_

#include <string>
#include "ca.h"

namespace bubi {
	class CAManager {
	public:
		// make request certificate
		//bool RequestCA(char *common_name, char *organization, char *email, char *priv_password, char *hard_addr, char *node_id, char *out_msg);
		bool RequestCA(char *file_path, char *common_name, char *organization, char *email, char *priv_password,
			char *hard_addr, char *node_id, char *out_msg);

		// show request certificate
		bool ShowRequestCSR(char *req_file, char *out_msg);

		// check user entity certificate
		//int CheckCertificate(const bubi::P2pConfigure& p2p_configure, char *serial, bool& use_ca, char *out_msg);
		int CheckCertificate(const std::string& node_private_key, const std::string& verify_file, const std::string& chain_file, 
			const std::string& private_key_file, const std::string& private_password, const std::string& domain, const std::string& path, 
			const int& port, char *serial, bool& cert_enabled, char *out_msg);

		// verify certificate when connect
		//bool VerifyCertificate(void *x509, const bubi::SSLConfigure& ssl_configure, const void *ca_list, char *out_msg);
		bool VerifyCertificate(void *x509, const char *verify_file, const char * chain_file, const void *ca_lists, char *out_msg);

		// get all ca list
		//bool GetCertificatList(const bubi::CAServerConfigure& ca_server_configure, const std::string serial_num, void *ca_lists, char *out_msg);
		bool GetCertificatList(const std::string& domain, const std::string& path, const int& port, 
			const std::string serial_num, void *ca_lists, char *out_msg);
	};
}

#endif
