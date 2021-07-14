import Test.QuickCheck
import Data.Char
import Data.Maybe

double :: Int -> Int
double = (*) 2

triple :: Int -> Int
triple = (*) 3

penta :: Int -> Int
penta = (*) 5

test x = (double x + triple x) == (penta x)

myLookUp :: Int -> [(Int,String)]-> Maybe String
myLookUp x [] = Nothing
myLookUp x (l:ls) = if x == fst(l) then Just $ snd(l) else myLookUp x ls

testLookUp :: Int -> [(Int,String)] -> Bool
testLookUp x l = myLookUp x l == lookup x l

testLookUpCond :: Int -> [(Int,String)] -> Property
testLookUpCond n list = n > 0 && n `div` 5 == 0 ==> testLookUp n list

capitalise :: String -> String
capitalise (head:tail) = toUpper head : tail
capitalise [] = []

myLookUp' :: Int -> [(Int, String)] -> Maybe String
myLookUp' x [] = Nothing
myLookUp' x (l:ls) = if x == fst l then Just $ (capitalise (snd l)) else myLookUp' x ls

testLookUp' :: Int -> [(Int, String)] -> Property
testLookUp' n list = and [snd p /= [] && isUpper (head (snd p)) | p <- list] ==> testLookUp n list

data ElemIS = I Int | S String
     deriving (Show,Eq)

instance Arbitrary ElemIS where
     arbitrary = do
          i <- arbitrary
          s <- arbitrary
          elements[I i, S s]

myLookUpElem :: Int -> [(Int,ElemIS)]-> Maybe ElemIS
myLookUpElem _ [] = Nothing
myLookUpElem y (x:xs) = if fst(x) == y then Just $ snd(x) else myLookUpElem y xs

testLookUpElem :: Int -> [(Int,ElemIS)] -> Bool
testLookUpElem x l = myLookUpElem x l == lookup x l

