/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (C) 2014 Named Data Networking Project
 * See COPYING for copyright and distribution information.
 */

#include "multicast-udp-face.hpp"

namespace nfd {

NFD_LOG_INIT("MulticastUdpFace");


MulticastUdpFace::MulticastUdpFace(const shared_ptr<MulticastUdpFace::protocol::socket>& socket)
  : DatagramFace<protocol>(FaceUri(socket->local_endpoint()), socket)
{
  NFD_LOG_DEBUG("Face creation. Multicast group: "
                << m_socket->local_endpoint());
  m_multicastGroup = m_socket->local_endpoint();
}

const boost::asio::ip::udp::endpoint&
MulticastUdpFace::getMulticastGroup() const
{
  return m_multicastGroup;
}

void
MulticastUdpFace::sendInterest(const Interest& interest)
{
  NFD_LOG_DEBUG("Sending interest");
  m_socket->async_send_to(boost::asio::buffer(interest.wireEncode().wire(),
                                              interest.wireEncode().size()),
                          m_multicastGroup,
                          bind(&DatagramFace<protocol>::handleSend, this, _1, interest.wireEncode()));
    
  // anything else should be done here?
}

void
MulticastUdpFace::sendData(const Data& data)
{
  NFD_LOG_DEBUG("Sending data");
  m_socket->async_send_to(boost::asio::buffer(data.wireEncode().wire(),
                                           data.wireEncode().size()),
                          m_multicastGroup,
                          bind(&DatagramFace<protocol>::handleSend, this, _1, data.wireEncode()));
    
  // anything else should be done here?
}
  
bool
MulticastUdpFace::isMultiAccess() const
{
  return true;
}

} // namespace nfd
