#!/usr/bin/python

import sys
import os
import struct

class CEDIDDump(object):
	""" format edid bin
		read bin file example
		author: xxpyb@126.com
		date  : 2016.4.27
	"""
	def __init__(self, fileName):
		print fileName
		super(CEDIDDump, self).__init__()
		self.fileName = fileName

	def format_block(self, blockCnt, bin_array):
		print "format block %d start" % blockCnt
		print "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"
		print "       --------------------Block %d--------------------" % blockCnt

		for row in range(0, 8):
			print "  %d0| " % row,
			for colum in range (0, 16):
				print "%-2x" % bin_array[row*16+colum],
			print ""

	def do_format(self):
		bin_array = self.read_file(128)
		self.format_block(0, bin_array)
		bin_array = self.read_file(128)
		self.format_block(1, bin_array)

	def format(self):
		self.open_file()
		self.do_format()
		self.close_file()

	def open_file(self):
		self.file_handle = open(self.fileName, 'rb')

	def read_file(self, len):
		bin_array = []
		for i in range(0, len):
			bin_array.append(struct.unpack("B",self.file_handle.read(1))[0])

		return bin_array

	def close_file(self):
		self.file_handle.close();


if __name__ == "__main__":
	if 0 == len(sys.argv):
		print "no param! usage: edid_dump.py fileName"
		pass

	for fileName in sys.argv[1:]:
		edidFormat = CEDIDDump(fileName)
		edidFormat.format()
