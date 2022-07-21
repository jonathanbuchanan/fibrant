(*
  An implementation of a type checker for the type theory of Lean 3. This aims
  to be as passive as possible, not even automatically reducing terms. Instead,
  the type checker verifies types after being given a list of computational
  rules for types. 
*)

(* The type of universe expressions. *)
type level =
  | Var of { name: string; }
  | Zero
  | Succ of { lvl: level; }
  | Max of { lhs: level; rhs: level; }
  | IMax of { lhs: level; rhs: level; }

let rec print_level = function
  | Var x -> x.name
  | Zero -> "0"
  | Succ x -> "(S " ^ print_level x.lvl ^ ")"
  | Max x -> "Max(" ^ print_level x.lhs ^ ", " ^ print_level x.rhs ^ ")"
  | IMax x -> "IMax(" ^ print_level x.lhs ^ ", " ^ print_level x.rhs ^ ")"

(* The type of expressions. *)
type expr =
  | Var of { index: int32; }
  | Universe of { lvl: level; }
  | App of { fn: expr; arg: expr; }
  | Lambda of { binding_domain: expr; binding_value: expr; }
  | Pi of { binding_domain: expr; binding_value: expr; }
  | Let of { binding_value: expr; expr_value: expr; }
  | Const of { name: string; level_params: level list; }

type decl = {
  name: string;
  dtype: expr;
  value: expr;
  level_params: level list;
}

type env = {
  decls: decl list;
}

(*let () = print_endline "Hello, World!"*)
