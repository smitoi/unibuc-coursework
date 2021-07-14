import   Data.List

-- L3.1 Încercati sa gasiti valoarea expresiilor de mai jos si
-- verificati raspunsul gasit de voi în interpretor:


exemplu1 = [x^2 | x <- [1 .. 10], x `rem` 3 == 2]
exemplu2 = [(x, y) | x <- [1 .. 5], y <- [x .. (x+2)]]
exemplu3 = [(x, y) | x <- [1 .. 3], let k = x^2, y <- [1 .. k]]
exemplu4 = [x | x <- "Facultatea de Matematica si Informatica", elem x ['A' .. 'Z']]
exemplu5 = [[x .. y] | x <- [1 .. 5], y <- [1 .. 5], x < y ]


factori :: Int -> [Int]
factori x = [1] ++ [ k | k <- [2 .. floor (sqrt (fromIntegral x))], x `rem` k == 0] ++ [x]

prim :: Int -> Bool
prim x
    | length (factori x) == 2 = True
    | otherwise = False

numerePrime :: Int -> [Int]
numerePrime x = [ k | k <- [2 .. x], prim k == True]

-- L3.2 Testati si sesizati diferenta:
exemplu6 = [(x,y) | x <- [1..5], y <- [1..3]]
exemplu7 = zip [1..5] [1..3]

myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 (h1:l1) (h2:l2) (h3:l3) = [(h1, h2, h3)] ++ myzip3 l1 l2 l3
myzip3 _ _ _ = []

--------------------------------------------------------
----------FUNCTII DE NIVEL INALT -----------------------
--------------------------------------------------------
aplica2 :: (a -> a) -> a -> a
--aplica2 f x = f (f x)
--aplica2 f = f.f
--aplica2 f = \x -> f (f x)
aplica2  = \f x -> f (f x)

-- L3.3
exemplu8 = map (\ x -> 2 * x) [1 .. 10]
exemplu9 = map (1 `elem` ) [[2, 3], [1, 2]]
exemplu10 = map ( `elem` [2, 3] ) [1, 3, 4, 5]

firstEl :: [(a, b)] -> [a]
firstEl [] = []
--firstEl xs = [ fst(x) | x <- xs ]
--firstEl (x:xs) = fst(x) : firstEl xs
firstEl xs = map fst xs
test1 = firstEl [ ('a', 3), ('b', 2), ('c', 1)]


sumList :: [[Int]] -> [Int]
sumList [] = []
--sumList xs = [ sum(x) | x <- xs ]
--sumList (x:xs) = sum(x) : sumList xs
sumList xs = map sum xs
test2 = sumList [[1, 3],[2, 4, 5], [], [1, 3, 5, 6]]

func :: Int -> Int
func x
    | x `rem` 2 == 0 = x `div` 2
    | otherwise = x * 2

prel2 :: [Int] -> [Int]
--prel2 xs = [ if x `rem` 2 == 0 then x `div` 2 else x * 2 | x <- xs]

--prel2 [] = []
--prel2 (x : xs)
--    | x `rem` 2 == 0 = x `div` 2 : prel2 xs
--    | otherwise = x * 2 : prel2 xs 

--prel2 xs = map (\ x -> if x `rem` 2 == 0 then x `div` 2 else x * 2) xs
prel2 xs = map func xs
test3 = prel2 [2,4,5,6]

charSir :: Char -> [String] -> [String]
charSir c xc = filter (c `elem`) xc
test4 = charSir 'c' ["Acesta este sirul corect", "Asta este sir gresit", ""]

patrateImpare :: [Int] -> [Int]
patrateImpare xs = map (^2) (filter (\x -> x `mod` 2 == 1) xs)
test5 = patrateImpare [2, 4, 5, 6, 9]

patrateImpare2 :: [Int] -> [Int] --pozitii de la 1
--patrateImpare2 xs = map (\x -> fst(x) * fst(x)) (filter (\x -> snd(x) `mod` 2 == 1) (xs `zip` [1..]))
patrateImpare2 xs = map ((^2) . fst) (filter ((== 1) . (`mod` 2) . snd) (xs `zip` [1..]))
test6 = patrateImpare2 [2, 4, 5, 6, 9]

numaiVocale :: [String] -> [String]
numaiVocale xs = map (\x -> [ c | c <- x, c `elem` "AEIOUaeiou"]) xs
test7 = numaiVocale ["laboratorul", "PrgAmare", "DEclarativa", ""]

mymap :: (a -> b) -> [a] -> [b]
mymap f xs = [ f(x) | x <- xs]

test8 = mymap (\ x -> 2 * x) [1 .. 10]
test9 = mymap (1 `elem` ) [[2, 3], [1, 2]]
test10 = mymap ( `elem` [2, 3] ) [1, 3, 4, 5]

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f xs = [ x | x <- xs, f(x) ]

numerePrimeLim :: Int -> [Int] 
numerePrimeLim n = [ x | x <- [2..n], prim(x) ]

ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x : xs) = and (map (x <) xs) && ordonataNat xs

myzipS :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzipS l1 l2 l3 = map (\x -> (fst(fst x), snd(fst x), snd x))  (l1 `zip` l2 `zip` l3)