/* peer.cc
   Mathieu Stefani, 12 August 2015

*/

#include <iostream>
#include <stdexcept>

#include <sys/socket.h>

#include <pistache/peer.h>
#include <pistache/async.h>
#include <pistache/transport.h>

namespace Pistache {
namespace Tcp {

using namespace std;

Peer::Peer() : transport_(nullptr) , fd_(-1)
{
  std::cout << __PRETTY_FUNCTION__ << endl;
}

Peer::Peer(const Address& addr) : transport_(nullptr) , addr(addr) , fd_(-1)
{
  std::cout << __PRETTY_FUNCTION__ << endl;
}

Peer::~Peer() { std::cout << __PRETTY_FUNCTION__ << endl; }

Address
Peer::address() const {
  std::cout << __PRETTY_FUNCTION__ << endl;
  return addr;
}

string
Peer::hostname() const {
  std::cout << __PRETTY_FUNCTION__ << endl;
  return hostname_;
}

void
Peer::associateFd(int fd) {
std::cout << __PRETTY_FUNCTION__ << std::endl;
  fd_ = fd;
}

#ifdef PISTACHE_USE_SSL
void
Peer::associateSSL(void *ssl)
{
    ssl_ = ssl;
}

void *
Peer::ssl(void) const {
    return ssl_;
}
#endif /* PISTACHE_USE_SSL */

int
Peer::fd() const {
  std::cout << __PRETTY_FUNCTION__ << endl;
  if (fd_ == -1) {
    throw std::runtime_error("The peer has no associated fd");
    }

    return fd_;
}

void
Peer::putData(std::string name, std::shared_ptr<void> data) {
std::cout << __PRETTY_FUNCTION__ << std::endl;
  std::cout << __PRETTY_FUNCTION__ << endl;
  auto it = data_.find(name);
  
  if (it != std::end(data_)) {
    throw std::runtime_error("The data already exists");
    }

    data_.insert(std::make_pair(std::move(name), std::move(data)));

}

std::shared_ptr<void>
Peer::getData(std::string name) const {
  std::cout << __PRETTY_FUNCTION__ << endl;
  auto data = tryGetData(std::move(name));
  if (data == nullptr) {
    throw std::runtime_error("The data does not exist");
    }

    return data;
}

std::shared_ptr<void>
Peer::tryGetData(std::string(name)) const {
    std::cout << __PRETTY_FUNCTION__ << endl;
    auto it = data_.find(name);
    if (it == std::end(data_)) return nullptr;

    return it->second;
}

Async::Promise<ssize_t>
Peer::send(const Buffer& buffer, int flags) {
std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << endl;
    return transport()->asyncWrite(fd_, buffer, flags);
}

std::ostream& operator<<(std::ostream& os, const Peer& peer) {
    const auto& addr = peer.address();
    os << "(" << addr.host() << ", " << addr.port() << ") [" << peer.hostname() << "]";
    return os;
}

void
Peer::associateTransport(Transport* transport) {
std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << endl;
    transport_ = transport;
}

Transport*
Peer::transport() const {
    std::cout << __PRETTY_FUNCTION__ << endl;
    if (!transport_)
        throw std::logic_error("Orphaned peer");

    return transport_;
}

} // namespace Tcp
} // namespace Pistache
