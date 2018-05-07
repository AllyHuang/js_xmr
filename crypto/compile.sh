# compile command for wasm
emcc hash-extra-*.c jh.c skein.c groestl.c blake256.c aesb.c oaes_lib.c slow-hash.c keccak.c hash.c crypto-ops-data.c crypto-ops.c main.c -o abc.html -g -maes -s WASM=1 -s 'EXTRA_EXPORTED_RUNTIME_METHODS=["ccall", "cwrap"]' -s EXPORTED_FUNCTIONS="['_main', '_crack']"
mv abc.wasm* /home/ubuntu/reinforce3/web/
mv abc.js /home/ubuntu/reinforce3/web/

# compile gcc
# gcc hash-extra-*.c jh.c skein.c groestl.c blake256.c aesb.c oaes_lib.c slow-hash.c keccak.c hash.c crypto-ops-data.c crypto-ops.c main.c -o abc -g -maes
