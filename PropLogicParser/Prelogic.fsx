
// We need to import a couple of modules, including the generated lexer and parser
#r "FsLexYacc.Runtime.7.0.6/lib/portable-net45+netcore45+wpa81+wp8+MonoAndroid10+MonoTouch10/FsLexYacc.Runtime.dll"
open Microsoft.FSharp.Text.Lexing
open System
open System.IO
#load "PreLogicTypes.fs"
open PreLogicTypes
#load "PreLogicParser.fs"
open PreLogicParser
#load "PreLogicLexer.fs"
open PreLogicLexer

//
//  Convert propositional logic to CNF
//

let rec RemoveBiAndImp prop = 
    match prop with
    | Bi(a,b) -> And(
                    Or(RemoveBiAndImp a,Neg(RemoveBiAndImp b)),
                    Or(Neg(RemoveBiAndImp a),RemoveBiAndImp b))
    | Imp(a,b) -> Or(Neg(RemoveBiAndImp a),RemoveBiAndImp b)
    | _ -> prop

let rec MoveNegationsInward prop =
    match prop with
    | Neg(a) -> match a with
                | Par(b) -> MoveNegationsInward (Neg(b))
                | Or(b,c) -> Or(MoveNegationsInward (Neg(b)), MoveNegationsInward (Neg(c)))
                | And(b,c) -> And(MoveNegationsInward (Neg(b)), MoveNegationsInward (Neg(c)))
                | Neg(b) -> MoveNegationsInward b
                | _ -> prop
    | _ -> prop

let rec Distribute prop =
    match prop with
    |Bi(_,_) -> failwith "Not done RemoveBI/imp"
    |Imp(_,_) -> failwith "Not done RemoveBI/imp"
    |Or(a,b) -> match a with
                | Var(k)    -> match b with
                               | And(c,d)   -> And(Distribute (Or(Distribute a, Distribute c)), 
                                                   Distribute (Or(Distribute a, Distribute d)))
                               | Par(c)     -> Distribute (Or(a,c))
                               | _          -> prop
                | And(c,d)  -> match b with
                               | Var(k)     -> And(Distribute (Or(Distribute b, Distribute c)), 
                                                   Distribute (Or(Distribute b, Distribute d)))
                               | Par(e)     -> Distribute (Or(a,e))
                               | _          -> prop
                | Or(c,d)   -> match b with
                               | And(e,f)   -> Distribute (Or(c, Distribute (Or(d,b))))
                               | Var(g)     -> Distribute (Or((Distribute a), b))
                               | Par(c)     -> Distribute (Or(a,c))
                               | _          -> prop
                | Par(c)    -> Distribute (Or(c,b))
                | _         -> prop    

    | Par(a) -> Distribute a
    |_ -> prop


let PropToCNF prop =
    let stepOne = RemoveBiAndImp prop
    let stepTwo = MoveNegationsInward stepOne
    let stepThree = Distribute stepTwo 
    printfn "stepOne: %A" stepOne
    printfn "stepTwo: %A" stepTwo
    stepThree

//
// Build string for CNF-file
//

let rec stringBuilderClause vars s =
    match s with
    | Or(a,b)   -> let (s1, v1) = stringBuilderClause vars a
                   let (s2, v2) = stringBuilderClause v1 b
                   (s1 + s2, Set.union v1 v2)
    | Var(a)    -> (a + " ", Set.empty.Add a)
    | Neg(a)    -> let (s1, v1) = stringBuilderClause vars a
                   let s2 = "-" + s1
                   (s2, v1)
    | _         -> failwith("string clause failed")

let rec stringBuilder sarray vars s =
    match s with
    | And(a,b)                  -> let (s1, v1) = stringBuilder sarray vars a
                                   let (s2, v2) = stringBuilder s1 v1 b
                                   (s1@s2, Set.union v1 v2)
    | Or(_) | Var(_) | Neg(_)   -> let (s1, v1) = stringBuilderClause vars s
                                   let s2 = s1 + "0\n"
                                   ([s2], v1)
    | _                         -> failwith("string failed")


let cnfToString s =
    let (s,v) = stringBuilder [] Set.empty s
    let ls = List.length s
    let lv = Seq.length v
    let sHeader = "p cnf" + " " + string lv + " " + string ls + "\n"
    let s1 = s |> String.Concat
    let s2 = sHeader + s1
    s2


//
// Parse text to propositional logic
//
let parse input =
    // translate string into a buffer of characters
    let lexbuf = LexBuffer<char>.FromString input
    // translate the buffer into a stream of tokens and parse them
    let res = PreLogicParser.start PreLogicLexer.tokenize lexbuf
    // return the result of parsing (i.e. value of type "expr")  
    res


// We implement here the function that interacts with the user
let rec compute n =
    if n = 0 then
        printfn "Bye bye"
    else
        printf "Enter Propositional logic: "
        try 
        // We parse the input string
        let e = parse (Console.ReadLine())

        let cnf = PropToCNF e
        printfn "CNF: %A" cnf

        let s = cnfToString cnf

        File.WriteAllText("test123.txt", s )

        printfn "ok"
        compute n

        with err -> printfn "ko"; compute (n-1)
         
// Start interacting with the user
compute 3

