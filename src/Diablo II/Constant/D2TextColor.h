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

#ifndef SGD2MAPI_DIABLOII_CONSTANT_D2TEXTCOLOR_H_
#define SGD2MAPI_DIABLOII_CONSTANT_D2TEXTCOLOR_H_

namespace slashgaming::diabloii::constant {

/**
 * The different colors used to display text in Diablo II.
 */
enum class D2TextColors {
    kBlack = 0,
    kBlue = 1,
    kCorrupted = 2,
    kVomit = kCorrupted,
    kDarkGold = 3,
    kGold = 4,
    kDarkGreen = 5,
    kDarkerGreen = 6,
    kLightGreen = 7,
    kDarkGrey = 8,
    kLightGrey = 9,
    kMetallic = 10,
    kOrange = 11,
    kPurple = 12,
    kLightRed = 13,
    kDarkRed = 14,
    kBrightWhite = 15,
    kWhite = 16,
    kYellow = 17,
};

/**
 * A wrapper class to represent the D2TextColor constant in a version and
 * architecture agnostic way.
 */
class ExD2TextColor {
public:
    /**
     * Creates an instance of ExD2TextColor, resolving the value of the constant
     * to an integer based on the running game version and architecture.
     */
    explicit ExD2TextColor(enum D2TextColors text_color);

    explicit ExD2TextColor(const ExD2TextColor& base_constant) = default;
    explicit ExD2TextColor(ExD2TextColor&& base_constant) = default;

    ExD2TextColor& operator=(const ExD2TextColor& rhs) = default;
    ExD2TextColor& operator=(ExD2TextColor&& rhs) = default;

    /**
     * Returns the resolved value that corresponds to this instance of the
     * constant.
     */
    int value() const;

    /**
     * Returns the value of the constant that corresponds to this instance of
     * the constant. The underlying value of returned does not necessarily
     * correspond to that used in the game. Use value() for that purpose.
     */
    enum D2TextColors text_color() const;

private:
    enum D2TextColors text_color_;
    int value_;

    static int ResolveValue(enum D2TextColors text_color);
};

} // namespace slashgaming::diabloii::constant

#endif // SGD2MAPI_DIABLOII_CONSTANT_D2TEXTCOLOR_H_
