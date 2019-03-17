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

#ifndef SGD2MAPI_C_GAME_PATCH_GAME_BRANCH_PATCH_H_
#define SGD2MAPI_C_GAME_PATCH_GAME_BRANCH_PATCH_H_

#include <stddef.h>

#include "../game_address.h"
#include "../game_patch.h"

#include "../../dllexport_define.inc"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * The branch types that are used to call an inserted function. A call saves
 * some state defined by the architecture, with the purpose of returning to the
 * calling function. A jump does not save any state information.
 */
enum MAPI_BranchType {
  BRANCH_CALL,
  BRANCH_JUMP,
};

/**
 * Initializes a new GameBranchPatch. The patch buffer is configured to use
 * the specified branch type to branch to the specified function. The
 * remaining bytes are filled with no-op instructions.
 */
DLLEXPORT void MAPI_GamePatch_InitGameBranchPatch(
    struct MAPI_GamePatch* game_patch,
    const struct MAPI_GameAddress* game_address,
    int branch_opcode,
    void (*func_ptr)(void),
    size_t patch_size
);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#include "../../dllexport_undefine.inc"
#endif // SGD2MAPI_C_GAME_PATCH_GAME_BRANCH_PATCH_H_
