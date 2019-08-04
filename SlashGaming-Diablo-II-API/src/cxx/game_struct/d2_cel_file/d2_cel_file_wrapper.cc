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

#include "../../../../include/cxx/game_struct/d2_cel_file.hpp"

#include "../../../../include/cxx/game_struct/d2_cel_context.hpp"
#include "d2_cel_file_impl.hpp"

namespace d2 {

CelFile_Wrapper::CelFile_Wrapper(
    CelFile* ptr
) noexcept :
    CelFile_ConstWrapper(ptr),
    ptr_(ptr) {
}

CelFile_Wrapper::CelFile_Wrapper(
    const CelFile_Wrapper& other
) = default;

CelFile_Wrapper::CelFile_Wrapper(
    CelFile_Wrapper&& other
) noexcept = default;

CelFile_Wrapper::~CelFile_Wrapper() = default;

CelFile_Wrapper& CelFile_Wrapper::operator=(
    const CelFile_Wrapper& other
) = default;

CelFile_Wrapper& CelFile_Wrapper::operator=(
    CelFile_Wrapper&& other
) noexcept = default;

CelFile* CelFile_Wrapper::Get() noexcept {
  return this->ptr_;
}

const CelFile* CelFile_Wrapper::Get() const noexcept {
  return CelFile_ConstWrapper::Get();
}

Cel* CelFile_Wrapper::GetCel(unsigned int direction, unsigned int frame) {
  CelContext_API cel_context(this->Get(), direction, frame);
  return cel_context.GetCel();
}

void CelFile_Wrapper::SetVersion(unsigned int value) noexcept {
  auto actual_cel_file = reinterpret_cast<CelFile_1_00*>(this->Get());

  actual_cel_file->version = value;
}

void CelFile_Wrapper::SetNumDirections(unsigned int value) noexcept {
  auto actual_cel_file = reinterpret_cast<CelFile_1_00*>(this->Get());

  actual_cel_file->num_directions = value;
}

void CelFile_Wrapper::SetNumFrames(unsigned int value) noexcept {
  auto actual_cel_file = reinterpret_cast<CelFile_1_00*>(this->Get());

  actual_cel_file->num_frames = value;
}

} // namespace d2
