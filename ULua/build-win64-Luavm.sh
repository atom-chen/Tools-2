cd lua-5.1.5/src
make -f Makefile-Static all
cd ../..

make -f makefile-Luavm all

cd luasocket/src
make -f makefile-Luavm all
cd ../..