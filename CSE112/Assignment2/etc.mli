(* $Id: etc.mli,v 1.2 2020-08-17 00:02:07-07 - - $ *)

(*
* Main program and system access.
*)

val warn : string list -> unit

val die : string list -> unit

val syntax_error : Lexing.position -> string list -> unit

val usage_exit : string list -> unit

val read_number : unit -> float

val int_of_round_float : float -> int

