Reseni progtestu se nam docela libilo, ale chteli bychom  jeste upravit nasledujici, abychom ho mohli plne akceptovat.
 
- Podle zadani ulohy ma prvni vlakno slouzit ke cteni vstupu, parsovani, predani dat filtru a ulozeni vystupu od filtru. 
  Druhe pak ma slouzit pouze k fitrovani. Nicmene v aplikace je rozdeleni funkcionalit mezi vlakna nasledujici: 
    prvni vlakno cteni a zapis, druhe vlakno parsovani a filtrovani. Radi bychom, aby to bylo dle zadani.

- Nelibilo se nam vyuziti regexu na filtrovani. Radi bychom, aby filtr neobsahoval regex.

- Aplikace generuje spatny vystup pro vnorene tagy (nested tags) tedy napr. pro  <object><param/><object></object></object>. 
  Chteli bychom, aby aplikace spravne filtrovala I vnorene tagy
