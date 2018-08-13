/**
 * SlashGaming Diablo II Modding API
 * Copyright (C) 2018  SlashGaming Community
 *
 * This file is part of SlashGaming Diablo II Modding API.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Additional permissions under GNU Affero General Public License version 3
 *  section 7
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with Diablo II (or a modified version of that game and its
 *  libraries), containing parts covered by the terms of Blizzard End User
 *  License Agreement, the licensors of this Program grant you additional
 *  permission to convey the resulting work. This additional permission is
 *  also extended to any combination of expansions, mods, and remasters of
 *  the game, provided that the game or its libraries do not link to this
 *  Program.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Glide wrapper (or a modified version of that library),
 *  containing parts not covered by a compatible license, provided that the
 *  wrapper does not link to this Program, the licensors of this Program
 *  grant you additional permission to convey the resulting work.
 */

#ifndef SGD2MAPI_GAME_PATCH_GAME_BUFFER_PATCH_H_
#define SGD2MAPI_GAME_PATCH_GAME_BUFFER_PATCH_H_

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "../game_address.h"
#include "game_patch_base.h"

#if defined(SGD2MAPI_DLLEXPORT)
#define DLLEXPORT __declspec(dllexport)
#elif defined(SGD2MAPI_DLLIMPORT)
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT
#endif

namespace sgd2mapi {

/**
 * A patch that replaces the destination address with the bytes stored in a
 * buffer.
 */
class DLLEXPORT GameBufferPatch : public GamePatchBase {
 public:
  /**
   * Creates an instance of BufferPatch.
   */
  GameBufferPatch(
      const GameAddress& game_address,
      const std::int8_t buffer[],
      std::size_t patch_size);

  /**
   * Creates an instance of BufferPatch.
   */
  GameBufferPatch(
      const GameAddress& game_address,
      const std::vector<std::int8_t>& buffer);

  /**
   * Creates an instance of BufferPatch.
   */
  GameBufferPatch(
      GameAddress&& game_address,
      const std::vector<std::int8_t>& buffer);

  /**
   * Creates an instance of BufferPatch.
   */
  GameBufferPatch(
      const GameAddress& game_address,
      std::vector<std::int8_t>&& buffer);

  /**
   * Creates an instance of BufferPatch.
   */
  GameBufferPatch(
      GameAddress&& game_address,
      std::vector<std::int8_t>&& buffer);

  GameBufferPatch(const GameBufferPatch&);

  GameBufferPatch(GameBufferPatch&&) noexcept;

  ~GameBufferPatch() override;

  GameBufferPatch& operator=(const GameBufferPatch&);

  GameBufferPatch& operator=(GameBufferPatch&&) noexcept;

  void Apply() noexcept override;

  const std::vector<std::int8_t>& buffer() const noexcept;

 private:
  std::vector<std::int8_t> buffer_;
};

} // namespace sgd2mapi

#endif // SGD2MAPI_GAME_PATCH_GAME_BUFFER_PATCH_H_
