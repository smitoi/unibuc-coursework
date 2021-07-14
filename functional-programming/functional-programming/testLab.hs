-- Intoarce valoarea asociata celei mai mari cifre din sir

import Data.Char
import Test.QuickCheck

-- 0 sa nu fie inainte / dupa 1, si sa fie comprimat
functieZero :: [Int] -> [Int]
functieZero [] = []
functieZero [x] = [x]
functieZero (x:y:xs) = if x == 0 && y == 0 then functieZero (y:xs) else if x == 0 && y == 1 then functieZero (y:xs) else if x == 1 && y == 0 then functieZero (x:xs) else [x] ++ functieZero (y:xs)

-- scorul unui caracter este 10 daca apare in "haskell" 1 altfel, produs de scoruri

--1
scor :: Char -> Int
scor c = if c `elem` "Haskell" then 10 else 1

scorRec :: String -> Int
scorRec [] = 1
scorRec (s:sx) = scor s * scorRec sx

--2
scorList :: String -> Int
scorList s = product [ scor x | x <- s ]

--3
scorFunctii :: String -> Int
scorFunctii s = foldr (*) 1 (map (scor) s)

--4
testScor :: String -> Bool
testScor s = scorList s == scorFunctii s

--Verificati daca fiecare vocala din sir e litera mare
vocalaRec :: String -> Bool
vocalaRec [] = True
vocalaRec (s:sx) = if s `elem` "aeiou" then False else vocalaRec sx

vocalaList :: String -> Bool
vocalaList s = not ([ x | x <- s, x `elem` "aeiou" ] /= [])

vocalaFunctii :: String -> Bool
vocalaFunctii s = foldr (&&) True (map (\x -> if x `elem` "aeiou" then False else True) s)

testVocala :: String -> Bool
testVocala s = vocalaList s == vocalaFunctii s

--Verificati daca intr-o lista de siruri unul incepe cu litera mare
listaSiruriRec :: [String] -> Bool
listaSiruriRec [] = False
listaSiruriRec (x:xs) = if length x > 0 && head x `elem` ['A'..'Z'] then True else listaSiruriRec xs

listaSiruriList :: [String] -> Bool
listaSiruriList l = [ x:xs | (x:xs) <- l, x `elem` ['A'..'Z'] ] /= []

listaSiruriFunctii :: [String] -> Bool
listaSiruriFunctii l = foldr (||) False (map (\x -> length x > 0 && head x `elem` ['A'..'Z']) l)

testListaSiruri :: [String] -> Bool
testListaSiruri l = listaSiruriList l == listaSiruriFunctii l && listaSiruriFunctii l == listaSiruriRec l

--Functii de tipul msFun
--Functie pentru reverse-ul unui element
msReverse :: [p] -> [p]
msReverse [] = []
msReverse (x:xs) = msReverse xs ++ [x]

--Functii de tipul msFun

--Verificam fiecare element si reapelam functia cu restul listei
--Pentru lista vida se primeste False deoarece nu avem palindrom
--msRec ["palindrom", ['a'..'z'], "abcba"] = True
--msRec [] = False
--msRec ["palindrom"] = False

msRec :: [String] -> Bool
msRec [] = False
msRec (x:xs) = (x == msReverse x) || msRec xs


--Luam doar elementele care sunt palindroame si comparam lista rezultata cu lista vida
--msList ["cuvant", ['0'..'9']] = False
--msList [] = False
--msList ["abcba"] = True

testCeva :: (Eq a) => [a] -> Bool
testCeva l = reverse l == msReverse l

msList :: [String] -> Bool
msList x = [ e | e <- x, e == msReverse e ] /= []


--Aplicam functia de verificare palindrom pe fiecar element si apoi foldr cu operatorul ||
--Asta pentru a fi diferit fata de cel de mai sus (ca se putea cu un simplu filter)
--msFunctii ["cuvant", "abcba", ['0'..'9']] = True
--msFunctii [] = False
--msFunctii ["abcba"] = True

msFunctii :: [String] -> Bool
msFunctii x = foldr (||) False (map (\x -> x == msReverse x) x)

--Am verificat punctul 3 cu 1, passed 100 tests
msTest :: [String] -> Bool
msTest l = msFunctii l == msRec l

-- Descifrare cod pasareasca
pasareasca :: String -> String
pasareasca (x:y:z:p) = if y == 'p' then (if x /= z then error "Cod invalid" else [z] ++ pasareasca (p)) else [x] ++ pasareasca (y:z:p)
pasareasca x = x

-- Codificare dupa reguli litera mica -> '#', litera mare -> '*', cifra '^', restul -> '_'

codRec :: String -> [(Char, Char)]
codRec [] = []
codRec (x:xs) = if x `elem` ['a'..'z'] then (x, '#') : codRec xs else 
    if x `elem` ['A'..'Z'] then (x, '*') : codRec xs else 
        if x `elem` ['0'..'9'] then (x, '^') : codRec xs 
        else (x, '_') : codRec xs

codList :: String -> [(Char, Char)]
codList l = [ if x `elem` ['a'..'z'] then (x, '#') else if x `elem` ['A'..'Z'] then (x, '*') else if x `elem` ['0'..'9'] then (x, '^') else (x, '_') | x <- l ]

codFunctii :: String -> [(Char, Char)]
codFunctii l = map (\x -> if x `elem` ['a'..'z'] then (x, '#') else if x `elem` ['A'..'Z'] then (x, '*') else if x `elem` ['0'..'9'] then (x, '^') else (x, '_')) l

testCod :: String -> Bool
testCod s = codRec s == codList s && codList s == codFunctii s

-- Semn de punctuatie
semnRecHelper :: Int -> String -> [Int]
semnRecHelper p [] = []
semnRecHelper p (s:sx) = if s `elem` ".?!:,()" then [p] ++ semnRecHelper (p + 1) sx else semnRecHelper (p + 1) sx

semnRec :: String -> [Int]
semnRec s = semnRecHelper 0 s

semnList :: String -> [Int]
semnList s = [ snd x | x <- s `zip` [0..], fst x `elem` ".?!:,()" ]

semnFunctii :: String -> [Int]
semnFunctii s = map (\x -> snd x) (filter (\x -> fst x `elem` ".?!:,()") (s `zip` [0..]))

testSemn :: String -> Bool
testSemn s = semnRec s == semnList s && semnList s == semnFunctii s

-- Fara 0 inainte, dar cu 0 dupa fiecare din urmatoarele numere 3 7 11 101
-- cu 0 inainte dar fara 0 dupa numarul 13


-- Cerinta e putin vaga, pentru ca nu stiu ce fac cu conflictele. In cazul listei [3, 7] s-ar presupune ca 0 trebuie sa fie dupa 3
-- dar nu inainte de 7, deci avem un conflict? puteam sa adaug altfel trimiterea in recursie si astfel s-ar fi prioritizat numerele
-- de la capatul listei (puneam 0-ul dupa 3, dar era eliminat de 7)
--msZero [3, 7, 11, 101]
--msZero [13]
--msZero []
--msZero [1, 2, 13, 0, 2, 0, 3, 0, 9, 11, 24, 0, 101]
msZero :: [Int] -> [Int]
msZero [] = [] -- nu se mai intra pe ramura asta, dar am lasat-o in caz ca se paseaza lista vida ca argument
msZero [x] = if x `elem` [3, 7, 11, 101] then [x, 0] else if x == 13 then [0, x] else [x] -- cand prindem un element pe pozitie finala
msZero (x:y:t) = 
    if x `elem` [3, 7, 11, 101] && y == 0 then -- avem primul caz, cu 0 dupa
        [x] ++ msZero (y:t)
    else if x `elem` [3, 7, 11, 101] && y /= 0 then -- avem primul caz caz, fara 0 dupa deci il adaugam
        [x] ++ [0] ++ msZero (y:t)
    else if y `elem` [3, 7, 11, 101] && x == 0 then -- avem primul caz, cu 0 inainte deci il eliminam
        msZero (y:t)
    else if x == 13 && y == 0 then -- avem al doilea caz, cu 0 dupa, deci il eliminam
        msZero (x:t)
    else if y == 13 && x == 0 then -- avem al doilea caz, cu 0 inainte deci il pastram acolo
        [x] ++ msZero (y:t)
    else if y == 13 && x /= 0 then -- avem al doilea caz, cu 0 dupa deci il eliminam
        [x] ++ [0] ++ msZero (y:t)
    else -- o alta ramura pentru elementele care nu indeplinesc conditiile de mai sus
        [x] ++ msZero (y:t)

subsecvHelper :: [Int] -> Int -> [Int]
subsecvHelper [] n = []
subsecvHelper (x:xs) n = if x == 0 && n >= 1 then [n - 1] ++ subsecvHelper xs 1 else subsecvHelper xs (n + 1)

subsecvCifrata :: [Int] -> [Int]
subsecvCifrata (l:lx) = if l < 10 then subsecvHelper [ if x < 10 then 0 else 1 | x <- (l:lx) ] 0 else subsecvCifrata lx
