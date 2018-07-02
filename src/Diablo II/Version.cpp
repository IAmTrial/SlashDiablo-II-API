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
 *  If you modify this Program, or any covered work, by linking or combining it
 *  with Diablo II (or a modified version of that library), containing parts
 *  covered by the terms of Blizzard End User License Agreement, the licensors
 *  of this Program grant you additional permission to convey the resulting
 *  work.
 *
 *  If you modify this Program, or any covered work, by declaring a custom
 *  version of an existing Diablo II data structure with members ordered
 *  differently from any official version of the game, then such declarations
 *  are exempt from the terms of GNU Affero General Public License version 3
 *  section 6.
 */

#include "Version.h"

#include <windows.h>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "../Common/Common.h"
#include "GameLibrary.h"

namespace slashgaming::diabloii {
namespace {

std::string ExtractFileVersionString(std::string_view file_name);
enum GameVersion GetGameVersionByFileVersion(std::string_view file_version);

} // namespace

enum GameVersion GetGameVersion() {
    // TODO(Mir Drualga): Figure out how to get versions 1.06(B) and 1.14+
    // classic detection.
    static std::string game_version_string = ExtractFileVersionString(
            kGameExecutable);
    static enum GameVersion game_version = GetGameVersionByFileVersion(
            game_version_string);

    return game_version;
}

namespace {

std::string ExtractFileVersionString(std::string_view file_name) {
    // All the code for this function originated from StackOverflow user
    // crashmstr. Some parts were refactored for clarity.

    DWORD version_handle;

    // Check version size.
    std::wstring file_name_wide = common::ConvertAnsiToUnicode(file_name);
    DWORD version_size = GetFileVersionInfoSizeW(file_name_wide.data(),
            &version_handle);
    common::AssertOrTerminateWithMessage(
            (version_size != 0),
            "Error",
            "GetFileVersionInfo failed.");

    // Get the file version info.
    auto version_data = std::make_unique<wchar_t[]>(version_size);
    common::AssertOrTerminateWithMessage(
            GetFileVersionInfoW(file_name_wide.data(),
                    version_handle, version_size, version_data.get()),
            "Error",
            "GetFileVersionInfo failed.");

    // Gather all of the information into the specified buffer, then check
    // version info signature.
    UINT version_info_size;
    VS_FIXEDFILEINFO* version_info = nullptr;
    common::AssertOrTerminateWithMessage(
            VerQueryValueW(version_data.get(), L"\\", (LPVOID*)&version_info,
                    &version_info_size) || version_info_size <= 0 ||
                    version_info->dwSignature != 0xfeef04bd,
            "Error",
            "VerQueryValueW failed.");

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

enum GameVersion GetGameVersionByFileVersion(std::string_view version_string) {
    static const std::unordered_map<std::string_view, enum GameVersion>
            game_versions_by_file_version = {
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
    };

    auto found_version_pair = game_versions_by_file_version.find(
            version_string);

    common::AssertOrTerminateWithMessage(
        (found_version_pair != game_versions_by_file_version.cend()),
        "Error",
        "Unknown game version detected.");

    return found_version_pair->second;
}

} // namespace

} // namespace slashgaming::diabloii::version
