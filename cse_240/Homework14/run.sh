# Example: 
#   `bash run.sh 1` to run question #1 (question1Sort.pl)

if [ $1 -eq 1 ]
then
  gplc question1Sort.pl && ./question1Sort
elif [ $1 -eq 2 ]
then
  gplc question2Pizza.pl && ./question2Pizza
elif [ $1 -eq 3 ]
then
  gplc question3Math.pl && ./question3Math
else
  echo 'Invalid input!!'
fi