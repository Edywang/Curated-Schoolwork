(* $Id: absyn.mli,v 1.7 2020-09-06 20:49:42-07 - - $ *)

(*
* Abstract syntax definitions for MB.
*)

type linenr    = int
type ident     = string
type label     = string
type oper      = string

type memref    = Arrayref of ident * expr
               | Variable of ident

and  expr      = Number of float
               | Memref of memref
               | Unary of oper * expr
               | Binary of oper * expr * expr

and  relexpr   = Relexpr of oper * expr * expr

type printable = Printexpr of expr
               | String of string

type stmt      = Dim of ident * expr
               | Let of memref * expr
               | Goto of label
               | If of relexpr * label
               | Print of printable list
               | Input of memref list

type progline  = linenr * label option * stmt option

type program   = progline list

