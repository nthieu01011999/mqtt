#!/bin/sh
ifconfig eth0 down
ifconfig eth0 up
ifconfig eth0 hw ether 00:11:22:07:05:23
udhcpc -i eth0
mkdir -p /tmp/huy_linux_nfs
mkdir -p /tmp/sd
mount -t nfs -o nolock 192.168.1.141:/mnt/nfs_huy_linux /tmp/huy_linux_nfs
/tmp/huy_linux_nfs/kill-realtek.sh
/tmp/huy_linux_nfs/fcam-rts
