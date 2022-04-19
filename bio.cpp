#include <bio/stream/transparent_istream.hpp>


int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 3)
        return 1;

    bio::transparent_istream_options opt{.threads = 1 };

    if (argc == 3)
        opt.threads = std::stoull(argv[2]);

    bio::transparent_istream istr{argv[1], opt};

    std::cout << istr.rdbuf();
}
