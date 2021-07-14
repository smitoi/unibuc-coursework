isVocalRec :: String -> Bool
isVocalRec [] = True
isVocalRec (x:xs) = (x `notElem` "aeiou") && isVocalRec xs

isVocalList :: String -> Bool
isVocalList s = null ([x | x <- s, x `elem` "aeiou"])

isVocalHigh :: String -> Bool 
isVocalHigh = foldr (\ x -> (&&) (x `notElem` "aeiou")) True

data Pol = X Integer | S Integer | Pol :*: Pol deriving (Show)

getCoef :: Pol -> (Integer, Integer)
getCoef (S m :*: X n) = (n, m)
getCoef _ = (0, 0)

forma :: Pol -> Pol -> Pol -> Pol
forma ((X x :*: S y)) (X n) (S m) = (S $ y + m) :*: (X $ x + n)
forma (X x :*: p) (X n) (S m) = S (y + m) :*: X (x + x' + n)
    where
        (x', y) = getCoef (forma' p)
forma (S y :*: p) (X n) (S m) = S (y + y' + m) :*: X (x + n)
    where
        (x, y') = getCoef (forma' p)
forma (p :*: p') (X n) (S m) = S (y + y' + m) :*: X (x + x' + n)
    where
        (x, y) = getCoef (forma' p)
        (x', y') = getCoef (forma' p')

forma' :: Pol -> Pol
forma' p = forma p 0

pol = X 4 :*: S 3
pol' = X 3 :*: (X 4 :*: S 3)
pol'' = S 2 :*: (X 3 :*: (X 4 :*: S 3))