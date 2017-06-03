import os
import glob
import struct
import time 

filePrefix50 = "/home/ubuntu/inputs/tiles/50/"
filePrefix9000 = "/home/ubuntu/inputs/tiles/9000/"
allFilePrefixes = [filePrefix50, filePrefix9000]
chunkSize = 24010000
mode =  "_withSizes" # "_padded_24M"  #


def time_file_writes():
    for filePrefix in allFilePrefixes:
        print("\n\n" + filePrefix)
        times_for_amalgamated_files = []
        times_for_single_files = []
        for i in range(16):
            total_time = 0
            file_contents = []
            filesToAppend = glob.glob(filePrefix + str(i) + '/*.hevc')
            # print(filesToAppend)
            
            # read files 
            for movie_file in filesToAppend:
                with open(movie_file, "rb") as binary_input_file:
                    file_contents.append(binary_input_file.read())

            # time single files
            for j in range(18):   
                start_time = time.clock()
                with open("singleFile", "wb") as binary_output_file:
                    binary_output_file.write(file_contents[j])
                end_time = time.clock()
                times_for_single_files.append((end_time-start_time))
                        
            # time amalgamation file
            start_time = time.clock()
            with open("concatenatedFile", "wb") as binary_output_file:
                for j in range(18):     
                    binary_output_file.write(file_contents[j])
            end_time = time.clock()
            total_time += (end_time-start_time)
            # print("Time for amalgamated file at timestamp " + str(i) + ": " + str(total_time))
            times_for_amalgamated_files.append(total_time)

        print("Average time for amalgamated files " + \
                str(sum(times_for_amalgamated_files)*1.0/len(times_for_amalgamated_files)))
        print("Average time for single files " + \
                str(sum(times_for_single_files)*1.0/len(times_for_single_files)))


def make_amalgamated_files():
    for filePrefix in allFilePrefixes:
        for i in range(16):
            total_time = 0
            filesToAppend = glob.glob(filePrefix + str(i) + '/*.hevc')
            print(filesToAppend)
            with open(filePrefix + str(i) + "/concatenated" + mode, "wb") as binary_output_file:
                for movie_file in filesToAppend:
                    fileSize = os.path.getsize(movie_file)
                    if ("Sizes" in mode):
                        binary_output_file.write(struct.pack("<L", fileSize))
                    with open(movie_file, "rb") as binary_input_file:
                        fileContents = binary_input_file.read()
                        start_time = time.clock()
                        binary_output_file.write(fileContents)
                        end_time = time.clock()
                        total_time += (end_time-start_time)
                    if ("padded" in mode):
                        len_diff = chunkSize - fileSize
                        if len_diff < 0:
                            print("\n\n\n\n\n\nERROR: FILE SIZE EXCEEDED\n\n\n\n\n\n")
                        binary_output_file.write("\0" * len_diff)


def main():
    time_file_writes()
    # make_amalgamated_files()
    

    
if __name__ == main():
    main()