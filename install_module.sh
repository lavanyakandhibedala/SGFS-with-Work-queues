#!/bin/sh
set -x
# WARNING: this script doesn't check for errors, so you have to enhance it in case any of the commands
# below fail.
lsmod
rmmod proc_queue_len.ko
insmod proc_queue_len.ko
rmmod proc_file_num.ko
insmod proc_file_num.ko
rmmod proc_key.ko
insmod proc_key.ko
rmmod sys_xclone2
insmod sys_xclone2.ko
rmmod sys_deletethread
insmod sys_deletethread.ko
rmmod sys_xclone2async
insmod sys_xclone2async.ko
lsmod
