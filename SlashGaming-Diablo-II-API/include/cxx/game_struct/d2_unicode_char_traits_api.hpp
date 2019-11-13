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

#ifndef SGD2MAPI_CXX_GAME_STRUCT_D2_UNICODE_CHAR_TRAITS_API_HPP_
#define SGD2MAPI_CXX_GAME_STRUCT_D2_UNICODE_CHAR_TRAITS_API_HPP_

#include "d2_unicode_char.hpp"

#include <cstddef>

#include "../../dllexport_define.inc"

namespace d2 {

/*
 * Due to the nature of how this API must be implemented (information hiding
 * being necessary to prevent user-created errors), all string APIs cannot be
 * derived from the standard library's.
 */

class DLLEXPORT UnicodeCharTraits_API {
 public:
  using value_type = UnicodeChar;

  static void assign(value_type& r, const value_type& a) noexcept;
  static value_type* assign(value_type* p, std::size_t count, const value_type& a);
  static bool eq(const value_type& a, const value_type& b);
  static bool lt(const value_type& a, const value_type& b);
  static value_type* move(value_type* dest, const value_type* src, std::size_t count);
  static value_type* copy(value_type* dest, const value_type* src, std::size_t count);
  static int compare(const value_type* s1, const value_type* s2, std::size_t count);
  static const UnicodeCharTraits_API::value_type* find(
      const value_type* p,
      std::size_t count,
      const value_type& ch
  );
};

} // namespace d2

#include "../../dllexport_undefine.inc"
#endif // SGD2MAPI_CXX_GAME_STRUCT_D2_UNICODE_CHAR_TRAITS_API_HPP_