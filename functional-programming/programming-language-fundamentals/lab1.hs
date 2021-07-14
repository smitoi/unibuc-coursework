data Prog = On Instr
data Instr = Off | Expr :> Instr
data Expr = Mem | V Int | Expr :+ Expr
type Env = Int -- valoarea celulei de memorie
type DomProg = [Int]   
type DomInstr = Env -> [Int]
type DomExpr = Env -> Int

-- 1
prog :: Prog -> DomProg
prog (On i) = stmt i 0

stmt :: Instr -> DomInstr
stmt Off e = []
stmt (x :> i) e = eval : stmt i eval
    where
        eval = expr x e

expr :: Expr -> DomExpr
expr Mem e = e
expr (V v) e = v
expr (x :+ y) e = eval + expr y eval
    where
        eval = expr x e

p1 = On ( (V 3) :> ((Mem :+ (V 5)) :> Off))
p2 = On ( ( Mem :+ (V 5) :+ (V 3) ) :> (( Mem ) :> (( Mem :+ (V 12)) :> Off)))

type Name = String
data Hask = HTrue --x
 | HFalse --x
 | HLit Int --x
 | HIf Hask Hask Hask --x
 | Hask :==: Hask --x
 | Hask :+: Hask --x
 | HVar Name --x
 | HLam Name Hask
 | Hask :$: Hask
  deriving (Read, Show)
infix 4 :==:
infixl 6 :+:
infixl 9 :$:

-- 2
sEnv :: Name -> HEnv -> Value
sEnv n [] = VError
sEnv n (x : xs)
    | fst x == n = snd x
    | otherwise = sEnv n xs

vAdd :: Value -> Value -> Value
vAdd (VInt x) (VInt y) = VInt (x + y)
vAdd (VBool b) (VBool v) = VBool (b || v) -- Am adăugat eu un plus ca operator între operații de tip Bool
vAdd _ _ = VError

evaluate :: Value -> Value -> Value
evaluate (VFun f) eval = f eval

hEval :: Hask -> DomHask
hEval HTrue _ = VBool True
hEval HFalse _ = VBool False
hEval (HLit x) _ = VInt x
hEval (HVar n) e = sEnv n e
hEval (HIf c t f) e
    | eval == VBool True = hEval t e
    | otherwise = hEval f e
    where eval = hEval c e
hEval (x :==: y) e = VBool (fEval == sEval)
    where
        fEval = hEval x e
        sEval = hEval y e
hEval (x :+: y) e = vAdd fEval sEval
    where
        fEval = hEval x e
        sEval = hEval y e
hEval (HLam n h) e = evaluate f eval
    where
        f = sEnv n e
        eval = hEval h e
hEval (x :$: y) e = evaluate fEval sEval
    where
        fEval = hEval x e
        sEval = hEval y e

data Value = VBool Bool
 | VInt Int
 | VFun (Value -> Value)
 | VError -- pentru reprezentarea erorilor
type HEnv = [(Name, Value)]

type DomHask = HEnv -> Value

instance Show Value where
    show (VBool b) = show b
    show (VInt v) = show v
    show (VFun _) = "Function..."
    show VError = "Error..."

instance Eq Value where
    VBool b == VBool v = b == v
    VInt x == VInt y = x == y
    VInt _ == VBool _ = False
    VBool _ == VInt _ = False
    _ == _ = error "Can't check for equality..."
