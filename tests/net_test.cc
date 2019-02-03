#include "gtest/gtest.h"

#include <pistache/net.h>

#include <stdexcept>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace Pistache;

TEST(net_test, port_creation)
{
    Port port1(3000);
    ASSERT_FALSE(port1.isReserved());
    uint16_t value1 = port1;
    ASSERT_EQ(value1, 3000);
    ASSERT_EQ(port1.toString(), "3000");

    Port port2(80);
    ASSERT_TRUE(port2.isReserved());
    uint16_t value2 = port2;
    ASSERT_EQ(value2, 80);
    ASSERT_EQ(port2.toString(), "80");
}

TEST(net_test, address_creation)
{
    Address address1("127.0.0.1:8080");
    ASSERT_EQ(address1.host(), "127.0.0.1");
    ASSERT_EQ(address1.port(), 8080);

    std::string addr = "127.0.0.1";
    Address address2(addr, Port(8080));
    ASSERT_EQ(address2.host(), "127.0.0.1");
    ASSERT_EQ(address2.port(), 8080);

    Address address3(Ipv4(127, 0, 0, 1), Port(8080));
    ASSERT_EQ(address3.host(), "127.0.0.1");
    ASSERT_EQ(address3.port(), 8080);

    Address address4(Ipv4::any(), Port(8080));
    ASSERT_EQ(address4.host(), "0.0.0.0");
    ASSERT_EQ(address4.port(), 8080);

    Address address5("*:8080");
    ASSERT_EQ(address5.host(), "0.0.0.0");
    ASSERT_EQ(address5.port(), 8080);

    Address address6("[::1]:8080");
    ASSERT_EQ(address6.host(), "::1");
    ASSERT_EQ(address6.port(), 8080);

    std::string addr2 = "[::1]";
    Address address7(addr2, Port(8080));
    ASSERT_EQ(address7.host(), "::1");
    ASSERT_EQ(address7.port(), 8080);

    Address address8(Ipv6(0, 0, 0, 0, 0, 0, 0, 1), Port(8080));
    ASSERT_EQ(address8.host(), "::1");
    ASSERT_EQ(address8.port(), 8080);

    Address address9(Ipv6::any(), Port(8080));
    ASSERT_EQ(address9.host(), "::");
    ASSERT_EQ(address9.port(), 8080);

    Address address10("[::]:8080");
    ASSERT_EQ(address10.host(), "::");
    ASSERT_EQ(address10.port(), 8080);

    Address address11("[2001:0DB8:AABB:CCDD:EEFF:0011:2233:4455]:8080");
    ASSERT_EQ(address11.host(), "2001:0DB8:AABB:CCDD:EEFF:0011:2233:4455");
    ASSERT_EQ(address11.port(), 8080);

    Address address12(Ipv4::loopback(), Port(8080));
    ASSERT_EQ(address12.host(), "127.0.0.1");
    ASSERT_EQ(address12.port(), 8080);

    Address address13(Ipv6::loopback(), Port(8080));
    ASSERT_EQ(address13.host(), "::1");
    ASSERT_EQ(address13.port(), 8080);

    Address address14("localhost", Port(8080));
    ASSERT_EQ(address14.host(), "127.0.0.1");
    ASSERT_EQ(address14.port(), 8080);

    Address address15("127.0.0.1");
    ASSERT_EQ(address15.host(), "127.0.0.1");
    ASSERT_EQ(address15.port(), 80);
}

TEST(net_test, invalid_address)
{
    ASSERT_THROW(Address("127.0.0.1:9999999"), std::invalid_argument);
    ASSERT_THROW(Address("127.0.0.1:"), std::invalid_argument);
    ASSERT_THROW(Address("127.0.0.1:-10"), std::invalid_argument);

    ASSERT_THROW(Address("[GGGG:GGGG:GGGG:GGGG:GGGG:GGGG:GGGG:GGGG]:8080");, std::invalid_argument);
    ASSERT_THROW(Address("[::GGGG]:8080");, std::invalid_argument);
    ASSERT_THROW(Address("256.256.256.256:8080");, std::invalid_argument);
    ASSERT_THROW(Address("1.0.0.256:8080");, std::invalid_argument);
}
