--I

produsRec :: [Integer] -> Integer
produsRec l
  | null l = 1
  | otherwise = h * t'
  where
    h = head l
    t = tail l
    t' = produsRec t

produsFold :: [Integer] -> Integer
produsFold l = foldr (*) 1 l

andRec :: [Bool] -> Bool
andRec l
  | null l = True
  | otherwise = h && t'
  where
    h = head l
    t = tail l
    t' = andRec t

andFold :: [Bool] -> Bool
andFold l = foldr (&&) True l

concatRec :: [[a]] -> [a]
concatRec [] = []
concatRec (x:xs) = x ++ concatRec xs

concatFold :: [[a]] -> [a]
concatFold l = foldr (++) [] l

rmChar :: Char -> String -> String
rmChar c [] = []
rmChar c (s:sx) = if s == c then rmChar c sx else s : rmChar c sx

rmCharsRec :: String -> String -> String
rmCharsRec s [] = []
rmCharsRec s (h:sx) = if h `elem` s then rmCharsRec s (rmChar h sx) else h : rmCharsRec s sx

test_rmchars :: Bool
test_rmchars = rmCharsRec ['a'..'l'] "fotbal" == "ot"

rmCharsFold :: String -> String -> String
--rmCharsFold s sx = filter (`notElem` s) sx
rmCharsFold s sx = foldr (\x -> if x `elem` s then ([] ++) else ([x] ++)) "" sx


--logistic :: Num a => a -> a -> Natural -> a
--logistic rate start = f
--  where
--    f 0 = start
--    f n = rate * f(n - 1) * (1 - f(n - 1))

--logistic0 :: Fractional a => Natural -> a
--logistic0 = logistic 3.741 0.00079

--III
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

--if x `elem` [-9..(-1)] then '-' else if x == 0 then '0' else if x `elem` [1..9] then '+'