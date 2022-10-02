# Makefile - Script to convert html/js to a C resource header
#
# Copyright (c) 2022 Thorsten Brehm, brehmt (at) gmail.com
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

INDEX_FILE = html/index.html
JS_FILE = html/hamegControl.js
PNG_FILE = html/favicon.png
OUTPUT_FILE = WifiScope/resource.h

TOOL = tools/file2header.py

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(INDEX_FILE) $(JS_FILE) $(PNG_FILE) $(TOOL)
	python3 $(TOOL) --strip --file $(INDEX_FILE) --file $(JS_FILE) --file $(PNG_FILE) > $(OUTPUT_FILE)

