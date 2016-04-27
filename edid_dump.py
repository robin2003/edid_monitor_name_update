#!/usr/bin/python

import sys
import os
import struct

class CEDIDDump(object):
	""" dump edid bin
		author: xxpyb@126.com
		date  : 2016.4.27
	"""
	def __init__(self):
		super(CEDIDDump, self).__init__()

	def set_file_name(self, fileName):
		print fileName
		self.fileName = fileName

	def format_block(self, blockIdx, item_array):
		print "format block %d start" % blockIdx
		print "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"
		print "       --------------------Block %d--------------------" % blockIdx

		for row in range(0, 8):
			print "  %d0| " % row,
			for column in range (0, 16):
				print "%-2x" % item_array[row*16+column],
			print ""

	def do_dump(self):
		item_array = self.read_file(128)
		if self.check_edid_valid(item_array[:8]) != True:
			print "not vaild edid"
			pass

		self.format_block(0, item_array)
		item_array = self.read_file(128)
		self.format_block(1, item_array)

	def dump(self):
		self.open_file()
		self.do_dump()
		self.close_file()

	def open_file(self):
		self.file_handle = open(self.fileName, 'rb')

	def read_file(self, len):
		item_array = []
		for i in range(0, len):
			item_array.append(struct.unpack("B",self.file_handle.read(1))[0])

		return item_array

	def close_file(self):
		self.file_handle.close();

	def check_edid_valid(self, item_array):
		if len(item_array) != 8:
			print "invalid edid header, return!"
			return False

		if 0 == item_array[0] and 0 == item_array[7]:
			print "invalid magic code"
			return False

		for item in item_array[1:7]:
			if hex(item) != 0xFF:
				print "invalid magic code"
				return False

		return True

if __name__ == "__main__":
	if 0 == len(sys.argv):
		print "no param! usage: edid_dump.py fileName"
		pass

	edidDump = CEDIDDump()
	for fileName in sys.argv[1:]:
		edidDump.set_file_name(fileName)
		edidDump.dump()
