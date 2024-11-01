CREATE VIEW v_generated_dates AS
 SELECT gs::date AS generated_date FROM generate_series('2022-01-01'::DATE, '2022-01-31'::DATE,'1 day'::INTERVAL) AS gs
 ORDER BY 1;


 --SELECT * FROM v_generated_dates;