all: compile exec

compile:
	g++ main.cpp libs/*.cpp -o recommender

exec:
	./recommender ratings.csv targets.csv > submission.csv

clean:
	rm recommender *.out
