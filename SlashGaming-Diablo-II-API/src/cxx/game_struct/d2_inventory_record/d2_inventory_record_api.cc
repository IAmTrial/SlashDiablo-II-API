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

#include "../../../../include/cxx/game_struct/d2_inventory_record/d2_inventory_record_api.hpp"

#include <algorithm>

#include "../../../../include/cxx/game_struct/d2_equipment_layout/d2_equipment_layout_wrapper.hpp"
#include "../../../../include/cxx/game_struct/d2_grid_layout/d2_grid_layout_wrapper.hpp"
#include "../../../../include/cxx/game_struct/d2_positional_rectangle/d2_positional_rectangle_wrapper.hpp"
#include "../../../../include/cxx/game_version.hpp"

namespace d2 {
namespace {

template <typename InventoryRecord_T>
static std::unique_ptr<InventoryRecord_T> CreatePtr(
    const PositionalRectangle* position,
    const GridLayout* grid_layout,
    const EquipmentLayout* equipment_slots
) {
  using PositionalRectangle_T =
      std::remove_pointer_t<decltype(InventoryRecord_T::position)>;
  using GridLayout_T =
      std::remove_pointer_t<decltype(InventoryRecord_T::grid_layout)>;
  using EquipmentLayout_T =
      std::remove_extent_t<decltype(InventoryRecord_T::equipment_slots)>;

  constexpr std::size_t kNumEquipmentSlots =
      sizeof(InventoryRecord_T::equipment_slots)
          / sizeof(InventoryRecord_T::equipment_slots[0]);

  const PositionalRectangle_T* actual_src_positional_rectangle =
      reinterpret_cast<const PositionalRectangle_T*>(position);
  const GridLayout_T* actual_src_grid_layout =
      reinterpret_cast<const GridLayout_T*>(grid_layout);
  const EquipmentLayout_T* actual_src_equipment_slots =
      reinterpret_cast<const EquipmentLayout_T*>(equipment_slots);

  std::unique_ptr inventory_record = std::make_unique<InventoryRecord_T>();

  inventory_record->position = *actual_src_positional_rectangle;
  inventory_record->grid_layout = *actual_src_grid_layout;

  std::copy_n(
      actual_src_equipment_slots,
      sizeof(inventory_record->equipment_slots)
          / sizeof(inventory_record->equipment_slots[0]),
      inventory_record->equipment_slots
  );

  return inventory_record;
}

} // namespace

InventoryRecord_Api::InventoryRecord_Api(
    PositionalRectangle_View position,
    GridLayout_View grid_layout,
    EquipmentLayout_View equipment_slots
) : inventory_record_(
        CreateVariant(
            position.Get(),
            grid_layout.Get(),
            equipment_slots.Get()
        )
    ) {
}

InventoryRecord_Api::InventoryRecord_Api(
    const InventoryRecord_Api& other
) : InventoryRecord_Api(
        other.GetPosition(),
        other.GetGridLayout(),
        other.GetEquipmentSlots()
    ) {
}

InventoryRecord_Api::InventoryRecord_Api(
    InventoryRecord_Api&& other
) noexcept = default;

InventoryRecord_Api::~InventoryRecord_Api() = default;

InventoryRecord_Api& InventoryRecord_Api::operator=(
    const InventoryRecord_Api& other
) {
  *this = InventoryRecord_Api(
      other.GetPosition(),
      other.GetGridLayout(),
      other.GetEquipmentSlots()
  );

  return *this;
}

InventoryRecord_Api& InventoryRecord_Api::operator=(
    InventoryRecord_Api&& other
) noexcept = default;

InventoryRecord_Api::operator InventoryRecord_View() const noexcept {
  return InventoryRecord_View(this->Get());
}

InventoryRecord_Api::operator InventoryRecord_Wrapper() noexcept {
  return InventoryRecord_Wrapper(this->Get());
}

InventoryRecord* InventoryRecord_Api::Get() noexcept {
  const auto* const_this = this;

  return const_cast<InventoryRecord*>(const_this->Get());
}

const InventoryRecord* InventoryRecord_Api::Get() const noexcept {
  auto& actual_inventory_record =
      std::get<unique_ptr_1_00>(this->inventory_record_);

  return reinterpret_cast<const InventoryRecord*>(actual_inventory_record.get());
}

PositionalRectangle* InventoryRecord_Api::GetPosition() noexcept {
  InventoryRecord_Wrapper wrapper(this->Get());

  return wrapper.GetPosition();
}

const PositionalRectangle* InventoryRecord_Api::GetPosition() const noexcept {
  InventoryRecord_View view(this->Get());

  return view.GetPosition();
}

GridLayout* InventoryRecord_Api::GetGridLayout() noexcept {
  InventoryRecord_Wrapper wrapper(this->Get());

  return wrapper.GetGridLayout();
}

const GridLayout* InventoryRecord_Api::GetGridLayout() const noexcept {
  InventoryRecord_View view(this->Get());

  return view.GetGridLayout();
}

EquipmentLayout* InventoryRecord_Api::GetEquipmentSlots() noexcept {
  InventoryRecord_Wrapper wrapper(this->Get());

  return wrapper.GetEquipmentSlots();
}

const EquipmentLayout*
InventoryRecord_Api::GetEquipmentSlots() const noexcept {
  InventoryRecord_View view(this->Get());

  return view.GetEquipmentSlots();
}

InventoryRecord_Api::ptr_variant InventoryRecord_Api::CreateVariant(
    const PositionalRectangle* position,
    const GridLayout* grid_layout,
    const EquipmentLayout* equipment_slots
) {
  return CreatePtr<InventoryRecord_1_00>(
      position,
      grid_layout,
      equipment_slots
  );
}

} // namespace d2
