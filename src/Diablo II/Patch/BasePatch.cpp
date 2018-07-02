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

#include "BasePatch.h"

#include <windows.h>
#include <cstdint>
#include <cstring>

#include "../Pointer.h"

namespace slashgaming::diabloii::patch {

BasePatch::BasePatch(const Pointer& pointer, size_t patch_size) :
        pointer_(pointer), patch_size_(patch_size), old_bytes_(patch_size) {
    // Copy the old bytes of data for later restoring.
    intptr_t address = pointer_.address();
    std::memmove(old_bytes_.data(), reinterpret_cast<const void*>(address),
            patch_size_);
}

BasePatch::~BasePatch() {
    if (!is_patch_applied()) {
        return;
    }

    Remove();
}

void BasePatch::Apply() {
    is_patch_applied_ = true;
}

void BasePatch::Remove() {
    if (!is_patch_applied()) {
        return;
    }

    // Restore the old bytes of data.
    uintptr_t address = pointer().address();
    std::memmove(reinterpret_cast<void*>(address), old_bytes_.data(),
            patch_size_);

    is_patch_applied_ = false;
}

const Pointer& BasePatch::pointer() const {
    return pointer_;
}

size_t BasePatch::patch_size() const {
    return patch_size_;
}

bool BasePatch::is_patch_applied() const {
    return is_patch_applied_;
}

} // namespace slashgaming::diabloii::patch
