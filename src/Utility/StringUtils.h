#ifndef SEAOTTER_UTILITY_STRING_UTILS_H
#define SEAOTTER_UTILITY_STRING_UTILS_H
#include <string>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <hex.h>
#include <md5.h>

namespace Otter {
class StringUtils {
public:
  static std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim)) {
      tokens.push_back(item);
    }
    return tokens;
  }

  static bool replace(std::string &str, const std::string &from,
                      const std::string &to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
      return false;
    str.replace(start_pos, from.length(), to);
    return true;
  }

  static std::string md5(const std::string &t_input) {
    CryptoPP::byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];
    CryptoPP::Weak::MD5 hash;

    hash.CalculateDigest(digest, (const CryptoPP::byte *)t_input.c_str(),
                         t_input.length());

    CryptoPP::HexEncoder encoder;
    std::string output;

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
  }
};
} // namespace Otter

#endif // SEAOTTER_UTILITY_STRING_UTILS_H