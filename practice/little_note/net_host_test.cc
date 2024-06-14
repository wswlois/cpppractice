#include <iostream>

using std::cout;
using std::endl;

union test_u{
    int i;
    char c;
};//test_u的大小是4个字节


int main(int argc, char **argv)
{
    test_u u;
    u.i = 15;//上面是一个i储存在里面
    u.c = 'a';//这一行把上面的数据进行了取代
    // 对于大端，联合结构体的char[0]的位置低地址应该存储高位，就是0
    // 15被0取代了，char[0] = 0, char[4] = 97
    // 对于小端，联合结构体的char[0]的位置低地址存低位，就是97(a)
    // 15被97取代了,char[0] = 97, char[4] = 0
    cout << "u.i = " << u.i << endl;
    return 0;
}

