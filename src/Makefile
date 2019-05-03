all: clean compile run

compile:
	g++ -std=c++11 -Wall -Wextra -Werror -Ofast main.cpp libs/*.cpp -o recommender

run:
	./recommender ../data/ratings.csv ../data/targets.csv > ../data/submission.csv

clean:
	-rm recommender
