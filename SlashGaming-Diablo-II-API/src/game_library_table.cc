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

#include "game_library_table.h"

#include <windows.h>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <string_view>

#include <fmt/format.h>
#include <fmt/printf.h>
#include "../include/game_library.h"

namespace sgd2mapi {

GameLibraryTable::GameLibraryTable(
    void
) = default;

const GameLibrary&
GameLibraryTable::GetGameLibrary(
    const std::filesystem::path& library_path
) noexcept {
  try {
    return libraries_.at(library_path);
  } catch (const std::out_of_range& e) {
    constexpr std::wstring_view kErrorFormatMessage =
        L"File: %s \n"
        L"Line: %d \n"
        L"Could not determine the game library from the file path: %s.";

    std::wstring full_message = fmt::sprintf(
        kErrorFormatMessage,
        fmt::to_wstring(__FILE__),
        __LINE__,
        library_path
    );

    MessageBoxW(
        nullptr,
        full_message.data(),
        L"Failed to Determine Game Library",
        MB_OK | MB_ICONERROR
    );

    std::exit(0);
  }
}

const GameLibrary&
GameLibraryTable::GetGameLibrary(
    enum DefaultLibrary library
) noexcept {
  const std::filesystem::path& library_path =
      GameLibrary::GetLibraryPathWithRedirect(
          library
      );
  return GetGameLibrary(library_path);
}

GameLibraryTable&
GameLibraryTable::GetInstance(
    void
) {
  static GameLibraryTable instance;
  return instance;
}

} // namespace sgd2mapi
