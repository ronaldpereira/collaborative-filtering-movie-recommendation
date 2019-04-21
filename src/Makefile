all: clean compile exec

test: clean compile
	./recommender ../data/ratings.csv ../data/targets.csv

smalltest: clean compile
	./recommender ../data/smallratings.csv ../data/smalltargets.csv

compile:
	g++ main.cpp libs/*.cpp -o recommender

exec:
	./recommender ../data/ratings.csv ../data/targets.csv > ../data/submission.csv

clean:
	-rm recommender ../data/submission.csv

gdb: clean
	g++ -Wall -Wextra -g main.cpp libs/*.cpp -o recommender
	gdb --args recommender ../data/smallratings.csv ../data/smalltargets.csv

valgrind: clean compile
	valgrind ./recommender ../data/ratings.csv ../data/targets.csv


# Submission command
# kaggle competitions submit -c recsys-20191-cfmr -f ../data/submission.csv -m "Message"
