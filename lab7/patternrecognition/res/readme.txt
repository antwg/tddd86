/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150	  0.030         0.016
    200	  0.086         0.030
    300	  0.256         0.075
    400	  0.592         0.141
    800	  4.785         0.542
   1600	  38.450        2.428
   3200	  300.863       10.071
   6400                   42.714
  12800                   181.942


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: Värsta fall ordo(n⁴). I värsta fall ligger alla punkter på en linje och då måste alla fyra loopar köras. Varje loop är ordo(n).

Sortering: Värsta fall ordo(n²logn). Två nästlade loops med ordo(n) och en multimap count som är ordo(logn).
