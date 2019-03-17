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

#ifndef SGD2MAPI_CXX_GAME_LIBRARY_HPP_
#define SGD2MAPI_CXX_GAME_LIBRARY_HPP_

#include <cstdint>
#include <filesystem>

#include "../../include/cxx/default_game_library.hpp"

namespace mapi {

/**
 * A class that corresponds to a library used by the game.
 */
class GameLibrary {
 public:
  /**
   * Creates a new instance of a GameLibrary using the default library ID.
   */
  explicit GameLibrary(
      enum DefaultLibrary library
  );

  /**
   * Creates a new instance of a GameLibrary using the library path.
   */
  explicit GameLibrary(
      const std::filesystem::path& library_path
  );

  /**
   * Creates a new instance of a GameLibrary using the library path.
   */
  explicit GameLibrary(
      std::filesystem::path&& library_path
  );

  GameLibrary(
      const GameLibrary& rhs
  );

  GameLibrary(
      GameLibrary&& rhs
  );

  virtual
  ~GameLibrary(
      void
  );

  GameLibrary&
  operator=(
      const GameLibrary& rhs
  );

  GameLibrary&
  operator=(
      GameLibrary&& rhs
  );

  /**
   * Returns the base address value of this GameLibrary.
   */
  std::intptr_t
  base_address(
      void
  ) const noexcept;

  /**
   * Returns the library path of this GameLibrary.
   */
  const std::filesystem::path&
  library_path(
      void
  ) const noexcept;

 private:
  std::filesystem::path library_path_;
  std::intptr_t base_address_;
};

const GameLibrary&
GetGameLibrary(
    enum DefaultLibrary library
);

const GameLibrary&
GetGameLibrary(
    const std::filesystem::path& library_path
);

} // namespace mapi

#endif // SGD2MAPI_CXX_GAME_LIBRARY_HPP_
