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

#include "D2ClientFunc.h"

#include <cstdint>
#include <unordered_map>

#include "../GameLibrary.h"
#include "../Offset.h"
#include "../Version.h"

namespace slashgaming::diabloii::func {

// D2Client_ExitGame() Start
namespace {

void D2Client_Unknown_001_Lod_1_11();

extern "C" {
    void __stdcall D2Client_Unknown_001_Lod_1_11_Stub(uintptr_t func_ptr);
}

} // namespace

void D2Client_Unknown_001() {
    D2Client_Unknown_001_Lod_1_11();
}

namespace {

void D2Client_Unknown_001_Lod_1_11() {
    static const Offset offset(GameLibraries::kD2Client, {
        { GameVersion::kLod1_11, 0x875B0 },
        { GameVersion::kLod1_12, 0x7AB00 },
        { GameVersion::kLod1_13C, 0x42850 },
        { GameVersion::kLod1_13D, 0x43870 }
    });

    uintptr_t func_ptr = offset.CalculateAddress();
    D2Client_Unknown_001_Lod_1_11_Stub(func_ptr);
}

} // namespace
// D2Client_ExitGame() End

} // namespace slashgaming::diabloii::func
