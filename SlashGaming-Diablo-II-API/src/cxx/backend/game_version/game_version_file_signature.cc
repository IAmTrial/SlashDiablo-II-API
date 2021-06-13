/**
 * SlashGaming Diablo II Modding API for C++
 * Copyright (C) 2018-2021  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Modding API for C++.
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
 *  it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
 *  Glide, OpenGL, or Rave wrapper (or modified versions of those
 *  libraries), containing parts not covered by a compatible license, the
 *  licensors of this Program grant you additional permission to convey the
 *  resulting work.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any library (or a modified version of that library) that links
 *  to Diablo II (or a modified version of that game and its libraries),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "game_version_file_signature.hpp"

#include <algorithm>
#include <utility>

#include <mdc/wchar_t/filew.h>
#include <mdc/error/exit_on_error.hpp>
#include "../../../../include/cxx/game_executable.hpp"
#include "../game_file/file_signature.hpp"

namespace mapi::game_version::file_signature {
namespace {

using FileSignatureTableEntry = ::std::pair<
    FileSignature,
    ::d2::GameVersion
>;

struct FileSignatureTableEntryCompareKey {
  constexpr bool operator()(
      const FileSignatureTableEntry& entry1,
      const FileSignatureTableEntry& entry2
  ) const noexcept {
    return entry1.first < entry2.first;
  }

  constexpr bool operator()(
      const FileSignatureTableEntry& entry,
      const FileSignature& file_signature
  ) const noexcept {
    return entry.first < file_signature;
  }

  constexpr bool operator()(
      const FileSignature& file_signature,
      const FileSignatureTableEntry& entry
  ) const noexcept {
    return file_signature < entry.first;
  }
};

static constexpr const ::std::array<
    FileSignatureTableEntry,
    16
> kFileSignatureSortedTable = {{
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x05, 0x00,
            0x34, 0x81, 0xD4, 0x56, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x02, 0x01,
            0x0B, 0x01, 0x08, 0x00, 0x00, 0xC0, 0x2C, 0x00,

            0x00, 0xE0, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x42, 0x13, 0x29, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0xD0, 0x2C, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kLod1_14A
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x05, 0x00,
            0x38, 0x81, 0xD4, 0x56, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x02, 0x01,
            0x0B, 0x01, 0x08, 0x00, 0x00, 0xC0, 0x2C, 0x00,

            0x00, 0xD0, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x82, 0xFB, 0x28, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0xD0, 0x2C, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kClassic1_14A
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x05, 0x00,
            0x4D, 0xDF, 0x2C, 0x57, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x02, 0x01,
            0x0B, 0x01, 0x08, 0x00, 0x00, 0xC0, 0x2C, 0x00,

            0x00, 0xD0, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xE2, 0x50, 0x28, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0xD0, 0x2C, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kLod1_14C
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x05, 0x00,
            0x52, 0xDF, 0x2C, 0x57, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x02, 0x01,
            0x0B, 0x01, 0x08, 0x00, 0x00, 0xC0, 0x2C, 0x00,

            0x00, 0xC0, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x82, 0xF9, 0x28, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0xD0, 0x2C, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kClassic1_14C
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x05, 0x00,
            0xA8, 0x78, 0xFC, 0x56, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x02, 0x01,
            0x0B, 0x01, 0x08, 0x00, 0x00, 0xC0, 0x2C, 0x00,

            0x00, 0xE0, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xF2, 0x54, 0x28, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0xD0, 0x2C, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kLod1_14B
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x05, 0x00,
            0xAE, 0x78, 0xFC, 0x56, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x02, 0x01,
            0x0B, 0x01, 0x08, 0x00, 0x00, 0xC0, 0x2C, 0x00,

            0x00, 0xD0, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x92, 0xFD, 0x28, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0xD0, 0x2C, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kClassic1_14B
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x05, 0x00,
            0xBC, 0xDF, 0x4D, 0x57, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x02, 0x01,
            0x0B, 0x01, 0x08, 0x00, 0x00, 0xB0, 0x2C, 0x00,

            0x00, 0x60, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x85, 0x29, 0x28, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0xC0, 0x2C, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kLod1_14D
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x05, 0x00,
            0xC4, 0xDF, 0x4D, 0x57, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x02, 0x01,
            0x0B, 0x01, 0x08, 0x00, 0x00, 0xB0, 0x2C, 0x00,

            0x00, 0x50, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xB5, 0xCC, 0x28, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0xC0, 0x2C, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kClassic1_14D
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x06, 0x00,
            0x25, 0x47, 0x52, 0x39, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0E, 0x21,
            0x0B, 0x01, 0x06, 0x00, 0x00, 0xF0, 0x02, 0x00,

            0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x20, 0xA4, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::k1_01
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x06, 0x00,
            0x32, 0xA6, 0xDC, 0x3A, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0E, 0x21,
            0x0B, 0x01, 0x06, 0x00, 0x00, 0x00, 0x03, 0x00,

            0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x50, 0xA7, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0x10, 0x03, 0x00, 0x00, 0x00, 0xFB, 0x6F,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::k1_07Beta
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x06, 0x00,
            0x43, 0x0C, 0xD6, 0x3A, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0E, 0x21,
            0x0B, 0x01, 0x06, 0x00, 0x00, 0x00, 0x03, 0x00,

            0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x50, 0xA7, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0x10, 0x03, 0x00, 0x00, 0x00, 0xFB, 0x6F,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::k1_06
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x06, 0x00,
            0x79, 0xBD, 0x20, 0x39, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0E, 0x21,
            0x0B, 0x01, 0x06, 0x00, 0x00, 0xF0, 0x02, 0x00,

            0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x20, 0xA4, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kBeta1_02StressTest
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x06, 0x00,
            0xB5, 0x92, 0xF5, 0x3A, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0E, 0x21,
            0x0B, 0x01, 0x06, 0x00, 0x00, 0x00, 0x03, 0x00,

            0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x50, 0xA7, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0x10, 0x03, 0x00, 0x00, 0x00, 0xFB, 0x6F,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::k1_07
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x06, 0x00,
            0xB7, 0x70, 0xD0, 0x38, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0E, 0x21,
            0x0B, 0x01, 0x06, 0x00, 0x00, 0xF0, 0x02, 0x00,

            0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x70, 0x9A, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::kBeta1_02
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x06, 0x00,
            0xBC, 0xC7, 0x2E, 0x39, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0E, 0x21,
            0x0B, 0x01, 0x06, 0x00, 0x00, 0xF0, 0x02, 0x00,

            0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x20, 0xA4, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::k1_00
    },
    {
        FileSignature{{
            0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x06, 0x00,
            0xC1, 0x7B, 0xE0, 0x3A, 0x00, 0x00, 0x00, 0x00,

            0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0E, 0x21,
            0x0B, 0x01, 0x06, 0x00, 0x00, 0x00, 0x03, 0x00,

            0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x50, 0xA7, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00,

            0x00, 0x10, 0x03, 0x00, 0x00, 0x00, 0xFB, 0x6F,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
        }},
        d2::GameVersion::k1_06B
    },
}};

// If this assertion compiles but produces a linter error, ignore it.
static_assert(
    ::std::is_sorted(
        kFileSignatureSortedTable.cbegin(),
        kFileSignatureSortedTable.cend(),
        FileSignatureTableEntryCompareKey()
    )
);

static d2::GameVersion SearchTable(
    const FileSignature& file_signature
) {
  ::std::pair search_range = ::std::equal_range(
      kFileSignatureSortedTable.cbegin(),
      kFileSignatureSortedTable.cend(),
      file_signature,
      FileSignatureTableEntryCompareKey()
  );

  if (search_range.first == kFileSignatureSortedTable.cend()
      || search_range.first == search_range.second) {
    ::mdc::error::ExitOnGeneralError(
        L"Error",
        L"Could not determine the game version from the file signature.",
        __FILEW__,
        __LINE__
    );

    return static_cast<d2::GameVersion>(-1);
  }

  return search_range.first->second;
}

} // namespace

::d2::GameVersion GetGameVersion(
    bool is_game_version_at_least_1_14
) {
  ::std::filesystem::path path = is_game_version_at_least_1_14
      ? game_executable::GetPath()
      : L"Storm.dll";

  FileSignature signature = FileSignature::ReadFile(path.c_str());

  return SearchTable(signature);
}

} // namespace mapi::game_version::file_signature
