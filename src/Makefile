all: compile exec

compile:
	g++ main.cpp libs/*.cpp -o recommender

exec:
	./recommender ../data/ratings.csv ../data/targets.csv > ../data/submission.csv

clean:
	rm recommender ../data/submission.csv
