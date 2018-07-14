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

#include "Version.hpp"

#include <windows.h>

#include <cwchar>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

#include <frozen/string.h>
#include <frozen/unordered_map.h>
#include "GameLibrary.hpp"


namespace sgd2mapi::version {
namespace {

constexpr const frozen::unordered_map game_versions_by_file_version =
    frozen::make_unordered_map<frozen::string, enum GameVersion>({
        { "1.0.3.0", GameVersion::k1_03 },
        { "1.0.4.0", GameVersion::k1_04 },
        // 1.04B and 1.04C use the same DLLs
        { "1.0.4.1", GameVersion::k1_04B },
        { "1.0.4.2", GameVersion::k1_04C },
        { "1.0.5.0", GameVersion::k1_05 },
        { "1.0.5.1", GameVersion::k1_05B },
        // TODO(Mir Drualga): 1.06 & 1.06B have the same version #, but use
        // completely different DLLs
        { "1.0.6.0", GameVersion::k1_06 },
        { "1.0.7.0", GameVersion::k1_07 },
        { "1.0.8.28", GameVersion::k1_08 },
        { "1.0.9.19", GameVersion::k1_09 },
        { "1.0.9.20", GameVersion::k1_09B },
        { "1.0.9.21", GameVersion::k1_09C },
        { "1.0.9.22", GameVersion::k1_09D },
        { "1.0.9.23", GameVersion::k1_09E },
        { "1.0.10.9", GameVersion::k1_10Beta },
        { "1.0.10.10", GameVersion::k1_10SBeta },
        { "1.0.10.39", GameVersion::k1_10 },
        { "1.0.11.45", GameVersion::k1_11 },
        { "1.0.11.46", GameVersion::k1_11B },
        { "1.0.12.49", GameVersion::k1_12A },
        { "1.0.13.55", GameVersion::k1_13ABeta },
        { "1.0.13.60", GameVersion::k1_13C },
        { "1.0.13.64", GameVersion::k1_13D },
        { "1.14.0.64", GameVersion::kLod1_14A },
        { "1.14.1.68", GameVersion::kLod1_14B },
        { "1.14.2.70", GameVersion::kLod1_14C },
        { "1.14.3.71", GameVersion::kLod1_14D }
    });

std::optional<std::string> ExtractFileVersionString(
    std::string_view file_name) noexcept {
  // All the code for this function originated from StackOverflow user
  // crashmstr. Some parts were refactored for clarity.

  // Convert file name to wide string, but first test that a conversion is
  // possible.
  const char* file_name_buffer = file_name.data();
  auto file_name_wide_buffer = std::make_unique<wchar_t[]>(file_name.length());
  std::mbstate_t state;

  std::size_t buffer_size = std::mbsrtowcs(nullptr, &file_name_buffer, 0,
                                           &state) + 1;
  if (buffer_size == static_cast<std::size_t>(-1)) {
    return std::nullopt;
  }

  file_name_buffer = file_name.data();
  std::mbsrtowcs(file_name_wide_buffer.get(), &file_name_buffer, buffer_size,
                 &state);

  // Check version size.
  DWORD version_handle;
  DWORD version_size = GetFileVersionInfoSizeW(file_name_wide_buffer.get(),
                                               &version_handle);

  if (version_size == 0) {
    return std::nullopt;
  }

  // Get the file version info.
  auto version_data = std::make_unique<wchar_t[]>(version_size);

  if (!GetFileVersionInfoW(file_name_wide_buffer.get(), version_handle,
                           version_size, version_data.get())) {
    return std::nullopt;
  }

  // Gather all of the information into the specified buffer, then check
  // version info signature.
  UINT version_info_size;
  VS_FIXEDFILEINFO* version_info;

  if (!VerQueryValueW(version_data.get(), L"\\", (LPVOID*)&version_info,
                      &version_info_size)
      || version_info_size <= 0
      || version_info->dwSignature != 0xfeef04bd) {
    return std::nullopt;
  }

  // Doesn't matter if you are on 32 bit or 64 bit,
  // DWORD is always 32 bits, so first two revision numbers
  // come from dwFileVersionMS, last two come from dwFileVersionLS
  std::ostringstream stringStream;

  stringStream << ((version_info->dwFileVersionMS >> 16) & 0xffff) << ".";
  stringStream << ((version_info->dwFileVersionMS >> 0) & 0xffff) << ".";
  stringStream << ((version_info->dwFileVersionLS >> 16) & 0xffff) << ".";
  stringStream << ((version_info->dwFileVersionLS >> 0) & 0xffff);

  return stringStream.str();
}

constexpr std::optional<enum GameVersion> GetGameVersionByFileVersion(
    std::string_view version_string) {
  auto found_version_pair = game_versions_by_file_version.find(
      frozen::string(version_string.data(), version_string.length()));

  return (found_version_pair != game_versions_by_file_version.cend())
      ? std::make_optional(found_version_pair->second)
      : std::nullopt;
}

enum GameVersion DetermineRunningGameVersion() noexcept {
  // TODO(Mir Drualga): Figure out how to get versions 1.06(B) and 1.14+
  // classic detection.
  std::string game_version_string;

  try {
    game_version_string =
        ExtractFileVersionString(library::kGameExecutable).value();
  } catch (const std::bad_optional_access&) {
    MessageBoxA(
        nullptr,
        "Failed to extract file version from Game.exe.",
        "Error Detecting Game Version",
        MB_OK | MB_ICONSTOP);
    std::exit(0);
  }

  enum GameVersion game_version;

  try {
    game_version = GetGameVersionByFileVersion(game_version_string).value();
  } catch (const std::bad_optional_access&) {
    MessageBoxA(
        nullptr,
        "Failed to determine game version using file information.",
        "Error Detecting Game Version",
        MB_OK | MB_ICONSTOP);
    std::exit(0);
  }

  return game_version;
}

} // namespace

RunningGameVersion::RunningGameVersion() noexcept :
    game_version_(DetermineRunningGameVersion()) {
}

const RunningGameVersion& RunningGameVersion::GetInstance() noexcept {
  static RunningGameVersion instance;
  return instance;
}

} // namespace sgd2mapi::version
