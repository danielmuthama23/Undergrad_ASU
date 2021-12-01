# Example: 
#   `bash run.sh 1` to run question #1 (1mapPopulation.pl)

if [ $1 -eq 1 ]
then
  gplc 1mapPopulation.pl && ./1mapPopulation
elif [ $1 -eq 2 ]
then
  gplc 2students.pl && ./2students
elif [ $1 -eq 3 ]
then
  gplc 3recursion.pl && ./3recursion
else
  echo 'Invalid input!!'
fi