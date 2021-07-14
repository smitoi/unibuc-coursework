--- Monada Identity

newtype Identity a = Identity { runIdentity :: a }

instance (Show a) => Show (Identity a) where
    show = show . runIdentity

instance Monad Identity where
    return va = Identity va
    ma >>= k = k $ runIdentity ma

instance Applicative Identity where
    pure = Identity
    mf <*> ma = do
      f <- mf
      va <- ma
      return (f va) 

instance Functor Identity where
  fmap f ma = pure f <*> ma  

--- Limbajul si  Interpretorul

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
  deriving (Show)

data Value = Num Integer
           | Fun (Value -> M Value)
           | Wrong

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"
 show Wrong   = "<wrong>"

type Environment = [(Name, Value)]

---------------------------------------------------------
-- Cu Identity
-- type M = Identity

-- showM :: Show a => M a -> String
-- showM = show

-- unjust :: Maybe a -> a
-- unjust (Just v) = v
-- unjust _ = error "Undefned variable..."

-- add :: Value -> Value -> M Value
-- add (Num x) (Num y) = return $ Num $ x + y
-- add _ _ = return Wrong

-- interp :: Term -> Environment -> M Value
-- interp (Var n) e = return $ unjust $ lookup n e
-- interp (Con v) _ = return $ Num v
-- interp (x :+: y) e = add x' y'
--     where
--         x' = runIdentity $ interp x e
--         y' = runIdentity $ interp y e
-- interp (Lam n x) e = return $ Fun $ \y -> interp x ((n, y) : e)
-- interp (App x y) e = app x' y'
--     where
--         x' = runIdentity $ interp x e
--         y' = runIdentity $ interp y e
--         app (Fun f) x = f x
--         app _ _ = return Wrong
---------------------------------------------------------

---------------------------------------------------------
-- Cu Maybe
-- type M = Maybe

-- showM :: Show a => M a -> String
-- showM (Just x) = show x
-- showM Nothing = error "Nothing encountered..."

-- unjust :: Maybe a -> a
-- unjust (Just v) = v
-- unjust _ = error "Undefned variable..."

-- add :: Value -> Value -> M Value
-- add (Num x) (Num y) = return $ Num $ x + y
-- add _ _ = return Wrong

-- interp :: Term -> Environment -> M Value
-- interp (Var n) e = return $ unjust $ lookup n e
-- interp (Con v) _ = return $ Num v
-- interp (x :+: y) e = add x' y'
--     where
--         x' = unjust $ interp x e
--         y' = unjust $ interp y e
-- interp (Lam n x) e = return $ Fun $ \y -> interp x ((n, y) : e)
-- interp (App x y) e = app x' y'
--     where
--         x' = unjust $ interp x e
--         y' = unjust $ interp y e
--         app (Fun f) x = f x
--         app _ _ = return Wrong
---------------------------------------------------------

---------------------------------------------------------
-- Cu Either
-- type M = Either String

-- showM :: Show a => M a -> String
-- showM (Right v) = show v
-- showM (Left v) = show v

-- unjust :: Maybe a -> a
-- unjust (Just v) = v
-- unjust _ = error "Undefined variable..."

-- add :: Value -> Value -> M Value
-- add (Num x) (Num y) = return $ Num $ x + y
-- add _ _ = Left "Undefined error in add..."

-- interp :: Term -> Environment -> M Value
-- interp (Var n) e = unjust x n
--     where
--         x = lookup n e
--         unjust (Just v) n = return v
--         unjust Nothing n = Left $ "Undefined variable" ++ n
-- interp (Con v) _ = return $ Num v
-- interp (x :+: y) e = do
--     x' <- interp x e
--     y' <- interp y e
--     add x' y'
-- interp (Lam n x) e = return $ Fun $ \y -> interp x ((n, y) : e)
-- interp (App x y) e = do
--     x' <- interp x e
--     y' <- interp y e
--     app x' y'
--     where
--         app (Fun f) x = f x
--         app _ _ = Left "Undefined error in apply..."
---------------------------------------------------------

---------------------------------------------------------
-- Cu listă
-- type M a = [a]

-- data Term = Var Name
--           | Con Integer
--           | Term :+: Term
--           | Lam Name Term
--           | App Term Term
--           | Fail
--           | Amb Term Term
--   deriving (Show)

-- showM :: Show a => M a -> String
-- showM = show

-- unjust :: Maybe a -> a
-- unjust (Just v) = v
-- unjust _ = error "Undefined variable..."

-- add :: Value -> Value -> M Value
-- add (Num x) (Num y) = return $ Num $ x + y
-- add _ _ = return Wrong

-- interp :: Term -> Environment -> M Value
-- interp (Var n) e = return $ unjust $ lookup n e
-- interp (Con v) _ = return $ Num v
-- interp (x :+: y) e = do
--     x' <- interp x e
--     y' <- interp y e
--     add x' y'
-- interp (Lam n x) e = return $ Fun $ \y -> interp x ((n, y) : e)
-- interp (App x y) e = do
--     x' <- interp x e
--     y' <- interp y e
--     app x' y'
--     where
--         app (Fun f) x = f x
--         app _ _ = return Wrong
-- interp (Fail) e = return Wrong
-- interp (Amb x x') e = do
--     y <- interp x e
--     y' <- interp x' e
--     y : [y']

-- pgm2 :: Term
-- pgm2 = App (Lam "x" (Var "x" :+: Var "x")) (Amb (Con 1) (Con 2))
---------------------------------------------------------

---------------------------------------------------------
-- Cu EnvReader
-- newtype EnvReader a = Reader { runEnvReader :: Environment -> a }
-- type M a = EnvReader a

-- instance Functor EnvReader where
--   fmap f ma = pure f <*> ma  

-- instance Applicative EnvReader where
--     pure = return
--     mf <*> ma = do
--       f <- mf
--       va <- ma
--       return (f va) 

-- instance Monad EnvReader where
--     return a = Reader $ \_ -> a
--     ma >>= k = Reader f
--       where f env = let a = runEnvReader ma env
--                     in  runEnvReader (k a) env

-- instance Show a => Show (EnvReader a) where
--     show (Reader k) = show $ k []

-- showM :: Show a => M a -> String
-- showM = show

-- unjust :: Maybe a -> a
-- unjust (Just v) = v
-- unjust _ = error "Undefined variable..."

-- add :: Value -> Value -> M Value
-- add (Num x) (Num y) = return $ Num $ x + y
-- add _ _ = return Wrong

-- ask :: EnvReader Environment
-- ask = Reader id

-- local :: (Environment -> Environment) -> EnvReader a -> EnvReader a
-- local f ma = Reader $ runEnvReader ma . f

-- interp :: Term -> M Value
-- interp (Var n) = unjust . lookup n <$> ask -- am scris-o așa cu ajutorul IDE-ului
-- interp (Con v) = return $ Num v
-- interp (x :+: y)= do
--     x' <- interp x
--     y' <- interp y
--     add x' y'
-- -- interp (Lam n x) = do
-- --   env <- ask
-- --   return (Fun $ \y -> local (const ((n, y) : env)) (interp x))
-- interp (Lam n x) = ask >>= \env -> return (Fun $ \y -> local (\_ -> ((n, y) : env)) (interp x))
-- interp (App x y) = do
--     x' <- interp x
--     y' <- interp y
--     app x' y'
--     where
--         app (Fun f) x = f x
--         app _ _ = error "Undefined error in apply..."
---------------------------------------------------------

---------------------------------------------------------
-- Cu StringWriter
-- newtype StringWriter a = StringWriter { runStringWriter :: (a, String) }
-- type M a = StringWriter a

-- instance Functor StringWriter where
--     fmap f ma = f <$> ma
    
-- instance Applicative StringWriter where
--     pure = return
--     mf <*> ma = do 
--       f <- mf
--       f <$> ma

-- instance Monad StringWriter where
--     return a = StringWriter (a, mempty)
--     ma >>= k = let (v, log) = runStringWriter ma
--                    (v', log') = runStringWriter $ k v
--                 in  StringWriter (v', log ++ log')

-- instance (Show a) => Show (StringWriter a) where
--   show (StringWriter (v, log)) = "Output: " ++ log ++ "Value: " ++ show v

-- data Term = Var Name
--           | Con Integer
--           | Term :+: Term
--           | Lam Name Term
--           | App Term Term
--           | Out Term
--   deriving (Show)

-- tell :: String -> StringWriter () 
-- tell log = StringWriter ((), log)

-- showM :: Show a => M a -> String
-- showM = show

-- unjust :: Maybe a -> a
-- unjust (Just v) = v
-- unjust _ = error "Undefined variable..."

-- add :: Value -> Value -> M Value
-- add (Num x) (Num y) = return $ Num $ x + y
-- add _ _ = return Wrong

-- interp :: Term -> Environment -> M Value
-- interp (Var n) e = return $ unjust $ lookup n e
-- interp (Con v) _ = return $ Num v
-- interp (x :+: y) e = do
--       x' <- interp x e
--       y' <- interp y e
--       add x' y'
-- interp (Lam n x) e = return $ Fun $ \y -> interp x ((n, y) : e)
-- interp (App x y) e = do
--       x' <- interp x e
--       y' <- interp y e
--       app x' y'
--         where
--           app (Fun f) x = f x
--           app _ _ = return Wrong
-- interp (Out x) e = do
--   o <- interp x e
--   tell $ show o ++ "; "
--   return o
---------------------------------------------------------

---------------------------------------------------------
-- Cu State
-- newtype IntState a = IntState { runIntState :: Integer -> (a, Integer) }
-- type M a = IntState a

-- instance Functor IntState where
--   fmap f ma = pure f <*> ma  

-- instance Applicative IntState where
--     pure = return
--     mf <*> ma = do
--       f <- mf
--       va <- ma
--       return (f va)     

-- instance Monad IntState where
--     return a = IntState $ \s -> (a, s)
--     ma >>= k = IntState f
--       where f s = let (a, s') = runIntState ma s
--                   in runIntState (k a) s'

-- instance Show a => Show (IntState a) where
--     show ma = "Value: " ++ show v ++ "; " ++ "Count: " ++ show s
--       where (v, s) = runIntState ma 0

-- data Term = Var Name
--           | Con Integer
--           | Term :+: Term
--           | Lam Name Term
--           | App Term Term
--           | Count
--   deriving (Show)

-- showM :: Show a => M a -> String
-- showM = show

-- unjust :: Maybe a -> a
-- unjust (Just v) = v
-- unjust _ = error "Undefined variable..."

-- add :: Value -> Value -> M Value
-- add (Num x) (Num y) = return $ Num $ x + y
-- add _ _ = return Wrong

-- modify :: (Integer -> Integer) -> IntState ()
-- modify f = IntState (\s -> ((), f s))

-- get :: IntState Integer
-- get = IntState (\s -> (s, s))

-- tickS :: IntState ()
-- tickS = modify (+ 1)

-- interp :: Term -> Environment -> M Value
-- interp (Var n) e = return $ unjust $ lookup n e
-- interp (Con v) _ = return $ Num v
-- interp (Count) _ = do
--   Num <$> get
-- interp (x :+: y) e = do
--       x' <- interp x e
--       y' <- interp y e
--       tickS
--       add x' y'
-- interp (Lam n x) e = return $ Fun $ \y -> interp x ((n, y) : e)
-- interp (App x y) e = do
--       x' <- interp x e
--       y' <- interp y e
--       tickS
--       app x' y'
--         where
--           app (Fun f) x = f x
--           app _ _ = return Wrong
---------------------------------------------------------

-- Test
-- test :: Term -> String
-- test t = showM $ interp t []

-- Test pentru Reader (fără environment)
testR :: Term -> String
testR t = showM $ interp t

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)

pgm1:: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          ((Con 10) :+:  (Con 11))

-- Pentru StringWriter
-- pgm2 :: Term
-- pgm2 = Out (Con 41) :+: Out (Con 1)

pgm3 :: Term
pgm3 = App
        (Lam "x" (Var "x" :+: Var "x"))
        (Con 10 :+: Con 20)

-- pgm4 :: Term
-- pgm4 = ((Con 1 :+: Con 2) :+: Count)
-- test pgm
-- test pgm1
-- test pgm2