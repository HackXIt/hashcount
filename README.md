# Compilation

This project contains a makefile which automatically compiles the necessary files.
Follow these steps to compile the project:

```bash
cd project_hashcount
mkdir build
make hashcount
```

# Execution

# Completed Tasks

| emoji                 | meaning           |
| -------------         |:-------------:    |
| :heavy_check_mark:    | erfüllt           |
| :o:                   | teilweise erfüllt |
| :x:                   | nicht erfüllt     |

:heavy_check_mark: **Main Task "hashcount" (50 points)**
<details>
<summary> Task-details </summary>

  * Open a text file and read the text row by row.
  * Separate words by these characters:
    * Space ( )
    * Dot (.)
    * new line (\n)
  * Store the values in a hashtable using dynamic linked lists.
  * Use the sum of character values as value to be hashed. E.g. Cat = (67+97+116) % 23
  * Words shall be stored in dynamically allocated memory
  * Select a good spreading hash value
  * Print out the hash in a readable way. E.g. max 10 words per row.
</details>
<br>

:heavy_check_mark: **Task "Word-occurence + additional seperators" (15 points)**
<details>
<summary> Task-details </summary>

  * The occurrence of words shall be counted instead of multiple entries in the list. (see example output)
  * Add additional word separators:
  ** semicolon (;)
  ** colon (:)
  ** comma (,)
  ** question mark (?)
  ** tab (\t)
</details>
<br>

:heavy_check_mark: **Task "Alphabetical Order" (15 points)**
<details>
<summary> Task-details </summary>

  * The lists shall always retain alphabetic order.
</details>
<br>

:o: **Task "User-Selection: Remove" (15 points)**
<details>
<summary> Task-details </summary>

  * Give the user a choice to select one bucket to output separately.
Print out the entries in the Bucket.
  * Let the user select one or more buckets and remove all words from the text which do not match to these selected buckets and write it to a new text file.  
</details>
<br>

:heavy_check_mark: **Task "User-Selection: Censoring" (15 points)**
<details>
<summary> Task-details </summary>

  * Let the user select one or more buckets and censor all words from the text which match to these selected buckets and write it to a new text file.  
  * All word separators shall be copied to the new file in the correct places.
</details>
<br>
  
:x: **Task "binary hash-table" (15 points)**
<details>
<summary> Task-details </summary>

  * Store the hash in a **binary** file
  * Read and populate the hash from a file and append/count new words into it when the user wants to do this.
</details>
<br>

:heavy_check_mark: **Task "getopt() argument-handling" (15 points)**
<details>
<summary> Task-details </summary>

  * The program arguments are handled by `getopt(3)`.
</details>
<br>