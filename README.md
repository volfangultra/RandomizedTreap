# RandomizedTreap
C++ Implementation of Randomized Treap

Postoje mnoge metode koje služe za održavanje balansiranosti binarnog stable pretrage (kao što su 
AVL stabla ili crveno-crna stabla). Jedan od načina je da se simulira slučajni redoslijed umetanja u 
stablo, odakle onda na osnovu teorije vjerovatnoće slijedi da će stablo biti balansirano sa velikom 
vjerovatnoćom (tj. visina stabla će biti 𝑂(log 𝑛)). 
Ideja je da elementi stabla pored vrijednosti (koja će u ovom slučaju biti i ključ za pretragu), sadrže i 
prioritete, koji se slučajno generišu pri umetanju elemenata u stablo. Svaka dva čvora treba da 
zadovoljavaju osobinu heapa za prioritete, tj. svaki čvor ima veći prioritet od svog djeteta, a manji od 
svog roditelja. 
Operacije koje je potrebno podržati (sve treba da rade u vremenu 𝑂(log 𝑛)):
 <ul> 
  <li>Pretraga – vrši se kao u običnom binarnom stablu, po vrijednosti (koja je ujedno i ključ);</li>
  
  <li>Umetanje – najprije se element umeće u stablo na klasičan način, kao list, te mu se slučajno
  dodjeljuje prioritet. Nakon toga, ako nije zadovoljena osobina heapa za prioritete, vrše se 
  neophodne modifikacije (u ovom slučaju rotacije) kako bi se očuvala ta osobina prilikom svakog 
  umetanja.</li>
  
  <li>Brisanje – ako je dati element list, jednostavno ga obrišemo. Ako ima samo jedno dijete, na
  njegovo mjesto postavimo to dijete, a njega obrišemo. U slučaju da ima dvoje djece, onda ga 
  zamijenimo sa njegovim sljedbenikom (ili prethodnikom) u sortiranom redoslijedu (po 
  vrijednosti). U posljednjem slučaju, može se desiti da se naruši osobina heapa za prioritete, te 
  će onda trebati izvršiti dodatne rotacije.</li>
  
  <li>Razdvajanje – funkcija koja prima stablo i neku vrijednost ključa 𝑘 (za koji se može pretpostaviti 
  da ne postoji u stablu), te vraća par stabala, jedno stablo gdje su svi elementi manji od 𝑘, te 
  drugo stablo gdje su svi elementi veći od 𝑘. Ideja je da se u postojeće stablo umetne element 
  koji ima vrijednost 𝑘 i dodijeli mu se prioritet veći od prioriteta svih elemenata u stablu (tj. od 
  prioriteta korijena), tako da će on prilikom umetanja postati korijen. Tada njegovo lijevo i 
  desno podstablo predstavljaju stabla koja treba vratiti. Nije bitno u kakvom stanju nakon 
  funkcije ostaje originalno stablo (tj. nije potrebno da se poziva konstruktor kopije koji bi 
    usporio funkciju).</li>
  
  <li>Pomoćna funkcija - spajanje dva stabla koja su prethodno nastala razdvajanjem – funkcija koja 
  prima dva stabla 𝑆1 i 𝑆2, takva da su svi elementi u 𝑆1 manji od svih elemenata u 𝑆2. Napravi 
  se čvor čija je vrijednost veća od svih elemenata u 𝑆1, a manja od svih elemenata u 𝑆2, te mu 
  se dodijeli prioritet manji od svih prioriteta u stablima 𝑆1 i 𝑆2. Nakon toga, napravi se stablo čiji 
  je korijen novokreirani čvor, te mu je lijevo podstablo 𝑆1, a desno 𝑆2. Nakon toga se izvrše 
  potrebne rotacije da bi se zadržala osobina heapa za prioritete, nakon čega će ovaj element 
  postati list te se može bezbjedno izbrisati.</li>
  
  <li>Implementirati funkciju koja prima dva stabla i vraća njihovu uniju kao stablo, pri čemu se može 
  pretpostaviti da stabla nemaju zajedničkih elemenata. Funkcija radi na način da se provjeri koji 
  od korijena ova dva stabla ima veći prioritet. Ako je to korijen prvog stabla, onda se funkcija 
  (unija) rekurzivno poziva najprije za lijevo podstablo prvog stabla i lijevo stablo koje nastane 
  razdvajanjem drugog stabla na vrijednosti manje i veće od vrijednosti korijena prvog stabla, a 
  zatim na desno podstablo prvog stabla i desno stablo drugog stabla koje nastane razdvajanjem. 
  Nakon toga se izvrši spajanje dvije novodobijene unije pomoću prethodne funkcije. 
  Prodiskutovati složenost ove funkcije. (Napomena: nije bitno u kakvom su stanju početna 
    stabla nakon završetka funkcije, tj. ne treba da se poziva konstruktor kopije)</li>
</ul>
