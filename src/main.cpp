#include <argparse/argparse.hpp>

#include "generation.hpp"
#include "util.hpp"

int main(int argc, char** argv) {
    std::string version_info = "v0.1.1\nGNU GPLv3 License\nCopyright (c) 2026 ESzPa";
    argparse::ArgumentParser program("simpass", version_info);

    program.add_argument("-c", "--count")
        .help("Count of elements in the password")
        .required()
        .scan<'i', int>();

    program.add_argument("-l", "--lowercase")
        .help("Use lowercase letters")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-u", "--uppercase")
        .help("Use uppercase letters")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-d", "--digit")
        .help("Use number digits")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-s", "--special")
        .help("Use special characters")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-w", "--words")
        .help("Make a human memorizable password")
        .default_value(false)
        .implicit_value(true);

    try {
        program.parse_args(argc, argv);
    } catch(const std::exception& err) {
        std::cerr << err.what() << '\n';
        return 1;
    }

    int count = program.get<int>("-c");

    bool l = program.get<bool>("-l");
    bool u = program.get<bool>("-u");
    bool d = program.get<bool>("-d");
    bool s = program.get<bool>("-s");

    bool w = program.get<bool>("-w");

    if(w && (l || u || d || s)) {
        std::cerr << "Unable to create a password: wrong arguments\n";
        return 1;
    }

    if(w) {
        auto pass = GEN::generate_password_wordlist(count);

        safeprint(pass);
        burn_string(pass);
    }
    else {
        std::vector<std::string_view> active_lists;

        if(l) {
            active_lists.push_back(GEN::lowercase);
        }
        if(u) {
            active_lists.push_back(GEN::uppercase);
        }
        if(d) {
            active_lists.push_back(GEN::numbers);
        }
        if(s) {
            active_lists.push_back(GEN::spechars);
        }

        if(active_lists.empty()) {
            active_lists.assign(std::begin(GEN::default_charlists), std::end(GEN::default_charlists));
        }

        auto pass = GEN::generate_password_charlist(count, active_lists);

        safeprint(pass);
        burn_string(pass);
    }

    return 0;
}
