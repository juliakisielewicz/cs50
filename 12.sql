


SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE people.name LIKE "Helena Bonham Carter" AND movie_id IN
(SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE people.name LIKE "Johnny Depp"));


