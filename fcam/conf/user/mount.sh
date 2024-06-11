#!/bin/sh 

DIR_NFS_PATH=/tmp/nfs
DIR_USER_PATH=/tmp/nfs/nhanh7

if [ ! -d "$DIR_NFS_PATH" ]; then
        mkdir $DIR_NFS_PATH
fi

if [ ! -d "$DIR_USER_PATH" ]; then                                                                                                        
        mkdir $DIR_USER_PATH                                                                                                          
fi
        
mount -t nfs -o nolock 192.168.11.78:/mnt/nfs_share/realtek $DIR_USER_PATH
