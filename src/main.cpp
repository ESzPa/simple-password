#include "generation.hpp"
#include "util.hpp"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    auto pass = GEN::generate_password_charlist(12);
    safeprint(pass);
    burn_string(pass);

    return 0;
}
