
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

let rec RemoveBiAndImp prop = 
    match prop with
    |Bi(a,b) -> And(Or(RemoveBiAndImp a,Neg(RemoveBiAndImp b)),Or(Neg(RemoveBiAndImp a),RemoveBiAndImp b))
    |Imp(a,b) -> Or(Neg(RemoveBiAndImp a),RemoveBiAndImp b)
    |_ -> prop

let rec DistributeAndOverOr stepOneDone =
    match stepOneDone with
    |Bi(_,_) -> failwith "Not done RemoveBI/imp"
    |Imp(_,_) -> failwith "Not done RemoveBI/imp"
    |Or(a,b) -> match b with
                |And(c,d) -> And(Or(DistributeAndOverOr a, DistributeAndOverOr c), Or(DistributeAndOverOr a, DistributeAndOverOr d))
                |_ -> match a with
                      |And(c,d) -> And(Or(DistributeAndOverOr b, DistributeAndOverOr c), Or(DistributeAndOverOr b, DistributeAndOverOr d))
                      |_ -> stepOneDone         
    |_ -> stepOneDone


let PropToCNF prop =
    let stepOne = RemoveBiAndImp prop
    printfn "stepOne: %A" stepOne
    DistributeAndOverOr stepOne 



// We
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
        printfn "%A" (PropToCNF e)
        printfn "ok"
        compute n
        //compute n
        with err -> printfn "ko"; compute (n-1)

// Start interacting with the user
compute 3

