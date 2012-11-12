#!/bin/sh

cd nginx;

auto/configure --without-http_rewrite_module --add-module=../ngx_httplog_module --add-module=../hello

make
make install



# cd nginx;

# PLAT=`uname -s`

# # I was having issues w/ PCRE; so I'm just not using it on the Mac
# if [[ $PLAT = 'Darwin' ]]; then
# 	auto/configure --without-http_rewrite_module --add-module=../ngx_devel_kit --add-module=../hello --add-module=../nginx_lua_module
# else
# 	auto/configure --add-module=../ngx_devel_kit --add-module=../hello
# fi

# make
# make install
