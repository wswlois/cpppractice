
#include "sha1Sum.h"
 int sha1Sum(char * filepath, char *sha1_hex)
{
    SHA_CTX ctx;
    // 初始化
    SHA1_Init(&ctx);
    int fd = open(filepath,O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    char buf[SINGLE_LENGTH] = {0};
    ssize_t sret;
    while((sret = read(fd,buf,SINGLE_LENGTH))>0) {
        SHA1_Update(&ctx,buf,sret);
    }
    ERROR_CHECK(sret, -1,"read");
    unsigned char md[SHA1_LENGTH] = {0};
    SHA1_Final(md,&ctx);
    // bin_to_hex(md,sha1_hex,SHA1_LENGTH);
    for(int i = 0; i< SHA1_LENGTH; ++i){
        sprintf(sha1_hex + (i *2),"%02x",md[i]);
    }
    sha1_hex[SHA1_HEX_LEGTH]='\0';
    close(fd);
    return 0;
}

