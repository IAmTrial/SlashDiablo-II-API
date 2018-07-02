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
 *  If you modify this Program, or any covered work, by linking or combining it
 *  with Diablo II (or a modified version of that library), containing parts
 *  covered by the terms of Blizzard End User License Agreement, the licensors
 *  of this Program grant you additional permission to convey the resulting
 *  work.
 *
 *  If you modify this Program, or any covered work, by declaring a custom
 *  version of an existing Diablo II data structure with members ordered
 *  differently from any official version of the game, then such declarations
 *  are exempt from the terms of GNU Affero General Public License version 3
 *  section 6.
 */

#if defined(__i386__) || defined(_M_IX86) || defined(_X86_)

#ifndef SGD2MAPI_DIABLOII_IA_32_POINTER_FUNC_HELPER_D2CLIENTFUNCHELPER_H_INCLUDE_
#error This file should only be included by the API implementation.
#endif // SGD2MAPI_DIABLOII_IA_32_POINTER_FUNC_D2CLIENTFUNCHELPER_H_INCLUDE_

#ifndef SGD2MAPI_DIABLOII_IA_32_POINTER_FUNC_HELPER_D2CLIENTFUNCHELPER_H_
#define SGD2MAPI_DIABLOII_IA_32_POINTER_FUNC_HELPER_D2CLIENTFUNCHELPER_H_

#include <cstdint>
#include <windows.h>

#include "../../../../GameLibrary.h"
#include "../../../../Pointer.h"
#include "../../../../Structs.h"
#include "../../../../Version.h"

namespace slashgaming::diabloii::func {

void D2Client_Unknown_001_1_11();

void __fastcall D2Client_DrawRectFrame_1_00(const RECT* rect_ptr);
void __stdcall D2Client_DrawRectFrame_1_11(const RECT* rect_ptr);

int8_t D2Client_GetDifficulty_1_00();
int D2Client_GetMouseX_1_00();
int D2Client_GetMouseY_1_00();
struct D2UnitAny* D2Client_GetPlayerUnit_1_00();

void __fastcall D2Client_SetDifficulty_1_00(int8_t raw_value);

} // namespace slashgaming::diabloii::func

#endif // SGD2MAPI_DIABLOII_IA_32_POINTER_FUNC_D2CLIENTFUNCHELPER_H_
#endif // defined(__i386__) || defined(_M_IX86) || defined(_X86_)
