#pragma once

#include <cstdlib>
#include <span>
#include <string>

namespace GEN {

using charlist = const std::string_view;
using wordlist = const std::string_view[];

// clang-format off
inline constexpr charlist lowercase       = "abcdefghijklmnopqrstuvwxyz";
inline constexpr charlist uppercase       = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
inline constexpr charlist numbers         = "0123456789";
inline constexpr charlist spechars        = "!@#$%^&*()_+-=[]{}|;:,.<>?";
inline constexpr charlist default_lists[] = {lowercase, uppercase, numbers, spechars};
// clang-format on

std::string generate_password_charlist(size_t length,
                                       std::span<charlist> character_lists = default_lists);

std::string generate_password_human(size_t count, const std::string& separator, wordlist word_list);

} // namespace GEN
