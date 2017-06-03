import os
import struct


bitrates = [50, 9000]

with open('data.bin', 'wb') as out:
  for bitrate in bitrates:
    for tile in xrange(18):
        for time in xrange(16):            
            filename = '/home/ubuntu/inputs/tiles/{}/{}/{}.hevc'.format(bitrate, time, tile)
            with open(filename, 'rb') as input:
                size = os.path.getsize(filename)
                out.write(struct.pack("<L", size))
                out.write(input.read())
