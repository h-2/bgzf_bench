#include <shrinkwrap/istream.hpp>

int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 3)
        return 1;

    shrinkwrap::istream istr{argv[1]};

    std::cout << istr.rdbuf();
}
