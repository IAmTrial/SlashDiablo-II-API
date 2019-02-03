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

#ifndef SGD2MAPI_GAME_PATCH_GAME_BRANCH_PATCH_H_
#define SGD2MAPI_GAME_PATCH_GAME_BRANCH_PATCH_H_

#include <stdlib.h>

#include "../game_address.h"
#include "game_patch_base.h"

#ifdef __cplusplus
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#endif // __cplusplus

#if defined(SGD2MAPI_DLLEXPORT)
#define DLLEXPORT __declspec(dllexport)
#elif defined(SGD2MAPI_DLLIMPORT)
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
namespace sgd2mapi {

/**
 * The branch types that are used to call an inserted function. A call saves
 * some state defined by the architecture, with the purpose of returning to the
 * calling function. A jump does not save any state information.
 */
enum class BranchType;

/**
 * A patch that replaces the first bytes with a branch to a function, then
 * replaces the rest of the bytes with no-op instructions.
 */
class DLLEXPORT GameBranchPatch
    : public GamePatchBase {
 public:
  /**
   * Creates a new instance of GameBranchPatch.
   */
  template<typename T, typename... Args>
  GameBranchPatch(
      const GameAddress& game_address,
      enum BranchType branch_type,
      T func(Args...),
      std::size_t patch_size
  )
      : GameBranchPatch(
            game_address,
            branch_type,
            reinterpret_cast<std::intptr_t>(func),
            patch_size
        ) {
  }

  /**
   * Creates a new instance of GameBranchPatch.
   */
  template<typename T, typename... Args>
  GameBranchPatch(
      GameAddress&& game_address,
      enum BranchType branch_type,
      T func(Args...),
      std::size_t patch_size
  )
      : GameBranchPatch(
            std::move(game_address),
            branch_type,
            reinterpret_cast<std::intptr_t>(func),
            patch_size
        ) {
  }

  GameBranchPatch(
      const GameBranchPatch&
  );

  GameBranchPatch(
      GameBranchPatch&&
  ) noexcept;

  ~GameBranchPatch(
      void
  ) override;

  GameBranchPatch&
  operator=(
      const GameBranchPatch&
  );

  GameBranchPatch&
  operator=(
      GameBranchPatch&&
  ) noexcept;

  /**
   * Returns the branch opcode used for calling the inserted function.
   */
  enum BranchType
  branch_type(
      void
  ) const noexcept;

  /**
   * Returns the pointer to the inserted function.
   */
  std::intptr_t
  func_ptr(
      void
  ) const noexcept;

 private:
  GameBranchPatch(
      const GameAddress& game_address,
      enum BranchType branch_type,
      std::intptr_t func_ptr,
      std::size_t patch_size
  );

  GameBranchPatch(
      GameAddress&& game_address,
      enum BranchType branch_type,
      std::intptr_t func_ptr,
      std::size_t patch_size
  );

  enum BranchType branch_type_;
  std::intptr_t func_ptr_;
};

} // namespace sgd2mapi
#endif // __cplusplus

/**
 * C Interface
 */

struct SGD2MAPI_GameBranchPatch;

/**
 * The branch types that are used to call an inserted function. A call saves
 * some state defined by the architecture, with the purpose of returning to the
 * calling function. A jump does not save any state information. Disabled if
 * compiling as C++ code.
 *
 */
enum SGD2MAPI_BranchType
#ifdef __cplusplus
{};

enum class sgd2mapi::BranchType
#endif // __cplusplus
{
  kCall,
  kJump,
};

#if !defined(__cplusplus) || defined(SGD2MAPI_DLLEXPORT)

#ifdef __cplusplus
struct SGD2MAPI_GameBranchPatch {
  std::shared_ptr<sgd2mapi::GameBranchPatch> actual_ptr;
};

extern "C" {
#endif // __cplusplus

/**
 * Creates a new GameBranchPatch. The patch buffer is configured by the
 * specified branch type, the function to branch to, and the patch size.
 */
DLLEXPORT struct SGD2MAPI_GameBranchPatch*
SGD2MAPI_GameBranchPatch_Create(
    const struct SGD2MAPI_GameAddress* c_game_address,
    enum SGD2MAPI_BranchType c_branch_type,
    void* func(),
    size_t patch_size
);

/**
 * Creates a new GameBranchPatch. The patch buffer is configured by the
 * specified branch type, the function to branch to, and the patch size.
 */
DLLEXPORT struct SGD2MAPI_GamePatchBase*
SGD2MAPI_GameBranchPatch_CreateAsGamePatchBase(
    const struct SGD2MAPI_GameAddress* c_game_address,
    enum SGD2MAPI_BranchType c_branch_type,
    void* func(),
    size_t patch_size
);

/**
 * Frees the memory used by the specified game patch.
 */
DLLEXPORT void
SGD2MAPI_GameBranchPatch_Destroy(
    struct SGD2MAPI_GameBranchPatch* c_game_branch_patch
);

/**
 * Creates an upcast of the specified game patch to a
 * GamePatchBase.
 */
DLLEXPORT struct SGD2MAPI_GamePatchBase*
SGD2MAPI_GameBranchPatch_UpcastToGamePatchBase(
    struct SGD2MAPI_GameBranchPatch* c_game_branch_patch
);

/**
 * Creates an upcast of the specified game patch to a
 * GamePatchBase and destroys the specified game patch.
 */
DLLEXPORT struct SGD2MAPI_GamePatchBase*
SGD2MAPI_GameBranchPatch_UpcastToGamePatchBaseThenDestroy(
    struct SGD2MAPI_GameBranchPatch* c_game_branch_patch
);

/**
 * Applies the game patch by replacing the bytes at its target address with the
 * bytes stored in its buffer.
 */
DLLEXPORT void
SGD2MAPI_GameBranchPatch_Apply(
    struct SGD2MAPI_GameBranchPatch* c_game_branch_patch
);

/**
 * Removes the effects of the game patch by restoring the original state of the
 * bytes at its target address.
 */
DLLEXPORT void
SGD2MAPI_GameBranchPatch_Remove(
    struct SGD2MAPI_GameBranchPatch* c_game_branch_patch
);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !defined(__cplusplus) || defined(SGD2MAPI_DLLEXPORT)

#undef DLLEXPORT
#endif // SGD2MAPI_GAME_PATCH_GAME_BRANCH_PATCH_H_
