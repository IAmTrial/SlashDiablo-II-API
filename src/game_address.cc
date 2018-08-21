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

#include "../include/game_address.h"

#include <windows.h>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

#include <boost/format.hpp>
#include "c_interface/game_address.h"
#include "game_address_locator/c_interface/game_address_locator_interface.h"
#include "../include/game_address_locator.h"
#include "../include/game_library.h"
#include "game_library_table.h"
#include "../include/game_version.h"

namespace sgd2mapi {

namespace {

std::intptr_t ResolveGameAddress(
    std::string_view library_path,
    const GameAddressLocatorInterface& address_locator
) noexcept {

  // Figure out which game library is specified.
  const GameLibrary& address_library =
      GameLibraryTable::GetInstance().GetGameLibrary(library_path);

  // Calculate the resolved address
  std::intptr_t base_address = address_library.base_address();
  std::intptr_t resolved_address =
      address_locator.ResolveGameAddress(base_address);

  return resolved_address;
}

std::intptr_t ResolveGameAddress(
    std::string_view library_path,
    const std::unordered_map<
        enum GameVersion,
        std::shared_ptr<GameAddressLocatorInterface>
    >& address_locators) noexcept {
  enum GameVersion current_version = GetRunningGameVersionId();

  const GameLibrary& address_library =
      GameLibraryTable::GetInstance().GetGameLibrary(library_path);

  std::intptr_t resolved_address;

  try {
    const auto& running_address_locator =
        address_locators.at(current_version);

    std::intptr_t base_address = address_library.base_address();

    resolved_address =
        running_address_locator->ResolveGameAddress(base_address);
  } catch (std::out_of_range&) {
    std::wstring error_message = (boost::wformat(
        L"Game address not defined for the game version: %s. The game will "
        L"nowexit.") % GetRunningGameVersionName().data()).str();
    MessageBoxW(nullptr,
                error_message.data(),
                L"Error: Missing Game Address",
                MB_OK | MB_ICONERROR);
    std::exit(EXIT_FAILURE);
  }

  return resolved_address;
}

} // namespace

GameAddress::GameAddress(std::intptr_t address) noexcept
    : address_(address) {
}

GameAddress::GameAddress(
    std::string_view library_path,
    const GameAddressLocatorInterface& address_locator
) noexcept
    : address_(ResolveGameAddress(library_path, address_locator)) {
}

GameAddress::GameAddress(
    enum DefaultLibrary library,
    const GameAddressLocatorInterface& address_locator
) noexcept
    : GameAddress(GameLibrary::GetLibraryPathWithRedirect(library),
                  address_locator) {
}

GameAddress::GameAddress(
    std::string_view library_path,
    const std::unordered_map<
        enum GameVersion,
        std::shared_ptr<GameAddressLocatorInterface>
    >& address_locators) noexcept
    : address_(ResolveGameAddress(library_path, address_locators)) {
}

GameAddress::GameAddress(
    enum DefaultLibrary library,
    const std::unordered_map<
        enum GameVersion,
        std::shared_ptr<GameAddressLocatorInterface>
    >& address_locators) noexcept
    : GameAddress(GameLibrary::GetLibraryPathWithRedirect(library),
                  address_locators) {
}

GameAddress::GameAddress(const GameAddress&) noexcept = default;

GameAddress::GameAddress(GameAddress&&) noexcept = default;

GameAddress& GameAddress::operator=(const GameAddress&) noexcept = default;

GameAddress& GameAddress::operator=(GameAddress&&) noexcept = default;

std::intptr_t GameAddress::address() const noexcept {
  return address_;
}

} // namespace sgd2mapi

void sgd2mapi_game_address_create_from_library_path(
    struct SGD2MAPI_GameAddress* game_address,
    const char* library_path,
    const struct SGD2MAPI_GameAddressLocatorInterface* game_address_locators[]
) {
  int game_version_value =
      static_cast<int>(sgd2mapi::GetRunningGameVersionId());
  const sgd2mapi::GameAddressLocatorInterface& address_locator =
      *(game_address_locators[game_version_value]->game_address_locator);

  game_address->game_address =
      new sgd2mapi::GameAddress(library_path, address_locator);
}

void sgd2mapi_game_address_create_from_library_id(
    struct SGD2MAPI_GameAddress* game_address,
    enum SGD2MAPI_DefaultLibrary library_id,
    const struct SGD2MAPI_GameAddressLocatorInterface* game_address_locators[]
) {
  int game_version_value =
      static_cast<int>(sgd2mapi::GetRunningGameVersionId());
  const sgd2mapi::GameAddressLocatorInterface& address_locator =
      *(game_address_locators[game_version_value]->game_address_locator);

  enum sgd2mapi::DefaultLibrary converted_library_id =
      static_cast<sgd2mapi::DefaultLibrary>(library_id);

  game_address->game_address =
      new sgd2mapi::GameAddress(converted_library_id, address_locator);
}

void sgd2mapi_game_address_destroy(
    struct SGD2MAPI_GameAddress* game_address
) {
  delete game_address->game_address;
}

std::intptr_t sgd2mapi_game_address_get_address(
    const struct SGD2MAPI_GameAddress* game_address
) {
  return game_address->game_address->address();
}
