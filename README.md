# Benchmarking Array-Based Database Systems
> I'm not sure we actually want that as our title?  Doesn't even mention the file system

by Brandon Haynes and Jessica Schroeder

Recent advances in virtual reality (VR) 

Recent interest in virtual reality (VR) applications, particularly those featuring spherical panoramic VR videos (a.k.a. *360◦ videos*), has produced a need for rapid data streaming and storage at volumes far exceeding 2D videos.  Supporting such high volumes of data requires maximum efficiency to provide the user with a seamless portrayal of 

In this article, we compare data storage and retrieval using SciDB, TileDB, and the file system to determine which system allows for the fastest storage and retrieval of video segments of myriad encodings and segmentations.



## Video Data
Video data is 
We need to store the video encoded because the size of the unencoded video is up to XX% larger than the unencoded form.

## Systems Overview 
We investigated data storage and retrieval on the file system, as well as two array-based database management systems: [SciDB](http://www.paradigm4.com/try_scidb/) and [TileDB](http://istc-bigdata.org/tiledb/).  We chose to focus on array-based database systems, as they allow easy storage and retrieval of particular dimensions and ranges.  Their query languages are also well-suited to the kinds of queries needed to process video data for VR applications.

### File System
By far the easiest system to use to store and retrieve video data is the file system.  Reading and writing binary files is relatively easy using simple C scripts, so if the file system had been comparable to the database systems, it would have been the clear choice in terms of ease of use.

###SciDB
SciDB was the first array-based database management system.  In their [paper](http://doi.org/10.1007/978-3-642-22351-8_1), Stonebreaker et al. describe their main motivation for SciDB as designing a system for the data management needs of scientists.  Specifically, many scientists (especially those working with astronomy or genetics data) often have multiple petabytes of data they need to store and process.  They also need to be able to perform complex analytics of those data, which requires open-sourced data so they can add any necessary missing features.

SciDB employs a shared-nothing architecture that consists of a coordinator node and worker nodes.  Chunks of data are automatically distributed across worker nodes.  The system can be queried using 'AFL', their array functional language.  These features, which were developed to support the large amount of array-based data that scientists often work with, are also useful for managing 360◦ video data.

###TileDB 
TileDB is a new array-based database management system that is currently used by the Intel Health and Life Sciences Group to process genomics data.  Papadopoulos et al. developed TileDB to be optimized for both dense and sparse arrays.  It focuses on super fast storage and retrieval of array-based data.  In their [paper](https://doi.org/10.14778/3025111.3025117), they compare the performance of loading and updating data in TileDB to that of SciDB, and conclude that TileDB is faster for both dense and sparse arrays.


##Experiments
To compare the performance of all three of our systems, we wrote scripts to read from and write to the file system and TileDB (in C) SciDB (in AFL).  The experiments we performed were: 

1. Storage and retrieval of videos for various temporal segmentation sizes
2. Storage and retrieval of tiles for various temporal and spatial segmentation sizes
3. Retrieval of all tiles corresponding to a specific video at a single timestamp 
4. Retrieval of all tiles corresponding to a specific video between two timestamps 
5. Streaming of all tiles corresponding to a specific video, ordered by coordinate and time

## Results 
TileDB was fastest for all experiments.

###Experiment 1:
![Storage and retrieval of videos for various temporal segmentation sizes](plots/examplegraph.jpeg)

###Experiment 2:
![Storage and retrieval of tiles for various temporal and spatial segmentation sizes](plots/examplegraph.jpeg)

###Experiment 3:
![Retrieval of all tiles corresponding to a specific video at a single timestamp ](plots/examplegraph.jpeg)

###Experiment 4:
![Retrieval of all tiles corresponding to a specific video between two timestamps ](plots/examplegraph.jpeg)

###Experiment 5:
![Streaming of all tiles corresponding to a specific video, ordered by coordinate and time](plots/examplegraph.jpeg)

## Conclusions 




