/**
 * SlashGaming Diablo II Modding API
 * Copyright (C) 2018  SlashGaming Community
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
 *  the game, provided that the game or its libraries do not link to this
 *  Program.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Glide wrapper (or a modified version of that library),
 *  containing parts not covered by a compatible license, provided that the
 *  wrapper does not link to this Program, the licensors of this Program
 *  grant you additional permission to convey the resulting work.
 */

#ifndef SGD2MAPI_GAME_LIBRARY_H_
#define SGD2MAPI_GAME_LIBRARY_H_

#include <cstdint>
#include <string>
#include <string_view>

#if defined(SGD2MAPI_DLLEXPORT)
#define DLLEXPORT __declspec(dllexport)
#elif defined(SGD2MAPI_DLLIMPORT)
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT
#endif

namespace sgd2mapi {

/**
 * The executable used to run the game.
 */
constexpr std::string_view kGameExecutable = "Game.exe";

/**
 * The default libraries that are used by Diablo II.
 */
enum class DefaultLibrary {
  kBNClient, kD2Client, kD2CMP, kD2Common, kD2DDraw, kD2Direct3D, kD2Game,
  kD2GDI, kD2GFX, kD2Glide, kD2Lang, kD2Launch, kD2MCPClient, kD2Multi,
  kD2Net, kD2Server, kD2Sound, kD2Win, kFog, kStorm,
};

class DLLEXPORT GameLibrary {
 public:
  explicit GameLibrary(enum DefaultLibrary library);
  explicit GameLibrary(std::string_view library_path);

  GameLibrary(const GameLibrary& rhs);
  GameLibrary(GameLibrary&& rhs) noexcept;

  virtual ~GameLibrary() noexcept;

  GameLibrary& operator=(const GameLibrary& rhs);
  GameLibrary& operator=(GameLibrary&& rhs) noexcept;

  static std::string_view GetLibraryPathWithRedirect(
      enum DefaultLibrary library) noexcept;

  std::intptr_t base_address() const noexcept;

  std::string_view library_path() const noexcept;

 private:
  std::intptr_t base_address_;
  std::string library_path_;
};

} // namespace sgd2mapi

#undef DLLEXPORT
#endif // SGD2MAPI_GAME_LIBRARY_H_
