import Data.Maybe
import Data.List

type Env = [(Name, Integer)]

type Name = String

data  Pgm  = Pgm [Name] Stmt
        deriving (Read, Show)

data Stmt = Skip | Stmt ::: Stmt | If BExp Stmt Stmt | While BExp Stmt | Name := AExp
        deriving (Read, Show)

data AExp = Lit Integer | AExp :+: AExp | AExp :*: AExp | Var Name
        deriving (Read, Show)

data BExp = BTrue | BFalse | AExp :==: AExp | Not BExp
        deriving (Read, Show)

infixr 2 :::
infix 3 :=
infix 4 :==:
infixl 6 :+:
infixl 7 :*:

bEval :: BExp -> Env -> Bool
bEval BTrue _ = True
bEval BFalse _ = False
bEval (Not b) e = not $ bEval b e
bEval (x :==: y) e = aEval x e == aEval y e

sEnv :: Name -> Env -> Integer
sEnv n [] = error "undefined value..."
sEnv n (x : xs)
    | fst x == n = snd x
    | otherwise = sEnv n xs

aEval :: AExp -> Env -> Integer
aEval (Lit x) _ = x
aEval (x :+: y) e = aEval x e + aEval y e
aEval (x :*: y) e = aEval x e * aEval y e
aEval (Var n) e = sEnv n e

sEval :: Stmt -> Env -> Env
sEval Skip e = e
sEval (x ::: y) e = sEval y e'
    where e' = sEval x e
sEval (If x t f) e
    | v = sEval t e
    | otherwise = sEval f e
    where
        v = bEval x e
sEval (While x s) e
    | v = sEval (While x s) (sEval s e)
    | otherwise = e
    where
        v = bEval x e
sEval (n := a) e = sEval' n (aEval a e) e
    where
        sEval' n v (e : ex)
            | n == fst e = (n, v) : ex
            | otherwise = e : sEval' n v ex
        sEval' n v [] = [(n, v)]

pEval :: Pgm -> Env
pEval (Pgm e s) = sEval s (e `zip` [0, 0..])

factStmt :: Stmt
factStmt =
  "p" := Lit 1 ::: "n" := Lit 3 :::
  While (Not (Var "n" :==: Lit 0))
    ( "p" := Var "p" :*: Var "n" :::
      "n" := Var "n" :+: Lit (-1)
    )

factStmt2 :: Stmt
factStmt2 =
    "n" := Lit 1 :::
    If (Var "n" :==: Lit 0)
        (
            While (Not (Var "n" :==: Lit 5))
                (
                    "n" := Var "n" :+: Lit 1
                )
        )
        (
            "n" := Var "n" :+: Lit (-50)
        )

pg1 = Pgm ["a"] factStmt
pg2 = Pgm [] factStmt2