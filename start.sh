#!/bin/sh

CURDIR=`pwd`
CMD="/usr/local/nginx/sbin/nginx -c $CURDIR/ngx_dev.conf"
`$CMD`
echo "nginx started with conf $CURDIR/ngx_dev.conf"