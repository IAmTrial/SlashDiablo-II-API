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
 */

#ifndef SGD2MAPI_DIABLOII_CONSTANT_D2CHARACTERCLASS_H_
#define SGD2MAPI_DIABLOII_CONSTANT_D2CHARACTERCLASS_H_

namespace slashgaming::diabloii::constant {

/**
 * The character classes of Diablo II.
 */
enum class D2CharacterClass {
    kAmazon = 0,
    kBarbarian = 1,
    kNecromancer = 2,
    kPaladin = 3,
    kSorceress = 4,

    kAssassin = 5,
    kDruid = 6
};

/**
 * Returns the resolved raw integer value of the constant, based on the running
 * game version and architecture.
 */
int ResolveD2CharacterClassToValue(enum D2CharacterClass character_class);

/**
 * Returns the resolved constant that is associated with the specified integer,
 * based on the running game version and architecture.
 */
enum D2CharacterClass ResolveValueToD2CharacterClass(int raw_value);

} // namespace slashgaming::diabloii::constant

#endif // SGD2MAPI_DIABLOII_CONSTANT_D2CHARACTERCLASS_H_
