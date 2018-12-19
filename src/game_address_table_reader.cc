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

#include "game_address_table_reader.h"

#include <cstdint>
#include <charconv>
#include <fstream>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>

#include <nlohmann/json.hpp>
#include "../include/game_address_locator.h"
#include "../include/game_library.h"
#include "game_library_table.h"
#include "../include/game_version.h"

namespace sgd2mapi {

namespace {

constexpr std::string_view kLocatorTypeKey = "Locator Type";
constexpr std::string_view kLocatorValueKey = "Locator Value";

constexpr std::string_view kLocatorTypeOffset = "Offset";
constexpr std::string_view kLocatorTypeOrdinal = "Ordinal";
constexpr std::string_view kLocatorTypeDecoratedName = "Decorated Name";

using Locator = std::unordered_map<std::string, nlohmann::json>;
using LocatorByVersion = std::unordered_map<std::string, Locator>;

std::intptr_t
ResolveLocatorAndGetAddress(
    std::intptr_t game_library_base_address,
    std::string_view locator_type,
    std::string_view locator_value
) {
  std::unique_ptr<GameAddressLocatorInterface> game_address_locator;

  if (locator_type == kLocatorTypeOffset) {
    int offset = std::stoi(locator_value.data(), 0, 16);
    game_address_locator = std::make_unique<GameOffset>(offset);
  } else if (locator_type == kLocatorTypeOrdinal) {
    int ordinal;
    std::from_chars(
        locator_value.data(),
        locator_value.data() + locator_value.length(),
        ordinal
    );

    game_address_locator = std::make_unique<GameOrdinal>(ordinal);
  } else if (locator_type == kLocatorTypeDecoratedName) {
    game_address_locator = std::make_unique<GameDecoratedName>(locator_value);
  }

  return game_address_locator->ResolveGameAddress(game_library_base_address);
}

std::intptr_t
ResolveAddress(
    std::string_view library_name,
    std::string_view address_name,
    std::string_view locator_type,
    std::string_view locator_value
) {
  std::string library_file_name = library_name.data();
  library_file_name += ".dll";

  const GameLibrary& game_library =
      GameLibraryTable::GetInstance().GetGameLibrary(library_file_name);
  std::intptr_t game_library_base_address = game_library.base_address();

  std::intptr_t resolved_game_address = ResolveLocatorAndGetAddress(
      game_library_base_address,
      locator_type,
      locator_value
  );

  return resolved_game_address;
}

} // namespace

std::unordered_map<std::string, std::intptr_t>
ReadTsvTableFile(
    std::string_view table_file_path
) {
  static const std::regex kLineRegex(
      "(.*?)\t(.*?)\t(.*?)\t([^\t]*)(.*)",
      std::regex_constants::ECMAScript | std::regex::icase
  );

  std::unordered_map<std::string, std::intptr_t> address_table;

  // Open the file and check for it to be valid.
  std::ifstream address_table_file_stream(table_file_path.data());

  if (!address_table_file_stream) {
    return address_table;
  }

  // Discard the header line, because it's for humans.
  address_table_file_stream.ignore(
      std::numeric_limits<std::streamsize>::max(),
      '\n'
  );

  // Read each line.
  for (std::string line; std::getline(address_table_file_stream, line); ) {
    std::smatch matches;
    if (!std::regex_match(line.cbegin(), line.cend(), matches, kLineRegex)) {
      continue;
    }

    // Pull the column data.
    const std::string& library_name = matches[1];
    const std::string& address_name = matches[2];
    const std::string& locator_type = matches[3];
    const std::string& locator_value = matches[4];

    std::intptr_t resolved_game_address = ResolveAddress(
        library_name,
        address_name,
        locator_type,
        locator_value
    );

    std::string full_address_name = library_name + "_" + address_name;

    address_table.insert_or_assign(
        std::move(full_address_name),
        resolved_game_address
    );
  }

  return address_table;
}

std::unordered_map<std::string, std::intptr_t>
ReadJsonTableFile(
    std::string_view table_file_path
) {
  // Read the address table into JSON.
  nlohmann::json address_table_json;
  if (std::ifstream address_table_file(table_file_path.data());
      address_table_file.good()) {
    address_table_json = nlohmann::json::parse(address_table_file);
  }

  // Parse the JSON into the address table.
  std::unordered_map<std::string, std::intptr_t> address_table;

  std::string_view version_name = GetRunningGameVersionName();
  for (const auto& library_items : address_table_json.items()) {
    const std::string library_name = library_items.key();
    const std::string library_path = library_name + ".dll";
    const GameLibrary& game_library =
        GameLibraryTable::GetInstance().GetGameLibrary(library_path);
    std::intptr_t base_address = game_library.base_address();

    for (const auto& item : library_items.value().items()) {
      std::string game_address_name = item.key();

      // Determine the destination game address.
      LocatorByVersion locator_by_version = item.value();
      Locator locator = locator_by_version.at(version_name.data());

      std::string locator_type = locator.at(kLocatorTypeKey.data());
      std::string locator_value = locator.at(kLocatorValueKey.data());

      std::intptr_t resolved_game_address = ResolveLocatorAndGetAddress(
          base_address,
          locator_type,
          locator_value
      );

      // Determine the full game address name.
      std::string full_address_name = library_name + "_" + game_address_name;

      address_table.insert_or_assign(
          std::move(full_address_name),
          resolved_game_address
      );
    }
  }

  return address_table;
}

} // namespace sgd2mapi
