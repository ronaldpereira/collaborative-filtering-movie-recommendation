clear
dropbox stop
make all
kaggle competitions submit -c recsys-20191-cfmr -f ../data/submission.csv -m "$1"
make clean
dropbox start

# less -N +F ../data/submission.csv
