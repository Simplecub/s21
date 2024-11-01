CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
    pperson varchar default 'Dmitriy', 
    pprice integer DEFAULT 500, 
    pdate date DEFAULT '2022-01-08') 
RETURNS varchar AS $$
    DECLARE
         pizzeria_name varchar;
    BEGIN
        SELECT pz.name INTO pizzeria_name
        FROM menu m
        JOIN pizzeria pz ON m.pizzeria_id = pz.id
        JOIN person_visits pv ON pz.id = pv.pizzeria_id
        JOIN  person p ON p.id = pv.person_id 
        WHERE p.name = pperson
            AND m.price < pprice
            AND pv.visit_date = pdate;
    RETURN pizzeria_name;
    END;
$$ LANGUAGE plpgsql;


select *
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');

CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
    pperson varchar default 'Dmitriy', 
    pprice integer DEFAULT 500, 
    pdate date DEFAULT '2022-01-08') 
RETURNS TABLE(name varchar) AS $$
    BEGIN 
    RETURN QUERY 
        SELECT pz.name AS pizzeria_name
        FROM menu m
        JOIN pizzeria pz ON m.pizzeria_id = pz.id
        JOIN person_visits pv ON pz.id = pv.pizzeria_id
        JOIN  person p ON p.id = pv.person_id 
        WHERE p.name = pperson
            AND m.price < pprice
            AND pv.visit_date = pdate
            order by 1 desc;
    END;
$$ LANGUAGE plpgsql;


select *
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');