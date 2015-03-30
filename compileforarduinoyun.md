cd ~


wget -O OpenWrt-SDK-ar71xx-for-linux-i486-gcc-4.6-linaro_uClibc-0.9.33.2.tar.bz2 http://goo.gl/VTiAdi


md5sum OpenWrt-SDK-ar71xx-for-linux-i486-gcc-4.6-linaro_uClibc-0.9.33.2.tar.bz2
0e5706c72e433c362cf384c462b86f86


tar -vxjf OpenWrt-SDK-ar71xx-for-linux-i486-gcc-4.6-linaro_uClibc-0.9.33.2.tar.bz2


cd ~

git clone  https://github.com/sonnyyu/UsbRelay.git

cd UsbRelay

source setupcrosscompile.sh

mips-openwrt-linux-uclibc-gcc   -O -Wall  -c usbrelay.c -o usbrelay.o

mips-openwrt-linux-uclibc-gcc  -O -Wall -I${CFLAGS} -c hiddata.c -o hiddata.o

mips-openwrt-linux-uclibc-gcc -L${LDFLAGS} -o usbrelay usbrelay.o hiddata.o -Wl,-rpath-link=${LDFLAGS} -lusb

mips-openwrt-linux-uclibc-strip usbrelay

file usbrelay

