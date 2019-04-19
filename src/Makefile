all: clean compile exec

test: clean compile
	./recommender ../data/ratings.csv ../data/targets.csv

compile:
	g++ -Wall -Wextra -g main.cpp libs/*.cpp -o recommender

exec:
	./recommender ../data/ratings.csv ../data/targets.csv > ../data/submission.csv

clean:
	-rm recommender ../data/submission.csv

gdb: clean compile
	gdb --args recommender ../data/ratings.csv ../data/targets.csv

valgrind: clean compile
	valgrind ./recommender ../data/ratings.csv ../data/targets.csv


# Submission command
# kaggle competitions submit -c recsys-20191-cfmr -f ../data/submission.csv -m "Message"
