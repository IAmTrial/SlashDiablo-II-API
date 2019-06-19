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

#include "../../../../include/cxx/game_struct/d2_mpq_archive_handle.hpp"

#include <filesystem>

#include "../../../../include/cxx/game_func/d2win_func.hpp"

namespace d2 {

MPQArchiveHandle_API::MPQArchiveHandle_API(
    const std::filesystem::path& mpq_file_path,
    bool is_set_error_on_drive_query_fail,
    int priority
) : MPQArchiveHandle_API(
        mpq_file_path,
        is_set_error_on_drive_query_fail,
        nullptr,
        priority
    ) {
}

MPQArchiveHandle_API::MPQArchiveHandle_API(
    const std::filesystem::path& mpq_file_path,
    bool is_set_error_on_drive_query_fail,
    void* (*on_fail_callback)(),
    int priority
) : MPQArchiveHandle_Wrapper(
        d2win::LoadMPQ(
            mpq_file_path.u8string().data(),
            is_set_error_on_drive_query_fail,
            on_fail_callback,
            priority
        )
    ) {
}

MPQArchiveHandle_API::MPQArchiveHandle_API(
    const MPQArchiveHandle_API& other
) = default;

MPQArchiveHandle_API::MPQArchiveHandle_API(
    MPQArchiveHandle_API&& other
) noexcept = default;

MPQArchiveHandle_API::~MPQArchiveHandle_API() {
  d2win::UnloadMPQ(this->Get());
}

MPQArchiveHandle_API& MPQArchiveHandle_API::operator=(
    const MPQArchiveHandle_API& other
) = default;

MPQArchiveHandle_API& MPQArchiveHandle_API::operator=(
    MPQArchiveHandle_API&& other
) noexcept = default;

} // namespace d2
