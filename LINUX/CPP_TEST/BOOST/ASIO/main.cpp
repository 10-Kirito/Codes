#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>

void handler(const boost::system::error_code & ec) {
  std::cout << "5 s." << std::endl;
}

int main (int argc, char *argv[])
{
  boost::asio::io_service io_service;
  boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(5));
  timer.async_wait(handler);
  io_service.run(); 
  return 0;
}
