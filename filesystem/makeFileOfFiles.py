import os
import glob
import struct

filePrefix50 = "/home/ubuntu/inputs/tiles/50/"
filePrefix9000 = "/home/ubuntu/inputs/tiles/9000/"
allFilePrefixes = [filePrefix50, filePrefix9000]
chunkSize = 24010000
mode = "_padded_24M"  # "_withSizes" # 

def main():
    for filePrefix in allFilePrefixes:
        for i in range(16):
            filesToAppend = glob.glob(filePrefix + str(i) + '/*.hevc')
            print(filesToAppend)
            with open(filePrefix + str(i) + "/concatenated" + mode, "wb") as binary_output_file:
                for movie_file in filesToAppend:
                    fileSize = os.path.getsize(movie_file)
                    if ("Sizes" in mode):
                        binary_output_file.write(struct.pack("<L", fileSize))
                    with open(movie_file, "rb") as binary_input_file:
                        binary_output_file.write(binary_input_file.read())
                    if ("padded" in mode):
                        len_diff = chunkSize - fileSize
                        if len_diff < 0:
                            print("\n\n\n\n\n\nERROR: FILE SIZE EXCEEDED\n\n\n\n\n\n")
                        binary_output_file.write("\0" * len_diff)
    
if __name__ == main():
    main()