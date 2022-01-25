(* $Id: interp.ml,v 1.11 2020-08-30 14:48:52-07 - - $ *)

open Absyn

exception Unimplemented of string
let no_expr reason = raise (Unimplemented reason)
let no_stmt reason continuation = raise (Unimplemented reason)

let want_dump = ref false

let rec eval_expr (expr : Absyn.expr) : float = match expr with
    | Number number -> number
    | Memref memref -> eval_memref memref
    | Unary (oper, expr) ->
        Hashtbl.find Tables.unary_fn_table oper
            (eval_expr expr)
    | Binary (oper, expr1, expr2) ->
        Hashtbl.find Tables.binary_fn_table oper
            (eval_expr expr1)
            (eval_expr expr2)

and eval_memref (memref : Absyn.memref) : float = match memref with
    | Arrayref (ident, expr) ->
        Array.get (Hashtbl.find Tables.array_table ident)
                  (int_of_float (eval_expr expr))
    | Variable ident -> try Hashtbl.find Tables.variable_table ident
                        with Not_found -> 0.0

let eval_cond (cond : Absyn.relexpr) = match cond with
    | Relexpr (cond, l, r) -> 
        Hashtbl.find Tables.bool_fn_table cond
            (eval_expr l)
            (eval_expr r)

let set_val memref expr=
    (match memref with
        | Arrayref (ident, index) -> Array.set
            (Hashtbl.find Tables.array_table ident)
            (int_of_float (eval_expr index)) (eval_expr expr)
        | Variable ident -> Hashtbl.replace Tables.variable_table
                            ident (eval_expr expr))
 
let rec interpret (program : Absyn.program) = match program with
    | [] -> ()
    | firstline::continuation -> match firstline with
      | _, _, None -> interpret continuation
      | _, _, Some stmt -> (interp_stmt stmt continuation)

and interp_stmt (stmt : Absyn.stmt) (continuation : Absyn.program) =
    match stmt with
    | Dim (ident, expr) -> interp_dim ident expr continuation
    | Let (memref, expr) -> interp_let memref expr continuation
    | Goto label -> interp_goto label continuation
    | If (expr, label) -> interp_if expr label continuation
    | Print print_list -> interp_print print_list continuation
    | Input memref_list -> interp_input memref_list continuation

and interp_dim (ident : Absyn.ident) (expr: Absyn.expr)
               (continuation : Absyn.program) =
    Hashtbl.replace Tables.array_table ident
        (Array.make (int_of_float (eval_expr expr)) 0.0);
    interpret continuation

and interp_let (memref : Absyn.memref) (expr : Absyn.expr)
               (continuation : Absyn.program) = 
   (set_val memref expr;
   interpret continuation)

and interp_goto (label : Absyn.label)
                (continuation : Absyn.program) =
    interpret (Hashtbl.find Tables.label_table label)

and interp_if (cond : Absyn.relexpr) (label : Absyn.label)
                (continuation : Absyn.program) =
    if (eval_cond cond) then interp_goto label continuation
    else interpret continuation

and interp_print (print_list : Absyn.printable list)
                 (continuation : Absyn.program) =
    let print_item item =
        match item with
        | String string ->
          let regex = Str.regexp "\"\\(.*\\)\""
          in print_string (Str.replace_first regex "\\1" string)
        | Printexpr expr ->
          (print_string " "; print_float (eval_expr expr))
     in (List.iter print_item print_list; print_newline ());
     interpret continuation

and interp_input (memref_list : Absyn.memref list)
                 (continuation : Absyn.program)  =
    let input_number memref =
        try  let number = Etc.read_number ()
             in (set_val memref (Number (number)))
        with End_of_file ->
             (set_val (Variable ("eof")) (Number (1.)))
    in List.iter input_number memref_list;
    interpret continuation

let interpret_program program =
    (Tables.init_label_table program; 
     if !want_dump then Tables.dump_label_table ();
     if !want_dump then Dumper.dump_program program;
     interpret program)

