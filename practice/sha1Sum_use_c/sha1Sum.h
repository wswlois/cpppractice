#include <func.h>
#include <openssl/sha.h>
#define SINGLE_LENGTH 4096
#define SHA1_LENGTH 20
#define SHA1_HEX_LEGTH (SHA1_LENGTH * 2)

int sha1Sum(char * filepath, char *sha1_val);

