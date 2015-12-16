ARCH="x86"

NDK="$HOME/code/android-ndk-r10e"
SYSROOT="$NDK/platforms/android-21/arch-x86"

CC="$NDK/toolchains/x86-4.9/prebuilt/linux-x86_64/bin/i686-linux-android-gcc --sysroot=$SYSROOT"
CFLAGS="-O0 -g -fPIC -rdynamic -shared -m32 -Wl,--hash-style=sysv"

EXTENSION_LIB="libcrosswalk-oic.so"
SOURCES="json/mjson.c iotivity/iotivity_api.c iotivity/iotivity_extension.c"

# Prepare folders
mkdir -p out/$ARCH

# Generage API
python \
    iotivity/generate_api.py \
    iotivity/iotivity_api.js \
    kSource_iotivity_api \
    iotivity/iotivity_api.c

# Build
$CC \
   $CFLAGS \
   -o out/$ARCH/$EXTENSION_LIB \
   $SOURCES
