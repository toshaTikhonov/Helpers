#.rst:
# FindHelpers
# -----------
#
# Find HELPERS
#
# Find HELPERS headers and libraries.
#
# ::
#
#   HELPERS_FOUND          - True if HELPERS found.
#   HELPERS_INCLUDE_DIRS   - Where to find helpers.h.
#   HELPERS_LIBRARIES      - List of libraries when using Helpers.
#   HELPERS_VERSION_STRING - The version of Helpers found.

#=============================================================================
# Copyright 2019 Anton Tikhonov <mail@armshine.net>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation;
# version 2.1 of the License.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU GENERAL PUBLIC LICENSE for more details.
#
# You should have received a copy of the GNU General Public
# License along with this library.	If not, see <http://www.gnu.org/licenses/>.
#=============================================================================

find_package(PkgConfig QUIET)
pkg_check_modules(PC_HELPERS QUIET libHelpers)

find_path(HELPERS_INCLUDE_DIR
        NAMES helpers-cfg.h
        HINTS ${PC_HELPERS_INCLUDEDIR} ${PC_HELPERS_INCLUDE_DIRS})

find_library(HELPERS_LIBRARY
        NAMES Helpers libHelpers
        HINTS ${PC_HELPERS_LIBDIR} ${PC_HELPERS_LIBRARY_DIRS})

set(HELPERS_VERSION_STRING 0.0.0)

if (PC_HELPERS_VERSION)
    set(HELPERS_VERSION_STRING ${PC_HELPERS_VERSION})
elseif (HELPERS_INCLUDE_DIR AND EXISTS "${HELPERS_INCLUDE_DIR}/helpers-cfg.h")
    set(regex_Helpers_version "^#define[ \t]+HELPERS_VERSION[ \t]+([^\"]+).*")
    file(STRINGS "${HELPERS_INCLUDE_DIR}/helpers-cfg.h" Helpers_version REGEX "${regex_Helpers_version}")
    string(REGEX REPLACE "${regex_Helpers_version}" "\\1" HELPERS_VERSION_STRING "${Helpers_version}")
    unset(regex_Helpers_version)
    unset(Helpers_version)
    if (NOT HELPERS_VERSION_STRING)
       set(regex_Helpers_version "^#define[ \t]+HELPERS_VERSION[ \t]+([^\"]+).*")
        file(STRINGS "${HELPERS_INCLUDE_DIR}/helpers-cfg.h" Helpers_version REGEX "${regex_Helpers_version}")
        string(REGEX REPLACE "${regex_Helpers_version}" "\\1" HELPERS_VERSION_STRING "${Helpers_version}")
        unset(regex_Helpers_version)
        unset(Helpers_version)
    endif ()
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Helpers
        REQUIRED_VARS HELPERS_LIBRARY HELPERS_INCLUDE_DIR
        VERSION_VAR HELPERS_VERSION_STRING)

if (HELPERS_FOUND)
    set(HELPERS_LIBRARIES ${HELPERS_LIBRARY})
    set(HELPERS_INCLUDE_DIRS ${HELPERS_INCLUDE_DIR})
endif ()

mark_as_advanced(HELPERS_INCLUDE_DIR HELPERS_LIBRARY)
