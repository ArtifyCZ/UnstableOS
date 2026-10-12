#!/usr/bin/env bash
if [[ ! -e termcap-1.3.1 ]]; then
	curl -L https://mirror.team-cymru.com/gnu//termcap/termcap-1.3.1.tar.gz | tar xz
fi
cd termcap-1.3.1
./configure --prefix="$(pwd)/../../sysroot/usr" --host=i686-unstableos --enable-install-termcap --with-termcap="$(pwd)/../../sysroot/etc/termcap"
make CFLAGS="-std=c89"
make install
cd ..
