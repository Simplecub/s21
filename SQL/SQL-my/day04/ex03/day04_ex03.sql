 SELECT generated_date as missing_date
 FROM v_generated_dates 
 EXCEPT ALL
 SELECT visit_date FROM person_visits
 ORDER BY 1;