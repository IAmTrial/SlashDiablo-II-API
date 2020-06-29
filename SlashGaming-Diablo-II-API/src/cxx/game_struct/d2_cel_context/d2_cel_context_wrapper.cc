/**
 * SlashGaming Diablo II Modding API for C++
 * Copyright (C) 2018-2020  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Modding API for C++.
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
 *  it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
 *  Glide, OpenGL, or Rave wrapper (or modified versions of those
 *  libraries), containing parts not covered by a compatible license, the
 *  licensors of this Program grant you additional permission to convey the
 *  resulting work.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any library (or a modified version of that library) that links
 *  to Diablo II (or a modified version of that game and its libraries),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "../../../../include/cxx/game_struct/d2_cel_context/d2_cel_context_wrapper.hpp"

#include "../../../../include/cxx/game_function/d2cmp/d2cmp_get_cel_from_cel_context.hpp"
#include "../../../../include/cxx/game_function/d2gfx/d2gfx_draw_cel_context.hpp"
#include "../../../../include/cxx/game_struct/d2_cel/d2_cel_view.hpp"
#include "../../../../include/cxx/game_version.hpp"

namespace d2 {

CelContext_Wrapper::CelContext_Wrapper(
    CelContext* cel_context
) noexcept : cel_context_(CreateVariant(cel_context)) {
}

CelContext_Wrapper::CelContext_Wrapper(
    const CelContext_Wrapper& other
) noexcept = default;

CelContext_Wrapper::CelContext_Wrapper(
    CelContext_Wrapper&& other
) noexcept = default;

CelContext_Wrapper::~CelContext_Wrapper() noexcept = default;

CelContext_Wrapper& CelContext_Wrapper::operator=(
    const CelContext_Wrapper& other
) noexcept = default;

CelContext_Wrapper& CelContext_Wrapper::operator=(
    CelContext_Wrapper&& other
) noexcept = default;

CelContext_View CelContext_Wrapper::operator[](
    std::size_t index
) const noexcept {
  CelContext_View view(this->Get());

  return view[index];
}

CelContext_Wrapper CelContext_Wrapper::operator[](
    std::size_t index
) noexcept {
  const auto* const_this = this;

  return const_cast<CelContext*>((*const_this)[index].Get());
}

CelContext_Wrapper::operator CelContext_View() const noexcept {
  return CelContext_View(this->Get());
}

CelContext* CelContext_Wrapper::Get() noexcept {
  const auto* const_this = this;

  return const_cast<CelContext*>(const_this->Get());
}

const CelContext* CelContext_Wrapper::Get() const noexcept {
  return std::visit(
      [](const auto& actual_cel_context) {
        return reinterpret_cast<const CelContext*>(actual_cel_context);
      },
      this->cel_context_
  );
}

void CelContext_Wrapper::Assign(CelContext_View src) {
  std::visit(
      [&src](auto& actual_dest) {
        using Dest_T = decltype(actual_dest);
        using ActualSrc_T = const std::remove_pointer_t<
            std::remove_reference_t<Dest_T>
        >*;

        const auto* actual_src = reinterpret_cast<ActualSrc_T>(src.Get());

        *actual_dest = *actual_src;
      },
      this->cel_context_
  );
}

bool CelContext_Wrapper::DrawFrame(int position_x, int position_y) {
  DrawCelFileFrameOptions frame_options;
  frame_options.color = mapi::Rgba32BitColor();
  frame_options.draw_effect = DrawEffect::kNone;
  frame_options.position_y_behavior = DrawPositionYBehavior::kBottom;

  return this->DrawFrame(
      position_x,
      position_y,
      frame_options
  );
}

bool CelContext_Wrapper::DrawFrame(
    int position_x,
    int position_y,
    const DrawCelFileFrameOptions& frame_options
) {
  Cel_View cel_view(this->GetCel());

  // Adjust the position_x to match the desired option.
  int actual_position_x = position_x;

  switch (frame_options.position_x_behavior) {
    case DrawPositionXBehavior::kLeft: {
      break;
    }

    case DrawPositionXBehavior::kCenter: {
      actual_position_x -= (cel_view.GetWidth() / 2);
      break;
    }

    case DrawPositionXBehavior::kRight: {
      actual_position_x -= cel_view.GetWidth();
      break;
    }
  }

  // Adjust the position_y to match the desired option.
  int actual_position_y = position_y;

  switch (frame_options.position_y_behavior) {
    case DrawPositionYBehavior::kTop: {
      actual_position_y += cel_view.GetHeight();
      break;
    }

    case DrawPositionYBehavior::kCenter: {
      actual_position_y += (cel_view.GetHeight() / 2);
      break;
    }

    case DrawPositionYBehavior::kBottom: {
      break;
    }
  }

  return d2gfx::DrawCelContext(
      this->Get(),
      actual_position_x,
      actual_position_y,
      frame_options.color.ToBgra(),
      frame_options.draw_effect,
      nullptr
  );
}

Cel* CelContext_Wrapper::GetCel() {
  return d2::d2cmp::GetCelFromCelContext(this->Get());
}

CelFile_Wrapper CelContext_Wrapper::GetCelFile() noexcept {
  const auto* const_this = this;

  return const_cast<CelFile*>(const_this->GetCelFile().Get());
}

CelFile_View CelContext_Wrapper::GetCelFile() const noexcept {
  CelContext_View view(*this);

  return view.GetCelFile();
}

void CelContext_Wrapper::SetCelFile(CelFile_Wrapper cel_file) noexcept {
  std::visit(
      [&cel_file](auto& actual_cel_context) {
        using CelContext_T = std::remove_pointer_t<
            std::remove_reference_t<decltype(actual_cel_context)>
        >;
        using CelFile_T = std::remove_pointer_t<
            decltype(CelContext_T::cel_file)
        >;

        actual_cel_context->cel_file =
            reinterpret_cast<CelFile_T*>(cel_file.Get());
      },
      this->cel_context_
  );
}

unsigned int CelContext_Wrapper::GetDirection() const noexcept {
  CelContext_View view(this->Get());

  return view.GetDirection();
}

void CelContext_Wrapper::SetDirection(unsigned int direction) noexcept {
  std::visit(
      [direction](auto& actual_cel_context) {
        actual_cel_context->direction = direction;
      },
      this->cel_context_
  );
}

unsigned int CelContext_Wrapper::GetFrame() const noexcept {
  CelContext_View view(this->Get());

  return view.GetFrame();
}

void CelContext_Wrapper::SetFrame(unsigned int frame) noexcept {
  std::visit(
      [frame](auto& actual_cel_context) {
        actual_cel_context->direction = frame;
      },
      this->cel_context_
  );
}

CelContext_Wrapper::WrapperVariant CelContext_Wrapper::CreateVariant(
    CelContext* cel_context
) {
  GameVersion running_game_version = GetRunningGameVersionId();

  if (running_game_version <= GameVersion::k1_10) {
    return reinterpret_cast<CelContext_1_00*>(cel_context);
  } else if (running_game_version == GameVersion::k1_12A) {
    return reinterpret_cast<CelContext_1_12A*>(cel_context);
  } else /* if (running_game_version >= GameVersion::k1_13ABeta) */ {
    return reinterpret_cast<CelContext_1_13C*>(cel_context);
  }
}

} // namespace d2
