SELECT people.name FROM people JOIN directors ON people.id = directors.person_id JOIN ratings ON directors.movie_id = ratings.movieid WHERE ratings.rating >= 9.0;