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

#include "../include/game_version.h"

#include <windows.h>

#include <cstdlib>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

#include <boost/bimap.hpp>
#include <boost/nowide/convert.hpp>
#include "../include/game_library.h"


namespace sgd2mapi {
namespace {

using GameVersionAndFileVersionBimapType = boost::bimap<
    enum GameVersion,
    std::string_view
>;

using GameVersionAndStringBimapType = boost::bimap<
    enum GameVersion,
    std::string_view
>;

const GameVersionAndFileVersionBimapType& GetGameVersionAndFileVersionBimap() {
  static const std::array<
      GameVersionAndFileVersionBimapType::value_type,
      29
  > version_array = {{
        // TODO(Mir Drualga): 1.00 & 1.01 have the same version #, but use
        // completely different DLLs
        { GameVersion::k1_00, "1.0.0.1" },
        { GameVersion::k1_02, "1.0.2.0" },
        { GameVersion::k1_03, "1.0.3.0" },
        { GameVersion::k1_04, "1.0.4.0" },
        // 1.04B and 1.04C use the same DLLs
        { GameVersion::k1_04B, "1.0.4.1" },
        { GameVersion::k1_04C, "1.0.4.2" },
        { GameVersion::k1_05, "1.0.5.0" },
        { GameVersion::k1_05B, "1.0.5.1" },
        // TODO(Mir Drualga): 1.06 & 1.06B have the same version #, but use
        // completely different DLLs
        { GameVersion::k1_06, "1.0.6.0" },
        // TODO(Mir Drualga): 1.07 Beta & 1.07 have the same version #, but use
        // completely different DLLs
        { GameVersion::k1_07, "1.0.7.0" },
        { GameVersion::k1_08, "1.0.8.28" },
        { GameVersion::k1_09, "1.0.9.19" },
        { GameVersion::k1_09B, "1.0.9.20" },
        { GameVersion::k1_09C, "1.0.9.21" },
        { GameVersion::k1_09D, "1.0.9.22" },
        { GameVersion::k1_09E, "1.0.9.23" },
        { GameVersion::k1_10Beta, "1.0.10.9" },
        { GameVersion::k1_10SBeta, "1.0.10.10" },
        { GameVersion::k1_10, "1.0.10.39" },
        { GameVersion::k1_11, "1.0.11.45" },
        { GameVersion::k1_11B, "1.0.11.46" },
        { GameVersion::k1_12A, "1.0.12.49" },
        { GameVersion::k1_13ABeta, "1.0.13.55" },
        { GameVersion::k1_13C, "1.0.13.60" },
        { GameVersion::k1_13D, "1.0.13.64" },
        { GameVersion::kLod1_14A, "1.14.0.64" },
        { GameVersion::kLod1_14B, "1.14.1.68" },
        { GameVersion::kLod1_14C, "1.14.2.70" },
        { GameVersion::kLod1_14D, "1.14.3.71" }
  }};

  static const GameVersionAndFileVersionBimapType
      game_version_and_file_version_bimap(
          version_array.cbegin(),
          version_array.cend()
      );

  return game_version_and_file_version_bimap;
}

const GameVersionAndStringBimapType& GetGameVersionAndStringBimap() {
  static const std::array<
      GameVersionAndStringBimapType::value_type,
      36
  > version_array = {{
        { GameVersion::k1_00, "1.00" },
        { GameVersion::k1_01, "1.01" },
        { GameVersion::k1_02, "1.02" },
        { GameVersion::k1_03, "1.03" },
        { GameVersion::k1_04, "1.04" },
        { GameVersion::k1_04B, "1.04B" },
        { GameVersion::k1_04C, "1.04C" },
        { GameVersion::k1_05, "1.05" },
        { GameVersion::k1_05B, "1.05B" },
        { GameVersion::k1_06, "1.06" },
        { GameVersion::k1_06B, "1.06B" },
        { GameVersion::k1_07Beta, "1.07 Beta" },
        { GameVersion::k1_07, "1.07" },
        { GameVersion::k1_08, "1.08" },
        { GameVersion::k1_09, "1.09" },
        { GameVersion::k1_09B, "1.09B" },
        { GameVersion::k1_09C, "1.09C" },
        { GameVersion::k1_09D, "1.09D" },
        { GameVersion::k1_09E, "1.09E" },
        { GameVersion::k1_10Beta, "1.10 Beta" },
        { GameVersion::k1_10SBeta, "1.10S Beta" },
        { GameVersion::k1_10, "1.10" },
        { GameVersion::k1_11, "1.11" },
        { GameVersion::k1_11B, "1.11B" },
        { GameVersion::k1_12A, "1.12A" },
        { GameVersion::k1_13ABeta, "1.13A Beta" },
        { GameVersion::k1_13C, "1.13C" },
        { GameVersion::k1_13D, "1.13D" },
        { GameVersion::kClassic1_14A, "Classic 1.14A" },
        { GameVersion::kLod1_14A, "LoD 1.14A" },
        { GameVersion::kClassic1_14B, "Classic 1.14B" },
        { GameVersion::kLod1_14B, "LoD 1.14B" },
        { GameVersion::kClassic1_14C, "Classic 1.14C" },
        { GameVersion::kLod1_14C, "LoD 1.14C" },
        { GameVersion::kClassic1_14D, "Classic 1.14D" },
        { GameVersion::kLod1_14D, "LoD 1.14D" }
  }};

  static const GameVersionAndStringBimapType game_version_and_string_bimap(
      version_array.cbegin(),
      version_array.cend()
  );

  return game_version_and_string_bimap;
}

std::optional<std::string> ExtractFileVersionString(std::string_view file_name)
    noexcept {
  // All the code for this function originated from StackOverflow user
  // crashmstr. Some parts were refactored for clarity.

  std::wstring file_name_wide;
  try {
    file_name_wide = boost::nowide::widen(file_name.data());
  } catch (boost::locale::conv::conversion_error&) {
    return std::nullopt;
  }

  // Check version size.
  DWORD version_handle;
  DWORD version_size = GetFileVersionInfoSizeW(file_name_wide.data(),
                                               &version_handle);

  if (version_size == 0) {
    return std::nullopt;
  }

  // Get the file version info.
  auto version_data = std::make_unique<wchar_t[]>(version_size);

  if (!GetFileVersionInfoW(file_name_wide.data(), version_handle,
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

std::optional<enum GameVersion> GetGameVersionByFileVersion(
    std::string_view version_string) {
  const auto& game_versions_by_file_version =
      GetGameVersionAndFileVersionBimap().right;
  auto found_version_pair = game_versions_by_file_version.find(
      version_string
  );

  return (found_version_pair != game_versions_by_file_version.end())
      ? std::make_optional(found_version_pair->second)
      : std::nullopt;
}

enum GameVersion DetermineRunningGameVersion() noexcept {
  // TODO(Mir Drualga): Figure out how to get versions 1.06(B) and 1.14+
  // classic detection.
  std::string game_version_string;

  try {
    game_version_string =
        ExtractFileVersionString(kGameExecutable).value();
  } catch (const std::bad_optional_access&) {
    MessageBoxA(
        nullptr,
        "Failed to extract file version from Game.exe.",
        "Error Detecting Game Version",
        MB_OK | MB_ICONSTOP);
    std::exit(EXIT_FAILURE);
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
    std::exit(EXIT_FAILURE);
  }

  return game_version;
}

/**
 * A singleton class that detects the game version on runtime and stores this
 * information.
 */
class RunningGameVersion {
 public:
  RunningGameVersion(const RunningGameVersion&) = delete;
  RunningGameVersion(RunningGameVersion&&) = delete;

  RunningGameVersion operator=(const RunningGameVersion&) = delete;
  RunningGameVersion operator=(RunningGameVersion&&) = delete;

  /**
   * Returns the singleton instance of RunningGameVersion.
   */
  static RunningGameVersion& GetInstance() noexcept {
    static RunningGameVersion instance;
    return instance;
  }

  /**
   * Returns the running game's version.
   */
  constexpr enum GameVersion game_version_id() const noexcept {
    return game_version_id_;
  }

  constexpr std::string_view game_version_name() const noexcept {
    return game_version_name_;
  }

 private:
  enum GameVersion game_version_id_;
  std::string_view game_version_name_;

  RunningGameVersion() noexcept
    : game_version_id_(DetermineRunningGameVersion()),
      game_version_name_(GetGameVersionName(game_version_id())) {
  }
};

} // namespace

enum GameVersion GetGameVersionId(std::string_view game_version_name) noexcept {
  return GetGameVersionAndStringBimap().right.at(game_version_name);
}

std::string_view GetGameVersionName(enum GameVersion game_version) noexcept {
  return GetGameVersionAndStringBimap().left.at(game_version);
}

enum GameVersion GetRunningGameVersionId() noexcept {
  return RunningGameVersion::GetInstance().game_version_id();
}

std::string_view GetRunningGameVersionName() noexcept {
  return RunningGameVersion::GetInstance().game_version_name();
}

bool IsGameVersionAtLeast1_14(enum GameVersion game_version) noexcept {
  return !(game_version >= GameVersion::k1_00
               && game_version <= GameVersion::k1_13D);
}

bool IsRunningGameVersionAtLeast1_14() noexcept {
  return
      IsGameVersionAtLeast1_14(
          RunningGameVersion::GetInstance().game_version_id()
      );
}

} // namespace sgd2mapi

/**
 * C Interface
 */

const char* sgd2mapi_get_game_version_name(
    enum SGD2MAPI_GameVersion game_version
) {
  return sgd2mapi::GetGameVersionName(
      static_cast<sgd2mapi::GameVersion>(game_version)
  ).data();
}

enum SGD2MAPI_GameVersion sgd2mapi_get_game_version_id(
    const char* game_version_name
) {
  return static_cast<enum SGD2MAPI_GameVersion>(
      sgd2mapi::GetGameVersionId(game_version_name)
  );
}

enum SGD2MAPI_GameVersion sgd2mapi_get_running_game_version_id() {
  return static_cast<enum SGD2MAPI_GameVersion>(
      sgd2mapi::GetRunningGameVersionId()
  );
}

const char* sgd2mapi_get_running_game_version_name() {
  return sgd2mapi::GetRunningGameVersionName().data();
}

bool sgd2mapi_is_game_version_at_least_1_14(
    enum SGD2MAPI_GameVersion game_version
) {
  return sgd2mapi::IsGameVersionAtLeast1_14(
      static_cast<sgd2mapi::GameVersion>(game_version)
  );
}

bool sgd2mapi_is_running_game_version_at_least_1_14() {
  return sgd2mapi::IsRunningGameVersionAtLeast1_14();
}
