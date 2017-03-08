#!/bin/bash

#mount_dev="StrNode1:/${1}"
mount_dev="/dev/${1}"
if [ ! -d /media/udisk ]; then
    sudo mkdir /media/udisk 
fi

sudo mount -t 'ext4' $mount_dev /media/udisk
val=`echo $?`
if [ $val -eq 0 ]; then
    sudo chown sg-os:sg-os /media/udisk -R
fi
