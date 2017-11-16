cmd_crypto/built-in.o :=  arm-cortexm3-uclinuxeabi-ld -EL    -r -o crypto/built-in.o crypto/crypto.o crypto/crypto_algapi.o crypto/aes_generic.o crypto/rng.o crypto/krng.o crypto/ansi_cprng.o 
