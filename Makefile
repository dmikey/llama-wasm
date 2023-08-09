# choose your compiler, e.g. gcc/clang
# example override to clang: make run CC=clang
CC=/Users/derekanderson/wasi-sdk/bin/clang
SYSROOT=/Users/derekanderson/wasi-sdk/share/wasi-sysroot

# the most basic way of building that is most likely to work on most systems
.PHONY: run
run: llama.c
	$(CC) --sysroot=$(SYSROOT)  -D_WASI_EMULATED_MMAN -lwasi-emulated-mman llama.c -o llama.wasm -O3

.PHONY: clean
clean:
	rm -f llama.wasm
