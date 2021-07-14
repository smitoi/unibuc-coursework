import Data.List
import Data.Monoid
import           Test.QuickCheck hiding (Failure, Success)

data Arbore a =
    Nod (Arbore a) a (Arbore a)
    | Frunza a
    | Empty

-- I (a)
arboreValid' :: (Ord a) => Arbore a -> a -> Bool
arboreValid' Empty _ = True
arboreValid' (Frunza a) v = a < v
arboreValid' (Nod _ a _) v = a < v

arboreValid'' :: (Ord a) => Arbore a -> a -> Bool
arboreValid'' Empty _ = True
arboreValid'' (Frunza a) v = a > v
arboreValid'' (Nod _ a _) v = a > v

arboreValid :: (Ord a) => Arbore a -> Bool
arboreValid Empty = True
arboreValid (Frunza a) = True
arboreValid (Nod as v ad) = arboreValid' as v && arboreValid'' ad v && arboreValid as && arboreValid ad

-- I (b)
insertArbore :: (Ord a) => a -> Arbore a -> Arbore a
insertArbore v Empty = Frunza v
insertArbore v (Frunza a)
    | v < a = Nod (Frunza v) a (Empty)
    | v > a = Nod (Empty) a (Frunza v)
    | otherwise = Frunza v
insertArbore v (Nod as a ad)
    | v < a = Nod (insertArbore v as) a ad
    | v > a = Nod as a (insertArbore v ad)
    | otherwise = Nod as v ad

-- I (c)
instance Functor Arbore where
    fmap _ Empty = Empty
    fmap f (Frunza x) = Frunza (f x)
    fmap f (Nod left x right) = Nod (fmap f left) (f x) (fmap f right)

-- II (a)
instance Foldable Arbore where
    foldMap f Empty = mempty
    foldMap f (Frunza a) = f a
    foldMap f (Nod as a ad) = foldMap f as <> f a <> foldMap f ad

-- II (b)
inOrder :: Arbore a -> [a]
inOrder Empty = []
inOrder (Frunza x) = [x]
inOrder (Nod as x ad) = inOrder as ++ [x] ++ inOrder ad

instance Show a => Show (Arbore a) where
    show a = intercalate ", " (map show (inOrder a))

instance (Ord a, Arbitrary a) => Arbitrary (Arbore a) where
    arbitrary = arbore'

arbore' :: (Ord a, Arbitrary a) => Gen (Arbore a)
arbore' = listOf arbitrary >>= return . foldr insertArbore Empty

testArboreValiditate :: (Ord a) => Arbore a -> Bool
testArboreValiditate = arboreValid

test = Empty
test2 = insertArbore 2 test
test3 = insertArbore 5 test2
test4 = insertArbore 3 test3
test5 = insertArbore 2 test4
test6 = insertArbore 7 test5
test7 = insertArbore 5 test6
test8 = insertArbore 9 test7
test9 = insertArbore 22 test8
