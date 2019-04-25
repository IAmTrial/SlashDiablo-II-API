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

#include "../../../../include/c/game_func/d2lang/d2lang_unicode_strcat.h"

#include "../../../../include/c/game_struct/d2_unicode_char.h"
#include "../../../../include/cxx/game_func/d2lang/d2lang_unicode_strcat.hpp"

D2_UnicodeChar* D2_D2Lang_Unicode_strcat(
    D2_UnicodeChar dest[],
    const D2_UnicodeChar src[]
) {
  auto actual_dest = reinterpret_cast<d2::UnicodeChar*>(dest);
  auto actual_src = reinterpret_cast<const d2::UnicodeChar*>(src);

  d2::UnicodeChar* ret_value = d2::d2lang::Unicode_strcat(actual_dest, actual_src);

  return reinterpret_cast<D2_UnicodeChar*>(ret_value);
}
