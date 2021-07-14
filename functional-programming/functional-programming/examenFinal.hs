import Data.Char ( toLower )
import Data.List ( sort )

-- Template: smr27Functie

type Concept = String
type Definitie = String
type Categorie = String
data Enciclopedie =  Intrare Concept Definitie  | Lista Categorie [Enciclopedie]
                                 deriving Show

-- a
-- Luam elementele unice dintr-o lista
smr27getUnique :: (Eq a) => [a] -> [a]
smr27getUnique [] = []
smr27getUnique (x:xs)
    | x `elem` xs = smr27getUnique xs
    | otherwise = x : smr27getUnique xs

-- Luam conceptele (fara unicitate) - mentiunea e ca se iau cu litera mica, deoarece nu se face diferenta
smr27getConcepte' :: Enciclopedie -> [Concept]
smr27getConcepte' (Intrare c _) = [map toLower c]
smr27getConcepte' (Lista c l) 
    | null l = []
    | otherwise = smr27getConcepte (head l) ++ smr27getConcepte (Lista c $ tail l)

-- Luam conceptele unice
smr27getConcepte :: Enciclopedie -> [Concept]
smr27getConcepte x = smr27getUnique $ smr27getConcepte' x

-- Luam lungimea conceptelor
smr27getConcepteLen :: Enciclopedie -> Int
smr27getConcepteLen x = length $ smr27getConcepte x

-- Se pot testa pe aceste tipuri
-- Caz normal
smr27enc1 :: Enciclopedie
smr27enc1 = Lista "animal"[Lista "mamifer"[Intrare "elefant" "acesta e un elefant", Intrare "caine" "acesta este un caine", Intrare "pisica" "aceasta este o pisica"], Intrare "zebra" "zebra este un animal"]
-- Caz cu duplicat
smr27enc2 :: Enciclopedie
smr27enc2 = Lista "Animal"[Lista "animal" [Intrare "Elefant" "acesta e un elefant",Intrare "caIne" "acesta este un caine"], Intrare "caine" "definitie"]
-- Caz doar cu o intrare
smr27enc3 :: Enciclopedie
smr27enc3 = Intrare "mamifer" "ceva"
-- Caz normal, egal cu caz 1
smr27enc4 :: Enciclopedie
smr27enc4 = Lista "animal"[Lista "mamifer"[Intrare "elefant" "acesta e un elefant", Intrare "zebra" "acesta este o zebra", Intrare "pisica" "aceasta este o pisica"], Intrare "caine" "acesta este un caine"]
-- Caz cu duplicat
smr27enc5 :: Enciclopedie
smr27enc5 =  Lista "animal"[Lista "mamifer"[Intrare "elefant" "def1", Intrare "caine" "def2"], Intrare "eLEfant" "def3", Lista "altceva" [Intrare "caINe" "def3"]]
-- Caz gol
smr27enc6 :: Enciclopedie
smr27enc6 =  Lista "goala" []
-- Alt caz gol
smr27enc7 :: Enciclopedie
smr27enc7 =  Lista "goala" []

-- Un mic test
-- Va da TRUE
smr27testConcepte :: Bool
smr27testConcepte = smr27getConcepteLen smr27enc1 == smr27getConcepteLen smr27enc4 && smr27getConcepteLen smr27enc1 == 4 && smr27getConcepteLen smr27enc2 == 2 && smr27getConcepteLen smr27enc3 == 1 && smr27getConcepteLen smr27enc5 == 2 && smr27getConcepteLen smr27enc6 == 0

-- b
instance Eq Enciclopedie where
    x == y = sort (smr27getConcepte x) == sort (smr27getConcepte y)

-- Testam cu smr27enc1 si smr27enc4, respectiv smr27enc6 si smr27enc7 pentru egalitate
-- Va da TRUE
smr27testEgal :: Bool
smr27testEgal = smr27enc1 == smr27enc4 && smr27enc1 /= smr27enc2 && smr27enc1 /= smr27enc3 && smr27enc1 /= smr27enc5 && smr27enc1 /= smr27enc6 && smr27enc2 == smr27enc5 && smr27enc7 == smr27enc6

-- c
type Dictionar = [(Concept, [Definitie])]

-- Adaugam elementul (a, b) la o lista [(a, [b])] dupa cheia de tip a, adaugandu-i valoarea de tip b
smr27addToKey :: (Eq a, Eq b) => (a, b) -> [(a, [b])] -> [(a, [b])]
smr27addToKey e [] = []
smr27addToKey e (x:xs)
    | fst e == fst x = (fst x, snd e : snd x) : xs
    | otherwise = x : smr27addToKey e xs

-- Pentru o lista de [(a, b)] se presupune a ca fiind cheia, si b valoarea pentru a transforma in lista de [(a, [b])]
smr27smashTogether :: (Eq a, Eq b) => [(a, b)] -> [(a, [b])]
smr27smashTogether x = smr27smashTogether' [] [] x
    where
        smr27smashTogether' k acc [] = acc
        smr27smashTogether' k acc (x:xs)
            | fst x `elem` k = smr27smashTogether' k (smr27addToKey x acc) xs
            | otherwise = smr27smashTogether' (fst x : k) ((fst x, [snd x]) : acc) xs

-- Se iau doar tuplurile (Concept, Definitie) - avem concepte duplicate
smr27toDictionary' :: Enciclopedie -> [(Concept, Definitie)]
smr27toDictionary' (Intrare c d) = [(map toLower c, d)]
smr27toDictionary' (Lista c l) 
    | null l = []
    | otherwise = smr27toDictionary' (head l) ++ smr27toDictionary' (Lista c $ tail l)

-- Transforma o enciclopedie in dictionar
smr27toDictionary :: Enciclopedie -> Dictionar
smr27toDictionary x = smr27smashTogether (smr27toDictionary' x)

-- Un test mai bun, scoate din dictionar conceptele, si le compara cu lista definita mai sus
smr27testDictionary' :: Enciclopedie -> Bool
smr27testDictionary' x = sort (map fst (smr27toDictionary x)) == sort (smr27getConcepte x)

-- Cu asta putem testa ce am definit mai sus
-- Va da TRUE
smr27testDictionary :: Bool
smr27testDictionary = smr27testDictionary' smr27enc1 && smr27testDictionary' smr27enc2 && smr27testDictionary' smr27enc3 && smr27testDictionary' smr27enc4 && smr27testDictionary' smr27enc5 && smr27testDictionary' smr27enc6 && smr27testDictionary' smr27enc7

-- Se poate rula acesta pentru a verifica daca sunt corecte
smr27testac :: Bool
smr27testac = smr27testConcepte && smr27testEgal && smr27testDictionary

-- c
data B e = R e Bool | B e ::: B e
infixr 5 :::

instance Foldable B where
    foldMap f (R e _) = f e
    foldMap f (R e _ ::: t) = f e <> foldMap f t

-- Am testat, e True
fTest0 :: Bool
fTest0 = maximum (R 1 True ::: R 5 False ::: R 3 True ::: R 2 True) == 5

-- Un alt test
smr27test :: Bool 
smr27test = sum (R 1 True ::: R 2 False ::: R 8 True ::: R 9 True ::: R 2 False ::: R 5 False) == 27

smr27test''' :: Bool
smr27test''' = product (R 1 True ::: R 2 False ::: R 2 True) == 4

-- d
class C e where
  cFilter :: (a -> Bool) -> e a -> e a
  toList :: e a -> [a]

instance C B where
    cFilter x (R v b)
        | not b = R v False
        | otherwise = R v (x v)
    cFilter x (s ::: t) = cFilter x s ::: cFilter x t
    toList (R v b)
        | not b = []
        | otherwise = [v]
    toList (s ::: t) = toList s ++ toList t

-- Am testat, e True
cTest0 :: Bool
cTest0 = toList  (cFilter (> 2) (R 1 True ::: R 5 False ::: R 3 True ::: R 2 True)) == [3]

-- Un alt test
smr27test' :: Bool
smr27test' = toList (cFilter even (R 1 True ::: R 2 False ::: R 8 True ::: R 9 True ::: R 2 False ::: R 5 False)) == [8]

smr27test'' :: Bool
smr27test'' = toList (cFilter even (R 1 True ::: R 2 False ::: R 8 True ::: R 9 True ::: R 2 False ::: R 6 True)) == [8, 6]


-- Se poate rula asta ca sa fim siguri ca e ok
smr27testcd :: Bool
smr27testcd = smr27test' && smr27test && fTest0 && cTest0 && smr27test'' && smr27test'''