import           Prelude hiding (lookup)
import qualified Data.List as List

class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert
      :: Ord key
      => key -> value -> c key value -> c key value
  lookup :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  keys collection = [fst(x) | x <- toList collection]
  values :: c key value -> [value]
  values collection = [snd(x) | x <- toList collection]
  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key,value)] -> c key value
  fromList [] = empty
  fromList (x:xs) =  uncurry insert x $ fromList xs

newtype PairList k v
  = PairList { getPairList :: [(k, v)] }

instance Collection PairList where
  empty = PairList []
  singleton k v = PairList [(k, v)]
  insert k v c = PairList $ getPairList c ++ [(k, v)]
  lookup k c = lookup' k (getPairList c)
      where
        lookup' _ [] = Nothing
        lookup' k (x:xs)
          | k == fst x = Just $ snd x
          | otherwise = lookup' k xs
  delete k c = delete' k (getPairList c) []
    where
      delete' _ [] r = PairList r
      delete' k (x:xs) r
        | k == fst x = PairList $ r ++ xs
        | otherwise = delete' k xs (r ++ [x])
  toList c = getPairList c

data SearchTree key value
  = Empty
  | Node
      (SearchTree key value) -- elemente cu cheia mai mica 
      key                    -- cheia elementului
      (Maybe value)          -- valoarea elementului
      (SearchTree key value) -- elemente cu cheia mai mare

fromJust :: Maybe a -> a
fromJust (Just a) = a
fromJust Nothing = error "Nothing encountered"

instance Collection SearchTree where
  empty = Empty
  singleton k v = Node empty k (Just v) empty
  insert k v t = insert' k v t
    where
      insert' k v Empty = singleton k v
      insert' k v (Node tl tk tv tr)
        | k > tk = Node tl tk tv (insert' k v tr)
        | k < tk = Node (insert' k v tl) tk tv tr
        | otherwise = Node tl tk (Just v) tr
  lookup k t = lookup' k t
    where
      lookup' _ Empty = Nothing
      lookup' k (Node tl tk tv tr)
        | k > tk = lookup' k tr
        | k < tk = lookup' k tl
        | k == tk = tv
  delete k t = delete' k t
    where
      delete' k Empty = Empty
      delete' k (Node tl tk tv tr)
        | k > tk = Node tl tk tv (delete' k tr)
        | k < tk = Node (delete' k tl) tk tv tr
        | otherwise = Node tl tk Nothing tr
  toList t = toList' t
    where
      toList' Empty = []
      toList' (Node tl tk tv tr) = [(tk, fromJust tv)] ++ toList' tl ++ toList' tr
  

order = 1

data Element k v
  = Element k (Maybe v)
  | OverLimit

data BTree key value
  = BEmpty
  | BNode [(BTree key value, Element key value)]