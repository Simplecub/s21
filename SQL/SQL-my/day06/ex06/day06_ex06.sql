CREATE SEQUENCE IF NOT EXISTS seq_person_discounts
    START 1; 

SELECT setval('seq_person_discounts', (SELECT count(*)  FROM person_discounts));

ALTER TABLE person_discounts 
    ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');


/*

select * from person_discounts;

INSERT INTO person_discounts(person_id, pizzeria_id, discount)
VALUES (4,3,3);

INSERT INTO person_discounts(person_id, pizzeria_id, discount)
VALUES (5,3,3);

select * from person_discounts;


--DELETE FROM person_discounts WHERE id IN(15,14,16,17);

select * from person_discounts;

*/