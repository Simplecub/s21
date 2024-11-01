WITH 
cte0 AS (select generate_series('2022-01-01', '2022-01-10', interval '1 day' ) AS tag),
cte1 AS (select * from cte0 
                INNER JOIN  person_visits pv
                ON pv.visit_date = tag AND (pv.person_id = 1 OR pv.person_id = 2))

SELECT DISTINCT pvv.visit_date AS missing_date
from cte1 RIGHT JOIN  person_visits pvv ON pvv.visit_date = tag 
WHERE tag is null 
ORDER BY 1;