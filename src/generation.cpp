#include "generation.hpp"

#include <random>

#include "util.hpp"

namespace GEN {

namespace {

std::string combine_charlists(std::span<charlist> character_lists) {
    std::string out;
    for(const auto& cl : character_lists) {
        out.append(cl);
    }
    return out;
}

} // namespace

std::string generate_password_charlist(size_t length, std::span<charlist> character_lists) {
    std::string charset = combine_charlists(character_lists);

    if(charset.empty() || length == 0) {
        return "";
    }

    static std::random_device rd;
    std::uniform_int_distribution<std::size_t> dist(0, charset.size() - 1);

    std::string password;
    password.reserve(length);

    for(size_t i = 0; i < length; ++i) {
        password += charset[dist(rd)];
    }

    burn_string(charset);
    return password;
}

std::string generate_password_wordlist(size_t count, const std::string& separator, wordlist word_list) {
    if(word_list.empty() || count == 0) {
        return "";
    }

    static std::random_device rd;
    std::uniform_int_distribution<std::size_t> dist(0, word_list.size() - 1);

    std::string passphrase;
    passphrase.reserve(count * 10);

    for(size_t i = 0; i < count; ++i) {
        std::string word{word_list[dist(rd)]};

        if(!word.empty()) {
            word[0] = std::toupper(static_cast<unsigned char>(word[0]));
        }

        passphrase += word;

        if(i + 1 < count && separator != "\0") {
            passphrase += separator;
        }
    }

    return passphrase;
}

} // namespace GEN
