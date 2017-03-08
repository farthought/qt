#!/bin/bash
set -x
mount_dev="/dev/${1}"

echo $mount_dev
sudo mount -t 'ext4' $mount_dev  $HOME/ko
