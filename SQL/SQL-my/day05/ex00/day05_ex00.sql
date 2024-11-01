
--DROP INDEX idx_menu_unique;
--DROP INDEX idx_person_name;
--DROP INDEX idx_person_order_multi;
--DROP INDEX idx_person_order_order_date;

CREATE INDEX IF NOT EXISTS idx_menu_pizzeria_id ON menu (pizzeria_id);
CREATE INDEX IF NOT EXISTS idx_person_order_person_id ON person_order(person_id);
CREATE INDEX IF NOT EXISTS idx_person_order_menu_id ON person_order(menu_id);
CREATE INDEX IF NOT EXISTS idx_person_visits_person_id ON person_visits(person_id);
CREATE INDEX IF NOT EXISTS idx_person_visits_pizzeria_id ON person_visits(pizzeria_id);