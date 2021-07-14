import Data.List ( (\\), nub )
data Variable = Variable String Int
    deriving (Eq)

var :: String -> Variable 
var x = Variable x 0

fresh :: Variable -> [Variable] -> Variable
fresh (Variable name value) [] = Variable name value
fresh (Variable name value) ((Variable name' value'):list) = if name == name' then fresh (Variable name $ value' + 1) list else fresh (Variable name value) list

instance Show Variable where
    show (Variable name value) = if value == 0 then name else name ++ "_" ++ show value

data Term 
    = V Variable 
    | App Term Term 
    | Lam Variable Term
    deriving (Eq)

v :: String -> Term
v x = V (var x)

lam :: String -> Term -> Term
lam x = Lam (var x)

lams :: [String] -> Term -> Term
lams xs t = foldr lam t xs

($$) :: Term -> Term -> Term
($$) = App
infixl 9 $$

instance Show Term where
    show (V v) = show v
    show (App x y) = "(" ++ show x ++ " " ++ show y ++ ")"
    show (Lam v t) = "(\\" ++ show v ++ "." ++ show t ++ ")"

freeVars :: Term -> [Variable]
freeVars (V v) = [v]
freeVars (App x y) = freeVars x ++ freeVars y
freeVars (Lam x t) = freeVars t \\ [x] 

allVars :: Term -> [Variable]
allVars (V v) = [v]
allVars (App x y) = nub $ freeVars x ++ freeVars y
allVars (Lam x t) = nub $ x : freeVars t

subst :: Term -> Variable -> Term -> Term-- [u/x]t
subst u x (V y) = if y == x then u else V y
subst u x (App t t') = App (subst u x t) (subst u x t')
subst u x (Lam y t)
    | x == y = Lam y t
    | x `notElem` freeVarsT = Lam y t
    | y `notElem` freeVarsU = Lam y (subst u x t)
    | otherwise = Lam y' (subst u x t')
        where
            freeVarsT = freeVars t
            freeVarsU = freeVars u
            allFreeVars = nub ([x] ++ freeVarsU ++ freeVarsT)
            y' = fresh y allFreeVars
            t' = subst (V y') y t

aEq :: Term -> Term -> Bool
aEq (App t t') (App t'' t''') = aEq t t'' && aEq t' t'''
aEq (Lam x t) (Lam x' t') = st' == st''
    where
        freeVarsT = freeVars t
        freeVarsT' = freeVars t'
        allFreeVars = nub ([x] ++ [y] ++ freeVarsT ++ freeVarsT')
        y = fresh x allFreeVars
        st' = subst (V y) x t
        st'' = subst (V y) x' t'
aEq (V x) (V x') = x == x'
aEq _ _ = False 

test7_1 :: Bool
test7_1 = aEq (lam "x" (v "x")) (lam "y" (v "y"))
test7_2 :: Bool
test7_2 = not (aEq (lam "x" (v "x")) (lam "y" (v "z")))

u :: Term
u = lam "z" (v "z")
x :: Variable
x = var "x"
t0 :: Term
t0 = lam "x" (v "x" $$ v "y")
t1 :: Term
t1 = lam "y" (v "y" $$ v "y")
t2 :: Term
t2 = lam "y" (v "x" $$ v "y")
u1 :: Term
u1 = lam "z" (v "z" $$ v "y")