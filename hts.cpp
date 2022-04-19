#include <htslib/bgzf.h>
#include <string>

int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 3)
        return 1;

    std::string buffer;
    buffer.resize(1024*1024);

    auto * istr = bgzf_open(argv[1], "r");

    while (bgzf_read(istr, buffer.data(), 1024*1024) > 0)
        printf("%s", buffer.c_str());

    bgzf_close(istr);
}
