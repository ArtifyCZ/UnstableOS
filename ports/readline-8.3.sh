#!/usr/bin/env bash
if [[ ! -e readline-8.3 ]]; then
	curl -L https://mirror.team-cymru.com/gnu//readline/readline-8.3.tar.gz | tar xz
	cd readline-8.3
	patch -p1 <../../patches/readline-8.3.patch
	cd ..
fi
cd readline-8.3
./configure --host=i686-unstableos --prefix="$(pwd)/../../sysroot/usr" --enable-multibyte --enable-year2038
make -j$(nproc) && make install
cd ..
