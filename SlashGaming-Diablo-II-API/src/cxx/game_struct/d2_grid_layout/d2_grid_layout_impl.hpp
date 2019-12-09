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

#ifndef SGD2MAPI_CXX_GAME_STRUCT_D2_GRID_LAYOUT_D2_GRID_LAYOUT_IMPL_HPP_
#define SGD2MAPI_CXX_GAME_STRUCT_D2_GRID_LAYOUT_D2_GRID_LAYOUT_IMPL_HPP_

#include <cstdint>
#include <cstddef>

#include "../../../../include/cxx/game_struct/d2_grid_layout/d2_grid_layout_struct.hpp"
#include "../d2_positional_rectangle/d2_positional_rectangle_impl.hpp"

namespace d2 {

#pragma pack(push, 1)

/* sizeof: 0x18 */ struct GridLayout_1_00 {
  /* 0x00 */ std::uint8_t num_columns;
  /* 0x01 */ std::uint8_t num_rows;
  /* 0x02 */ std::uint8_t unused__to_align_0x02[2];
  /* 0x04 */ PositionalRectangle_1_00 position;
  /* 0x14 */ std::uint8_t width;
  /* 0x15 */ std::uint8_t height;
  /* 0x16 */ std::uint8_t unused__to_align_0x22[2];
};

static_assert(sizeof(GridLayout_1_00) == 0x18);
static_assert(offsetof(GridLayout_1_00, num_columns) == 0x00);
static_assert(offsetof(GridLayout_1_00, num_rows) == 0x01);
static_assert(offsetof(GridLayout_1_00, position) == 0x04);
static_assert(offsetof(GridLayout_1_00, width) == 0x14);
static_assert(offsetof(GridLayout_1_00, height) == 0x15);

#pragma pack(pop)

GridLayout* CreateGridLayout(
    std::int_least8_t num_columns,
    std::int_least8_t num_rows,
    const PositionalRectangle* position,
    std::int_least8_t width,
    std::int_least8_t height
);

void DestroyGridLayout(GridLayout* grid_layout);

} // namespace d2

#endif // SGD2MAPI_CXX_GAME_STRUCT_D2_GRID_LAYOUT_D2_GRID_LAYOUT_IMPL_HPP_