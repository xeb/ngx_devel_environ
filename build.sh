#!/bin/sh
cd nginx
auto/configure --add-module=../ngx_devel_kit --add-module=../hello
make
make install
