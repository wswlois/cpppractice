#include "Hash.h"
#include "unixHeader.h"

#include <openssl/sha.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;



std::string Hash::sha1() const
{
    //按照只读模式打开的，后面什么时候close?
    int fd = open(_filename.c_str(), O_RDONLY);
    cout << "_filename:" << _filename << endl;
    if(fd < 0) {
        perror("open");
        return string();
    }

    // 注意需要链接-lcrypto
    SHA_CTX ctx;
    // 初始化
    SHA1_Init(&ctx);
    char buff[4096] = {0};
    //这种以前试过也可以
    //while((sret = read(fd,buff,4096))>0) {
    //    SHA1_Update(&ctx,buf,sret);
    //}
    //ERROR_CHECK(sret, -1,"read");
    while(1) {
        int ret = read(fd, buff, 4096);
        if(ret == 0) {
            break;
        }
        SHA1_Update(&ctx, buff, ret);
        bzero(buff, sizeof(buff));
    }
    unsigned char md[20] = {0};
    SHA1_Final(md, &ctx);
    char fragment[3] = {0};
    string result;
    for(int i = 0; i < 20; ++i) {
        sprintf(fragment, "%02x", md[i]);
        result += fragment;
    }
    return result;
}
