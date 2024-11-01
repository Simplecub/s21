SELECT name, count_of_visits
FROM 
(
SELECT person_id, count(*) AS count_of_visits
FROM person_visits
GROUP BY person_id
ORDER BY  2 DESC, 1
)  q1
JOIN person ON q1.person_id = person.id
ORDER BY 2 DESC, 1
LIMIT 4;