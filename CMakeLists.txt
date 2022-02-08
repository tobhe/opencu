# Copyright (c) 2022 Tobias Heider <tobhe@openbsd.org>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

cmake_minimum_required(VERSION 3.12)

project(cu)

find_library(bsd NAMES bsd)

add_definitions(-D_GNU_SOURCE)

set(CFLAGS)
list(APPEND CFLAGS
	-O2
	-Wall
	-Wno-pointer-sign
	-Wno-deprecated-declarations
	-Wstrict-prototypes
	-Wmissing-prototypes
	-Wmissing-declarations
	-Wshadow
	-Wpointer-arith
	-Wcast-qual
	-Wsign-compare
	"$<$<CONFIG:DEBUG>:-O0;-g>"
)

add_executable(cu
	command.c
	cu.c
	error.c
	input.c
	xmodem.c
	compat/vis.c
	compat/strtonum.c
)

target_compile_options(cu PRIVATE ${CFLAGS})
target_link_libraries(cu event)
target_include_directories(cu PUBLIC
	compat
)

install(TARGETS cu RUNTIME DESTINATION bin)
set (CMAKE_INSTALL_MANDIR /usr/share/man)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cu.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/)
