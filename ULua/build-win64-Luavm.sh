cd lua-5.1.5/src
mingw32-make -fMakefile-Static all
cd ../..

cd luasocket/src
mingw32-make -fmakefile-Luavm all
cd ../..

gcc lua_wrap.c \
    -o Plugins/x86_64/ulua.dll -m64 -shared \
    -I./ \
    -Ilua-5.1.5/src \
    -Wl,--whole-archive \
    window/x86_64/liblua.a \
    -Wl,--no-whole-archive -lwsock32 -static-libgcc -static-libstdc++
