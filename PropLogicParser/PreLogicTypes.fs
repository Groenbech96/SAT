module PreLogicTypes

type logic = 
    | Var of string
    | Par of logic
    | Neg of logic
    | And of logic * logic
    | Or of logic * logic
    | Imp of logic * logic
    | Bi of logic * logic


type parsetree = 
    | Node of logic * parsetree list







