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

#ifndef SGD2MAPI_DIABLOII_POINTER_FUNC_D2CLIENTFUNC_H_
#define SGD2MAPI_DIABLOII_POINTER_FUNC_D2CLIENTFUNC_H_

#include <windows.h>
#include <cstdint>

#include "../../Constants.h"
#include "../../Structs.h"

#ifdef SGD2MAPI_DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#elif defined(SGD2MAPI_DLLIMPORT)
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT
#endif

namespace slashgaming::diabloii::func {

extern "C" {
    DLLEXPORT void D2Client_DrawRectFrame(RECT* rect_ptr);
    DLLEXPORT enum constant::D2Difficulty D2Client_GetDifficulty();
    DLLEXPORT struct D2UnitAny* D2Client_GetMercUnit();
    DLLEXPORT int D2Client_GetMouseX();
    DLLEXPORT int D2Client_GetMouseY();
    DLLEXPORT struct D2UnitAny* D2Client_GetPlayerUnit();
    DLLEXPORT void D2Client_SetDifficulty(
            enum constant::D2Difficulty difficulty);
}

} // namespace slashgaming::diabloii::func

#undef DLLEXPORT

#endif // SGD2MAPI_DIABLOII_POINTER_FUNC_D2CLIENTFUNC_H_
