obj-m += caesar_cipher.o

all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
		install tcp_tsunami.ko /lib/modules/$(shell uname -r)/kernel/net/ipv4
		insmod /lib/modules/$(shell uname -r)/kernel/net/ipv4/tcp_tsunami.ko
		gzip /lib/modules/$(shell uname -r)/kernel/net/ipv4/tcp_tsunami.ko
		depmod -a
		sysctl -w net.ipv4.tcp_congestion_control=tsunami
