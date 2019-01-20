/* Copyright (c) 2019, tini2p
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SRC_CRYPTO_RAND_H_
#define SRC_CRYPTO_RAND_H_

#include <cryptopp/osrng.h>

namespace ntcp2
{
namespace crypto
{
/// @brief Generate a random block of data with OS RNG
/// @param Blocking Boolean flag to use blocking RNG
/// @param data Buffer to fill with random data
/// @param size Size of data buffer
template <bool Blocking = false>
inline void RandBytes(uint8_t* data, const std::size_t size)
{
  CryptoPP::OS_GenerateRandomBlock(Blocking, data, size);
}

/// @brief Generate a random block of data with OS RNG
/// @param Blocking Boolean flag to use blocking RNG
/// @param buf Buffer to fill with random data
template <bool Blocking = false, class Buffer>
inline void RandBytes(Buffer& buf)
{
  CryptoPP::OS_GenerateRandomBlock(Blocking, buf.data(), buf.size());
}

template <class Int>
inline Int RandInRange(const Int min, const Int max)
{
  Int rand;
  do
    {
      CryptoPP::OS_GenerateRandomBlock(
          false, reinterpret_cast<std::uint8_t*>(&rand), sizeof(rand));
    }
  while (rand < min || rand > max);

  return rand;
}
}  // namespace crypto
}  // namespace ntcp2

#endif  // SRC_CRYPTO_RAND_H_