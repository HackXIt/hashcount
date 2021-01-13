# TODO 
* Split hash.c into more readable & single-purpose functions (DONE)
* Move all list-operations (e.g. Bucket-Stuff) to list-utils (DONE)
* Test all program-operations in hashcount.c (DONE)
* Add alphabetical sorting to list-utils.c (DONE)
* Implement getopt() argument-handling in hashcount.c (DONE)
* Fix last 1% of memcheck-losses (currently 120 Bytes are "possibly lost") (DONE)
> The loss came from my missing allocation/deallocation for the line-buffer. Getline reallocates that buffer if necessary, thus I had a memory leak, but it was not appearant in my code, because I didn't allocate it originally.
* Write common-file operations in file-utils
* Write to output-file
* Add option to censor words in output-file
* Add option to remove words in output-file
* Add delimiter-memory for words, to output word-seperators @ correct places.
* Formulate binary-structure. Using binary format might require different approach to read data from input.
* Add Write-to-Binary functionality
* Add Read-from-Binary functionality
* Add continous binary appending/population functionality
* Write doxygen for ALL functions
