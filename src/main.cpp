#include "generation.hpp"
#include "util.hpp"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    auto pass = GEN::generate_password_wordlist(6);
    safeprint(pass);
    burn_string(pass);

    return 0;
}
