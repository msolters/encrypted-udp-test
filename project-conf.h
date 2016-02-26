#ifndef __PROJECT_ENCRYPTED_UDP_TEST_CONF_H__
#define __PROJECT_ENCRYPTED_UDP_TEST_CONF_H__

/* Custom channel and PAN ID configuration for your project. */

#undef RF_CHANNEL
#define RF_CHANNEL                     25

#undef IEEE802154_CONF_PANID
#define IEEE802154_CONF_PANID          0xABCD

/* IP buffer size must match all other hops, in particular the border router. */
#undef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE           1280

#undef UIP_CONF_TCP
#define UIP_CONF_TCP                   0

#undef NETSTACK_CONF_LLSEC
#define NETSTACK_CONF_LLSEC                   noncoresec_driver
#undef LLSEC802154_CONF_SECURITY_LEVEL
#define LLSEC802154_CONF_SECURITY_LEVEL       7

#endif
