# BASE64与SHA256与HMAC-SHA256.md

介绍一下 C++ 计算 BASE64 SHA256 HMAC-SHA256 的代码。

实现代码 `demo.h`

```c++
#include <iostream>
#include <string>
#include <string.h>

#include <openssl/sha.h>
#include <openssl/hmac.h>

//********************** base64 algorithm  **********************//
// code come from https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';
  }

  return ret;

}
std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}


//********************** SHA256 algorithm  **********************//

std::string sha256_hex(const std::string& str) {
    char buf[2*SHA256_DIGEST_LENGTH];
    memset(buf, 0, sizeof(buf));

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(buf+i*2, "%02x", hash[i]);
    }
    return buf;
}


//********************** HMAC-SHA256 algorithm  **********************//

int hmac_sha256(const std::string& secret_key, const std::string& str,
                        unsigned char* output, unsigned int& output_len) {    
    const EVP_MD * engine = EVP_sha256();

    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, (const void*)secret_key.c_str(), secret_key.size(), engine, NULL);
    HMAC_Update(&ctx, (const unsigned char*)str.c_str(), str.size());
    HMAC_Final(&ctx, output, &output_len);
    HMAC_CTX_cleanup(&ctx);

    // 如果使用的 openssl 的版本大于等于 1.1.0, 那么 HMAC_CTX 是不允许直接进行构造的，
    // 上面这段代码需要改成下面这种格式
    // https://stackoverflow.com/questions/63256081/error-aggregate-hmac-ctx-ctx-has-incomplete-type-and-cannot-be-defined
    // HMAC_CTX* ctx;
    // ctx = HMAC_CTX_new();
    // HMAC_Init_ex(ctx, (const void*)secret_key.c_str(), secret_key.size(), engine, NULL);
    // HMAC_Update(ctx, (const unsigned char*)str.c_str(), str.size());
    // HMAC_Final(ctx, output, &output_len);
    // HMAC_CTX_free(ctx);

    return 0;
}

std::string hmac_sha256_hex(const std::string& secret_key, const std::string& str) {
    unsigned char output[EVP_MAX_MD_SIZE];
    memset(output, 0, sizeof(output));
    unsigned int output_len = 0;

    hmac_sha256(secret_key, str, output, output_len);

    char buf[2*EVP_MAX_MD_SIZE];
    memset(buf, 0, sizeof(buf));

    for (int i = 0; i < EVP_MAX_MD_SIZE/2; ++i) {
        sprintf(buf+i*2, "%02x", output[i]);
    }

    return buf;
}

//********************** HMAC-SHA1 algorithm  **********************//
int hmac_sha1(const std::string& secret_key, const std::string& str,
                        unsigned char* output, unsigned int& output_len) {    
    const EVP_MD * engine = EVP_sha1();

    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, (const void*)secret_key.c_str(), secret_key.size(), engine, NULL);
    HMAC_Update(&ctx, (const unsigned char*)str.c_str(), str.size());
    HMAC_Final(&ctx, output, &output_len);
    HMAC_CTX_cleanup(&ctx);

    // 如果使用的 openssl 的版本大于等于 1.1.0, 那么 HMAC_CTX 是不允许直接进行构造的，
    // 上面这段代码需要改成下面这种格式
    // https://stackoverflow.com/questions/63256081/error-aggregate-hmac-ctx-ctx-has-incomplete-type-and-cannot-be-defined
    // HMAC_CTX* ctx;
    // ctx = HMAC_CTX_new();
    // HMAC_Init_ex(ctx, (const void*)secret_key.c_str(), secret_key.size(), engine, NULL);
    // HMAC_Update(ctx, (const unsigned char*)str.c_str(), str.size());
    // HMAC_Final(ctx, output, &output_len);
    // HMAC_CTX_free(ctx);

    std::cout << "output: " << output << std::endl;

    return 0;
}

std::string hmac_sha1_hex(const std::string& secret_key, const std::string& str) {
    unsigned char output[EVP_MAX_MD_SIZE];
    memset(output, 0, sizeof(output));
    unsigned int output_len = 0;

    hmac_sha1(secret_key, str, output, output_len);

    char buf[2*EVP_MAX_MD_SIZE];
    memset(buf, 0, sizeof(buf));

    for (int i = 0; i < 20; ++i) {
        sprintf(buf+i*2, "%02x", output[i]);
    }

    return buf;
}
```


测试代码 `demo.cpp`

```c++
#include "demo.h"
#include <assert.h>
#include <stdio.h>

// 每个测试都是独立的，不依赖其他测试例子

void test_base64_encode(void) {
    std::string test_str = "this is a example!";
    std::string expected_decode_str = "dGhpcyBpcyBhIGV4YW1wbGUh";
    
    std::string base64_encode_str = base64_encode((const unsigned char*)test_str.c_str(), test_str.size());
    assert(expected_decode_str == base64_encode_str);
    printf("[SUCCESS] test_base64_encode\n");
}

void test_base64_decode(void) {
    std::string test_str = "this is a example!";

    std::string base64_encode_str = base64_encode((const unsigned char*)test_str.c_str(), test_str.size());
    std::string base64_decode_str = base64_decode(base64_encode_str);

    assert(test_str == base64_decode_str);
    printf("[SUCCESS] test_base64_decode\n");
}

void test_hmac_sha256_hex(void) {
    std::string secret_key = "hello_world";
    std::string test_str = "this is a example!";
    std::string expected_hmac_sha256_hex_str = "cebe17c6334156781138fc96a3ce8161d4e0c46eda08c0d869ac436b14e2af86";

    std::string hmac_sha256_hex_str = hmac_sha256_hex(secret_key, test_str);
    assert(expected_hmac_sha256_hex_str == hmac_sha256_hex_str);
    printf("[SUCCESS] test_hmac_sha256_hex\n");
}

void test_hmac_sha1_hex(void) {
    std::string secret_key = "hello_world";
    std::string test_str = "this is a example!";
    std::string expected_hmac_sha1_hex_str = "e48e00c826ed49434801d1adc8324e5f3a90f651";

    std::string hmac_sha1_hex_str = hmac_sha1_hex(secret_key, test_str);
    assert(expected_hmac_sha1_hex_str == hmac_sha1_hex_str);
    printf("[SUCCESS] test_hmac_sha1_hex\n");
}

int main() {
    test_base64_encode();
    test_base64_decode();
    test_hmac_sha256_hex();
    test_hmac_sha1_hex();

    return 0;
}
```