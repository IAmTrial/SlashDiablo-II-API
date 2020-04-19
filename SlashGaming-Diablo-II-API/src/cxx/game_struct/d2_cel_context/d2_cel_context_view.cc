/**
 * SlashGaming Diablo II Modding API for C++
 * Copyright (C) 2018-2020  Mir Drualga
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

#include "../../../../include/cxx/game_struct/d2_cel_context.hpp"

#include "../../../../include/cxx/game_version.hpp"

namespace d2 {

CelContext_View::CelContext_View(
    const CelContext* cel_context
) noexcept :
    cel_context_(cel_context) {
}

CelContext_View::CelContext_View(
    const CelContext_View& other
) noexcept = default;

CelContext_View::CelContext_View(
    CelContext_View&& other
) noexcept = default;

CelContext_View::~CelContext_View() noexcept = default;

CelContext_View& CelContext_View::operator=(
    const CelContext_View& other
) noexcept = default;

CelContext_View& CelContext_View::operator=(
    CelContext_View&& other
) noexcept = default;

const CelContext* CelContext_View::Get() const noexcept {
  return this->cel_context_;
}

const CelFile* CelContext_View::GetCelFile() const noexcept {
  GameVersion running_game_version = GetRunningGameVersionId();

  if (running_game_version <= GameVersion::k1_10) {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_00*>(this->Get());

    return reinterpret_cast<const CelFile*>(actual_cel_context->cel_file);
  } else if (running_game_version == GameVersion::k1_12A) {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_12A*>(this->Get());

    return reinterpret_cast<const CelFile*>(actual_cel_context->cel_file);
  } else /* if (running_game_version >= GameVersion::k1_13C) */ {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_13C*>(this->Get());

    return reinterpret_cast<const CelFile*>(actual_cel_context->cel_file);
  }
}

unsigned int CelContext_View::GetDirection() const noexcept {
  GameVersion running_game_version = GetRunningGameVersionId();

  if (running_game_version <= GameVersion::k1_10) {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_00*>(this->Get());

    return actual_cel_context->direction;
  } else if (running_game_version == GameVersion::k1_12A) {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_12A*>(this->Get());

    return actual_cel_context->direction;
  } else /* if (running_game_version >= GameVersion::k1_13C) */ {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_13C*>(this->Get());

    return actual_cel_context->direction;
  }
}

unsigned int CelContext_View::GetFrame() const noexcept {
  GameVersion running_game_version = GetRunningGameVersionId();

  if (running_game_version <= GameVersion::k1_10) {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_00*>(this->Get());

    return actual_cel_context->frame;
  } else if (running_game_version == GameVersion::k1_12A) {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_12A*>(this->Get());

    return actual_cel_context->frame;
  } else /* if (running_game_version >= GameVersion::k1_13C) */ {
    const auto* actual_cel_context =
        reinterpret_cast<const CelContext_1_13C*>(this->Get());

    return actual_cel_context->frame;
  }
}

} // namespace d2
