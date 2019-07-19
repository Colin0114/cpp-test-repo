#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#define TCP 1
#define UDP 0
#define PORT 808
#define CYC_TIME 10

class WriteTest {
 public:
  WriteTest(std::string host, int port) : host_(host), port_(port) {}

  void testSocketNotConnected();
  void testSocketConnectedButServerNotOnline();
  void createSocket(int type);
  void connect();
  void closeFd();

 private:
  std::string host_;
  int port_;
  int fd_;
};

void WriteTest::testSocketNotConnected() {
  std::cout
      << "*************Test write api, unconnected tcp socket*************\n";
  /*
  createSocket(TCP);
  char data[] = "123456789";
  int rt = write(fd_, data, strlen(data), 0);
  if( rt <0){
          std::cout << "error when write data for a unconnected tcp socket, error
  detail: " << strerror(errno) << std::endl; }else{ std::cout << "write api was
  success called for a unconnected tcp socket\n";
  }
  */
  std::cout << "a SIGPIPE was emitted, and program was terminated.\n";
  std::cout << "*************Test end*************\n";

  closeFd();

  std::cout
      << "*************Test write api, unconnected udp socket*************\n";
  createSocket(UDP);
  char data[] = "123456789";
  int rt = write(fd_, data, strlen(data));
  if (rt < 0) {
    std::cout
        << "error when write data for a unconnected udp socket, error detail: "
        << strerror(errno) << ", return val: " << rt << std::endl;
  } else {
    std::cout << "write api was success called for a unconnected udp socket, return val: " << rt << std::endl;
  }
  std::cout << "*************Test end*************\n";

  closeFd();

  return;
}

void WriteTest::testSocketConnectedButServerNotOnline() {
  std::cout << "*************Test write api, connected udp socket but server "
               "not online*************\n";
  createSocket(UDP);
  connect();
  char data[] = "123456789";
  for (int i = 0; i < CYC_TIME; i++) {
    std::cout << "[idx] " << i << ", ";
    int rt = write(fd_, data, strlen(data));
    if (rt < 0) {
      std::cout << "error when write data for a connected but server not online "
                   "udp socket, error detail: "
                << strerror(errno) << ", return val: " << rt << std::endl;
    } else {
      std::cout << "write api was success called for a connected but server not "
                   "online udp socket, return val: " << rt << std::endl;
    }
    sleep(1);
  }
  std::cout << "*************Test end*************\n";

  return;
}

void WriteTest::createSocket(int type) {
  if (type == TCP) {
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "create tcp socket\n";
  } else {
    fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    std::cout << "create udp socket\n";
  }

  if (fd_ == -1) {
    std::cout << "socket create fail\n";
    exit(1);
  }

  std::cout << "create socket success, fd_: " << fd_ << std::endl;
  return;
}

void WriteTest::connect() {
  struct sockaddr_in their_addr; /* connector's address information */

  their_addr.sin_family = AF_INET;   /* host byte order */
  their_addr.sin_port = htons(PORT); /* short, network byte order */
  their_addr.sin_addr.s_addr = inet_addr(host_.c_str());
  bzero(&(their_addr.sin_zero), 8); /* zero the rest of the struct */

  if (::connect(fd_, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) ==
      -1) {
    perror("connect");
    exit(1);
  }
  std::cout << "socket connected\n";

  return;
}

void WriteTest::closeFd() { close(fd_); }

int main() {
  WriteTest myWriteTest("172.18.66.226", PORT);
  myWriteTest.testSocketNotConnected();
  myWriteTest.testSocketConnectedButServerNotOnline();
  return 0;
}
