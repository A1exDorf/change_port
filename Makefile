KERNELDIR ?= /lib/modules/$(shell uname -r)/build

obj-m := change_port.o

PWD := $(shell pwd)

all:

	make -C $(KERNELDIR) M=$(PWD) modules

server: udp_server.c
	gcc udp_server.c -o server

udp_client: udp_client.c
	gcc udp_client.c -o udp_client

clean:
	rm -f server udp_client *.ko *.mod.c *.order *.symvers *.o
