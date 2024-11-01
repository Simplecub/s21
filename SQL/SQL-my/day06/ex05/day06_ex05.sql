COMMENT ON TABLE person_discounts IS 'This table stores information about discounts offered to different customers in different pizzerias. It contains customer IDs, pizzerias and information about the discount amount.';
COMMENT ON COLUMN person_discounts.id IS 'The id in the table';
COMMENT ON COLUMN person_discounts.person_id IS 'The ID of the customer receiving the discount.s';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'The identifier of the pizzeria providing the discount.';
COMMENT ON COLUMN person_discounts.discount IS 'The amount of the discount provided to the client, as a percentage.';

--SELECT * FROM pg_description WHERE objoid = 'person_discounts'::regclass;