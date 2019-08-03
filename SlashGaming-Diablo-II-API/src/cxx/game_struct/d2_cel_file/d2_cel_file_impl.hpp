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

#ifndef SGD2MAPI_CXX_GAME_STRUCT_D2_CEL_FILE_D2_CEL_FILE_IMPL_HPP_
#define SGD2MAPI_CXX_GAME_STRUCT_D2_CEL_FILE_D2_CEL_FILE_IMPL_HPP_

#include "../../../../include/cxx/game_struct/d2_cel_file.hpp"
#include "../../../../include/cxx/game_undefined.hpp"

namespace d2 {

#pragma pack(push, 1)

/* sizeof: 0x14 + sizeof(cels) */ struct CelFile_1_00 {
  /* 0x00 */ std::uint32_t version;
  /* 0x04 */ mapi::UndefinedByte unknown_0x04[0x10 - 0x04];
  /* 0x10 */ std::uint32_t num_directions;
  /* 0x14 */ std::uint32_t num_frames;
  /* 0x18 */ mapi::UndefinedByte cels[0]; // This field gives the struct variable length.
};

#pragma pack(pop)

} // namespace d2

#endif // SGD2MAPI_CXX_GAME_STRUCT_D2_CEL_FILE_D2_CEL_FILE_IMPL_HPP_
