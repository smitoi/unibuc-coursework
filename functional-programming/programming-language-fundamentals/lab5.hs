import Imp
import Text.Parsec (alphaNum, eof, letter, parse, (<|>))
import Text.Parsec.Expr
  ( Assoc (..),
    Operator (..),
    buildExpressionParser,
  )
import Text.Parsec.String (Parser, parseFromFile)
import qualified Text.Parsec.Token as Token
import Text.ParserCombinators.Parsec.Language
  ( GenLanguageDef (..),
    LanguageDef,
    emptyDef,
  )

impLanguageDef :: LanguageDef ()
impLanguageDef =
  emptyDef
    { commentStart = "/*",
      commentEnd = "*/",
      commentLine = "//",
      nestedComments = False,
      caseSensitive = True,
      identStart = letter,
      identLetter = alphaNum,
      reservedNames =
        [ "while",
          "if",
          "else",
          "int",
          "bool",
          "true",
          "false",
          "read",
          "print"
        ],
      reservedOpNames =
        [ "+",
          "-",
          "*",
          "/",
          "%",
          "==",
          "!=",
          "<",
          "<=",
          ">=",
          ">",
          "&&",
          "||",
          "!",
          "="
        ]
    }

impLexer :: Token.TokenParser ()
impLexer = Token.makeTokenParser impLanguageDef

identifier :: Parser String
identifier = Token.identifier impLexer

reserved :: String -> Parser ()
reserved = Token.reserved impLexer

reservedOp :: String -> Parser ()
reservedOp = Token.reservedOp impLexer

parens :: Parser a -> Parser a
parens = Token.parens impLexer

braces :: Parser a -> Parser a
braces = Token.braces impLexer

semiSep :: Parser a -> Parser [a]
semiSep = Token.semiSep impLexer

integer :: Parser Integer
integer = Token.integer impLexer

whiteSpace :: Parser ()
whiteSpace = Token.whiteSpace impLexer

expression :: Parser Exp
expression = buildExpressionParser operators term
  where
    operators =
      [ [ prefix "!" Not
        ],
        [ binary "*" (BinA Mul) AssocLeft
        ],
        [ binary "+" (BinA Add) AssocLeft
        ],
        [ binary "==" (BinE Eq) AssocNone,
          binary "<=" (BinC Lte) AssocNone
        ],
        [ binary "&&" (BinL And) AssocLeft,
          binary "||" (BinL Or) AssocLeft
        ]
      ]
    binary name fun = Infix (reservedOp name >> return fun)
    prefix name fun = Prefix (reservedOp name >> return fun)

term :: Parser Exp
term =
  parens expression
    <|> (I <$> integer)
    <|> (B <$> boolTrue)
    <|> (B <$> boolFalse)
    <|> (Id <$> identifier)

boolTrue :: Parser Bool
boolTrue = do
  reserved "true"
  return True

boolFalse :: Parser Bool
boolFalse = do
  reserved "false"
  return False

ifStmt :: Parser Stmt
ifStmt = do
  reserved "if"
  cond <- parens expression
  thenS <- statement
  reserved "else"
  elseS <- statement
  return (If cond thenS elseS)

whileStmt :: Parser Stmt
whileStmt = do
  reserved "while"
  cond <- parens expression
  whileS <- statement
  return (While cond whileS)

intStmt :: Parser Stmt
intStmt = do
  reserved "int"
  ident <- identifier
  return (Decl TInt ident)

boolStmt :: Parser Stmt
boolStmt = do
  reserved "bool"
  var <- identifier
  return (Decl TBool var)

asgnStmt :: Parser Stmt
asgnStmt = do
  var <- identifier
  reservedOp "="
  exp <- expression
  return (Asgn var exp)

stringLiteral :: Parser String
stringLiteral = Token.stringLiteral impLexer

lineParser :: Parser [Stmt]
lineParser = do
  lines <- semiSep statement
  return lines

statement :: Parser Stmt
statement = ifStmt <|> whileStmt <|> intStmt <|> boolStmt <|> asgnStmt

main = do
  result <- parseFromFile lineParser "main.imp"
  case result of
    Left err -> print err
    Right xs -> print xs