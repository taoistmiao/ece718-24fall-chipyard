#include <stdio.h>
#include <stdint.h>

#include "baremetal.h"

#include "inet.h"


typedef struct {
  __IO uint32_t RXIP;
  __IO uint32_t TXIP;
  __IO uint32_t RXPORT;
  __IO uint32_t TXPORT;
  __IO uint32_t CTRL;
  __IO uint32_t STATUS;
  __IO uint32_t RXSIZE;
  __IO uint32_t TXSIZE;
  __IO uint32_t RXFIFO_DATA;
  __IO uint32_t RXFIFO_SIZE;
  uint32_t RESERVED0[2];
  __IO uint32_t TXFIFO_DATA;
  __IO uint32_t TXFIFO_SIZE;
  uint32_t RESERVED1[2];
  __IO uint32_t RX_STATUS;
  __IO uint32_t TX_STATUS;
} UDP_Type;


#define UDP_BASE          0x10001000
#define UDP_SIZE          0x1000

#define UDP     ((UDP_Type*)UDP_BASE)




#define UDP_RX_IP "127.0.0.1"
#define UDP_RX_PORT 8181
#define UDP_TX_IP "127.0.0.1"
#define UDP_TX_PORT 8080


#define RX_SIZE 4
#define TX_SIZE 4


void UDP_init(UDP_Type *udp) {
  udp->RXIP = htonl(inet_addr(UDP_RX_IP));
  udp->TXIP = htonl(inet_addr(UDP_TX_IP));
  
  udp->RXPORT = htons(UDP_RX_PORT);
  udp->TXPORT = htons(UDP_TX_PORT);
  
  // device enable
  udp->CTRL = 0x01;
}


void UDP_receive_frame(UDP_Type *udp, uint8_t *buffer, size_t size) {
  // configure rx size
  udp->RXSIZE = size;
  // enable rx
  udp->CTRL = 0x01 << 1;

  // wait for rx to be ready
  while (!READ_BITS(udp->RX_STATUS, 1)) {
    // nop
  }

  size_t ptr = 0;
  while (ptr < size) {
    // read data from fifo register
    uint32_t rx_data = udp->RXFIFO_DATA;

    // check if fifo is empty
    uint32_t fifo_empty = READ_BITS(rx_data, 0x80000000);
    if (fifo_empty) {
      continue;
    }

    buffer[ptr] = (uint8_t)READ_BITS(rx_data, 0xFF);
    ptr += 1;
  }
}

void UDP_send_frame(UDP_Type *udp, uint8_t *buffer, size_t size) {
  udp->TXSIZE = size;

  udp->CTRL = 0x01 << 2; // enable tx
  
  for (size_t i = 0; i < size; i += 1){

    // TODO: fifo full handler
    // read fifo full bit
    // while (!READ_BITS(udp->TXFIFO_DATA, 0x80000000)) {
    // }

    udp->TXFIFO_DATA = buffer[i];
  }

  while (udp->TXFIFO_SIZE != 0) {
    printf("tx fifo size: %d\n", udp->TXFIFO_SIZE);
  }
  printf("tx fifo size: %d\n", udp->TXFIFO_SIZE);
}

void main() {
  printf("creating buffer\n");
  uint8_t buffer[RX_SIZE];

  UDP_init(UDP);

  UDP_receive_frame(UDP, &buffer, RX_SIZE);
  printf("[APP] Received frame: %x %x %x %x\n", buffer[0], buffer[1], buffer[2], buffer[3]);

  UDP_receive_frame(UDP, &buffer, RX_SIZE);
  printf("[APP] Received frame: %x %x %x %x\n", buffer[0], buffer[1], buffer[2], buffer[3]);

  buffer[0] *= 2;
  buffer[1] *= 2;
  buffer[2] *= 2;
  buffer[3] *= 2;

  UDP_send_frame(UDP, &buffer, TX_SIZE);
  printf("Sent frame\n");

  return 0;
}
