#include <cstdlib>
#include <string_view>
#include <vector>

#include "generation.hpp"
#include "words_data.hpp"

namespace GEN {

namespace {

std::vector<std::string_view> parse_words(std::string_view sv) {
    std::vector<std::string_view> result;
    size_t start = 0;

    while(start < sv.size()) {
        start = sv.find_first_not_of("\r\n", start);
        if(start == std::string_view::npos)
            break;

        size_t end = sv.find_first_of("\r\n", start);
        if(end == std::string_view::npos)
            end = sv.size();

        result.push_back(sv.substr(start, end - start));
        start = end;
    }

    if(result.empty()) {
        result.push_back("");
    }

    return result;
}

const std::vector<std::string_view> parsed_word_vec = [] {
    std::string_view raw(reinterpret_cast<const char*>(words_txt), words_txt_len);
    return parse_words(raw);
}();

} // namespace

const wordlist default_wordlist{parsed_word_vec};

} // namespace GEN
