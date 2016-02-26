# encrypted-udp-test

This application simply sends strings via UDP to a fixed destination IP.  The purpose is to explore the problems caused by enabling LLSEC encryption.

## Compile
This example will by default only compile for the `sensortag/cc2650` board.

```bash
make
```

### To Enable Encryption
1.  Make sure the following is uncommented in `project-conf.h`:

 ```c
 #undef NETSTACK_CONF_LLSEC
 #define NETSTACK_CONF_LLSEC                   noncoresec_driver
 #undef LLSEC802154_CONF_SECURITY_LEVEL
 #define LLSEC802154_CONF_SECURITY_LEVEL       7
 ```

2.  If you get `undefined reference to `noncoresec_driver'` errors, make sure you have added `core/net/llsec/noncoresec` to the `MODULES +=` line in `platform/srf06-cc26xx/Makefile.srf06-cc26xx`.

### To disable encryption
1.  Make sure the following is commented out in `project-conf.h`:

```c
#undef NETSTACK_CONF_LLSEC
#define NETSTACK_CONF_LLSEC                   noncoresec_driver
#undef LLSEC802154_CONF_SECURITY_LEVEL
#define LLSEC802154_CONF_SECURITY_LEVEL       7
```
