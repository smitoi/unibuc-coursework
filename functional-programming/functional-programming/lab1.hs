import Data.List

myInt = 55555555555555555555555555555555555555555555555555555555555
double :: Integer -> Integer
double x = x+x
triple :: Integer -> Integer
triple x = x+x+x

{-
in Data.List avem:
permutations - permutari de o lista
subsequences - sublistele de o lista
-}

maxim :: Integer -> Integer -> Integer
maxim x y =
    if (x > y)
        then x
        else y 

maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z =
    if (x >= y && x >= z)
        then x
        else if (y >= x && y >= z)
            then y
            else z

maxim4 :: (Integer, Integer, Integer, Integer) -> Integer
maxim4 (x, y, z, t) =
    let 
        u = maxim x y
        w = maxim z t
    in
        maxim u w

maxim4 x y z t =
    let
        u = maxim x y
    in
        let 
            w = maxim u z
        in
            maxim w t

-- Functie de verificare
maxim4ver x y z t =
    let
        u = maxim4 x y z t
    in
        u >= x && u >= y && u >= z && u >= t

data Alegere
    = Piatra
    | Foarfeca
    | Hartie
    deriving (Eq, Show)

data Rezultat
    = Infrangere
    | Egalitate
    | Victorie
    deriving (Eq, Show)

partida :: (Alegere, Alegere) -> Rezultat
partida (x, y) =
    if x == y
        then Egalitate
    else 
        if x == Piatra && y == Foarfeca || x == Foarfeca && y == Hartie || x == Hartie && y == Piatra
            then
                Victorie
            else
                Infrangere
