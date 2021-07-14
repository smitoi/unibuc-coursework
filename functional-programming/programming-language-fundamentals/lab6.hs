module Checker where

import Data.Map.Strict (Map)
import qualified Data.Map.Strict as Map

import SIMPLE

data Type = TInt | TBool
  deriving (Eq)

instance Show Type where
    show TInt = "int"
    show TBool = "bool"

type CheckerState = Map Name Type

emptyCheckerState :: CheckerState
emptyCheckerState = Map.empty

newtype EReader a =
    EReader { runEReader :: CheckerState ->  (Either String a) }

throwError :: String -> EReader a
throwError e = EReader (\_ -> (Left e))

instance Monad EReader where
    return a = EReader (\env ->  Right a)
    act >>= k = EReader  f
                where
                 f env  = case (runEReader act env) of
                           Left s -> Left s
                           Right va -> runEReader (k va) env

instance Functor EReader where
    fmap f ma = do { a <- ma; return (f a) }

instance Applicative EReader where
    pure = return
    mf <*> ma = do { f <- mf; a <- ma; return (f a)}

askEReader :: EReader CheckerState
askEReader = EReader (\env -> Right env)

localEReader :: (CheckerState -> CheckerState) -> EReader a -> EReader a
localEReader f ma = EReader (\env -> (runEReader ma) (f env))

type M = EReader

expect :: (Show t, Eq t, Show e) => t -> t -> e -> M ()
expect tExpect tActual e =
    if (tExpect /= tActual)
    then     (throwError
        $ "Type mismatch. Expected " <> show tExpect <> " but got " <> show tActual
        <> " for " <> show e)
    else (return ())

lookup' :: Name -> M Type
lookup' name = do
    env <- askEReader
    case (Map.lookup name env) of
        Nothing -> throwError $ "Variable " <> name <> " not declared"
        Just t -> return t

checkExp :: Exp -> M Type
checkExp (Id name) = lookup' name -- var
checkExp (I _) = return TInt -- int
checkExp (B _) = return TBool -- bool
checkExp (UMin e) = do -- -()
    t <- checkExp e
    expect TInt t e
    return TInt
checkExp (BinA _ e1 e2) = do -- +, -, *, /, %
    t1 <- checkExp e1
    t2 <- checkExp e2
    expect TInt t1 e1
    expect TInt t2 e2
    return TInt
checkExp (BinC _ e1 e2) = do -- <, <=, >, >=
    t1 <- checkExp e1
    t2 <- checkExp e2
    expect TInt t1 e1
    expect TInt t2 e2
    return TInt
checkExp (BinE _ e1 e2) = do -- ==, !=
    t1 <- checkExp e1
    t2 <- checkExp e2
    expect t2 t1 e1
    expect t1 t2 e2
    return TBool
checkExp (BinL _ e1 e2) = do -- &&, ||
    t1 <- checkExp e1
    t2 <- checkExp e2
    expect TBool t1 e1
    expect TBool t2 e2
    return TBool
checkExp (Not e) = do -- !
    t <- checkExp e
    expect TBool t e
    return TBool

checkStmt :: Stmt -> M ()
checkStmt (Decl _ _) = return()
checkStmt (Read _ _) = return()
checkStmt (Print _ _) = return()
checkStmt (Asgn x e) = do
    tx <- lookup' x
    te <- checkExp e
    expect tx te e
checkStmt (If e s1 s2) = do
    te <- checkExp e
    expect TBool te e
    checkStmt s1
    checkStmt s2
checkStmt (While e s) = do
    te <- checkExp e
    expect TBool te e
    checkStmt s
checkStmt (Block stmt) = checkBlock stmt
    

checkBlock :: [Stmt] -> M ()
checkBlock [] = return ()
checkBlock (Decl name exp : xs) = do
    curr <- checkExp exp
    localEReader (Map.insert name curr) (checkBlock xs)
checkBlock (x : xs) = checkStmt x >> checkBlock xs

checkPgm :: [Stmt] -> Bool
checkPgm pgm =
    case  (runEReader (checkBlock pgm)) emptyCheckerState of
        Left err -> error err
        Right _ -> True

testStmt :: Stmt -> Bool
testStmt stmt = case  (runEReader (checkStmt stmt)) emptyCheckerState of
        Left err -> error err
        Right _ -> True