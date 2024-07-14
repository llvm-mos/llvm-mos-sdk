// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.
//
// C++ support for MEGA65 DMA operations.
//

#pragma once

#include <array>
#include <cstdint>
#include <mega65.h>
#include <type_traits>

namespace mega65::dma {

/**
 * Data structure for running enhanced DMA jobs
 *
 * @tparam T Either a F018B (default) or F018 DMA list object.
 * @tparam N Byte count of the options and their potential
 *           arguments excluding the end option (0) which is automatically
 *           added.
 */
template <size_t N, typename T> struct DMAJob {
  static_assert(N > 0);
  static_assert(std::is_same<T, DMAList_F018A>::value ||
                std::is_same<T, DMAList_F018B>::value);
  std::array<uint8_t, N> options;
  const uint8_t end_option = 0;
  T dmalist; // Either F018 or F018B
};

/// Common structure for DMA fill and copy jobs
typedef DMAJob<7, DMAList_F018B> CommonDMAJob;

/**
 * Create DMA structure for filling memory with a value and optional skip
 *
 * To perform the actual fill, call `trigger_dma()` on the returned structure.
 *
 * @param dst 28-bit destination address
 * @param value Fill value
 * @param count Number of values to fill
 * @param skip Optional skip (default: 1)
 */
CommonDMAJob make_dma_fill(const uint32_t dst, const uint8_t value,
                           const uint16_t count, const uint8_t skip = 1) {
  CommonDMAJob dma;
  dma.options[0] = ENABLE_F018B_OPT;
  dma.options[1] = SRC_ADDR_BITS_OPT;
  dma.options[2] = 0;
  dma.options[3] = DST_ADDR_BITS_OPT;
  dma.options[4] = (uint8_t)(dst >> 20);
  dma.options[5] = DST_SKIP_RATE_OPT;
  dma.options[6] = skip;
  dma.dmalist.command = DMA_FILL_CMD;
  dma.dmalist.count = count;
  dma.dmalist.source_addr = value;
  dma.dmalist.source_bank = 0;
  dma.dmalist.dest_addr = dst & 0xffff;
  dma.dmalist.dest_bank = (dst >> 16) & 0x0f;
  dma.dmalist.command_msb = 0;
  dma.dmalist.modulo = 0;
  return dma;
}

/**
 * Create DMA structure for copying memory
 *
 * To perform the actual copy, call `trigger_dma()` on the returned structure.
 *
 * @param src 28-bit source address
 * @param dst 28-bit destination address
 * @param count Number of values to copy
 */
CommonDMAJob make_dma_copy(const uint32_t src, const uint32_t dst,
                           const uint16_t count) {
  auto dma = make_dma_fill(dst, 0, count);
  dma.options[2] = (uint8_t)(src >> 20);
  dma.dmalist.command = DMA_COPY_CMD;
  dma.dmalist.source_addr = src & 0xffff;
  dma.dmalist.source_bank = (src >> 16) & 0x0f;
  return dma;
}

/**
 * Perform DMA action defined in DMAJob structure.
 */
template <size_t N, typename T>
inline void trigger_dma(const DMAJob<N, T> &dma_job) {
  DMA.enable_f018b = std::is_same<T, DMAList_F018B>::value;
  DMA.addr_bank = 0;
  DMA.addr_msb = ((uint16_t)&dma_job) >> 8;
  DMA.trigger_enhanced = ((uint16_t)&dma_job) & 0xff;
}

} // end of namespace mega65::dma
