SELECT person_id, count(*) as count_of_visits
FROM person_visits
GROUP by person_id
ORDER BY  2 desc, 1;