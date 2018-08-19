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

#ifndef SGD2MAPI_GAME_ADDRESS_LOCATOR_GAME_ORDINAL_H_
#define SGD2MAPI_GAME_ADDRESS_LOCATOR_GAME_ORDINAL_H_

#include "game_address_locator_interface.h"

#ifdef __cplusplus
#include <cstdint>
#endif // __cplusplus

#if defined(SGD2MAPI_DLLEXPORT)
#define DLLEXPORT __declspec(dllexport)
#elif defined(SGD2MAPI_DLLIMPORT)
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT
#endif

namespace sgd2mapi {

class DLLEXPORT GameOrdinal : public GameAddressLocatorInterface {
 public:
  explicit GameOrdinal(int ordinal) noexcept;

  GameOrdinal(const GameOrdinal& rhs) noexcept;
  GameOrdinal(GameOrdinal&& rhs) noexcept;

  ~GameOrdinal() noexcept override;

  GameOrdinal& operator=(const GameOrdinal&) noexcept;
  GameOrdinal& operator=(GameOrdinal&&) noexcept;

  std::intptr_t ResolveGameAddress(std::intptr_t base_address)
      const noexcept override;

  int ordinal() const noexcept;

 private:
  int ordinal_;
};

} // namespace sgd2mapi

/**
 * C Interface
 */

struct SGD2MAPI_GameOrdinal;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

DLLEXPORT void sgd2mapi_game_ordinal_create(
    struct SGD2MAPI_GameOrdinal* game_ordinal,
    int ordinal
);

DLLEXPORT void sgd2mapi_game_ordinal_destroy(
    struct SGD2MAPI_GameOrdinal* game_ordinal
);

DLLEXPORT int sgd2mapi_game_ordinal_get_ordinal(
    const struct SGD2MAPI_GameOrdinal* game_ordinal
);

#ifdef __cplusplus
}
#endif // __cplusplus

#undef DLLEXPORT
#endif // SGD2MAPI_GAME_ADDRESS_LOCATOR_GAME_ORDINAL_H_
