all: clean compile exec

compile:
	g++ -Ofast main.cpp libs/*.cpp -o recommender

compilegdb:
	g++ -Wall -Wextra -O0 -g main.cpp libs/*.cpp -o recommender

exec:
	./recommender ../data/ratings.csv ../data/targets.csv > ../data/submission.csv

clean:
	-rm recommender

test: clean compile
	./recommender ../data/ratings.csv ../data/targets.csv

gdb: clean compilegdb
	gdb --args recommender ../data/ratings.csv ../data/targets.csv

valgrind: clean compile
	valgrind ./recommender ../data/ratings.csv ../data/targets.csv


# Submission command
# kaggle competitions submit -c recsys-20191-cfmr -f ../data/submission.csv -m "Message"
