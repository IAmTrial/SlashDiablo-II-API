/**
 * SlashGaming Diablo II Modding API
 * Copyright (C) 2018-2019  Mir Drualga
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
 *  the game.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Glide wrapper (or a modified version of that library),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "../../include/cxx/game_address.hpp"

#include <windows.h>
#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>

#include <fmt/format.h>
#include <fmt/printf.h>
#include "../../include/cxx/default_game_library.hpp"
#include "game_library.hpp"

namespace mapi {

GameAddress::GameAddress(
    std::intptr_t raw_address
)
    : raw_address_(raw_address) {
}

std::intptr_t GameAddress::raw_address(void) const noexcept {
  return raw_address_;
}

GameAddress GameAddress::FromDecoratedName(
    enum DefaultLibrary default_library,
    std::string_view decorated_name
) {
  const std::filesystem::path& default_library_path =
      GetDefaultLibraryPathWithRedirect(default_library);

  return FromDecoratedName(default_library_path, decorated_name);
}

GameAddress GameAddress::FromDecoratedName(
    const std::filesystem::path& library_path,
    std::string_view decorated_name
) {
  const GameLibrary& game_library = GetGameLibrary(library_path);

  FARPROC raw_address = GetProcAddress(
      reinterpret_cast<HMODULE>(game_library.base_address()),
      decorated_name.data()
  );

  if (raw_address == nullptr) {
    std::wstring error_message = fmt::sprintf(
        L"The data or function with the name %s could not be found.",
        fmt::to_wstring(decorated_name)
    );

    MessageBoxW(
        nullptr,
        error_message.data(),
        L"Failed to Locate Address",
        MB_OK | MB_ICONERROR
    );
    std::exit(0);
  }

  return GameAddress(
      reinterpret_cast<std::intptr_t>(raw_address)
  );
}

GameAddress GameAddress::FromOffset(
    enum DefaultLibrary default_library,
    std::intptr_t offset
) {
  const std::filesystem::path& game_library_path =
      GetDefaultLibraryPathWithRedirect(default_library);

  return FromOffset(game_library_path, offset);
}

GameAddress GameAddress::FromOffset(
    const std::filesystem::path& library_path,
    std::intptr_t offset
) {
  const GameLibrary& game_library = GetGameLibrary(library_path);
  
  return GameAddress(game_library.base_address() + offset);
}

GameAddress GameAddress::FromOrdinal(
    enum DefaultLibrary default_library,
    std::int16_t ordinal
) {
  const std::filesystem::path& game_library_path =
      GetDefaultLibraryPathWithRedirect(default_library);

  return FromOffset(game_library_path, ordinal);
}

GameAddress GameAddress::FromOrdinal(
    const std::filesystem::path& library_path,
    std::int16_t ordinal
) {
  const GameLibrary& game_library = GetGameLibrary(library_path);

  FARPROC func_address = GetProcAddress(
      reinterpret_cast<HMODULE>(game_library.base_address()),
      reinterpret_cast<const CHAR*>(ordinal)
  );

  if (func_address == nullptr) {
    std::wstring error_message = fmt::sprintf(
        L"The data or function with the ordinal %d could not be found.",
        ordinal
    );

    MessageBoxW(
        nullptr,
        error_message.data(),
        L"Failed to Locate Address",
        MB_OK | MB_ICONERROR
    );
    std::exit(0);
  }

  return GameAddress(
      reinterpret_cast<std::intptr_t>(func_address)
  );
}

} // namespace mapi
