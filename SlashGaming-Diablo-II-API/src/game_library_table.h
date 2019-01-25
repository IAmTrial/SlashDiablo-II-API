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

#ifndef SGD2MAPI_GAME_LIBRARY_TABLE_H_
#define SGD2MAPI_GAME_LIBRARY_TABLE_H_

#include <cstdint>
#include <filesystem>
#include <string>
#include <map>

#include "../include/game_library.h"

namespace sgd2mapi {

class GameLibraryTable {
 public:
  GameLibraryTable(
      const GameLibraryTable& rhs
  ) = delete;

  GameLibraryTable(
      GameLibraryTable&& rhs
  ) = delete;

  GameLibraryTable
  operator=(
      const GameLibraryTable& rhs
  ) = delete;

  GameLibraryTable
  operator=(
      GameLibraryTable&& rhs
  ) = delete;

  static GameLibraryTable&
  GetInstance(
      void
  );

  const GameLibrary&
  GetGameLibrary(
      enum DefaultLibrary library
  );

  const GameLibrary&
  GetGameLibrary(
      const std::filesystem::path& library_path
  );

 private:
  std::map<std::filesystem::path, GameLibrary> libraries_;

  GameLibraryTable(
      void
  );
};

} // namespace sgd2mapi

#endif // SGD2MAPI_GAME_LIBRARY_TABLE_H_
