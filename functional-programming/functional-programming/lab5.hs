import Numeric.Natural
import Data.Char
import Data.List

logistic :: Num a => a -> a -> Natural -> a
logistic rate start = f
  where
    f 0 = start
    f n = rate * f (n - 1) * (1 - f (n - 1))

logistic0 :: Fractional a => Natural -> a
logistic0 = logistic 3.741 0.00079

ex1 :: Natural
ex1 = undefined

ex20 :: Fractional a => [a]
ex20 = [1, logistic0 ex1, 3]

ex21 :: Fractional a => a
ex21 = head ex20

ex22 :: Fractional a => a
ex22 = ex20 !! 2

ex23 :: Fractional a => [a]
ex23 = drop 2 ex20

ex24 :: Fractional a => [a]
ex24 = tail ex20


ex31 :: Natural -> Bool
ex31 x = x < 7 || logistic0 (ex1 + x) > 2

ex32 :: Natural -> Bool
ex32 x = logistic0 (ex1 + x) > 2 || x < 7
ex33 :: Bool
ex33 = ex31 5

ex34 :: Bool
ex34 = ex31 7

ex35 :: Bool
ex35 = ex32 5

ex36 :: Bool
ex36 = ex32 7


semn :: [Integer] -> String
semn [] = []
semn (x:xs) =
    if x `elem` [-9..(-1)]
        then '-' : semn xs
    else if x `elem` [1..9]
        then '+' : semn xs
    else if x == 0
        then '0' : semn xs
    else
        semn xs

semnFold :: [Integer] -> String
semnFold = foldr op unit
    where
        unit = []
        x `op` xs
            | x `elem` [-9..(-1)] = '-' : xs
            | x == 0 = '0' : xs
            | x `elem` [1..9] = '+' : xs

semnFold2 :: [Integer] -> String
semnFold2 = foldr op unit
    where
        unit = []
        op = \x xs -> if x `elem` [-9..(-1)] then '-' : xs else (if x == 0 then '0' : xs else '+' : xs)
     

matrice :: Num a => [[a]]
matrice = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]     

maxim :: Ord a => [a] -> a
maxim [] = undefined
maxim [x] = x
maxim (x:xs)
    | (maxim xs) > x = maxim xs
    | otherwise = x

minim :: Ord a => [a] -> a
minim [] = undefined
minim [x] = x
minim (x:xs)
    | (minim xs) < x = minim xs
    | otherwise = x
    
corect :: [[a]] -> Bool
corect x = maxim aux == minim aux
    where aux = [ length t | t <- x ]

el :: [[a]] -> Int -> Int -> a
el x a b
    | a > 0 = el t (a-1) b
    | otherwise = h !! b
    where
        h = head x
        t = tail x

transforma :: [[a]] -> [(a, Int, Int)]
transforma [] = []
transforma m = if corect m then [ (fst(x), snd(x) `div` c, snd(x) `mod` r) | x <- (foldr (++) [] m `zip` [0..]) ] else error "Not a valid matrix"
    where 
        r = length m
        c = length (m !! 0)

transformaTest = transforma [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

rotate :: Int -> [Char] -> [Char]
rotate n [] = []
rotate n (c:s)
    | n == 0 = c:s
    | n < 0 || n > length s = error "Out of bounds N"
    | otherwise = rotate (n - 1) (s ++ [c])


makeKey :: Int -> [(Char, Char)]
makeKey n = [ (x, if ord (x) + n >= ord ('A') && ord (x) + n <= ord ('Z') then chr (ord (x) + n) else chr (ord (x) + n - (ord ('Z') - ord ('A') + 1) ) ) | x <- ['A'..'Z'] ]

lookUp :: Char -> [(Char, Char)] -> Char
lookUp c [] = c
lookUp c (h:t)
    | c == fst(h) = snd(h)
    | otherwise = lookUp c t

isElement :: Char -> [Char] -> Bool
isElement a [] = False
isElement a (x:xs) = if a == x then True else isElement a xs

encipher :: Int -> Char -> Char --Puteam sa ne folosim de makeKey si lookUp, but no ty
encipher n c = if isElement c ['A'..'Z'] == False && isElement c ['a'..'z'] == False then c else (if ord (c) + n >= ord ('A') && ord (c) + n <= ord ('Z') then chr (ord (c) + n) else chr (ord (c) + n - (ord ('Z') - ord ('A') + 1) ))

normalize :: String -> String
normalize [] = []
normalize (h:s)
    | isElement h ['A'..'Z'] || isElement h ['0'..'9'] = h : normalize s
    | isElement h ['a'..'z'] = chr (ord (h) + (ord ('A') - ord ('a'))) : normalize s
    | otherwise = normalize s


encipherStr' :: Int -> String -> String
encipherStr' n [] = []
encipherStr' n (x:xs) = (encipher n x) : encipherStr' n xs

encipherStr :: Int -> String -> String
encipherStr n s = encipherStr' n (normalize s)

reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey xs = [ (snd(x), fst(x)) | x <- xs ]

decipher :: Int -> Char -> Char
decipher n c = if isElement c ['A'..'Z'] == False && isElement c ['a'..'z'] == False then c else (if ord (c) - n >= ord ('A') && ord (c) - n <= ord ('Z') then chr (ord (c) - n) else chr (ord (c) - n + (ord ('Z') - ord ('A') + 1) ))

testEncrypt :: Int -> Bool
testEncrypt n = foldr (&&) True [ if decipher n (encipher n x) == x then True else False | x <- ['A'..'Z'] ]

decipherStr :: Int -> String -> String
decipherStr n [] = []
decipherStr n (x:xs) = decipher n x : decipherStr n xs

data Fruct
    = Mar String Bool
    | Portocala String Int

listaFructe = [ Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala tip val) = tip `elem` ["Tarocco", "Moro", "Sanguinello"]

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0
nrFeliiSicilia ( (Portocala tip val) : ls ) = if tip `elem` ["Tarocco", "Moro", "Sanguinello"] then val + nrFeliiSicilia ls else nrFeliiSicilia ls
nrFeliiSicilia ( (Mar tip viermi) : ls ) = nrFeliiSicilia ls

nrMereViermi :: [Fruct] -> Int
nrMereViermi [] = 0
nrMereViermi ( (Portocala tip val) : ls ) = nrMereViermi ls
nrMereViermi ( (Mar tip viermi) : ls ) = if viermi then 1 + nrMereViermi ls else nrMereViermi ls

data Linie = L [Int]
    --deriving Show

data Matrice = M [Linie]

instance Show Linie where
    show (L x) = foldr (\x y -> x ++ " " ++ y) "" x

verifica :: Matrice -> Int
verifica (M m) = foldr (+) 0 (map (\(L x) -> foldr (+) 0 x) m)

verifica' :: [[Int]] -> Int
verifica' l = foldr (+) 0 (map (\x -> foldr (+) 0 x) l)
