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

#include "../../include/game_address_locator/game_ordinal.h"

#include <windows.h>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <boost/format.hpp>

namespace sgd2mapi {

GameOrdinal::GameOrdinal(int ordinal) noexcept
    : ordinal_(ordinal) {
  if ((ordinal & 0xFFFF) != ordinal) {
    std::wstring error_message = (boost::wformat(
        L"Invalid ordinal value %d. The leftmost four bytes of an ordinal must"
        L"be zero.") % ordinal).str();
    MessageBoxW(nullptr,
                error_message.data(),
                L"Invalid Ordinal Value",
                MB_OK | MB_ICONERROR);
    std::exit(EXIT_FAILURE);
  }
}

GameOrdinal::GameOrdinal(const GameOrdinal&) noexcept = default;

GameOrdinal::GameOrdinal(GameOrdinal&&) noexcept = default;

GameOrdinal::~GameOrdinal() noexcept = default;

GameOrdinal& GameOrdinal::operator=(const GameOrdinal&) noexcept = default;

GameOrdinal& GameOrdinal::operator=(GameOrdinal&&) noexcept = default;

std::intptr_t GameOrdinal::ResolveGameAddress(std::intptr_t base_address)
    const noexcept {
  HMODULE library_handle = reinterpret_cast<HMODULE>(base_address);
  const CHAR* func_ordinal = reinterpret_cast<const CHAR*>(ordinal());

  FARPROC func_address = GetProcAddress(library_handle, func_ordinal);

  if (func_address == nullptr) {
    std::wstring error_message = (boost::wformat(
        L"The function with ordinal %d could not be found."
    ) % ordinal()).str();

    MessageBoxW(nullptr,
                error_message.data(),
                L"Failed to Locate Function",
                MB_OK | MB_ICONERROR);
    std::exit(0);
  }

  return reinterpret_cast<std::intptr_t>(func_address);
}

int GameOrdinal::ordinal() const noexcept {
  return ordinal_;
}

} // namespace sgd2mapi
