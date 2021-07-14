import           Test.QuickCheck hiding (Failure, Success)

semigroupAssoc :: (Eq m, Semigroup m) => m -> m -> m -> Bool
semigroupAssoc a b c = (a <> (b <> c)) == ((a <> b) <> c)

monoidLeftIdentity   :: (Eq m, Monoid m) => m -> Bool
monoidLeftIdentity a = (mempty <> a) == a

monoidRightIdentity   :: (Eq m, Monoid m) => m -> Bool
monoidRightIdentity a = (a <> mempty) == a

-- Example 1 - Trivial
 
data Trivial = Trivial
  deriving (Eq, Show)

instance Semigroup Trivial where
  _ <> _ = Trivial

instance Monoid Trivial where
  mempty  = Trivial

instance Arbitrary Trivial where
  arbitrary = return Trivial

type TrivAssoc = Trivial -> Trivial -> Trivial -> Bool
type TrivId    = Trivial -> Bool

testTrivial :: IO ()
testTrivial
  = do
    quickCheck (semigroupAssoc :: TrivAssoc)
    quickCheck (monoidLeftIdentity :: TrivId)
    quickCheck (monoidRightIdentity :: TrivId)

-- Exercise 2 - Identity
 
newtype Identity a = Identity a
  deriving (Eq, Show)

instance Semigroup a => Semigroup (Identity a) where
  Identity x <> Identity y = Identity $ x <> y

instance Monoid a => Monoid (Identity a) where
  mempty = Identity mempty

instance Arbitrary a => Arbitrary (Identity a) where
  arbitrary = Identity <$> arbitrary

type IdentityAssoc a = Identity a -> Identity a -> Identity a -> Bool
type IdentityId    a = Identity a -> Bool

testIdentity :: IO ()
testIdentity
  = do
    quickCheck (semigroupAssoc :: IdentityAssoc String)
    quickCheck (monoidLeftIdentity :: IdentityId [Int])
    quickCheck (monoidRightIdentity :: IdentityId [Int])

-- Exercise 3 - Pair

data Two a b = Two a b
  deriving (Eq, Show)

instance (Semigroup a, Semigroup b) => Semigroup (Two a b) where
  Two x y <> Two s t = Two (x <> s) (y <> t)

instance (Monoid a, Monoid b) => Monoid (Two a b) where
  mempty = Two mempty mempty

instance (Arbitrary a, Arbitrary b) => Arbitrary (Two a b) where
  arbitrary = fmap Two arbitrary <*> arbitrary

type PairAssoc a b = Two a b -> Two a b -> Two a b -> Bool
type PairId    a b = Two a b -> Bool

testPair :: IO ()
testPair
    = do
        quickCheck (semigroupAssoc :: PairAssoc [Int] [Int])
        quickCheck (monoidLeftIdentity :: PairId [Int] [Int])
        quickCheck (monoidRightIdentity :: PairId String String)

-- Exercise 4 - Triple
 
data Three a b c = Three a b c
  deriving (Eq, Show)

instance (Semigroup a, Semigroup b, Semigroup c) => Semigroup (Three a b c) where
  Three x y z <> Three x' y' z' = Three (x <> x') (y <> y') (z <> z')

instance (Monoid a, Monoid b, Monoid c) => Monoid (Three a b c) where
  mempty = Three mempty mempty mempty

instance ( Arbitrary a
         , Arbitrary b
         , Arbitrary c
         ) => Arbitrary (Three a b c) where
  arbitrary = fmap Three arbitrary <*> arbitrary <*> arbitrary

type TripleAssoc a b c = Three a b c -> Three a b c -> Three a b c -> Bool
type TripleId a b c = Three a b c -> Bool

testThree :: IO ()
testThree
    = do
        quickCheck (semigroupAssoc :: TripleAssoc String String String)
        quickCheck (monoidLeftIdentity :: TripleId String String String)
        quickCheck (monoidRightIdentity :: TripleId String String String)

-- Exercise 5 - Boolean conjunction
-- SAME
newtype BoolConj = BoolConj Bool
  deriving (Eq, Show)

instance Arbitrary BoolConj where
  arbitrary = BoolConj <$> arbitrary

-- Exercise 6 - Boolean disjunction
-- SAME
newtype BoolDisj = BoolDisj Bool
  deriving (Eq, Show)

instance Arbitrary BoolDisj where
  arbitrary = BoolDisj <$> arbitrary

-- Exercise 7 - Or

data Or a b = Fst a | Snd b
  deriving (Eq, Show)

instance (Semigroup a, Semigroup b) => Semigroup (Or a b) where
  Snd x <> _ = Snd x
  Fst _ <> Snd x = Snd x
  Fst _ <> Fst x = Fst x

instance (Monoid a, Monoid b) => Monoid (Or a b) where
  -- Wrong
  mempty = Snd mempty

instance (Arbitrary a, Arbitrary b) => Arbitrary (Or a b) where
  arbitrary = oneof [Fst <$> arbitrary, Snd <$> arbitrary]

type OrAssoc a b = Or a b -> Or a b -> Or a b -> Bool
type OrId a b = Or a b -> Bool

testOr :: IO ()
testOr
    = do
        quickCheck (semigroupAssoc :: OrAssoc String String)
        -- Can't instance monoid for OR
        --quickCheck (monoidLeftIdentity :: OrId String String)
        --quickCheck (monoidRightIdentity :: OrId String String)


-- Exercise 8 - Lifting Monoid to Functions
 
newtype Combine a b = Combine { unCombine :: a -> b }

instance (Semigroup a, Semigroup b) => Semigroup (Combine a b) where
   Combine f <> Combine g = Combine h
    where
        h x = f x <> g x

instance (Monoid a, Monoid b) => Monoid (Combine a b) where
    mempty = Combine $ const mempty

instance (CoArbitrary a, Arbitrary b) => Arbitrary (Combine a b) where
  arbitrary = Combine <$> arbitrary

f = Combine $ \n -> Sum (n + 1)
g = Combine $ \n -> Sum (n - 1)

newtype Sum a = Sum { getSum :: a }
    deriving (Eq, Read, Show)

instance Num a => Semigroup (Sum a) where
    Sum x <> Sum y = Sum (x + y)

instance Num a => Monoid (Sum a) where
    mempty = Sum 0