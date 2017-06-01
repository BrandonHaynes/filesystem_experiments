import os
import glob
import shutil

numDirs = 1 # 16 #

fileLocationPrefix = "/home/ubuntu/cache/coaster-"
# fileLocationPostfix = "slow-50-10-50.hevc" # slow-9000-10-50.hevc #


for i in range(numDirs):
    newpath = r'/home/ubuntu/inputs/tiles/50/' + str(i)
    if not os.path.exists(newpath):
        os.makedirs(newpath)
    filesToMove = glob.glob(fileLocationPrefix + str(i) + "-" + "*")
    for file in filesToMove:
        shutil.copy2(file, newpath)
