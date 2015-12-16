ARCH="x86"
NDK="$HOME/code/android-ndk-r10e"
SYSROOT="$NDK/platforms/android-21/arch-x86"
CC="$NDK/toolchains/x86-4.9/prebuilt/linux-x86_64/bin/i686-linux-android-gcc --sysroot=$SYSROOT"
EXTENSION_LIB="libcrosswalk-oic.so"

mkdir -p out/$ARCH
python iotivity/generate_api.py iotivity/iotivity_api.js kSource_iotivity_api iotivity/iotivity_api.c
$CC -O0 -g -fPIC -rdynamic -shared -m32 -Wl,--hash-style=sysv -o out/$ARCH/$EXTENSION_LIB iotivity/iotivity_api.c iotivity/iotivity_extension.c
