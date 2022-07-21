open Fibrant.Core

let x = Zero
let y = Succ { lvl = x; }

let z = IMax { lhs = x; rhs = y; }

let () = print_endline (print_level z)
