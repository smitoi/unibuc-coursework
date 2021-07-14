-- la nevoie decomentati liniile urmatoare:

import Test.QuickCheck
import Data.Char
import Data.List

-- RECURSIE: FIBONACCI

fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
  | n < 2     = n
  | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)

fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)
  
-- RECURSIE PE LISTE

semiPareRecDestr :: [Int] -> [Int]
semiPareRecDestr l
  | null l    = l
  | even h    = h `div` 2 : t'
  | otherwise = t'
  where
    h = head l
    t = tail l
    t' = semiPareRecDestr t

semiPareRecEq :: [Int] -> [Int]
semiPareRecEq [] = []
semiPareRecEq (h:t)
  | even h    = h `div` 2 : t'
  | otherwise = t'
  where t' = semiPareRecEq t

-- DESCRIERI DE LISTE 

semiPareComp :: [Int] -> [Int]
semiPareComp l = [ x `div` 2 | x <- l, even x ]

--Exerciții

-- L2.1
fibonacciLiniar :: Integer -> Integer
fibonacciLiniar 0 = 0
fibonacciLiniar n = snd (fibonacciPereche n)
  where
    fibonacciPereche :: Integer -> (Integer, Integer)
    fibonacciPereche 1 = (0, 1)
    fibonacciPereche n = (snd u, fst u + snd u)
      where
        u = fibonacciPereche (n - 1)

-- L2.2
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec lo hi xs
  | null xs = xs
  | h >= lo && h <= hi = h : inIntervalRec lo hi t'
  | otherwise = inIntervalRec lo hi t'
  where
    h = head xs
    t = tail xs
    t' = inIntervalRec lo hi t

-- Varianta cu sablon
inIntervaleRec2 :: Int -> Int -> [Int] -> [Int]
inIntervaleRec2 lo hi [] = []
inIntervaleRec2 lo hi (h:xs)
  | h >= lo && h <= hi = h : rest
  | otherwise = rest
  where
    rest = inIntervaleRec2 lo hi xs

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp lo hi xs = [ x | x <- xs, x >= lo && x <= hi]

inIntervalTest :: Int -> Int -> [Int] -> Bool
inIntervalTest lo hi l =
  inIntervalRec lo hi l == inIntervalComp lo hi l

-- L2.3
pozitiveRec :: [Int] -> Int
pozitiveRec l
  | null l = 0
  | h > 0 = 1 + t'
  | otherwise = t'
  where
    h = head l
    t = tail l
    t' = pozitiveRec t

pozitiveComp :: [Int] -> Int
pozitiveComp l = sum([ 1 | x <- l, x > 0])

pozitiveTest :: [Int] -> Bool
pozitiveTest l =
  pozitiveRec l == pozitiveComp l

-- L2.4 
pozitiiImpareRec2 :: [Int] -> Int -> [Int]
pozitiiImpareRec2 l p
  | null l = l
  | h `mod` 2 == 1 = p : t'
  | otherwise = t'
  where
    h = head l
    t = tail l 
    t' = pozitiiImpareRec2 t (p+1)

pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec [] = []
pozitiiImpareRec l = pozitiiImpareRec2 l 1

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [i | (i, x) <- [1..] `zip` l, x `mod` 2 == 1]

pozitiiImpareTest :: [Int] -> Bool
pozitiiImpareTest l =
  pozitiiImpareRec l == pozitiiImpareComp l

-- L2.5
multDigitsRec :: String -> Int
multDigitsRec sir
  | null sir = 1
  | isDigit(h) = digitToInt(h) * t'
  | otherwise = t'
  where
    h = head sir
    t = tail sir
    t' = multDigitsRec t

multDigitsComp :: String -> Int
multDigitsComp sir = product([ digitToInt(h) | h <- sir, isDigit(h) == True])

multDigitsTest :: String -> Bool
multDigitsTest l =
  multDigitsRec l == multDigitsComp l

-- L2.6
discountRec :: [Float] -> [Float]
discountRec list
  | null list = list
  | h * 0.75 < 200 = h * 0.75 : t'
  | otherwise = t'
  where
    h = head list
    t = tail list
    t' = discountRec t

discountComp :: [Float] -> [Float]
discountComp list = [ h * 0.75 | h <- list, h * 0.75 < 200 ]

discountTest :: [Float] -> Bool
discountTest l =
  discountRec l == discountComp l

main = do
  print (inIntervalTest 5 10 [0..15])
  print (pozitiveTest [0, 1, -3, -2, 8, -1, 6])
  print (pozitiiImpareTest [0, 1, -3, -2, 8, -1, 6, 1])
  print (multDigitsTest "Aceasta functie are 22 de valorii pe care le returneaza in 5 secunde")
  print (discountTest [ 150, 300, 250, 200, 450, 100 ])