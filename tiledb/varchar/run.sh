rm -rf workspace
gcc create.cc -ltiledb -o create && ./create &&
gcc write.cc -ltiledb -o write && time ./write &&
gcc read.cc -ltiledb -o read && time ./read
