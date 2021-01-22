# Compilation

This project contains a makefile which automatically compiles the necessary files.
Copy the steps below into your terminal to compile the project:

```bash
cd project_hashcount
mkdir build # if it doesn't exist already
make hashcount
chmod +x ./build/hashcount
```

# Execution

This project has multiple execution modes.

### Interactive-Mode

Start the program with `hashcount -i` and work through the user-interactions to the desired output.
Please keep in mind that all other arguments are ignored when using this mode.

### Generic CLI-Mode

Before you start, read the help-message by executing the program with `hashcount -h`.
This will output the following message:
```
./hashcount [OPTIONS]... [FILE]...
Creates a hash-table, based on the words from the supplied file.
The words are seperated by: " .;:,?\t"

---- ARGUMENTS: --------------------
[FILE]           text file to be parsed by the program for the hash-table.
---- OPTIONS:   --------------------
         -h              prints this help text.  -b [FILENAME]   binary file that will be parsed to generate the table.
         -o [FILENAME]   name of the binary file, in which the hash-table will be stored.
         -i              runs the program in interactive-mode, requiring user-input for the program to run.
```

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