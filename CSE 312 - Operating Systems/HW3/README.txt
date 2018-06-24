after make command

to run you need to do

./emulator comFile fileSystemFile debugOption

To run P4:
The homework pdf did not want to ask the user for the file name for the p4. So I made it for a specific file name.It's called "numbers.txt". The "filesytem5" contain it. You can test P4 with using "filesystem5.dat" file.

I assume that,
last access time changes according to opening,writing
modification time changes according to writing.
The new kernel calls cycles assumes 0.Because they was not given in the homework pdf.


Time information format:
month/day/year hour:minute:microsecond

The hour can be different from your computer hour.(that was 3 hour back form my computer)Other information will be same (like minute,month,day,year). Hour is format related, not an error.

There are 4096 block and each blocks 256 bytes.

Of course one file can handle several blocks in creating time (if writed more than 255 bytes writed first time) or when appending to the file(if new size will be grather than 256 bytes, we need to allocate next block of the file's to the file but next block may handle by another file. I write a compaction function for this purpose.So I handle this problem.)
filesystem2,filesystem3,filesystem4 and filesystem5 contains 611 bytes file.It holds 3 blocks.


If a new file is created with the existing file name, numbers such as 2 3 4 are appended to the end of the new file to be opened.The user should then open the file with this name. The solution is same with Windows,Linux solution for the problem.


The datas of files can check with p3.