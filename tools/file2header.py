# file2header.py - Script to convert ASCII files to C resources
#
# Copyright (c) 2022 Thorsten Brehm.

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
 
import sys
import os

DoStrip = False

def convertFile(inFile):
	#print("converting", inFile, "==>", outFile)
	
	f = open(inFile, "r")
	l = f.readlines()
	f.close()
	
	FileName = os.path.basename(inFile)
	FileName = FileName.replace(".", "_")
	FileName = FileName.upper()
	out = ["#define "+FileName+" \\"]
	for e in l:
		if DoStrip:
			e = e.strip()
			if e=="":
				continue
			if e.startswith("//"):
				continue
		else:
			while (e!="")and((e[-1]=="\n")or(e[-1]=="\x0d")):
				e = e[:-1]
		e = e.replace("\\", "\\\\")
		e = e.replace("\"", "\\\"")
		e = "    \"%s\\n\" \\" % (e,)
		out.append(e)
	
	out.append("")
	print("\n".join(out))

def run(args):
	global DoStrip
	
	IsFirst = True
	args = args[1:]
	Ok = False
	while len(args)>0:
		if args[0] == "--strip":
			DoStrip = True
			args = args[1:]
		elif args[0] == "--file":
			inFile = args[1]
			p = inFile.rfind(".")
			if p>-1:
				outFile = inFile[:p]+".h"
			else:
				outFile = inFile+".h"
			if IsFirst:
				print("/*******************************************************")
				print(" * GENERATED FILE")
				print(" *******************************************************/")
			convertFile(inFile)
			args = args[2:]
			Ok = True
		else:
			sys.stderr.write("Unknown parameter: "+args[0]+"\n")
			break
	if not Ok:
		sys.stderr.write("\n"
		                 "Usage: python file2header.py [--strip] (--file <filename>)*\n\n"
		                 "  --strip:           strips trailing whitespace, empty lines from the ASCII sources\n\n"
		                 "  --file <filename>: file name to be processed (parameter may be given multiple\n"
		                 "                     times to convert multiple files)\n\n")

run(sys.argv)

