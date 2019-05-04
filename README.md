# Movie Recommendation

Movie Recommendation algorithm.

## Tools

Movie Recommendation task by using:

- Item-based Collaborative Filtering
- Matrix Mean Normalization
- Cosine Distance
- k-Nearest Neighbors selection for computed similarities (k = 0 (default disabled))
- Item cold-start:
  1. Uses item average as the <user, item> prediction
  2. If the item average doesn't exists, uses all items rating average as the <user, item> prediction
  
## Evaluation Metric
  
- Accuracy metric: RMSE (Root Mean Squared Error)

## Leaderboard

The leaderboard can be seen in this [Kaggle Competition](https://www.kaggle.com/c/recsys-20191-cfmr/leaderboard)
