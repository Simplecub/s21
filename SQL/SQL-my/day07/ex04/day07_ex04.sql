SELECT p.name, count(person_id) AS count_of_visits
FROM person_visits pv JOIN person p ON p.id = pv.person_id
GROUP BY p.name
HAVING COUNT(p.name) >3