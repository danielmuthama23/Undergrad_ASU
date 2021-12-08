# Example: 
#   `bash run.sh c` to run test.c

# `rkt` not included because it's ran in external program 

if [ "$1" = "c" ]
then
  gcc -g test.c -o output && ./output
elif [ "$1" = "cpp" ]
then
  g++ -g test.cpp -o output && ./output
elif [ "$1" = "pl" ]
then
  gplc test.pl && ./test
else
  echo 'Invalid input!!'
fi