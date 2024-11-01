SELECT   
    COALESCE(p.name, '-') AS person_name, 
    pv.visit_date as visit_date, 
    COALESCE(pz.name, '-') as pizzeria_name
FROM  person p
    LEFT JOIN person_visits pv ON pv.person_id = p.id AND (pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03')
    FULL JOIN pizzeria pz ON pz.id = pv.pizzeria_id
ORDER BY 1,2,3;