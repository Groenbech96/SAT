// Implementation file for parser generated by fsyacc
module PreLogicParser
#nowarn "64";; // turn off warnings that type variables used in production annotations are instantiated to concrete type
open Microsoft.FSharp.Text.Lexing
open Microsoft.FSharp.Text.Parsing.ParseHelpers
# 1 "PreLogicParser.fsp"

open PreLogicTypes

# 10 "PreLogicParser.fs"
// This type is the type of tokens accepted by the parser
type token = 
  | EOF
  | LPAR
  | RPAR
  | NEGATION
  | IMPLICATION
  | BIIMPLICATION
  | AND
  | OR
  | VAR of (string)
// This type is used to give symbolic names to token indexes, useful for error messages
type tokenId = 
    | TOKEN_EOF
    | TOKEN_LPAR
    | TOKEN_RPAR
    | TOKEN_NEGATION
    | TOKEN_IMPLICATION
    | TOKEN_BIIMPLICATION
    | TOKEN_AND
    | TOKEN_OR
    | TOKEN_VAR
    | TOKEN_end_of_input
    | TOKEN_error
// This type is used to give symbolic names to token indexes, useful for error messages
type nonTerminalId = 
    | NONTERM__startstart
    | NONTERM_start
    | NONTERM_logic

// This function maps tokens to integer indexes
let tagOfToken (t:token) = 
  match t with
  | EOF  -> 0 
  | LPAR  -> 1 
  | RPAR  -> 2 
  | NEGATION  -> 3 
  | IMPLICATION  -> 4 
  | BIIMPLICATION  -> 5 
  | AND  -> 6 
  | OR  -> 7 
  | VAR _ -> 8 

// This function maps integer indexes to symbolic token ids
let tokenTagToTokenId (tokenIdx:int) = 
  match tokenIdx with
  | 0 -> TOKEN_EOF 
  | 1 -> TOKEN_LPAR 
  | 2 -> TOKEN_RPAR 
  | 3 -> TOKEN_NEGATION 
  | 4 -> TOKEN_IMPLICATION 
  | 5 -> TOKEN_BIIMPLICATION 
  | 6 -> TOKEN_AND 
  | 7 -> TOKEN_OR 
  | 8 -> TOKEN_VAR 
  | 11 -> TOKEN_end_of_input
  | 9 -> TOKEN_error
  | _ -> failwith "tokenTagToTokenId: bad token"

/// This function maps production indexes returned in syntax errors to strings representing the non terminal that would be produced by that production
let prodIdxToNonTerminal (prodIdx:int) = 
  match prodIdx with
    | 0 -> NONTERM__startstart 
    | 1 -> NONTERM_start 
    | 2 -> NONTERM_logic 
    | 3 -> NONTERM_logic 
    | 4 -> NONTERM_logic 
    | 5 -> NONTERM_logic 
    | 6 -> NONTERM_logic 
    | 7 -> NONTERM_logic 
    | 8 -> NONTERM_logic 
    | _ -> failwith "prodIdxToNonTerminal: bad production index"

let _fsyacc_endOfInputTag = 11 
let _fsyacc_tagOfErrorTerminal = 9

// This function gets the name of a token as a string
let token_to_string (t:token) = 
  match t with 
  | EOF  -> "EOF" 
  | LPAR  -> "LPAR" 
  | RPAR  -> "RPAR" 
  | NEGATION  -> "NEGATION" 
  | IMPLICATION  -> "IMPLICATION" 
  | BIIMPLICATION  -> "BIIMPLICATION" 
  | AND  -> "AND" 
  | OR  -> "OR" 
  | VAR _ -> "VAR" 

// This function gets the data carried by a token as an object
let _fsyacc_dataOfToken (t:token) = 
  match t with 
  | EOF  -> (null : System.Object) 
  | LPAR  -> (null : System.Object) 
  | RPAR  -> (null : System.Object) 
  | NEGATION  -> (null : System.Object) 
  | IMPLICATION  -> (null : System.Object) 
  | BIIMPLICATION  -> (null : System.Object) 
  | AND  -> (null : System.Object) 
  | OR  -> (null : System.Object) 
  | VAR _fsyacc_x -> Microsoft.FSharp.Core.Operators.box _fsyacc_x 
let _fsyacc_gotos = [| 0us; 65535us; 1us; 65535us; 0us; 1us; 7us; 65535us; 0us; 2us; 10us; 4us; 11us; 5us; 12us; 6us; 13us; 7us; 14us; 8us; 15us; 9us; |]
let _fsyacc_sparseGotoTableRowOffsets = [|0us; 1us; 3us; |]
let _fsyacc_stateToProdIdxsTableElements = [| 1us; 0us; 1us; 0us; 5us; 1us; 2us; 3us; 4us; 5us; 1us; 1us; 5us; 2us; 2us; 3us; 4us; 5us; 5us; 2us; 3us; 3us; 4us; 5us; 5us; 2us; 3us; 4us; 4us; 5us; 5us; 2us; 3us; 4us; 5us; 5us; 5us; 2us; 3us; 4us; 5us; 6us; 5us; 2us; 3us; 4us; 5us; 7us; 1us; 2us; 1us; 3us; 1us; 4us; 1us; 5us; 1us; 6us; 1us; 7us; 1us; 7us; 1us; 8us; |]
let _fsyacc_stateToProdIdxsTableRowOffsets = [|0us; 2us; 4us; 10us; 12us; 18us; 24us; 30us; 36us; 42us; 48us; 50us; 52us; 54us; 56us; 58us; 60us; 62us; |]
let _fsyacc_action_rows = 18
let _fsyacc_actionTableElements = [|3us; 32768us; 1us; 15us; 3us; 14us; 8us; 17us; 0us; 49152us; 5us; 32768us; 0us; 3us; 4us; 12us; 5us; 13us; 6us; 10us; 7us; 11us; 0us; 16385us; 0us; 16386us; 1us; 16387us; 6us; 10us; 2us; 16388us; 6us; 10us; 7us; 11us; 3us; 16389us; 4us; 12us; 6us; 10us; 7us; 11us; 0us; 16390us; 5us; 32768us; 2us; 16us; 4us; 12us; 5us; 13us; 6us; 10us; 7us; 11us; 3us; 32768us; 1us; 15us; 3us; 14us; 8us; 17us; 3us; 32768us; 1us; 15us; 3us; 14us; 8us; 17us; 3us; 32768us; 1us; 15us; 3us; 14us; 8us; 17us; 3us; 32768us; 1us; 15us; 3us; 14us; 8us; 17us; 3us; 32768us; 1us; 15us; 3us; 14us; 8us; 17us; 3us; 32768us; 1us; 15us; 3us; 14us; 8us; 17us; 0us; 16391us; 0us; 16392us; |]
let _fsyacc_actionTableRowOffsets = [|0us; 4us; 5us; 11us; 12us; 13us; 15us; 18us; 22us; 23us; 29us; 33us; 37us; 41us; 45us; 49us; 53us; 54us; |]
let _fsyacc_reductionSymbolCounts = [|1us; 2us; 3us; 3us; 3us; 3us; 2us; 3us; 1us; |]
let _fsyacc_productionToNonTerminalTable = [|0us; 1us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; |]
let _fsyacc_immediateActions = [|65535us; 49152us; 65535us; 16385us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 16391us; 16392us; |]
let _fsyacc_reductions ()  =    [| 
# 123 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
                      raise (Microsoft.FSharp.Text.Parsing.Accept(Microsoft.FSharp.Core.Operators.box _1))
                   )
                 : '_startstart));
# 132 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 33 "PreLogicParser.fsp"
                                           _1 
                   )
# 33 "PreLogicParser.fsp"
                 : logic));
# 143 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 36 "PreLogicParser.fsp"
                                             And(_1,_3) 
                   )
# 36 "PreLogicParser.fsp"
                 : logic));
# 155 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 37 "PreLogicParser.fsp"
                                            Or(_1,_3) 
                   )
# 37 "PreLogicParser.fsp"
                 : logic));
# 167 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 38 "PreLogicParser.fsp"
                                                   Imp(_1,_3) 
                   )
# 38 "PreLogicParser.fsp"
                 : logic));
# 179 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 39 "PreLogicParser.fsp"
                                                     Bi(_1,_3) 
                   )
# 39 "PreLogicParser.fsp"
                 : logic));
# 191 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _2 = (let data = parseState.GetInput(2) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 40 "PreLogicParser.fsp"
                                            Neg(_2)
                   )
# 40 "PreLogicParser.fsp"
                 : logic));
# 202 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _2 = (let data = parseState.GetInput(2) in (Microsoft.FSharp.Core.Operators.unbox data : logic)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 41 "PreLogicParser.fsp"
                                             Par(_2) 
                   )
# 41 "PreLogicParser.fsp"
                 : logic));
# 213 "PreLogicParser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 42 "PreLogicParser.fsp"
                                                  Var(_1)
                   )
# 42 "PreLogicParser.fsp"
                 : logic));
|]
# 225 "PreLogicParser.fs"
let tables () : Microsoft.FSharp.Text.Parsing.Tables<_> = 
  { reductions= _fsyacc_reductions ();
    endOfInputTag = _fsyacc_endOfInputTag;
    tagOfToken = tagOfToken;
    dataOfToken = _fsyacc_dataOfToken; 
    actionTableElements = _fsyacc_actionTableElements;
    actionTableRowOffsets = _fsyacc_actionTableRowOffsets;
    stateToProdIdxsTableElements = _fsyacc_stateToProdIdxsTableElements;
    stateToProdIdxsTableRowOffsets = _fsyacc_stateToProdIdxsTableRowOffsets;
    reductionSymbolCounts = _fsyacc_reductionSymbolCounts;
    immediateActions = _fsyacc_immediateActions;
    gotos = _fsyacc_gotos;
    sparseGotoTableRowOffsets = _fsyacc_sparseGotoTableRowOffsets;
    tagOfErrorTerminal = _fsyacc_tagOfErrorTerminal;
    parseError = (fun (ctxt:Microsoft.FSharp.Text.Parsing.ParseErrorContext<_>) -> 
                              match parse_error_rich with 
                              | Some f -> f ctxt
                              | None -> parse_error ctxt.Message);
    numTerminals = 12;
    productionToNonTerminalTable = _fsyacc_productionToNonTerminalTable  }
let engine lexer lexbuf startState = (tables ()).Interpret(lexer, lexbuf, startState)
let start lexer lexbuf : logic =
    Microsoft.FSharp.Core.Operators.unbox ((tables ()).Interpret(lexer, lexbuf, 0))
