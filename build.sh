ARCH="x86"
NDK="$HOME/code/android-ndk-r10e"
SYSROOT="$NDK/platforms/android-21/arch-x86"
CC="$NDK/toolchains/x86-4.9/prebuilt/linux-x86/bin/i686-linux-android-gcc --sysroot=$SYSROOT"
EXTENSION_LIB="libcrosswalk-oic.so"

mkdir -p out/$ARCH
$CC -O0 -g -fPIC -rdynamic -shared -m32 -Wl,--hash-style=sysv -o out/$ARCH/$EXTENSION_LIB iotivity/iotivity.c
