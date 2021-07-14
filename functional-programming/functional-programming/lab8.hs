import Data.Maybe 
import Data.List

type Nume = String
data Prop
    = Var Nume
    | F
    | T
    | Not Prop
    | Prop :|: Prop
    | Prop :&: Prop
    deriving Eq
infixr 2 :|:
infixr 3 :&:


p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))

instance Show Prop where
    show (Var nume) = nume
    show F = "False"
    show T = "True"
    show (Not p) = "(~" ++ show p ++ ")"
    show (p :|: q) = "(" ++ show p ++ "|" ++ show q ++ ")"
    show (p :&: q) = "(" ++ show p ++ "&" ++ show q ++ ")"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a, b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval (Var nume) l = impureLookup nume l
eval F _ = False
eval T _ = True
eval (Not p) l = not (eval p l)
eval (p :|: q) l = (eval p l) || (eval q l)
eval (p :&: q) l = (eval p l) && (eval q l)

variabile :: Prop -> [Nume]
variabile (Var nume) = [nume]
variabile (Not p) = nub (variabile p)
variabile (p :|: q) = nub (variabile p ++ variabile q)
variabile (p :&: q) = nub (variabile p ++ variabile q)
variabile _ = []

-- toBinary [1, 0, 1]
toBinary :: Int -> [Int]
toBinary n = if n == 0 then [] else toBinary (n `div` 2) ++ [n `mod` 2] 

-- replic a 4 = [a, a, a, a]
replic :: a -> Int -> [a]
replic e n
    | n == 0 = []
    | otherwise = [e] ++ replic e (n - 1)

-- toBinaryDigit 3 4 = [0,0,1,1]
toBinaryDigit :: Int -> Int -> [Int]
toBinaryDigit n d = if dig >= d then bin else (replic 0 (d - dig)) ++ bin
    where 
        bin = toBinary n
        dig = length (toBinary n)

envs' :: [Nume] -> Int -> [Env]
envs' e n = if n == 2^l then [] else [e `zip` (map (\x -> if x == 1 then True else False) (toBinaryDigit n l))] ++ (envs' e (n + 1))
    where
        l = length e

envs :: [Nume] -> [Env]
envs e = envs' e 0

-- varianta Andrew
envsA :: [Nume] -> [Env]
envsA = mapM (\env -> [(env, False), (env, True)])

satisfiabila' :: Prop -> [Env] -> Bool
satisfiabila' p [] = False
satisfiabila' p (e:ex) = if eval p e then True else satisfiabila' p ex

satisfiabila :: Prop -> Bool
satisfiabila p = satisfiabila' p (envs (variabile p))

valida :: Prop -> Bool
valida p = satisfiabila (Not p) == False