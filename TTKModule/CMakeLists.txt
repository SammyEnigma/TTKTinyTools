# ***************************************************************************
# * This file is part of the TTK Tiny Tools project
# * Copyright (C) 2015 - 2025 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU Lesser General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU Lesser General Public License for more details.
#
# * You should have received a copy of the GNU Lesser General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# ***************************************************************************

cmake_minimum_required(VERSION 3.0.0)

if(WIN32)
  set(MODULE_RC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/TTKCore.rc)
endif()

set(QT_LINK_LIBS TTKLibrary TTKUi TTKThirdParty)

add_subdirectory(TTKImage)
add_subdirectory(TTKNetwork)
add_subdirectory(TTKText)
add_subdirectory(TTKTools)
