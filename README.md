Temat: jrpg


Członkowie zespołu:
Moczulski Cezary,
Aleksandra Piekarzewicz

Rozmiar skompilowanej aplikacji przekracza limit rozmiaru przesyłanego pliku,
uruchomienie jej bez użycia IDE QCreator wymaga umieszczenia w folderze wielu plików
składowych Qt 5.14.2 i z niewiadomych przyczyn nie umożliwia przejścia z
menu głównego do mapy.

Z tego powodu aby uruchomić projekt,
trzeba najpierw pobrać Qt(wersja darmowa jest oficjalnie dostępna), otworzyć plik jrpg.pro
używając Qt Creator i zbudować go. W tym samym folderze co folder zawierający plik projektu
zostanie utworzony folder o nazwie build-jrpg-*, po przeniesieniu do niego plików
tekstowych i folderu texts z folderu jrpg_build pobranego z repozytorium, gra będzie
działać.