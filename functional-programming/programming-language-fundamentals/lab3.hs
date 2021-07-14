{- Monada Maybe este definita in GHC.Base 

instance Monad Maybe where
  return = Just
  Just va  >>= k   = k va
  Nothing >>= _   = Nothing


instance Applicative Maybe where
  pure = return
  mf <*> ma = do
    f <- mf
    va <- ma
    return (f va)       

instance Functor Maybe where              
  fmap f ma = pure f <*> ma   
-}

import Test.QuickCheck

-- I
-- 1
(<=<) :: (a -> Maybe b) -> (c -> Maybe a) -> c -> Maybe b
f <=< g = \ x -> g x >>= f

f :: Int -> Maybe String
f x
    | x > 0 = Just "Pozitiv"
    | x < 0 = Just "Negativ"
    | otherwise = Nothing

g :: Bool -> Maybe Int
g x
    | x = Just 1
    | otherwise = Nothing

h :: String -> Maybe Int
h x
    | x == "Pozitiv" = Just 1
    | x == "Negativ" = Just $ -1
    | otherwise = Just 0

t :: Int -> Maybe Bool
t x
    | x > 0 = Just True
    | otherwise = Nothing

-- Exemple
ex', ex'', ex''' :: Maybe String
ex' = (f <=< g) True
ex'' = (f <=< g) False
ex''' = (f <=< h) "Negativ"
ex'''', ex''''' :: Maybe Int
ex'''' = (h <=< f <=< g <=< t) $ -2
ex''''' = (h <=< f <=< g <=< t) 42

-- Funcții particulare
f' :: Int -> Maybe Int
f' a
    | even a = Just $ a `div` 2 + 1
    | otherwise = Nothing

f'' :: Int -> Maybe Int
f'' a
    | a > 42 = Just $ (a - 42)
    | otherwise = Nothing

f''' :: Int -> Maybe Int
f''' a
    | a < 0 = Just $ (-1) * a
    | otherwise = Nothing

-- Asociativitate și quickCheck
asoc :: (Int -> Maybe Int) -> (Int -> Maybe Int) -> (Int -> Maybe Int) -> Int -> Bool
asoc f g h x = ((h <=< g) <=< f $ x) == (h <=< (g <=< f) $ x) 

test = quickCheck $ asoc f' f'' f'''

-- 2
pos :: Int -> Bool
pos  x = x >= 0

foo :: Maybe Int ->  Maybe Bool 
foo  mx =  mx  >>= Just . pos

foo' :: Maybe Int ->  Maybe Bool 
foo' mx = do
    x <- mx
    let r = pos x
    return r
 
-- 3
addM :: Maybe Int -> Maybe Int -> Maybe Int 
addM (Just x) (Just y) = Just $ x + y
addM _ _ = Nothing

addM' :: Maybe Int -> Maybe Int -> Maybe Int 
addM' mx my = do
    x <- mx
    y <- my
    return $ x + y

test' = quickCheck (\x y -> addM x y == addM' x y)

-- 4
cartesianProduct :: Monad m => m a -> m b -> m (a, b)
cartesianProduct xs ys = xs >>= (\x -> (ys >>= \y -> return (x, y)))
cartesianProduct' :: Monad m => m a -> m b -> m (a, b)
cartesianProduct' xs ys = do
    x <- xs
    y <- ys
    return (x, y)

prod :: (t1 -> t2 -> a) -> [t1] -> [t2] -> [a]
prod f xs ys = [f x y | x <- xs, y <- ys]
prod' :: Monad m => (t -> a -> b) -> m t -> m a -> m b
prod' f xs ys = do
    x <- xs
    fmap (f x) ys

myGetLine :: IO String
myGetLine = getChar >>= \x ->
    if x == '\n' then
        return []
    else
        myGetLine >>= \xs -> return (x:xs)

myGetLine' :: IO String
myGetLine' = do
    x <- getChar 
    if x == '\n' then
        return []
    else do
        xs <- myGetLine'
        return (x : xs)

prelNo :: Floating a => a -> a
prelNo noin = sqrt noin

ioNumber :: IO ()
ioNumber = do
    noin <- readLn :: IO Float
    putStrLn $ "Intrare\n" ++ show noin
    let noout = prelNo noin
    putStrLn "Iesire"
    print noout

ioNumber' :: IO()
ioNumber' = (readLn :: IO Float) >>= \noin -> putStr ("Intrare\n" ++ show noin) >> putStrLn "Iesire" >> print (prelNo noin)

-- II
--- Monada Writer

-- 1
{-
newtype WriterS a = Writer { runWriter :: (a, String) } 

instance  Monad WriterS where
  return va = Writer (va, "")
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)

instance  Applicative WriterS where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       


instance  Functor WriterS where              
  fmap f ma = pure f <*> ma     

tell :: String -> WriterS () 
tell log = Writer ((), log)
  
logIncrement :: Int  -> WriterS Int
logIncrement x = Writer(x + 1, "increment:" ++ show x ++ "\n")

logIncrementN :: Int -> Int -> WriterS Int
logIncrementN x n
    | n > 0 = logIncrement x >>= \y -> logIncrementN y (n - 1)
    | otherwise = Writer(x, "")  
-}

-- 2
newtype WriterLS a = Writer { runWriter :: (a, [String]) } 

instance  Monad WriterLS where
  return va = Writer (va, [])
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)

instance  Applicative WriterLS where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)  

instance  Functor WriterLS where              
  fmap f ma = pure f <*> ma

logIncrement :: Int  -> WriterLS Int
logIncrement x = Writer (x + 1, ["increment:" ++ show x])

logIncrementN :: Int -> Int -> WriterLS Int
logIncrementN x n
    | n > 0 = logIncrement x >>= \y -> logIncrementN y (n - 1)
    | otherwise = Writer(x, []) -- return x

-- 3
tell :: String -> WriterLS () 
tell log = Writer ((), [log])
                         
isPos :: Int -> WriterLS Bool
isPos x = if (x >= 0) then (Writer (True, ["poz"])) else (Writer (False, ["neg"]))

-- 4
mapWriterLS :: (a -> WriterLS b) -> [a] -> WriterLS [b]
mapWriterLS f [] = Writer (mempty, [])
mapWriterLS f xs = Writer (map fst map', concatMap snd map')
    where
        map' = map (runWriter . f) xs

-- 5
{-
mapWriterS :: (a -> WriterS b) -> [a] -> WriterS [b]
mapWriterS f [] = Writer (mempty, mempty)
mapWriterS f xs = Writer (map fst map', concatMap snd map')
    where
        map' = map (runWriter . f) xs
-}

isPos' :: Int -> Maybe String
isPos' x = if (x >= 0) then Just "Pozitiv" else Nothing

mapMaybe :: (Monoid b) => (a -> Maybe b) -> [a] -> Maybe [b]
mapMaybe f [] = Just mempty
mapMaybe f xs = Just map'
    where
        map' = map (unjust . f) xs
        unjust :: (Monoid a) => Maybe a -> a
        unjust (Just x) = x
        unjust Nothing = mempty

-- III
newtype Reader env a = Reader { runReader :: env -> a }

instance Monad (Reader env) where
  return x = Reader (\_ -> x)
  ma >>= k = Reader f
    where f env = let a = runReader ma env
                  in  runReader (k a) env

instance Applicative (Reader env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)

instance Functor (Reader env) where
  fmap f ma = pure f <*> ma

ask :: Reader env env
ask = Reader id

local :: (r -> r) -> Reader r a -> Reader r a
local f ma = Reader $ (\r -> (runReader ma)(f r))

-- Reader Person String
data Person = Person { name :: String, age :: Int }

showPersonN :: Person -> String
showPersonN p = "NAME:" ++ name p

showPersonA :: Person -> String
showPersonA p = "AGE:" ++ show (age p)

showPerson :: Person -> String
showPerson p = "(" ++ showPersonN p ++ "," ++ showPersonA p ++ ")"

mshowPersonN :: Reader Person String
mshowPersonN = Reader showPersonN

mshowPersonA ::  Reader Person String
mshowPersonA = Reader showPersonA

mshowPerson :: Reader Person String
mshowPerson = Reader showPerson