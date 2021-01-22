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

This project at the moment only has one execution mode.

An interactive mode is planned for the future.

<!-- ### Interactive-Mode

Start the program with `hashcount -i` and work through the user-interactions to the desired output.
Please keep in mind that all other arguments are ignored when using this mode. -->

### Generic CLI-Mode

Before you start, read the help-message by executing the program with `hashcount -h`.
This will output the following message:
```
./build/hashcount [OPTIONS]... [FILE.txt]...
Creates a hash-table, based on the words from the supplied file.
The words are seperated by: " .;:,?\t"

---- ARGUMENTS: --------------------
[FILE.txt]               text file to be parsed by the program for the hash-table.
---- OPTIONS:   --------------------
         -h              prints this help text.  -b [FILE.bin]   binary file that will be parsed and appended into if the user wants this. (not implemented yet)
         -n [FILE.bin]   New binary file to be created and filled with the hashtable. (not implemented yet)
         -o [FILE.txt]   name of the output file, to which the censor/remove changes will be written.
         -c [number]     censor the words in Bucket[num] from the input-file and write result to the output-file.
                        (Requires option '-o')
         -k [number]     keep the words in Bucket[num] from the input-file and remove all other words. Write result to the output-file. (not implemented yet)
                        (Requires option '-o')
         -p [number]     only print the given bucket-number instead of the whole table.
         -i              runs the program in interactive-mode, requiring user-input for the program to run. (not implemented yet)
(This will ignore all other options & parameters)
```

**The program requires an input file to create the hashtable.**

If no additional arguments are given, then the hashtable of the given input-file will be printed on the terminal:

<details>
  <summary> Hashcount print table </summary>

```
./build/hashcount sample.txt 
Bucket[0]: a(11), absolute, contemporary, delights, retaliation, setpieces, triumph, water
Bucket[1]: amusing, company, grossout, image, its(2), Ormond(3), part, periodical, Vincent(3), writer, you(2)
Bucket[2]: embodiment, essential, Inevitably, other(2), properly, reference, remains, Saw
Bucket[3]: being, buzz, creating, Needless, plot, serve, stating
Bucket[4]: film(2), further(2), life, mental, to(6)
Bucket[5]: lot, madness, off
Bucket[6]: besieged, just(2), opinion, solo, time(2), timefiller, victims
Bucket[7]: acts, could, joyous
Bucket[8]: because, depicts, first(2), horror(5), show(2), state, well
Bucket[9]: Like, most(2), once, simply, team, tormented(2), vile
Bucket[10]: descends, fear, interesting, starts
Bucket[11]: character(2), he, mesmerizing, now
Bucket[12]: acting, all, means, nose, point, saw, that(3), The(7)
Bucket[13]: also(3), period
Bucket[14]: and(18), Don(3), in(8), is(6), it(2), previous(2), Ross, turns, Wax
Bucket[15]: Girl, handful, must(2), pity, simultaneously, sleazy, starting
Bucket[16]: another, indescribably, Magician(3), Never, protagonist, trick(3)
Bucket[17]: authors, gradually, humble, place
Bucket[18]: are, crime(2), inventions, programs
Bucket[19]: although, House, like, penned, ransacked, starred
Bucket[20]: cares, fate, material, out(2), predecessor!, relentless, yoyo
Bucket[21]: begins, effects, events, every, magic, remain, what, Wilbur
Bucket[22]: about, butchers, career, employer, exactly, from(2), macabre, moments, own, the(22), thoroughly, towards
Bucket[23]: Basically, delightful, double, get, many, offers, unpretentious, very
Bucket[24]: 3D(2), around, behold, but(3), enormously, landlady, still, support, them, they, was, way(2), year
Bucket[25]: rampage, thought
Bucket[26]: end, greatest, grotesque, my, property, recreates, ruined, were
Bucket[27]: brilliant, Gallicos(4), Mad(3), master, promising, rightful
Bucket[28]: Crane, fountains, Guignol, plans, such
Bucket[29]: Alice, no, released
Bucket[30]: era, for(2), him(2), his(6), hit, obviously
Bucket[31]: against, famous, view, who(4), without
Bucket[32]: actor(2), element, have, of(14), on, realize
Bucket[33]: abruptly, accomplish, an(3), as(9), at, fingerprints, murderous, performances, seriously, soul, when(2)
Bucket[34]: death, entitled, merely, near, wronged, yet(2), You(2)
Bucket[35]: 50s(2), disguises, exhibit, genius, genuine, history, suggestive, take
Bucket[36]: before, Buzz, by(2), change, even(3), ever(2), fun, legendary, novelist, sheer, this(2), with(3)
Bucket[37]: down, genre, gimmicks, illusionist, leading, man, movie(3), Price(3), sadistically, wife, winning
Bucket[38]: beloved, Gallico(5), goofy, hype, perform, rival, same(2), stage, used
Bucket[39]: exact
Bucket[40]: beginning, fantastically, Grand, improbably, those, vengeance
Bucket[41]: appears, evidence, player, Rinaldi, snaps, sublime, thrills, twists, watch
Bucket[42]: contract, into, nearly, shoves, whole
```
</details>
<br>

It's also possible to only output a specific bucket:

<details>
  <summary> Hashcount Print selection </summary>

```
./build/hashcount sample.txt -p 24
Printing selection...
Bucket[24]: 3D(2), around, behold, but(3), enormously, landlady, still, support, them, they, was, way(2), year
```
</details>
<br>

In order to use the buckets to censor words from an input file, it is required to provide an output file where the changes will be written to.

<details>
  <summary> Hashcount Censor words </summary>

```
> ./build/hashcount sample.txt -c 24 -o censored.txt
Censoring all words, contained in...
Bucket[24]: 3D(2), around, behold, but(3), enormously, landlady, still, support, them, they, was, way(2), year
12 occurences of 13 Bucket-words were censored in censored.txt
Success!
> cat censored.txt 
Basically the exact same movie as House of Wax Vincent Prices first genuine
horror hit released the previous **** *** seriously who cares because The
Mad Magician offers just as many sheer thrills delightful period setpieces
joyous ** effects sublime acting performances and macabre horror gimmicks
as its predecessor! Never change a winning team is exactly what writer Crane
Wilbur must have thought when he penned down Prices character Don Gallico
another tormented soul besieged by fate and out for vengeance against those
who wronged him. Don Gallico is about to perform his very first own
illusionist show as Gallico the Great and plans to exhibit the greatest magic
trick in history entitled The Girl and the Buzz Saw. Gallicos promising
solo career is abruptly ruined before it even begins when his previous
employer Ross Ormond appears on stage and shoves a contract under his nose
stating that all of Gallicos inventions are the rightful property of the
company. The sleazy and relentless Ormond who by the *** also ransacked
Gallicos once beloved wife takes off with the buzz saw trick and programs
it in the show of Gallicos rival The Great Rinaldi.
Inevitably Gallico snaps and sadistically butchers Ormond *** also
being a master of creating disguises recreates his victims image and
even starts leading a double life. The Mad Magician is an amusing and
thoroughly unpretentious 50s horror movie in Grand Guignol style with a
whole lot of improbably plot twists  the ******** turns out a brilliant
crime novelist?  and a handful of fantastically grotesque grossout moments
although **** obviously remain suggestive for most part . The ** delights
near the beginning of the film like a yoyo player and a goofy trick with
water fountains merely just serve as timefiller and contemporary 50s hype
but its ***** fun to watch even now and without the means to properly behold
them. The Mad Magician is also interesting from a periodical setting point
of view as the events take place ****** the time fingerprints were starting
to get used as evidence material and the character of Alice Prentiss is an
obvious reference towards famous crime authors of that era. Needless to state
that Vincent Price remains the absolute most essential element of triumph
in this film as well as from nearly every other horror movie this legendary
man ever starred in. Like no other actor could ever accomplish Price
depicts the tormented protagonist who gradually descends further and further
into mental madness in such an indescribably mesmerizing way. You pity Don
Gallico yet at the same time you fear him enormously. You ******* his vile
acts of retaliation and yet simultaneously you realize his murderous rampage
must end in death. Vincent Price simply *** a genius actor and in my
humble opinion the embodiment of the horror genre.
```
</details>


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

  * Give the user a choice to select one bucket to output separately. :white_check_mark:
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