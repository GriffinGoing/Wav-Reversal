#! /bin/bash

echo '***RUNNING WAV TESTS***'
echo 'FIRST REVERSE:'
./a.out mysterySound.wav oneRev.wav
echo 'SECOND REVERSE:'
./a.out oneRev.wav twoRev.wav
echo'MD5 SUMS:'
md5sum mysterySound.wav && md5sum twoRev.wav && md5sum oneRev.wav
echo 'HEXDUMPING TO FILES...'
hexdump mysterySound.wav > origin.txt
hexdump oneRev.wav > oneRev.txt
hexdump twoRev.wav > twoRev.txt
echo 'CHECKING FOR DIFFERENCES'
diff origin.txt twoRev.txt
sort origin.txt twoRev.txt | uniq -uc
echo '***TEST FINISHED***'
