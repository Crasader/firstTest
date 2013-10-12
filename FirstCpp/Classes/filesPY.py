import os
import sys

files = ''
pre = '../../Classes/'

def checkFile(fallpath, filepath, filename):
    if os.path.isfile(fallpath):
        if filename[-4:] == '.cpp' or filename[-3:] == '.cc':
            global files
            files = files + pre + filepath + filename + ' \\\n'
    elif os.path.isdir(fallpath):
        filelist = os.listdir(fallpath)
        for cfile in filelist:
            cfff = fallpath + '/' + filepath + cfile
            checkFile(cfff, filepath + filename + '/', cfile)
            

filedir = os.getcwd()
filelist = os.listdir(filedir)
for cppFile in filelist:
    checkFile(os.path.abspath(cppFile), '', cppFile)

    
print files

f = file(os.getcwd() + '/filenames.txt', 'w')
f.write(files)
f.close()
