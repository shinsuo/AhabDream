import os, sys, shutil, codecs, xlrd,subprocess,re

newLine = "\n"

def readExcel():
	excelfile = "data.xlsx"
	jsonfile = "config.json"

	workbook = xlrd.open_workbook(excelfile)
	alljson = "{"+newLine
	for sheet in workbook.sheets():
		if sheet.name == "config":
			for row in range(sheet.nrows):
				rowData = sheet.row_values(row)
				alljson += "\""+str(rowData[0]) + "\":" + str(rowData[1])

				if row == sheet.nrows - 1:
					alljson += newLine
				else:
					alljson += ","+newLine
					pass
				pass
			pass
		pass
	pass

	alljson += "}"+newLine

	print(alljson)

	output = open(jsonfile, "wb") #codecs.open(jsonfile, 'w', 'utf-8')
	output.write(alljson)
	output.close()
	
	pass

if __name__ == '__main__':
	reload(sys)
	sys.setdefaultencoding('utf-8')
	readExcel()
	pass
