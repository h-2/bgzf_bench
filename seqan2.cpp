#ifndef SEQAN_BGZF_NUM_THREADS
#define SEQAN_BGZF_NUM_THREADS 1
#endif

#include <seqan/stream.h>

int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 3)
        return 1;

    seqan::VirtualStream<char, seqan::Input> istr{argv[1]};

    std::cout << istr.rdbuf();
}
