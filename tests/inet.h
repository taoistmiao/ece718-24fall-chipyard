#ifndef __INET_H
#define __INET_H

static inline uint32_t inet_addr(const char* ip) {
  uint32_t result = 0;
  uint8_t octet = 0;
  uint8_t octets = 0;

  while (*ip) {
    if (*ip >= '0' && *ip <= '9') {
      octet = octet * 10 + (*ip - '0');
    }
    else if (*ip == '.') {
      result = (result << 8) | octet;
      octet = 0;
      octets += 1;
    }
    else {
      // Invalid character in IP address
      return 0;
    }
    ip += 1;
  }

  result = (result << 8) | octet;
  octets += 1;

  if (octets != 4) {
    return 0;
  }
  return result;
}

static inline uint16_t htons(uint16_t port) {
  return __builtin_bswap16(port);
}

static inline uint32_t htonl(uint32_t ip) {
  return __builtin_bswap32(ip);
}


#endif /* __INET_H */
