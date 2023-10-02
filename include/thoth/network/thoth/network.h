
#ifndef __THOTH_NETWORK_NETWORK_H__
#define __THOTH_NETWORK_NETWORK_H__

#include <iostream>
#include <memory>
namespace thoth {
// abstract class
class P2PNode {};

// Will use -> #ifdef _WIN32 to check os when called ...? Can a dll/library do
// this??
std::unique_ptr<P2PNode> MakeP2PNode();  // For auto os detection */
}  // namespace thoth

#endif
