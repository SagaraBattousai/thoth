
#ifndef __THOTH_NETWORK_NETWORK_WIN32_H__
#define __THOTH_NETWORK_NETWORK_WIN32_H__

#include <winsock2.h>
#include <ws2tcpip.h> //May not need in header

//#include <iphlpapi.h> //If needed MUST be after winsock2.h

#include <memory>
#include <iostream>

#include <thoth/network/network.h>

namespace thoth {
		//Could be singelton init now that I think of it ....
		class WinP2PNode : public P2PNode
		{
		public:
			WinP2PNode();

		private:
			int InitWinsock();

			static std::unique_ptr<WSADATA> wsock_info;
			static int startup_result;

		};

	

		struct Socket
		{
		};

} //namespace thoth

#endif
